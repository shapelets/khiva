// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/normalization.h>
#include <khiva_c/normalization.h>

#ifdef __cplusplus
extern "C" {
#endif

KHIVAAPI void decimal_scaling_norm(khiva_array *tss, khiva_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, khiva::normalization::decimalScalingNorm(var).get());
}

KHIVAAPI void decimal_scaling_norm_in_place(khiva_array *tss) {
    af::array var = af::array(*tss);
    khiva::normalization::decimalScalingNormInPlace(var);
    af_retain_array(tss, var.get());
}

KHIVAAPI void max_min_norm(khiva_array *tss, double *high, double *low, double *epsilon, khiva_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, khiva::normalization::maxMinNorm(var, *high, *low, *epsilon).get());
}

KHIVAAPI void max_min_norm_in_place(khiva_array *tss, double *high, double *low, double *epsilon) {
    af::array var = af::array(*tss);
    khiva::normalization::maxMinNormInPlace(var, *high, *low, *epsilon);
    af_retain_array(tss, var.get());
}

KHIVAAPI void mean_norm(khiva_array *tss, khiva_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, khiva::normalization::meanNorm(var).get());
}

KHIVAAPI void mean_norm_in_place(khiva_array *tss) {
    af::array var = af::array(*tss);
    khiva::normalization::meanNormInPlace(var);
    af_retain_array(tss, var.get());
}

KHIVAAPI void znorm(khiva_array *tss, double *epsilon, khiva_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, khiva::normalization::znorm(var, *epsilon).get());
}

KHIVAAPI void znorm_in_place(khiva_array *tss, double *epsilon) {
    af::array var = af::array(*tss);
    khiva::normalization::znormInPlace(var, *epsilon);
    af_retain_array(tss, var.get());
}

#ifdef __cplusplus
}
#endif
