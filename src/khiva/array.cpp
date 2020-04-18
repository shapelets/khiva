// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/array.h>

af::array khiva::array::createArray(const void *data, unsigned ndims, const dim_t *dims, const int type) {
    af::dim4 d = af::dim4(ndims, dims);
    switch (static_cast<khiva::dtype>(type)) {
        case khiva::dtype::f32:
            return af::array(d, static_cast<const float *>(data));
        case khiva::dtype::c32:
            return af::array(d, static_cast<const af::cfloat *>(data));
        case khiva::dtype::f64:
            return af::array(d, static_cast<const double *>(data));
        case khiva::dtype::c64:
            return af::array(d, static_cast<const af::cdouble *>(data));
        case khiva::dtype::b8:
            return af::array(d, static_cast<const char *>(data));
        case khiva::dtype::s32:
            return af::array(d, static_cast<const int *>(data));
        case khiva::dtype::u32:
            return af::array(d, static_cast<const unsigned int *>(data));
        case khiva::dtype::u8:
            return af::array(d, static_cast<const unsigned char *>(data));
        case khiva::dtype::s64:
            return af::array(d, static_cast<const long long *>(data));
        case khiva::dtype::u64:
            return af::array(d, static_cast<const unsigned long long *>(data));
        case khiva::dtype::s16:
            return af::array(d, static_cast<const short *>(data));
        case khiva::dtype::u16:
            return af::array(d, static_cast<const unsigned short *>(data));
        default:
            return af::array(d, static_cast<const float *>(data));
    }
}

void khiva::array::deleteArray(af_array array) { af_release_array(array); }

void khiva::array::getData(const af::array &array, void *data) { array.host(data); }

af::dim4 khiva::array::getDims(const af::array &array) { return array.dims(); }

int khiva::array::getType(const af::array &array) { return array.type(); }

void khiva::array::print(const af::array &array){af_print(array)}

af::array khiva::array::join(int dim, const af::array &first, const af::array &second) {
    return af::join(dim, first, second);
}
