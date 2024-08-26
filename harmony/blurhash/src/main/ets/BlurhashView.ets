import {
  Descriptor,
  ViewBaseProps,
  RNViewBase,
  RNComponentContext
} from '@rnoh/react-native-openharmony';


interface BlurhashViewProps extends ViewBaseProps {
  size: number
}

export type BlurhashViewDescriptor = Descriptor<"BlurhashView", BlurhashViewProps>

@Component
export struct BlurhashView {
  public static readonly NAME = "BlurhashView"
  public ctx!: RNComponentContext
  public tag: number = 0
  @State descriptor: BlurhashViewDescriptor = {} as BlurhashViewDescriptor
  @State fontSize: number | undefined = undefined
  private cleanUpCallbacks: (() => void)[] = []

  aboutToAppear() {
    this.descriptor = this.ctx.descriptorRegistry.getDescriptor<BlurhashViewDescriptor>(this.tag)
    this.cleanUpCallbacks.push(this.ctx.descriptorRegistry.subscribeToDescriptorChanges(this.tag,
      (newDescriptor) => {
        this.descriptor = (newDescriptor as BlurhashViewDescriptor)
      }
    ))
    this.cleanUpCallbacks.push(this.ctx.componentCommandReceiver.registerCommandCallback(this.tag, (commandName) => {
      if (commandName === "toggleFontSize") {
        this.fontSize = this.fontSize ? undefined : 20
      }
    }))
  }

  aboutToDisappear() {
    this.cleanUpCallbacks.forEach(cb => cb())
  }

  build() {
    RNViewBase({ ctx: this.ctx, tag: this.tag }) {
      Text(this.descriptor.tag.toString()).fontColor("white").fontSize(this.fontSize ?? 12)
      this.ctx.wrappedRNChildrenBuilder.builder(this.ctx, this.tag)
    }
  }
}
