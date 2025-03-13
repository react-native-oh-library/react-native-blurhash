/**
 * MIT License
 *
 * Copyright (C) 2024 Huawei Device Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

import { TurboModule, RNOHError, Tag } from '@rnoh/react-native-openharmony/ts';
import Logger from './Logger'
import { BlurhashModule } from "./TMSpecs"
import { ImageLoaderTurboModule } from '@rnoh/react-native-openharmony/src/main/ets/RNOHCorePackage/turboModules';
import { RemoteImageLoader } from '@rnoh/react-native-openharmony/src/main/ets/RemoteImageLoader';

import rnKeysCPPLib from 'librnoh_blurhash.so';

export class RNBlurhashModule extends TurboModule implements BlurhashModule.Spec {
  clearCosineCache(): void {
    Logger.debug('[RNOH]:BlurhashModule call clearCosineCache');
  }

  async createBlurhashFromImage(imageUri: string, componentsX: number, componentsY: number): Promise<string> {
    const imageLoader = this.ctx.rnInstance.getTurboModule<ImageLoaderTurboModule>("ImageLoader");
    const RemoteImageLoader = this.ctx.rnInstance.getTurboModule<RemoteImageLoader>("ImageLoader");
    await imageLoader.prefetchImage(imageUri)
    const filePath = RemoteImageLoader.getPrefetchResult(imageUri)
    const fileName = filePath.split('/').pop();
    const blurhashcode = rnKeysCPPLib.getEncode(fileName,componentsX,componentsY)
    return (blurhashcode);
  }

}

