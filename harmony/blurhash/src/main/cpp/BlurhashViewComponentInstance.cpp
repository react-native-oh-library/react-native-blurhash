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

namespace rnoh {

BlurhashViewComponentInstance::BlurhashViewComponentInstance(Context context) : CppComponentInstance(std::move(context)) {
    this->getLocalRootArkUINode().setNodeDelegate(this);
}

void BlurhashViewComponentInstance::onPropsChanged(SharedConcreteProps const &props) {

    CppComponentInstance::onPropsChanged(props);

    if (!m_props || m_props->resizeMode != props->resizeMode) {
        this->getLocalRootArkUINode().setResizeMode(convertToImageResizeMode(props->resizeMode));
    }
    if (props->blurhash == "") {
        m_eventEmitter->onLoadError({"The provided Blurhash string must not be null!"});
    };
    if (props->decodeWidth <= 0) {
        m_eventEmitter->onLoadError({"decodeWidth must be greater than 0!"});
    };
    if (props->decodeHeight <= 0) {
        m_eventEmitter->onLoadError({"decodeHeight must be greater than 0!"});
    };
    if (props->decodePunch <= 0) {
        m_eventEmitter->onLoadError({"decodePunch must be greater than 0!"});
    };
    std::string filePath = decodeImageByBlurhash(props->blurhash, props->decodeWidth, props->decodeHeight, props->decodePunch);
    std::string tempPath = "/data/storage/el2/base/haps/entry/cache/" + filePath;
    char *path = new char[tempPath.size() + 1];
    std::strcpy(path, tempPath.c_str());
    unsigned int length = strlen(path);
    char *result = NULL;
    FileManagement_ErrCode ret = OH_FileUri_GetUriFromPath(path, length, &result);
    this->getLocalRootArkUINode().setSource(std::string(result));
    if (result != NULL) {
        free(result);
    }
}

std::string BlurhashViewComponentInstance::decodeImageByBlurhash(const std::string &blurhash, const int &width, const int &height, const float &punch) {
    blurhash::decode(blurhash, width, height, punch);
    auto rnInstance = m_deps->rnInstance.lock();
    auto turboModule = rnInstance->getTurboModule("ImageLoader");
    auto arkTsTurboModule = std::dynamic_pointer_cast<rnoh::ArkTSTurboModule>(turboModule);
    auto cache = arkTsTurboModule->callSync("getPrefetchResult", {blurhash + ".bmp"});
    return cache.asString();
}

BlurhashNode &BlurhashViewComponentInstance::getLocalRootArkUINode() { return m_imageNode; }

void BlurhashViewComponentInstance::onComplete() {
    m_eventEmitter->onLoadStart({});
    if (m_eventEmitter == nullptr) {
        return;
    }
    m_eventEmitter->onLoadEnd({});
}

void BlurhashViewComponentInstance::onError(int32_t errorCode) {
    if (m_eventEmitter) {
        m_eventEmitter->onLoadError({""});
    }
}

void BlurhashViewComponentInstance::onLoadStart(SharedConcreteProps const &props) {
    if (m_eventEmitter) {
        m_eventEmitter->onLoadStart({props->blurhash, props->decodeWidth, props->decodeHeight, props->decodePunch});
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
}
} // namespace rnoh