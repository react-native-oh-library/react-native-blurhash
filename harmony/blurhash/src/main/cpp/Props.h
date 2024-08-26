#pragma once

#include <jsi/jsi.h>
#include <react/renderer/components/view/ViewProps.h>
#include <react/renderer/core/PropsParserContext.h>
#include <react/renderer/core/propsConversions.h>
#include <vector>
#include <react/renderer/imagemanager/primitives.h>

namespace facebook {
namespace react {

enum class BlurhashViewResizeMode { Contain, Cover, Stretch, Center };

static inline void fromRawValue(const PropsParserContext &context, const RawValue &value, BlurhashViewResizeMode &result) {
    auto string = (std::string)value;
    if (string == "contain") {
        result = BlurhashViewResizeMode::Contain;
        return;
    }
    if (string == "cover") {
        result = BlurhashViewResizeMode::Cover;
        return;
    }
    if (string == "stretch") {
        result = BlurhashViewResizeMode::Stretch;
        return;
    }
    if (string == "center") {
        result = BlurhashViewResizeMode::Center;
        return;
    }
    abort();
}

static inline std::string toString(const BlurhashViewResizeMode &value) {
    switch (value) {
    case BlurhashViewResizeMode::Contain:
        return "contain";
    case BlurhashViewResizeMode::Cover:
        return "cover";
    case BlurhashViewResizeMode::Stretch:
        return "stretch";
    case BlurhashViewResizeMode::Center:
        return "center";
    }
}

enum class decodeWeight { defaltWeight };

class JSI_EXPORT BlurhashViewProps final : public ViewProps {
public:
    BlurhashViewProps() = default;
    BlurhashViewProps(const PropsParserContext &context, const BlurhashViewProps &sourceProps, const RawProps &rawProps);

#pragma mark - Props
    std::string imgUri{};
    std::string blurhash{};
    int decodeWidth{};
    int decodeHeight{};
    double decodePunch{};
    bool decodeAsync{};
    BlurhashViewResizeMode resizeMode{BlurhashViewResizeMode::Cover};
};

} // namespace react
} // namespace facebook
