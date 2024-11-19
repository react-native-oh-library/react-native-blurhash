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

