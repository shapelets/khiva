// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/array.h>
#include <khiva/internal/util.h>
#include <khiva/statistics.h>
#include <khiva_c/internal/util.h>
#include <khiva_c/statistics.h>

using namespace khiva;
using namespace khiva::util;

void covariance_statistics(const khiva_array *tss, const bool *unbiased, khiva_array *result, int *error_code,
                           char *error_message) {
    try {
        auto var = array::from_af_array(*tss);
        auto res = khiva::statistics::covariance(var, *unbiased);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void kurtosis_statistics(const khiva_array *tss, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*tss);
        auto res = khiva::statistics::kurtosis(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void ljung_box(const khiva_array *tss, const long *lags, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*tss);
        auto res = khiva::statistics::ljungBox(var, *lags);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void moment_statistics(const khiva_array *tss, const int *k, khiva_array *result, int *error_code,
                       char *error_message) {
    try {
        auto var = array::from_af_array(*tss);
        auto res = khiva::statistics::moment(var, *k);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void quantile_statistics(const khiva_array *tss, const khiva_array *q, const float *precision, khiva_array *result,
                         int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*tss);
        auto var_q = array::from_af_array(*q);
        auto res = khiva::statistics::quantile(var, var_q , *precision);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void quantiles_cut_statistics(const khiva_array *tss, const float *quantiles, const float *precision,
                              khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*tss);
        auto res = khiva::statistics::quantilesCut(var, *quantiles, *precision);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void sample_stdev_statistics(const khiva_array *tss, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*tss);
        auto res = khiva::statistics::sampleStdev(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void skewness_statistics(const khiva_array *tss, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*tss);
        auto res = khiva::statistics::skewness(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}
