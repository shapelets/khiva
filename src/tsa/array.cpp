// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <tsa/array.h>
#include <complex>

using namespace af;

af::dim4 toDim4(const unsigned ndims, const dim_t *const dims) {
    af::dim4 d(1, 1, 1, 1);

    for (unsigned i = 0; i < ndims; i++) {
        d[i] = dims[i];
    }
    return d;
}

af::array tsa::array::createArray(void *data, unsigned ndims, dim_t *dims, const int type) {
    af::dim4 d = toDim4(ndims, dims);
    switch ((tsa::dtype)(type)) {
        case tsa::dtype::f32:
            return af::array(d, static_cast<float *>(data));
        case tsa::dtype::c32:
            return af::array(d, static_cast<cfloat *>(data));
        case tsa::dtype::f64:
            return af::array(d, static_cast<double *>(data));
        case tsa::dtype::c64:
            return af::array(d, static_cast<cdouble *>(data));
        case tsa::dtype::b8:
            return af::array(d, static_cast<char *>(data));
        case tsa::dtype::s32:
            return af::array(d, static_cast<int *>(data));
        case tsa::dtype::u32:
            return af::array(d, static_cast<uint *>(data));
        case tsa::dtype::u8:
            return af::array(d, static_cast<unsigned char *>(data));
        case tsa::dtype::s64:
            return af::array(d, static_cast<intl *>(data));
        case tsa::dtype::u64:
            return af::array(d, static_cast<uintl *>(data));
        case tsa::dtype::s16:
            return af::array(d, static_cast<short *>(data));
        case tsa::dtype::u16:
            return af::array(d, static_cast<ushort *>(data));
        default:
            return af::array(d, static_cast<float *>(data));
    }
}

void tsa::array::getData(af::array array, void *data) { array.host(data); }

af::dim4 tsa::array::getDims(af::array array) { return array.dims(); }

void tsa::array::displayArray(af::array array) { af_print(array); }

void tsa::array::deleteArray(af_array array) { af_release_array(array); }
