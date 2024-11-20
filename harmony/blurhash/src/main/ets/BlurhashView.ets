// /*
//  * MIT License
//  *
//  * Copyright (C) 2023 Huawei Device Co., Ltd.
//  *
//  * Permission is hereby granted, free of charge, to any person obtaining a copy
//  * of this software and associated documentation files (the "Software"), to deal
//  * in the Software without restriction, including without limitation the rights
//  * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  * copies of the Software, and to permit persons to whom the Software is
//  * furnished to do so, subject to the following conditions:
//  *
//  * The above copyright notice and this permission notice shall be included in all
//  * copies or substantial portions of the Software.
//  *
//  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  * SOFTWARE.
//  */
//
// import {
//   Descriptor,
//   ViewBaseProps,
//   RNViewBase,
//   RNComponentContext
// } from '@rnoh/react-native-openharmony';
// // import { RNC } from "@rnoh/react-native-openharmony/generated";
// import { RNCBlurhashView } from './RNCBlurhashView'
// import Logger from './Logger';
//
//
// interface BlurhashViewProps extends ViewBaseProps {
//   size: number
// }
//
// export type BlurhashViewDescriptor = Descriptor<"BlurhashView", BlurhashViewProps>
//
// @Component
// export struct BlurhashView {
//   public static readonly NAME = "BlurhashView"
//   public ctx!: RNComponentContext
//   public tag: number = 0
//   // @State descriptor: BlurhashViewDescriptor = {} as BlurhashViewDescriptor
//   @State private descriptorWrapper: RNCBlurhashView.DescriptorWrapper = {} as RNCBlurhashView.DescriptorWrapper;
//   @State fontSize: number | undefined = undefined
//   private cleanUpCallbacks: (() => void)[] = []
//   private eventEmitter: RNCBlurhashView.EventEmitter | undefined = undefined
//
//   aboutToAppear() {
//     // this.descriptor = this.ctx.descriptorRegistry.getDescriptor<BlurhashViewDescriptor>(this.tag)
//     // this.cleanUpCallbacks.push(this.ctx.descriptorRegistry.subscribeToDescriptorChanges(this.tag,
//     //   (newDescriptor) => {
//     //     this.descriptor = (newDescriptor as BlurhashViewDescriptor)
//     //   }
//     // ))
//     // this.cleanUpCallbacks.push(this.ctx.componentCommandReceiver.registerCommandCallback(this.tag, (commandName) => {
//     //   if (commandName === "toggleFontSize") {
//     //     this.fontSize = this.fontSize ? undefined : 20
//     //   }
//     // }))
//     Logger.info('99999999999999999999')
//     console.log('9999999999999999999911')
//     this.eventEmitter = new RNCBlurhashView.EventEmitter(this.ctx.rnInstance, this.tag)
//     this.onDescriptorWrapperChange(this.ctx.descriptorRegistry.findDescriptorWrapperByTag<RNCBlurhashView.DescriptorWrapper>(this.tag)!);
//     this.cleanUpCallbacks.push(this.ctx.descriptorRegistry.subscribeToDescriptorChanges(this.tag,
//       (_descriptor, newDescriptorWrapper) => {
//         this.onDescriptorWrapperChange(newDescriptorWrapper! as RNCBlurhashView.DescriptorWrapper)
//       }
//     ))
//     this.descriptorWrapper.props
//   }
//
//   private onDescriptorWrapperChange(descriptorWrapper: RNCBlurhashView.DescriptorWrapper) {
//     this.descriptorWrapper = descriptorWrapper;
//   }
//
//   aboutToDisappear() {
//     this.cleanUpCallbacks.forEach(cb => cb())
//   }
//
//   build() {
//     RNViewBase({ ctx: this.ctx, tag: this.tag }) {
//       Text(this.descriptorWrapper.tag.toString()).fontColor("white").fontSize(this.fontSize ?? 12)
//       this.ctx.wrappedRNChildrenBuilder.builder(this.ctx, this.tag)
//     }
//   }
//
//   onLoadStart() {
//     Logger.info('RNOH component onLoadStart 11111111')
//     this.eventEmitter!.emit("loadStart", {})
//   }
//
//   onError() {
//     Logger.error(`RNOH in RNBlurhash onError,${this.tag}`);
//     this.eventEmitter!.emit("loadError", {})
//   }
//
//   onLoadEnd() {
//     Logger.info('RNOH component onLoadEnd 22222222')
//     this.eventEmitter!.emit("loadEnd", {})
//   }
//
// }
