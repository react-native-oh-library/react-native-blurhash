/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "EventEmitters.h"


namespace facebook {
namespace react {

void BlurhashViewEventEmitter::onLoadError(OnLoadError event) const {
    dispatchEvent("onLoadError", [event = std::move(event)](jsi::Runtime &runtime) {
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
    dispatchEvent("onLoadStart", [](jsi::Runtime &runtime) {
        auto payload = jsi::Object(runtime);
        return payload;
    });
}


} // namespace react
} // namespace facebook