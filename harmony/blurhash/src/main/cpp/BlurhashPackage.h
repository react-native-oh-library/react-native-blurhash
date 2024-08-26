#include "RNOH/Package.h"
#include "ComponentDescriptors.h"
#include "BlurhashViewJSIBinder.h"
#include "RNBlurhashTurboModule.h"
#include "BlurhashViewComponentInstance.h"

using namespace rnoh;

class BlurhashViewComponentInstanceFactoryDelegate : public ComponentInstanceFactoryDelegate {
public:
    using ComponentInstanceFactoryDelegate::ComponentInstanceFactoryDelegate;

    ComponentInstance::Shared create(ComponentInstance::Context ctx) override {
        if (ctx.componentName == "BlurhashView") {
            return std::make_shared<BlurhashViewComponentInstance>(std::move(ctx));
        }
        return nullptr;
    }
};

class BlurhashTurboModuleFactoryDelegate : public TurboModuleFactoryDelegate {
public:
    SharedTurboModule createTurboModule(Context ctx, const std::string &name) const override {
        if (name == "BlurhashModule") {
            return std::make_shared<RNBlurhashTurboModule>(ctx, name);
        }
        return nullptr;
    }
};

class BlurhashPackage : public Package {
public:
    BlurhashPackage(Package::Context ctx) : Package(ctx) {}

    std::unique_ptr<TurboModuleFactoryDelegate> createTurboModuleFactoryDelegate() override { return std::make_unique<BlurhashTurboModuleFactoryDelegate>(); }

    ComponentInstanceFactoryDelegate::Shared createComponentInstanceFactoryDelegate() override {
        return std::make_shared<BlurhashViewComponentInstanceFactoryDelegate>();
    }

    std::vector<facebook::react::ComponentDescriptorProvider> createComponentDescriptorProviders() override {
        return {facebook::react::concreteComponentDescriptorProvider<facebook::react::BlurhashViewComponentDescriptor>()};
    }

    ComponentJSIBinderByString createComponentJSIBinderByName() override { return {{"BlurhashView", std::make_shared<BlurhashViewJSIBinder>()}}; }
};
// namespace rnoh