#pragma once

#include "EventEmitters.h"
#include "BlurhashNode.h"
#include "ShadowNodes.h"
#include "RNOH/CppComponentInstance.h"
#include "RNOH/arkui/ImageNode.h"
#include "Blurhash.hpp"

namespace rnoh {
class BlurhashViewComponentInstance : public CppComponentInstance<facebook::react::BlurhashViewShadowNode>, public BlurhashNodeDelegate {
private:
    BlurhashNode m_imageNode;
    std::string m_uri;

    std::string decodeImageByBlurhash(std::string const &blurhash,int const &width, int const &height, float const &punch);

public:
    BlurhashViewComponentInstance(Context context);
    void onPropsChanged(SharedConcreteProps const &props) override;
    void onComplete();
    void onError();
    void onStart();

    facebook::react::ImageResizeMode convertToImageResizeMode(facebook::react::BlurhashViewResizeMode mode);

    BlurhashNode &getLocalRootArkUINode() override;
};
} // namespace rnoh
