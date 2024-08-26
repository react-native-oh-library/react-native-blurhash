#pragma once
#include <react/renderer/imagemanager/primitives.h>
#include "RNOH/arkui/ArkUINode.h"

namespace rnoh {

class BlurhashNodeDelegate {
public:
    virtual ~BlurhashNodeDelegate() = default;
    virtual void onComplete(float width, float height){};
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
//     BlurhashNode &setBlurhash(std::string const &blurhash);
//     BlurhashNode &setDecodeWidth(int32_t decodeWidth);
//     BlurhashNode &setDecodeHeight(int32_t);
//     BlurhashNode &setDecodePunch(double decodePunch);
//     BlurhashNode &setDecodeAsync(bool decodeAsync);
    BlurhashNode &setResizeMode(facebook::react::ImageResizeMode const &mode);
    void onNodeEvent(ArkUI_NodeEventType eventType, EventArgs &eventArgs) override;
    void setNodeDelegate(BlurhashNodeDelegate *blurhashNodeDelegate);
};
} // namespace rnoh
