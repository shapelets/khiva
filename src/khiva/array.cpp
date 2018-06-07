// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/array.h>
#include <complex>

af::dim4 toDim4(const unsigned ndims, const dim_t *const dims) {
    af::dim4 d(1, 1, 1, 1);

    for (unsigned i = 0; i < ndims; i++) {
        d[i] = dims[i];
    }
    return d;
}

af::array khiva::array::createArray(void *data, unsigned ndims, dim_t *dims, const int type) {
    af::dim4 d = toDim4(ndims, dims);
    switch ((khiva::dtype)(type)) {
        case khiva::dtype::f32:
            return af::array(d, static_cast<float *>(data));
        case khiva::dtype::c32:
            return af::array(d, static_cast<af::cfloat *>(data));
        case khiva::dtype::f64:
            return af::array(d, static_cast<double *>(data));
        case khiva::dtype::c64:
            return af::array(d, static_cast<af::cdouble *>(data));
        case khiva::dtype::b8:
            return af::array(d, static_cast<char *>(data));
        case khiva::dtype::s32:
            return af::array(d, static_cast<int *>(data));
        case khiva::dtype::u32:
            return af::array(d, static_cast<unsigned int *>(data));
        case khiva::dtype::u8:
            return af::array(d, static_cast<unsigned char *>(data));
        case khiva::dtype::s64:
            return af::array(d, static_cast<long long *>(data));
        case khiva::dtype::u64:
            return af::array(d, static_cast<unsigned long long *>(data));
        case khiva::dtype::s16:
            return af::array(d, static_cast<short *>(data));
        case khiva::dtype::u16:
            return af::array(d, static_cast<unsigned short *>(data));
        default:
            return af::array(d, static_cast<float *>(data));
    }
}

void khiva::array::getData(af::array array, void *data) { array.host(data); }

af::dim4 khiva::array::getDims(af::array array) { return array.dims(); }

void khiva::array::print(af::array array) { af_print(array); }

void khiva::array::deleteArray(af_array array) { af_release_array(array); }

int khiva::array::getType(af::array array) { return array.type(); }
