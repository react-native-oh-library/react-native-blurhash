export interface RGB {
    /**
     * The Red value component of this RGB instance. Ranges from 0 to 255.
     */
    r: number;
    /**
     * The Green value component of this RGB instance. Ranges from 0 to 255.
     */
    g: number;
    /**
     * The Blue value component of this RGB instance. Ranges from 0 to 255.
     */
    b: number;
}
export declare function decodeDC(value: number): RGB;
export declare function decode83(str: string): number;
export declare function isBlurhashValid(blurhash: string): {
    isValid: true;
} | {
    isValid: false;
    errorReason: string;
};
