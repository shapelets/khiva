// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/distances.h>
#include <khiva_c/distances.h>

#ifdef __cplusplus
extern "C" {
#endif

KHIVAAPI void euclidean(khiva_array *tss, khiva_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, khiva::distances::euclidean(var).get());
}

KHIVAAPI void dtw(khiva_array *tss, khiva_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, khiva::distances::dtw(var).get());
}

KHIVAAPI void hamming(khiva_array *tss, khiva_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, khiva::distances::hamming(var).get());
}

KHIVAAPI void manhattan(khiva_array *tss, khiva_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, khiva::distances::manhattan(var).get());
}

KHIVAAPI void squared_euclidean(khiva_array *tss, khiva_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, khiva::distances::squaredEuclidean(var).get());
}

#ifdef __cplusplus
}
#endif
