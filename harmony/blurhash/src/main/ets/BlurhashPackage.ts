import { RNPackage, TurboModulesFactory } from '@rnoh/react-native-openharmony/ts';
import type {
  TurboModule,
  TurboModuleContext,
  DescriptorWrapperFactoryByDescriptorTypeCtx,
  DescriptorWrapperFactoryByDescriptorType,
} from '@rnoh/react-native-openharmony/ts';
import { RNBlurhashModule } from './BlurhashTurboModule';
import { BlurhashModule } from './TMSpecs'
import { BlurhashView} from './RNCSpecs'

class BlurhashTurboModulesFactory extends TurboModulesFactory {
  createTurboModule(name: string): TurboModule | null {
    if (name === BlurhashModule.NAME) {
      return new RNBlurhashModule(this.ctx);
    }
    return null;
  }

  hasTurboModule(name: string): boolean {
    return name === BlurhashModule.NAME;
  }
}

export class BlurhashPackage extends RNPackage {
  createTurboModulesFactory(ctx: TurboModuleContext): TurboModulesFactory {
    return new BlurhashTurboModulesFactory(ctx);
  }
  createDescriptorWrapperFactoryByDescriptorType(ctx: DescriptorWrapperFactoryByDescriptorTypeCtx): DescriptorWrapperFactoryByDescriptorType {
    return {
      [BlurhashView.NAME]: (ctx) => new BlurhashView.DescriptorWrapper(ctx.descriptor)
    }
  }
}
