import * as React from 'react';
import { type NativeSyntheticEvent, type ViewProps } from 'react-native';
import { isBlurhashValid, type RGB } from './utils';
export interface BlurhashProps extends Omit<ViewProps, 'children'> {
    /**
     * The blurhash string to use. Example: `LGFFaXYk^6#M@-5c,1J5@[or[Q6`.
     */
    blurhash: string;
    /**
     * The width (resolution) to decode to. Higher values decrease performance, use `16` for large lists, otherwise you can increase it to `32`.
     * @default 32
     */
    decodeWidth?: number;
    /**
     * The height (resolution) to decode to. Higher values decrease performance, use `16` for large lists, otherwise you can increase it to `32`.
     * @default 32
     */
    decodeHeight?: number;
    /**
     * Adjusts the contrast of the output image. Tweak it if you want a different look for your placeholders.
     * @default 1.0
     */
    decodePunch?: number;
    /**
     * Asynchronously decode the Blurhash on a background Thread instead of the UI-Thread.
     * Read the [performance documentation](https://github.com/mrousavy/react-native-blurhash#performance)
     * before enabling this.
     * @default false
     */
    decodeAsync?: boolean;
    /**
     * Adjusts the resize mode of the image.
     * @default 'cover'
     */
    resizeMode?: 'cover' | 'contain' | 'stretch' | 'center';
    /**
     * Emitted when the Blurhash received new parameters and started to decode the given `blurhash` string.
     */
    onLoadStart?: () => void;
    /**
     * Emitted when the Blurhash successfully decoded the given `blurhash` string and rendered the image to the `<Blurhash>` view.
     */
    onLoadEnd?: () => void;
    /**
     * Emitted when the Blurhash failed to decode/load.
     */
    onLoadError?: (message?: string) => void;
}
export declare class Blurhash extends React.PureComponent<BlurhashProps> {
    static displayName: string;
    constructor(props: BlurhashProps);
    /**
     * Encodes the given image URI to a blurhash string
     * @param imageUri An URI to an Image parseable by the react native image loader
     * @param componentsX The number of X components
     * @param componentsY The number of Y components
     * @example
     * const blurhash = await Blurhash.encode('https://blurha.sh/assets/images/img2.jpg')
     */
    static encode(imageUri: string, componentsX: number, componentsY: number): Promise<string>;
    /**
     * Gets the average color in a given blurhash string.
     *
     * This uses the JS blurhash decoder, so it might be slow.
     * @param blurhash The blurhash string
     * @example
     * const averageColor = Blurhash.getAverageColor(`LGFFaXYk^6#M@-5c,1J5@[or[Q6.`)
     */
    static getAverageColor(blurhash: string): RGB | undefined;
    /**
     * Clears the cosine cache and frees up memory.
     *
     * @platform Android
     * @see https://github.com/mrousavy/react-native-blurhash#cosine-operations
     */
    static clearCosineCache(): void;
    /**
     * Verifies if the given blurhash is valid by checking it's type, length and size flag.
     *
     * This uses the JS blurhash decoder, so it might be slow.
     * @param blurhash The given blurhash string
     */
    static isBlurhashValid(blurhash: string): ReturnType<typeof isBlurhashValid>;
    _onLoadStart(): void;
    _onLoadEnd(): void;
    _onLoadError(event?: NativeSyntheticEvent<{
        message?: string;
    }>): void;
    render(): React.JSX.Element;
}
