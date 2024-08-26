#include "EventEmitters.h"

namespace facebook {
namespace react {

void BlurhashViewEventEmitter::onLoadError(OnLoadErrorEvent event) const {
    dispatchEvent("loadError", [event = std::move(event)](jsi::Runtime &runtime) {
        auto payload = jsi::Object(runtime);
        payload.setProperty(runtime, "message", event.message);
        return payload;
    });
}

void BlurhashViewEventEmitter::onLoadEnd() const {
    dispatchEvent("onLoadEnd", [](jsi::Runtime &runtime) {
        auto payload = jsi::Object(runtime);
        return payload;
    });
}
void BlurhashViewEventEmitter::onLoadStart(OnLoadStartEvent event) const {
    dispatchEvent("onLoadStart", [event = std::move(event)](jsi::Runtime &runtime) {
        auto payload = jsi::Object(runtime);
        if (event.blurhash == "") {
            payload.setProperty(runtime, "message", "The provided Blurhash string must not be null!");
        }
        return payload;
    });
}


} // namespace react
} // namespace facebook