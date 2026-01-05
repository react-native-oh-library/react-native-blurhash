import { type TurboModule } from 'react-native';
import type { Double } from 'react-native/Libraries/Types/CodegenTypes';
export interface Spec extends TurboModule {
    createBlurhashFromImage: (imageUri: string, componentsX: Double, componentsY: Double) => Promise<string>;
    clearCosineCache: () => void;
}
declare const _default: Spec;
export default _default;
