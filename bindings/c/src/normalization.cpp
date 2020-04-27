// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/array.h>
#include <khiva/normalization.h>
#include <khiva/internal/util.h>
#include <khiva_c/normalization.h>
#include <khiva_c/internal/util.h>

using namespace khiva;
using namespace khiva::util;

void decimal_scaling_norm(const khiva_array *tss, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*tss);
        auto res = khiva::normalization::decimalScalingNorm(var);
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

void decimal_scaling_norm_in_place(khiva_array *tss, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*tss);
        khiva::normalization::decimalScalingNormInPlace(var);
        *tss = array::increment_ref_count(var.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void max_min_norm(const khiva_array *tss, const double *high, const double *low, const double *epsilon,
                  khiva_array *result, int *error_code,
                  char *error_message) {
    try {
        auto var = array::from_af_array(*tss);
        auto res = khiva::normalization::maxMinNorm(var, *high, *low, *epsilon);
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

void max_min_norm_in_place(khiva_array *tss, const double *high, const double *low, const double *epsilon,
                           int *error_code,
                           char *error_message) {
    try {
        auto var = array::from_af_array(*tss);
        khiva::normalization::maxMinNormInPlace(var, *high, *low, *epsilon);
        *tss = array::increment_ref_count(var.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void mean_norm(const khiva_array *tss, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*tss);
        auto res = khiva::normalization::meanNorm(var);
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

void mean_norm_in_place(khiva_array *tss, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*tss);
        khiva::normalization::meanNormInPlace(var);
        *tss = array::increment_ref_count(var.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void znorm(const khiva_array *tss, const double *epsilon, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*tss);
        auto res = khiva::normalization::znorm(var, *epsilon);
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

void znorm_in_place(khiva_array *tss, const double *epsilon, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*tss);
        khiva::normalization::znormInPlace(var, *epsilon);
        *tss = array::increment_ref_count(var.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}
