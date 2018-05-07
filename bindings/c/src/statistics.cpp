// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <tsa/statistics.h>
#include <tsa_c/statistics.h>

#ifdef __cplusplus
extern "C" {
#endif

void covariance_statistics(af_array *tss, bool *unbiased, af_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, tsa::statistics::covariance(var, *unbiased).get());
}

void moment_statistics(af_array *tss, int *k, af_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, tsa::statistics::moment(var, *k).get());
}

void sample_stdev_statistics(af_array *tss, af_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, tsa::statistics::sampleStdev(var).get());
}

void kurtosis_statistics(af_array *tss, af_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, tsa::statistics::kurtosis(var).get());
}

void skewness_statistics(af_array *tss, af_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, tsa::statistics::skewness(var).get());
}

void quantile_statistics(af_array *tss, af_array *q, float *precision, af_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af::array var_q = af::array(*q);
    af_retain_array(q, var_q.get());
    af_retain_array(result, tsa::statistics::quantile(var, var_q, *precision).get());
}

void quantiles_cut_statistics(af_array *tss, float *quantiles, float *precision, af_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, tsa::statistics::quantilesCut(var, *quantiles, *precision).get());
}

#ifdef __cplusplus
}
#endif