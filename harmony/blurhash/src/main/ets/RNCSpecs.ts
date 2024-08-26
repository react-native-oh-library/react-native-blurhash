// This file was generated.
import {
  Descriptor as ComponentDescriptor,
  ViewBaseProps,
  ViewRawProps,
  ViewDescriptorWrapperBase,
  RNInstance,
  Tag,
  RNComponentCommandReceiver,
  ViewPropsSelector,
} from '@rnoh/react-native-openharmony/ts';


export namespace BlurhashView {
  export const NAME = "BlurhashView" as const

  export interface DirectRawProps {
    blurhash:string;
    decodeWidth?:number;
    decodeHeight?:number;
    decodePunch?:number;
    decodeAsync?:boolean;
    resizeMode?: 'contain' | 'cover' | 'stretch' | 'center';
  }

  export interface Props extends ViewBaseProps {}

  export interface State {}

  export interface RawProps extends ViewRawProps, DirectRawProps {}

  export class PropsSelector extends ViewPropsSelector<Props, RawProps> {

    get blurhash() {
      console.log(this.blurhash)
      return this.blurhash;
    }

    get decodeWidth() {
      console.log(this.decodeWidth)
      return this.decodeWidth;
    }

    get decodeHeight() {
      console.log(this.decodeHeight)
      return this.decodeHeight;
    }

    get decodePunch() {
      console.log(this.decodePunch)
      return this.decodePunch;
    }

    get decodeAsync() {
      console.log(this.decodeAsync)
      return this.decodeAsync;
    }

    get resizeMode() {
      console.log(this.resizeMode)
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
    "Error": {}
    "Load": {width: number, height: number}
    "LoadEnd": {}
    "LoadStart": {}
    "Progress": {loaded: number, total: number}
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
