// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa/normalization.h>
#include <tsa_c/normalization.h>

#ifdef __cplusplus
extern "C" {
#endif

void znorm(af_array *array, double *epsilon, af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, tsa::normalization::znorm(var, *epsilon).get());
}

void znorm_in_place(af_array *array, double *epsilon) {
    af::array var = af::array(*array);
    tsa::normalization::znormInPlace(var, *epsilon);
    af_retain_array(array, var.get());
}

#ifdef __cplusplus
}
#endif