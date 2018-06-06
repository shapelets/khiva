// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/statistics.h>
#include <khiva_c/statistics.h>

#ifdef __cplusplus
extern "C" {
#endif

KHIVAAPI void covariance_statistics(khiva_array *tss, bool *unbiased, khiva_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, khiva::statistics::covariance(var, *unbiased).get());
}

KHIVAAPI void kurtosis_statistics(khiva_array *tss, khiva_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, khiva::statistics::kurtosis(var).get());
}

KHIVAAPI void ljung_box(khiva_array *tss, long *lags, khiva_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, khiva::statistics::ljungBox(var, *lags).get());
}

KHIVAAPI void moment_statistics(khiva_array *tss, int *k, khiva_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, khiva::statistics::moment(var, *k).get());
}

KHIVAAPI void quantile_statistics(khiva_array *tss, khiva_array *q, float *precision, khiva_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af::array var_q = af::array(*q);
    af_retain_array(q, var_q.get());
    af_retain_array(result, khiva::statistics::quantile(var, var_q, *precision).get());
}

KHIVAAPI void quantiles_cut_statistics(khiva_array *tss, float *quantiles, float *precision, khiva_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, khiva::statistics::quantilesCut(var, *quantiles, *precision).get());
}

KHIVAAPI void sample_stdev_statistics(khiva_array *tss, khiva_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, khiva::statistics::sampleStdev(var).get());
}

KHIVAAPI void skewness_statistics(khiva_array *tss, khiva_array *result) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, khiva::statistics::skewness(var).get());
}

#ifdef __cplusplus
}
#endif
