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

TSAAPI void euclidean(tsa_array *tss, tsa_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, tsa::distances::euclidean(var).get());
}

TSAAPI void dtw(tsa_array *tss, tsa_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, tsa::distances::dtw(var).get());
}

TSAAPI void hamming(tsa_array *tss, tsa_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, tsa::distances::hamming(var).get());
}

TSAAPI void manhattan(tsa_array *tss, tsa_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, tsa::distances::manhattan(var).get());
}

TSAAPI void squared_euclidean(tsa_array *tss, tsa_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, tsa::distances::squaredEuclidean(var).get());
}

#ifdef __cplusplus
}
#endif