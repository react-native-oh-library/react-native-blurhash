/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "Props.h"
#include <react/renderer/core/PropsParserContext.h>
#include <react/renderer/core/propsConversions.h>

namespace facebook {
namespace react {

BlurhashViewProps::BlurhashViewProps(const PropsParserContext &context, const BlurhashViewProps &sourceProps, const RawProps &rawProps)
    : ViewProps(context, sourceProps, rawProps), 
      imgUri(convertRawProp(context, rawProps, "imgUri", sourceProps.imgUri, {})),
      blurhash(convertRawProp(context, rawProps, "blurhash", sourceProps.blurhash, {})),
      decodeWidth(convertRawProp(context, rawProps, "decodeWidth", sourceProps.decodeWidth, {})),
      decodeHeight(convertRawProp(context, rawProps, "decodeHeight", sourceProps.decodeHeight, {})),
      decodePunch(convertRawProp(context, rawProps, "decodePunch", sourceProps.decodePunch, {})),
      decodeAsync(convertRawProp(context, rawProps, "decodeAsync", sourceProps.decodeAsync, {})),
      resizeMode(convertRawProp(context, rawProps, "resizeMode", sourceProps.resizeMode, {facebook::react::BlurhashViewResizeMode::Cover})) {}

} // namespace react
} // namespace facebook