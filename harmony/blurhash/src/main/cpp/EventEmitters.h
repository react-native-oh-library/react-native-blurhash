#pragma once

#include <react/renderer/components/view/ViewEventEmitter.h>
#include <jsi/jsi.h>

namespace facebook {
namespace react {

class JSI_EXPORT BlurhashViewEventEmitter : public ViewEventEmitter {
public:
    using ViewEventEmitter::ViewEventEmitter;

    struct OnLoadStart {
        std::string blurhash;
        int decodeWidth;
        int decodeHeight;
        double  decodePunch;
    };

    struct OnLoadEnd {};

    struct OnLoadError {
        std::string message;
    };

    void onLoadError(OnLoadError value) const;

    void onLoadEnd(OnLoadEnd value) const;

    void onLoadStart(OnLoadStart value) const;
};

} // namespace react
} // namespace facebook