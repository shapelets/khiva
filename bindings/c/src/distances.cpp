// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <tsa/distances.h>
#include <tsa_c/distances.h>

#ifdef __cplusplus
extern "C" {
#endif

void euclidean(af_array *tss, af_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, tsa::distances::euclidean(var).get());
}

void squared_euclidean(af_array *tss, af_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, tsa::distances::squaredEuclidean(var).get());
}

void dtw(af_array *tss, af_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, tsa::distances::dtw(var).get());
}

#ifdef __cplusplus
}
#endif