/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "BlurhashViewComponentInstance.h"
#include "Blurhash.hpp"
#include "Props.h"
#include <filemanagement/file_uri/oh_file_uri.h>
#include "RNBlurhashTurboModule.h"
#include <filemanagement/environment/error_code.h>
#include <iomanip>
#include <react/renderer/core/ConcreteState.h>
#include <sstream>
#include <cstdio>

namespace rnoh {

BlurhashViewComponentInstance::BlurhashViewComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    this->getLocalRootArkUINode().setNodeDelegate(this);
}

void BlurhashViewComponentInstance::onPropsChanged(SharedConcreteProps const &props) {

    CppComponentInstance::onPropsChanged(props);

    if (!m_props || m_props->resizeMode != props->resizeMode) {
        this->getLocalRootArkUINode().setResizeMode(convertToImageResizeMode(props->resizeMode));
    }
    // Validate inputs and early-return to avoid passing null/invalid data into ArkUI
    if (props->blurhash == "") {
        if (m_eventEmitter) m_eventEmitter->onLoadError({.message = "The provided Blurhash string must not be empty!"});
        return;
    }
    if (props->decodeWidth <= 0) {
        if (m_eventEmitter) m_eventEmitter->onLoadError({.message = "decodeWidth must be greater than 0!"});
        return;
    }
    if (props->decodeHeight <= 0) {
        if (m_eventEmitter) m_eventEmitter->onLoadError({.message = "decodeHeight must be greater than 0!"});
        return;
    }
    if (props->decodePunch <= 0) {
        if (m_eventEmitter) m_eventEmitter->onLoadError({.message = "decodePunch must be greater than 0!"});
        return;
    }

    std::string filePath = decodeImageByBlurhash(props->blurhash, props->decodeWidth, props->decodeHeight, props->decodePunch);
    if (filePath.empty()) {
        if (m_eventEmitter) m_eventEmitter->onLoadError({.message = "Failed to decode blurhash to image."});
        return;
    }
    

    // If filePath is already a URI, use it directly
    if (filePath.find("://") != std::string::npos) {
    this->getLocalRootArkUINode().setSource(filePath);
        return;
    }
    // If filePath is an absolute path, use it as-is; otherwise prefix cache dir
    std::string absPath = filePath;
    if (!(absPath.rfind("/", 0) == 0)) {
        absPath = "/data/storage/el2/base/haps/entry/cache/rn_image_cache/" + absPath;
    }

    const char *path = absPath.c_str();
    unsigned int length = static_cast<unsigned int>(absPath.size());
    char *result = nullptr;
    FileManagement_ErrCode ret = OH_FileUri_GetUriFromPath(path, length, &result);
    if (ret != FileManagement_ErrCode::ERR_OK || result == nullptr) {
        if (m_eventEmitter) m_eventEmitter->onLoadError({.message = "Failed to convert path to file URI."});
        return;
    }
    std::string uriStr(result);
    this->getLocalRootArkUINode().setSource(uriStr);
    free(result);
}

std::string BlurhashViewComponentInstance::decodeImageByBlurhash(const std::string &blurhash, const int &width, const int &height, const float &punch) {
    std::string expectedName =
        blurhash + "_" + std::to_string(width) + "x" + std::to_string(height) +
        "_p" + std::to_string(static_cast<int>(punch * 100)) + ".bmp";
    blurhash::decode(blurhash, width, height, punch);
    auto rnInstance = m_deps->rnInstance.lock();
    auto turboModule = rnInstance->getTurboModule("ImageLoader");
    auto arkTsTurboModule = std::dynamic_pointer_cast<rnoh::ArkTSTurboModule>(turboModule);
    if (!arkTsTurboModule) {
        return expectedName; // fallback filename
    }
    auto cache = arkTsTurboModule->callSync("getPrefetchResult", {expectedName});
    std::string result;
    if (cache.isString()) {
        result = cache.asString();
    }
    if (result.empty()) {
        // in case non-string/unsupported shape returned, fallback
        result = expectedName;
    }
    return result;
}

BlurhashNode &BlurhashViewComponentInstance::getLocalRootArkUINode() { return m_imageNode; }

void BlurhashViewComponentInstance::onComplete() {
    if (m_eventEmitter) {
        m_eventEmitter->onLoadStart({});
        m_eventEmitter->onLoadEnd({});
    }
}

void BlurhashViewComponentInstance::onError(int32_t errorCode) {
    if (m_eventEmitter) {
    m_eventEmitter->onLoadError({.message = ""});
    }
}

void BlurhashViewComponentInstance::onLoadStart(SharedConcreteProps const &props) {
    if (m_eventEmitter) {
    // RN 0.77: DirectEventHandler<null>
    m_eventEmitter->onLoadStart({});
    }
}

facebook::react::ImageResizeMode BlurhashViewComponentInstance::convertToImageResizeMode(facebook::react::BlurhashViewResizeMode mode) {
    switch (mode) {
    case facebook::react::BlurhashViewResizeMode::Contain:
        return facebook::react::ImageResizeMode::Contain;
    case facebook::react::BlurhashViewResizeMode::Cover:
        return facebook::react::ImageResizeMode::Cover;
    case facebook::react::BlurhashViewResizeMode::Stretch:
        return facebook::react::ImageResizeMode::Stretch;
    case facebook::react::BlurhashViewResizeMode::Center:
        return facebook::react::ImageResizeMode::Center;
    }
    // Fallback to avoid undefined behavior
    return facebook::react::ImageResizeMode::Cover;
}
} // namespace rnoh