#pragma once

#include <react/renderer/components/view/ViewEventEmitter.h>
#include <jsi/jsi.h>

namespace facebook {
namespace react {

class JSI_EXPORT BlurhashViewEventEmitter : public ViewEventEmitter {
public:
    using ViewEventEmitter::ViewEventEmitter;

    struct OnLoadErrorEvent {
        std::string message;
    };

    struct OnLoadStartEvent {
        std::string blurhash;
    };

    void onLoadError(OnLoadErrorEvent value) const;

    void onLoadEnd() const;

    void onLoadStart(OnLoadStartEvent value) const;
};

} // namespace react
} // namespace facebook