#pragma once

#include <ReactCommon/TurboModule.h>
#include "RNOH/ArkTSTurboModule.h"
namespace rnoh {

class JSI_EXPORT RNBlurhashTurboModule : public ArkTSTurboModule {
public:
    RNBlurhashTurboModule(const ArkTSTurboModule::Context ctx, const std::string name);

    void clearCosineCache();

};
} // namespace rnoh
