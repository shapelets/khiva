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

void decimal_scaling_norm(af_array *tss, af_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, tsa::normalization::decimalScalingNorm(var).get());
}

void decimal_scaling_norm_in_place(af_array *tss) {
    af::array var = af::array(*tss);
    tsa::normalization::decimalScalingNormInPlace(var);
    af_retain_array(tss, var.get());
}

void max_min_norm(af_array *tss, double *high, double *low, double *epsilon, af_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, tsa::normalization::maxMinNorm(var, *high, *low, *epsilon).get());
}

void max_min_norm_in_place(af_array *tss, double *high, double *low, double *epsilon) {
    af::array var = af::array(*tss);
    tsa::normalization::maxMinNormInPlace(var, *high, *low, *epsilon);
    af_retain_array(tss, var.get());
}

void mean_norm(af_array *tss, af_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, tsa::normalization::meanNorm(var).get());
}

void mean_norm_in_place(af_array *tss) {
    af::array var = af::array(*tss);
    tsa::normalization::meanNormInPlace(var);
    af_retain_array(tss, var.get());
}

void znorm(af_array *tss, double *epsilon, af_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, tsa::normalization::znorm(var, *epsilon).get());
}

void znorm_in_place(af_array *tss, double *epsilon) {
    af::array var = af::array(*tss);
    tsa::normalization::znormInPlace(var, *epsilon);
    af_retain_array(tss, var.get());
}

#ifdef __cplusplus
}
#endif