#include "RNBlurhashTurboModule.h"
#include "Blurhash.hpp"
#include <sstream>
#include <jsi/jsi.h>
#include <react/renderer/components/view/ViewProps.h>
#include <react/renderer/core/propsConversions.h>
#include <react/renderer/imagemanager/primitives.h>
#include <string>

using namespace rnoh;
using namespace facebook;

using Object = std::optional<jsi::Object>;

static jsi::Value __hostFunction_RNBlurhashInstallModule_createBlurhashFromImage(jsi::Runtime &rt, react::TurboModule &turboModule, const jsi::Value *args,
                                                                                 size_t count) {
    
    return static_cast<ArkTSTurboModule &>(turboModule).callAsync(rt, "createBlurhashFromImage", args, count);
}


void RNBlurhashTurboModule::clearCosineCache() {
    ::blurhash::clearCache();
    return;
}

static jsi::Value __hostFunction_RNBlurhashInstallModule_clearCosineCache(jsi::Runtime &rt, react::TurboModule &turboModule, const jsi::Value *args, size_t count) {
    static_cast<RNBlurhashTurboModule *>(&turboModule)->clearCosineCache();
    return jsi::Value::undefined();
};


RNBlurhashTurboModule::RNBlurhashTurboModule(const ArkTSTurboModule::Context ctx, const std::string name) : ArkTSTurboModule(ctx, name) {
    methodMap_["clearCosineCache"] = MethodMetadata{0, __hostFunction_RNBlurhashInstallModule_clearCosineCache};
    methodMap_["createBlurhashFromImage"] = MethodMetadata{4, __hostFunction_RNBlurhashInstallModule_createBlurhashFromImage};
}
