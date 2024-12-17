/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#pragma once
#include "Props.h"
#include "EventEmitters.h"
#include <react/renderer/components/view/ConcreteViewShadowNode.h>
#include <jsi/jsi.h>

namespace facebook {
namespace react {

JSI_EXPORT extern const char BlurhashViewComponentName[];

/*
 * `ShadowNode` for <BlurhashView> component.
 */
using BlurhashViewShadowNode = ConcreteViewShadowNode<
    BlurhashViewComponentName,
    BlurhashViewProps,
    BlurhashViewEventEmitter>;

} // namespace react
} // namespace facebook