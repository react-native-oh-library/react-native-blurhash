#pragma once

#include "RNOHCorePackage/ComponentBinders/ViewComponentJSIBinder.h"

namespace rnoh {
class BlurhashViewJSIBinder : public ViewComponentJSIBinder {
protected:
    facebook::jsi::Object createNativeProps(facebook::jsi::Runtime &rt) override {
        auto object = ViewComponentJSIBinder::createNativeProps(rt);
        object.setProperty(rt, "imgUri", true);
        object.setProperty(rt, "blurhash", true);
        object.setProperty(rt, "decodeWidth", true);
        object.setProperty(rt, "decodeHeight", true);
        object.setProperty(rt, "decodePunch", true);
        object.setProperty(rt, "decodeAsync", true);
        object.setProperty(rt, "resizeMode", true);
        return object;
    }

    facebook::jsi::Object createBubblingEventTypes(facebook::jsi::Runtime &rt) override {
        facebook::jsi::Object events(rt);
        events.setProperty(rt, "topOnLoadStart", createDirectEvent(rt, "onLoadStart"));
        events.setProperty(rt, "topOnLoadEnd", createDirectEvent(rt, "onLoadEnd"));
        events.setProperty(rt, "topOnLoadError", createDirectEvent(rt, "onLoadError"));
        return events;
    }

    facebook::jsi::Object createDirectEventTypes(facebook::jsi::Runtime &rt) override {
        facebook::jsi::Object events(rt);
        return events;
    }
};
} // namespace rnoh