/**
 * MIT License
 *
 * Copyright (C) 2024 Huawei Device Co., Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

import {
  Descriptor as ComponentDescriptor,
  ViewBaseProps,
  ViewRawProps,
  ViewDescriptorWrapperBase,
  ColorValue,
  Color,
  RNInstance,
  Tag,
  RNComponentCommandReceiver,
  ViewPropsSelector,
} from '@rnoh/react-native-openharmony/ts';


export namespace RNCBlurhashView {
  export const NAME = "RNCBlurhashView" as const

  export interface DirectRawProps {
    blurhash: string;
    decodeWidth?: number;
    decodeHeight?: number;
    decodePunch?: number;
    decodeAsync?: boolean;
    resizeMode?: 'cover' | 'contain' | 'stretch' | 'center';
  }
  
  export interface Props extends ViewBaseProps {}
  
  export interface State {}
  
  export interface RawProps extends ViewRawProps, DirectRawProps {}
  
  export class PropsSelector extends ViewPropsSelector<Props, RawProps> {
    get blurhash() {
      return this.rawProps.blurhash;
    }
    
    get decodeWidth() {
      return this.rawProps.decodeWidth ?? 32;
    }
    
    get decodeHeight() {
      return this.rawProps.decodeHeight ?? 32;
    }
    
    get decodePunch() {
      return this.rawProps.decodePunch ?? 1;
    }
    
    get decodeAsync() {
      return this.rawProps.decodeAsync ?? false;
    }
    
    get resizeMode() {
      return this.rawProps.resizeMode ?? 'cover';
    }
    
  
  }

  export type Descriptor = ComponentDescriptor<
    typeof NAME,
    Props,
    State,
    RawProps
  >;
  
  export class DescriptorWrapper extends ViewDescriptorWrapperBase<
    typeof NAME,
    Props,
    State,
    RawProps,
    PropsSelector
  > {
    protected createPropsSelector() {
      return new PropsSelector(this.descriptor.props, this.descriptor.rawProps)
    }
  }
  
  export interface EventPayloadByName {
    "loadStart": {}
    "loadEnd": {}
    "loadError": {message?: string}
  }
  
  export class EventEmitter {
    constructor(private rnInstance: RNInstance, private tag: Tag) {}
    
    emit<TEventName extends keyof EventPayloadByName>(eventName: TEventName, payload: EventPayloadByName[TEventName]) {
      this.rnInstance.emitComponentEvent(this.tag, eventName, payload)
    }
  }
  
  export interface CommandArgvByName {
  }
  
  export class CommandReceiver {
    private listenersByCommandName = new Map<string, Set<(...args: any[]) => void>>()
    private cleanUp: (() => void) | undefined = undefined
  
    constructor(private componentCommandReceiver: RNComponentCommandReceiver, private tag: Tag) {
    }
  
    subscribe<TCommandName extends keyof CommandArgvByName>(commandName: TCommandName, listener: (argv: CommandArgvByName[TCommandName]) => void) {
      if (!this.listenersByCommandName.has(commandName)) {
        this.listenersByCommandName.set(commandName, new Set())
      }
      this.listenersByCommandName.get(commandName)!.add(listener)
      const hasRegisteredCommandReceiver = !!this.cleanUp
      if (!hasRegisteredCommandReceiver) {
        this.cleanUp = this.componentCommandReceiver.registerCommandCallback(this.tag, (commandName: string, argv: any[]) => {
          if (this.listenersByCommandName.has(commandName)) {
            const listeners = this.listenersByCommandName.get(commandName)!
            listeners.forEach(listener => {
              listener(argv)
            })
          }
        })
      }
  
      return () => {
        this.listenersByCommandName.get(commandName)?.delete(listener)
        if (this.listenersByCommandName.get(commandName)?.size ?? 0 === 0) {
          this.listenersByCommandName.delete(commandName)
        }
        if (this.listenersByCommandName.size === 0) {
          this.cleanUp?.()
        }
      }
    }
  }

}
