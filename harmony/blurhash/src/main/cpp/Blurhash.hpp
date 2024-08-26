#pragma once

#include <__functional/function.h>
#include <string>
#include <string_view>
#include <vector>
#include "SparseArray.h"

namespace blurhash {
struct Image {
    size_t width, height;
    std::vector<unsigned char> image; // pixels rgb
};

std::string decode(std::string_view blurhash, size_t width = 32, size_t height = 32, float punch = 1.0, bool useCache = true) noexcept;

std::string encode(char const *filename, int components_x, int components_y);

void clearCache();

} // namespace blurhash
