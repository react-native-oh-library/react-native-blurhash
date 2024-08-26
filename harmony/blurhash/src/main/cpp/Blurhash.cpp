#include "Blurhash.hpp"

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <numbers>
#include <stdexcept>
#include <string>
#ifdef __clang__
#define STBIWDEF static inline
#endif
#define STB_IMAGE_WRITE_STATIC
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image_write.h"
#include "stb_image.h"

using namespace std::literals;

namespace {
// 稀疏数组，用于存储cosines值
SparseArray<std::vector<double>> cacheCosinesX;
SparseArray<std::vector<double>> cacheCosinesY;
// 84个字符的数组，用于83进制编码
constexpr std::array<char, 84> int_to_b83{"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz#$%*+,-.:;=?@[]^_{|}~"};
// 将字符串左侧补零，直到字符串长度达到指定长度
std::string leftPad(std::string str, size_t len) {
    if (str.size() >= len)
        return str;
    return str.insert(0, len - str.size(), '0');
}
// 83进制解码表
constexpr std::array<int, 255> b83_to_int = []() constexpr {
    std::array<int, 255> a{};
    for (auto &e : a)
        e = -1;
    for (int i = 0; i < 83; i++) {
        a[static_cast<unsigned char>(int_to_b83[i])] = i;
    }
    return a;
}();
// 83进制编码函数
std::string encode83(int value) {
    std::string buffer;
    do {
        buffer += int_to_b83[value % 83];
    } while ((value = value / 83));
    std::reverse(buffer.begin(), buffer.end());
    return buffer;
}
// 组件结构体
struct Components {
    int x, y;
};
// 打包组件函数
int packComponents(const Components &c) noexcept { return (c.x - 1) + (c.y - 1) * 9; }
// 解包组件函数
Components unpackComponents(int c) noexcept { return {c % 9 + 1, c / 9 + 1}; }
// 83进制解码函数
int decode83(std::string_view value) {
    int temp = 0;
    for (char c : value)
        if (b83_to_int[static_cast<unsigned char>(c)] < 0)
            throw std::invalid_argument("invalid character in blurhash");
    for (char c : value)
        temp = temp * 83 + b83_to_int[static_cast<unsigned char>(c)];
    return temp;
}
// 解码最大AC值
float decodeMaxAC(int quantizedMaxAC) noexcept { return static_cast<float>(quantizedMaxAC + 1) / 166.f; }
// 解码最大AC值
float decodeMaxAC(std::string_view maxAC) {
    assert(maxAC.size() == 1);
    return decodeMaxAC(decode83(maxAC));
}
// 编码最大AC值
int encodeMaxAC(float maxAC) noexcept { return std::max(0, std::min(82, int(maxAC * 166 - 0.5f))); }
// sRGB到线性RGB的转换
float srgbToLinear(int value) noexcept {
    auto srgbToLinearF = [](float x) {
        if (x <= 0.0f)
            return 0.0f;
        else if (x >= 1.0f)
            return 1.0f;
        else if (x < 0.04045f)
            return x / 12.92f;
        else
            return std::pow((x + 0.055f) / 1.055f, 2.4f);
    };
    return srgbToLinearF(static_cast<float>(value) / 255.f);
}
// 线性到sRGB的转换
int linearToSrgb(float value) noexcept {
    auto linearToSrgbF = [](float x) -> float {
        if (x <= 0.0f)
            return 0.0f;
        else if (x >= 1.0f)
            return 1.0f;
        else if (x < 0.0031308f)
            return x * 12.92f;
        else
            return std::pow(x, 1.0f / 2.4f) * 1.055f - 0.055f;
    };
    return int(linearToSrgbF(value) * 255.f + 0.5f);
}
// 颜色结构体
struct Color {
    float r, g, b;
    // 颜色乘法
    Color &operator*=(float scale) {
        r *= scale;
        g *= scale;
        b *= scale;
        return *this;
    }
    // 颜色乘法
    friend Color operator*(Color lhs, float rhs) { return (lhs *= rhs); }
    // 颜色除法
    Color &operator/=(float scale) {
        r /= scale;
        g /= scale;
        b /= scale;
        return *this;
    }
    // 颜色加法
    Color &operator+=(const Color &rhs) {
        r += rhs.r;
        g += rhs.g;
        b += rhs.b;
        return *this;
    }
};
// 解码DC颜色
Color decodeDC(int value) {
    const int intR = value >> 16;
    const int intG = (value >> 8) & 255;
    const int intB = value & 255;
    return {srgbToLinear(intR), srgbToLinear(intG), srgbToLinear(intB)};
}
// 解码DC颜色
Color decodeDC(std::string_view value) {
    assert(value.size() == 4);
    return decodeDC(decode83(value));
}
// 编码DC颜色
int encodeDC(const Color &c) { return (linearToSrgb(c.r) << 16) + (linearToSrgb(c.g) << 8) + linearToSrgb(c.b); }
// 符号幂运算
float signPow(float value, float exp) { return std::copysign(std::pow(std::abs(value), exp), value); }
// 编码AC颜色
int encodeAC(const Color &c, float maximumValue) {
    auto quantR = int(std::max(0., std::min(18., std::floor(signPow(c.r / maximumValue, 0.5) * 9 + 9.5))));
    auto quantG = int(std::max(0., std::min(18., std::floor(signPow(c.g / maximumValue, 0.5) * 9 + 9.5))));
    auto quantB = int(std::max(0., std::min(18., std::floor(signPow(c.b / maximumValue, 0.5) * 9 + 9.5))));
    return quantR * 19 * 19 + quantG * 19 + quantB;
}
// 解码AC颜色
// 参数：value表示颜色的编码值，maximumValue表示颜色的最大值
// 返回值：返回一个Color对象，表示解码后的颜色
Color decodeAC(int value, float maximumValue) {
    // 计算RGB每个分量的量化值
    auto quantR = value / (19 * 19);
    auto quantG = (value / 19) % 19;
    auto quantB = value % 19;

    // 使用量化值计算解码后的颜色值
    return {signPow((float(quantR) - 9) / 9, 2) * maximumValue, signPow((float(quantG) - 9) / 9, 2) * maximumValue, signPow((float(quantB) - 9) / 9, 2) * maximumValue};
}
// 解码AC颜色，输入参数为字符串
// 参数：value表示颜色的编码字符串，maximumValue表示颜色的最大值
// 返回值：返回一个Color对象，表示解码后的颜色
Color decodeAC(std::string_view value, float maximumValue) { return decodeAC(decode83(value), maximumValue); }
// 圆周率的定义
const float pi = std::acos(-1.0f);
// 生成基函数
// 参数：dimension表示维度，components表示基函数的数量
// 返回值：返回一个float类型的向量，表示生成的基函数
std::vector<float> bases_for(size_t dimension, size_t components) {
    // 初始化一个大小为dimension*components的向量
    std::vector<float> bases(dimension * components);

    // 计算缩放因子
    float scale = pi / float(dimension);

    // 使用std::generate生成基函数
    size_t index = 0;
    std::generate(bases.begin(), bases.end(), [&]() {
        // 计算x和nx的值
        size_t x = index / components;
        size_t nx = index % components;
        index++;
        // 计算并返回基函数的值
        return std::cos(scale * float(nx * x));
    });

    return bases;
}


} // namespace
namespace blurhash {
std::string path = "/data/storage/el2/base/haps/entry/cache/";
/**
 * @brief 解码Blurhash为图像
 * @param blurhash 待解码的Blurhash字符串
 * @param width 图像宽度
 * @param height 图像高度
 * @param bytesPerPixel 每个像素的字节数
 * @param useCache 是否使用缓存
 * @return 解码后的图像
 * @note
 * 此函数首先检查Blurhash的长度，如果长度小于6，则返回空图像。然后，它尝试解码Blurhash的组件，
 * 如果解码失败，则返回空图像。接着，它解码最大AC值和平均颜色值。然后，它解码AC值并将其添加到值向量中。
 * 最后，它使用解码的值和基础函数计算图像的每个像素的颜色，并将其存储在图像的image数组中。
 */
std::string decode(std::string_view blurhash, size_t width, size_t height, float punch, bool useCache) noexcept {
    size_t bytesPerPixel = 3;
    Image i{};
    // 检查Blurhash的长度
    if (blurhash.size() < 6)
        return "";
    Components components{};
    std::vector<Color> values;
    values.reserve(blurhash.size() / 2);
    try {
        // 解码Blurhash的组件
        components = unpackComponents(decode83(blurhash.substr(0, 1)));
        // 检查解码的有效性
        if (components.x < 1 || components.y < 1 || blurhash.size() != size_t(1 + 1 + 4 + (components.x * components.y - 1) * 2))
            return {};
        // 解码最大AC值和平均颜色值
        auto maxAC = decodeMaxAC(blurhash.substr(1, 1));
        // 对比度调整
        maxAC *= punch;
        Color average = decodeDC(blurhash.substr(2, 4));
        values.push_back(average);
        for (size_t c = 6; c < blurhash.size(); c += 2)
            values.push_back(decodeAC(blurhash.substr(c, 2), maxAC));
    } catch (std::invalid_argument &) {
        return {};
    }
    // 初始化图像数组
    i.image = decltype(i.image)(height * width * bytesPerPixel, 255);
    // 计算基础函数
    std::vector<float> basis_x = bases_for(width, components.x);
    std::vector<float> basis_y = bases_for(height, components.y);
    // 计算图像的每个像素的颜色
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            Color c{};
            for (size_t nx = 0; nx < size_t(components.x); nx++) {
                for (size_t ny = 0; ny < size_t(components.y); ny++) {
                    float basis = basis_x[x * components.x + nx] * basis_y[y * components.y + ny];
                    c += values[nx + ny * components.x] * basis;
                }
            }
            // 将颜色值存储在图像数组中
            i.image[(y * width + x) * bytesPerPixel + 0] = static_cast<unsigned char>(linearToSrgb(c.r));
            i.image[(y * width + x) * bytesPerPixel + 1] = static_cast<unsigned char>(linearToSrgb(c.g));
            i.image[(y * width + x) * bytesPerPixel + 2] = static_cast<unsigned char>(linearToSrgb(c.b));
        }
    }
    // 设置图像的宽度和高度
    i.height = height;
    i.width = width;

    std::string filename = path + std::string(blurhash) + ".bmp";
    stbi_write_bmp(filename.c_str(), i.width, i.height, 3, (void *)i.image.data());
    return filename;
}


/**
 * 对图像进行编码的函数
 * @param image 待编码的图像数据
 * @param width 图像的宽度
 * @param height 图像的高度
 * @param components_x 在x方向上的分量数
 * @param components_y 在y方向上的分量数
 * @return 编码后的字符串
 */
std::string encode(char const *filename, int components_x, int components_y) {
    auto start = std::chrono::steady_clock::now();
    auto duration = std::chrono::seconds(5);
    int width, height, n;
    unsigned char *data = stbi_load((path + filename).c_str(), &width, &height, &n, 3);
    if (width < 1 || height < 1 || components_x < 1 || components_x > 9 || components_y < 1 || components_y > 9)
        return "";
    while (!data) {
        data = stbi_load((path + filename).c_str(), &width, &height, &n, 3);
        auto now = std::chrono::steady_clock::now();
        if (now - start >= duration) {
            return "";
        }
    }
    // 计算基准值
    std::vector<float> basis_x = bases_for(width, components_x);
    std::vector<float> basis_y = bases_for(height, components_y);
    // 初始化颜色因子
    std::vector<Color> factors(components_x * components_y, Color{});
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            // 将RGB值从sRGB转换为线性RGB
            Color linear{srgbToLinear(data[3 * x + 0 + y * width * 3]), srgbToLinear(data[3 * x + 1 + y * width * 3]), srgbToLinear(data[3 * x + 2 + y * width * 3])};
            // 进行归一化处理
            linear *= 1.f / static_cast<float>(width);
            // 计算颜色因子
            for (size_t ny = 0; ny < size_t(components_y); ny++) {
                for (size_t nx = 0; nx < size_t(components_x); nx++) {
                    float basis = basis_x[x * size_t(components_x) + nx] * basis_y[y * size_t(components_y) + ny];
                    factors[ny * components_x + nx] += linear * basis;
                }
            }
        }
    }
    // 进行归一化处理
    for (size_t i = 0; i < factors.size(); i++) {
        float normalisation = (i == 0) ? 1 : 2;
        float scale = normalisation / static_cast<float>(height);
        factors[i] *= scale;
    }
    // 断言颜色因子数量大于0
    assert(factors.size() > 0);
    // 获取直流分量并从颜色因子中移除
    auto dc = factors.front();
    factors.erase(factors.begin());
    // 初始化编码字符串
    std::string h;
    // 编码分量
    h += leftPad(encode83(packComponents({components_x, components_y})), 1);
    // 编码最大值
    float maximumValue;
    if (!factors.empty()) {
        float actualMaximumValue = 0;
        for (auto ac : factors) {
            actualMaximumValue = std::max({
                std::abs(ac.r),
                std::abs(ac.g),
                std::abs(ac.b),
                actualMaximumValue,
            });
        }
        int quantisedMaximumValue = encodeMaxAC(actualMaximumValue);
        maximumValue = ((float)quantisedMaximumValue + 1) / 166;
        h += leftPad(encode83(quantisedMaximumValue), 1);
    } else {
        maximumValue = 1;
        h += leftPad(encode83(0), 1);
    }
    // 编码直流分量
    h += leftPad(encode83(encodeDC(dc)), 4);
    // 编码余下的颜色因子
    for (auto ac : factors)
        h += leftPad(encode83(encodeAC(ac, maximumValue)), 2);
    return h;
}


void clearCache() {
    cacheCosinesX.clear();
    cacheCosinesY.clear();
}
} // namespace blurhash

#ifdef DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#endif