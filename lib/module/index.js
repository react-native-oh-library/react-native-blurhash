function _extends() { _extends = Object.assign ? Object.assign.bind() : function (target) { for (var i = 1; i < arguments.length; i++) { var source = arguments[i]; for (var key in source) { if (Object.prototype.hasOwnProperty.call(source, key)) { target[key] = source[key]; } } } return target; }; return _extends.apply(this, arguments); }
function _defineProperty(obj, key, value) { key = _toPropertyKey(key); if (key in obj) { Object.defineProperty(obj, key, { value: value, enumerable: true, configurable: true, writable: true }); } else { obj[key] = value; } return obj; }
function _toPropertyKey(t) { var i = _toPrimitive(t, "string"); return "symbol" == typeof i ? i : String(i); }
function _toPrimitive(t, r) { if ("object" != typeof t || !t) return t; var e = t[Symbol.toPrimitive]; if (void 0 !== e) { var i = e.call(t, r || "default"); if ("object" != typeof i) return i; throw new TypeError("@@toPrimitive must return a primitive value."); } return ("string" === r ? String : Number)(t); }
import * as React from 'react';
import { Platform } from 'react-native';
import NativeBlurhashModule from './specs/NativeBlurhashModule';
import NativeBlurhashView from './specs/NativeBlurhashView';
import { decode83, decodeDC, isBlurhashValid } from './utils';
export class Blurhash extends React.PureComponent {
  constructor(props) {
    super(props);
    this._onLoadStart = this._onLoadStart.bind(this);
    this._onLoadEnd = this._onLoadEnd.bind(this);
    this._onLoadError = this._onLoadError.bind(this);
  }

  /**
   * Encodes the given image URI to a blurhash string
   * @param imageUri An URI to an Image parseable by the react native image loader
   * @param componentsX The number of X components
   * @param componentsY The number of Y components
   * @example
   * const blurhash = await Blurhash.encode('https://blurha.sh/assets/images/img2.jpg')
   */
  static encode(imageUri, componentsX, componentsY) {
    if (typeof imageUri !== 'string') throw new Error('imageUri must be a non-empty string!');
    if (typeof componentsX !== 'number') throw new Error('componentsX must be a valid positive number!');
    if (typeof componentsY !== 'number') throw new Error('componentsY must be a valid positive number!');
    return NativeBlurhashModule.createBlurhashFromImage(imageUri, componentsX, componentsY);
  }

  /**
   * Gets the average color in a given blurhash string.
   *
   * This uses the JS blurhash decoder, so it might be slow.
   * @param blurhash The blurhash string
   * @example
   * const averageColor = Blurhash.getAverageColor(`LGFFaXYk^6#M@-5c,1J5@[or[Q6.`)
   */
  static getAverageColor(blurhash) {
    if (blurhash == null || blurhash.length < 7) return undefined;
    const value = decode83(blurhash.substring(2, 6));
    return decodeDC(value);
  }

  /**
   * Clears the cosine cache and frees up memory.
   *
   * @platform Android
   * @see https://github.com/mrousavy/react-native-blurhash#cosine-operations
   */
  static clearCosineCache() {
    if (Platform.OS === 'android' || _reactNative.Platform.OS === 'harmony') NativeBlurhashModule.clearCosineCache(); else console.warn('Blurhash.clearCosineCache is only available on Android.');
  }

  /**
   * Verifies if the given blurhash is valid by checking it's type, length and size flag.
   *
   * This uses the JS blurhash decoder, so it might be slow.
   * @param blurhash The given blurhash string
   */
  static isBlurhashValid(blurhash) {
    return isBlurhashValid(blurhash);
  }
  _onLoadStart() {
    if (this.props.onLoadStart != null) this.props.onLoadStart();
  }
  _onLoadEnd() {
    if (this.props.onLoadEnd != null) this.props.onLoadEnd();
  }
  _onLoadError(event) {
    var _event$nativeEvent;
    if (this.props.onLoadError != null) this.props.onLoadError(event === null || event === void 0 || (_event$nativeEvent = event.nativeEvent) === null || _event$nativeEvent === void 0 ? void 0 : _event$nativeEvent.message);
  }
  render() {
    return /*#__PURE__*/React.createElement(NativeBlurhashView, _extends({}, this.props, {
      onLoadStart: this._onLoadStart,
      onLoadEnd: this._onLoadEnd,
      onLoadError: this._onLoadError
    }));
  }
}
_defineProperty(Blurhash, "displayName", 'Blurhash');
//# sourceMappingURL=index.js.map