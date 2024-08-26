#include "BlurhashNode.h"

#include <string_view>
#include "RNOH/arkui/NativeNodeApi.h"


static constexpr ArkUI_NodeEventType IMAGE_NODE_EVENT_TYPES[] = {NODE_IMAGE_ON_COMPLETE, NODE_IMAGE_ON_ERROR, NODE_IMAGE_ON_DOWNLOAD_PROGRESS};

namespace rnoh {

using namespace std::literals;
constexpr std::string_view ASSET_PREFIX = "asset://"sv;
const std::string RAWFILE_PREFIX = "resource://RAWFILE/assets/";

BlurhashNode::BlurhashNode()
    : ArkUINode(NativeNodeApi::getInstance()->createNode(ArkUI_NodeType::ARKUI_NODE_IMAGE)), m_childArkUINodeHandle(nullptr), m_blurhashNodeDelegate(nullptr) {
    for (auto eventType : IMAGE_NODE_EVENT_TYPES) {
        maybeThrow(NativeNodeApi::getInstance()->registerNodeEvent(m_nodeHandle, eventType, eventType, this));
    }
}

BlurhashNode::~BlurhashNode() {
    for (auto eventType : IMAGE_NODE_EVENT_TYPES) {
        NativeNodeApi::getInstance()->unregisterNodeEvent(m_nodeHandle, eventType);
    }
}

BlurhashNode &BlurhashNode::setSource(std::string const &uri, std::string prefix) {
    ArkUI_AttributeItem item;
    std::string absolutePath = prefix == "" ? RAWFILE_PREFIX : prefix;
    if (uri.rfind(ASSET_PREFIX, 0) == 0) {
        absolutePath += uri.substr(ASSET_PREFIX.size());
        item = {.string = absolutePath.c_str()};
    } else {
        item = {.string = uri.c_str()};
    }
    maybeThrow(NativeNodeApi::getInstance()->setAttribute(m_nodeHandle, NODE_IMAGE_SRC, &item));
    return *this;
}

void BlurhashNode::setNodeDelegate(BlurhashNodeDelegate *blurhashNodeDelegate) { m_blurhashNodeDelegate = blurhashNodeDelegate; }

void BlurhashNode::onNodeEvent(ArkUI_NodeEventType eventType, EventArgs &eventArgs){
    if (eventType == ArkUI_NodeEventType::NODE_IMAGE_ON_COMPLETE) {
        if (m_blurhashNodeDelegate != nullptr && eventArgs[0].i32 == 1) {
            m_blurhashNodeDelegate->onComplete(eventArgs[1].f32, eventArgs[2].f32);
        }
    }

    if (eventType == ArkUI_NodeEventType::NODE_IMAGE_ON_ERROR) {
        if (m_blurhashNodeDelegate != nullptr) {
            m_blurhashNodeDelegate->onError(eventArgs[0].i32);
        }
    }

    if (eventType == ArkUI_NodeEventType::NODE_IMAGE_ON_DOWNLOAD_PROGRESS) {
        if (m_blurhashNodeDelegate != nullptr) {
            m_blurhashNodeDelegate->onProgress(eventArgs[0].u32, eventArgs[1].u32);
        }
    }
}

BlurhashNode &BlurhashNode::setResizeMode(facebook::react::ImageResizeMode const &mode) {
    int32_t val = ARKUI_OBJECT_FIT_COVER;
    if (mode == facebook::react::ImageResizeMode::Cover) {
        val = ARKUI_OBJECT_FIT_COVER;
    } else if (mode == facebook::react::ImageResizeMode::Contain) {
        val = ARKUI_OBJECT_FIT_CONTAIN;
    } else if (mode == facebook::react::ImageResizeMode::Stretch) {
        val = ARKUI_OBJECT_FIT_FILL;
    } else if (mode == facebook::react::ImageResizeMode::Center || mode == facebook::react::ImageResizeMode::Repeat) {
        val = ARKUI_OBJECT_FIT_NONE;
    }

    ArkUI_NumberValue value[] = {{.i32 = val}};
    ArkUI_AttributeItem item = {value, sizeof(value) / sizeof(ArkUI_NumberValue)};
    maybeThrow(NativeNodeApi::getInstance()->setAttribute(m_nodeHandle, NODE_IMAGE_OBJECT_FIT, &item));
    return *this;
}

} // namespace rnoh
