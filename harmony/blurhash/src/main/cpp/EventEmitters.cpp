#include "EventEmitters.h"

namespace facebook {
namespace react {

void BlurhashViewEventEmitter::onLoadError(OnLoadError event) const {
    dispatchEvent("loadError", [event = std::move(event)](jsi::Runtime &runtime) {
        auto payload = jsi::Object(runtime);
        payload.setProperty(runtime, "message", event.message);
        return payload;
    });
}

void BlurhashViewEventEmitter::onLoadEnd(OnLoadEnd event) const {
    dispatchEvent("onLoadEnd", [](jsi::Runtime &runtime) {
        auto payload = jsi::Object(runtime);
        return payload;
    });
}
void BlurhashViewEventEmitter::onLoadStart(OnLoadStart event) const {
    dispatchEvent("onLoadStart", [event = std::move(event)](jsi::Runtime &runtime) {
        auto payload = jsi::Object(runtime);
        if (event.blurhash == "") {
            payload.setProperty(runtime, "message", "The provided Blurhash string must not be null!");
        }
        if (event.decodeWidth <= 0) {
            payload.setProperty(runtime, "message", "decodeWidth must be greater than 0! Actual: $decodeWidth");
        }
        if (event.decodeHeight <= 0) {
            payload.setProperty(runtime, "message", "decodeHeight must be greater than 0! Actual: $decodeWidth");
        }
        if (event.decodePunch <= 0) {
            payload.setProperty(runtime, "message", "decodePunch must be greater than 0! Actual: $decodeWidth");
        }
        return payload;
    });
}


} // namespace react
} // namespace facebook