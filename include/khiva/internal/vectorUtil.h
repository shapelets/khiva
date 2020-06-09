// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_CORE_VECTOR_H
#define KHIVA_CORE_VECTOR_H

#ifndef BUILDING_KHIVA
#error Internal headers cannot be included from user code
#endif

#include <arrayfire.h>

#include <vector>

namespace khiva {
namespace vectorutil {

template <typename T>
std::vector<T> get(af::array arr) {
    std::vector<T> ret(arr.elements());
    arr.host(ret.data());
    return ret;
}

template <typename T>
af::array createArray(std::initializer_list<T> values, dim_t dim0, dim_t dim1 = 1, dim_t dim2 = 1, dim_t dim3 = 1) {
    std::vector<T> v(values);
    return af::array(dim0, dim1, dim2, dim3, v.data());
}

template <typename T>
af::array createArray(const std::vector<T> &values, dim_t dim0, dim_t dim1 = 1, dim_t dim2 = 1, dim_t dim3 = 1) {
    return af::array(dim0, dim1, dim2, dim3, values.data());
}
template <typename T>
af::array createArray(std::initializer_list<T> values) {
    std::vector<T> v(values);
    return af::array(values.size(), 1, 1, 1, v.data());
}

template <typename T>
af::array createArray(const std::vector<T> &values) {
    return af::array(values.size(), 1, 1, 1, values.data());
}

}  // namespace vectorutil
}  // namespace khiva

#endif
