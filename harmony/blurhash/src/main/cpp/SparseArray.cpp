/*
 * Copyright (c) 2024 Huawei Device Co., Ltd. All rights reserved
 * Use of this source code is governed by a MIT license that can be
 * found in the LICENSE file.
 */

#include "SparseArray.h"
#include <stdexcept>

template <typename T> void SparseArray<T>::set(int key, const T &value) { data[key] = value; }

template <typename T> T SparseArray<T>::get(int key) const {
    auto it = data.find(key);
    if (it != data.end()) {
        return it->second;
    }
    throw std::runtime_error("Key not found");
}

template <typename T> void SparseArray<T>::remove(int key) { data.erase(key); }

template <typename T> void SparseArray<T>::clear() { data.clear(); }

template <typename T> bool SparseArray<T>::containsKey(int key) const { return data.find(key) != data.end(); }

// 显式实例化模板类
template class SparseArray<std::vector<double>>;
template class SparseArray<std::vector<int>>;
