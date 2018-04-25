// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <tsa/array.h>
#include <tsa_c/array.h>

#ifdef __cplusplus
extern "C" {
#endif

void create_array(void *data, unsigned *ndims, dim_t *dims, af_array *result, int *type) {
    af_retain_array(result, tsa::array::createArray(data, *ndims, dims, *type).get());
}

void get_data(af_array *array, void *data) {
    af::array var = af::array(*array);
    tsa::array::getData(var, data);
    af_retain_array(array, var.get());
}

void get_dims(af_array *array, dim_t *dimens) {
    af::array var = af::array(*array);
    af::dim4 d = tsa::array::getDims(var);
    memcpy(dimens, d.dims, sizeof(d.dims));
    af_retain_array(array, var.get());
}

void print(af_array *array) {
    af::array var = af::array(*array);
    tsa::array::print(var);
    af_retain_array(array, var.get());
}

void delete_array(af_array *array) { tsa::array::deleteArray(*array); }

void get_type(af_array *array, int *t) {
    af::array var = af::array(*array);
    *t = tsa::array::getType(var);
    af_retain_array(array, var.get());
}

#ifdef __cplusplus
}
#endif