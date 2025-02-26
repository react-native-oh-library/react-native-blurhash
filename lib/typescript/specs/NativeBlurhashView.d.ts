/// <reference types="react-native/types/modules/codegen" />
import type { DirectEventHandler, Double, Int32, WithDefault } from 'react-native/Libraries/Types/CodegenTypes';
import type { ViewProps } from 'react-native';
type OnLoadErrorEvent = {
    message?: string;
};
interface NativeProps extends ViewProps {
    blurhash: string;
    decodeWidth?: WithDefault<Int32, 32>;
    decodeHeight?: WithDefault<Int32, 32>;
    decodePunch?: WithDefault<Double, 1>;
    decodeAsync?: WithDefault<boolean, false>;
    resizeMode?: WithDefault<'cover' | 'contain' | 'stretch' | 'center', 'cover'>;
    onLoadStart?: DirectEventHandler<null>;
    onLoadEnd?: DirectEventHandler<null>;
    onLoadError?: DirectEventHandler<OnLoadErrorEvent>;
}
declare const _default: import("react-native/Libraries/Utilities/codegenNativeComponent").NativeComponentType<NativeProps>;
export default _default;
