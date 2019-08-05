// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/statistics.h>
#include <khiva_c/statistics.h>
#include <khiva_c/util.h>

void covariance_statistics(khiva_array *tss, bool *unbiased, khiva_array *result, int* error_code, char* error_message) {
	try {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, khiva::statistics::covariance(var, *unbiased).get());
	*error_code = 0;
    } catch(const std::exception& e) {
       fill_error("covariance_statistics", e.what(), error_message, error_code, 1);
    } catch(...) {
        fill_unknown("covariance_statistics", error_message, error_code, -1);
    }
}

void kurtosis_statistics(khiva_array *tss, khiva_array *result, int* error_code, char* error_message) {
	try {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, khiva::statistics::kurtosis(var).get());
	*error_code = 0;
    } catch(const std::exception& e) {
       fill_error("kurtosis_statistics", e.what(), error_message, error_code, 1);
    } catch(...) {
        fill_unknown("kurtosis_statistics", error_message, error_code, -1);
    }
}

void ljung_box(khiva_array *tss, long *lags, khiva_array *result, int* error_code, char* error_message) {
	try {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, khiva::statistics::ljungBox(var, *lags).get());
	*error_code = 0;
    } catch(const std::exception& e) {
       fill_error("ljung_box", e.what(), error_message, error_code, 1);
    } catch(...) {
        fill_unknown("ljung_box", error_message, error_code, -1);
    }
}

void moment_statistics(khiva_array *tss, int *k, khiva_array *result, int* error_code, char* error_message) {
	try {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, khiva::statistics::moment(var, *k).get());
	*error_code = 0;
    } catch(const std::exception& e) {
       fill_error("moment_statistics", e.what(), error_message, error_code, 1);
    } catch(...) {
        fill_unknown("moment_statistics", error_message, error_code, -1);
    }
}

void quantile_statistics(khiva_array *tss, khiva_array *q, float *precision, khiva_array *result, int* error_code, char* error_message) {
	try {
    af::array var;
    af::array var_q;
    check_and_retain_arrays(tss, q, var, var_q);
    af_retain_array(result, khiva::statistics::quantile(var, var_q, *precision).get());
	*error_code = 0;
    } catch(const std::exception& e) {
       fill_error("quantile_statistics", e.what(), error_message, error_code, 1);
    } catch(...) {
        fill_unknown("quantile_statistics", error_message, error_code, -1);
    }
}

void quantiles_cut_statistics(khiva_array *tss, float *quantiles, float *precision, khiva_array *result, int* error_code, char* error_message) {
	try {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, khiva::statistics::quantilesCut(var, *quantiles, *precision).get());
	*error_code = 0;
    } catch(const std::exception& e) {
       fill_error("quantiles_cut_statistics", e.what(), error_message, error_code, 1);
    } catch(...) {
        fill_unknown("quantiles_cut_statistics", error_message, error_code, -1);
    }
}

void sample_stdev_statistics(khiva_array *tss, khiva_array *result, int* error_code, char* error_message) {
	try {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, khiva::statistics::sampleStdev(var).get());
	*error_code = 0;
    } catch(const std::exception& e) {
       fill_error("sample_stdev_statistics", e.what(), error_message, error_code, 1);
    } catch(...) {
        fill_unknown("sample_stdev_statistics", error_message, error_code, -1);
    }
}

void skewness_statistics(khiva_array *tss, khiva_array *result, int* error_code, char* error_message) {
	try {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af_retain_array(result, khiva::statistics::skewness(var).get());
	*error_code = 0;
    } catch(const std::exception& e) {
       fill_error("skewness_statistics", e.what(), error_message, error_code, 1);
    } catch(...) {
        fill_unknown("skewness_statistics", error_message, error_code, -1);
    }
}
