export namespace BlurhashModule {
  export const NAME = 'BlurhashModule' as const

  export interface Spec {
    createBlurhashFromImage(imageUri: string, componentsX: number, componentsY: number): Promise<string>;

    clearCosineCache(): void;
  }
}
