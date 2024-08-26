/// <reference types="react-native/types/modules/codegen" />
import { type TurboModule } from 'react-native';
import type { Int32 } from 'react-native/Libraries/Types/CodegenTypes';
export interface Spec extends TurboModule {
    createBlurhashFromImage: (imageUri: string, componentsX: Int32, componentsY: Int32) => Promise<string>;
    clearCosineCache: () => void;
}
declare const _default: Spec;
export default _default;
