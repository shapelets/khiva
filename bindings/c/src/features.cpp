// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa/features.h>

#ifdef __cplusplus
extern "C" {
#endif
void cidCe(double *tss, long *tss_length, long *tss_number_of_tss, bool *zNormalize, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::cidCe(af::array(*tss_length, *tss_number_of_tss, tss), *zNormalize);
    primitive_result.host(result);
}

void abs_energy(double *time_series, long *time_series_length, long *number_of_time_series, double *primitive_result) {
    af::array result;
    result = tsa::features::absEnergy(af::array(*time_series_length, *number_of_time_series, time_series));
    result.host(primitive_result);
}

void absolute_sum_of_changes(double *time_series, long *time_series_length, long *number_of_time_series,
                             double *primitive_result) {
    af::array result;
    result = tsa::features::absoluteSumOfChanges(af::array(*time_series_length, *number_of_time_series, time_series));
    result.host(primitive_result);
}

void c3(double *tss, long *tss_length, long *tss_number_of_tss, long *lag, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::c3(af::array(*tss_length, *tss_number_of_tss, tss), *lag);
    primitive_result.host(result);
}

void cross_correlation(double *xss, long *xss_length, long *xss_number_of_tss, double *yss, long *yss_length,
                       long *yss_number_of_tss, bool *unbiased, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::crossCorrelation(af::array(*xss_length, *xss_number_of_tss, xss),
                                                       af::array(*yss_length, *yss_number_of_tss, yss), *unbiased);
    primitive_result.host(result);
}

void auto_covariance(double *xss, long *xss_length, long *xss_number_of_tss, bool *unbiased, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::autoCovariance(af::array(*xss_length, *xss_number_of_tss, xss), *unbiased);
    primitive_result.host(result);
}

void cross_covariance(double *xss, long *xss_length, long *xss_number_of_tss, double *yss, long *yss_length,
                      long *yss_number_of_tss, bool *unbiased, double *result) {
    af::array primitive_result;
    primitive_result = tsa::features::crossCovariance(af::array(*xss_length, *xss_number_of_tss, xss),
                                                      af::array(*yss_length, *yss_number_of_tss, yss), *unbiased);
    primitive_result.host(result);
}

void approximate_entropy(double *tss, long *tss_length, long *tss_number_of_tss, int *m, float *r, float *result) {
    af::array primitive_result;
    primitive_result = tsa::features::approximateEntropy(af::array(*tss_length, *tss_number_of_tss, tss), *m, *r);
    primitive_result.host(result);
}

#ifdef __cplusplus
}
#endif
