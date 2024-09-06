#pragma once
#include <cstdint>
#include <react/renderer/imagemanager/primitives.h>
#include "RNOH/arkui/ArkUINode.h"

namespace rnoh {

class BlurhashNodeDelegate {
public:
    virtual ~BlurhashNodeDelegate() = default;
    virtual void onComplete(){};
    virtual void onError(int32_t errorCode){};
    virtual void onProgress(uint32_t loaded, uint32_t total){};
};

class BlurhashNode : public ArkUINode {
protected:
    ArkUI_NodeHandle m_childArkUINodeHandle;
    BlurhashNodeDelegate *m_blurhashNodeDelegate;

public:
    BlurhashNode();
    ~BlurhashNode();
    BlurhashNode &setSource(std::string const &uri, std::string prefix = "");
    BlurhashNode &setResizeMode(facebook::react::ImageResizeMode const &mode);
    void onNodeEvent(ArkUI_NodeEventType eventType, EventArgs &eventArgs) override;
    void setNodeDelegate(BlurhashNodeDelegate *blurhashNodeDelegate);
};
} // namespace rnoh
