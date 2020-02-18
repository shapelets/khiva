// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/normalization.h>
#include <khiva_c/normalization.h>
#include <khiva_c/internal/util.h>

void decimal_scaling_norm(khiva_array *tss, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*tss);
        af_retain_array(tss, var.get());
        af_retain_array(result, khiva::normalization::decimalScalingNorm(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("decimal_scaling_norm", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("decimal_scaling_norm", error_message, error_code, -1);
    }
}

void decimal_scaling_norm_in_place(khiva_array *tss, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*tss);
        khiva::normalization::decimalScalingNormInPlace(var);
        af_retain_array(tss, var.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("decimal_scaling_norm_in_place", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("decimal_scaling_norm_in_place", error_message, error_code, -1);
    }
}

void max_min_norm(khiva_array *tss, double *high, double *low, double *epsilon, khiva_array *result, int *error_code,
                  char *error_message) {
    try {
        af::array var = af::array(*tss);
        af_retain_array(tss, var.get());
        af_retain_array(result, khiva::normalization::maxMinNorm(var, *high, *low, *epsilon).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("max_min_norm", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("max_min_norm", error_message, error_code, -1);
    }
}

void max_min_norm_in_place(khiva_array *tss, double *high, double *low, double *epsilon, int *error_code,
                           char *error_message) {
    try {
        af::array var = af::array(*tss);
        khiva::normalization::maxMinNormInPlace(var, *high, *low, *epsilon);
        af_retain_array(tss, var.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("max_min_norm_in_place", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("max_min_norm_in_place", error_message, error_code, -1);
    }
}

void mean_norm(khiva_array *tss, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*tss);
        af_retain_array(tss, var.get());
        af_retain_array(result, khiva::normalization::meanNorm(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("mean_norm", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("mean_norm", error_message, error_code, -1);
    }
}

void mean_norm_in_place(khiva_array *tss, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*tss);
        khiva::normalization::meanNormInPlace(var);
        af_retain_array(tss, var.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("mean_norm_in_place", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("mean_norm_in_place", error_message, error_code, -1);
    }
}

void znorm(khiva_array *tss, double *epsilon, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*tss);
        af_retain_array(tss, var.get());
        af_retain_array(result, khiva::normalization::znorm(var, *epsilon).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("znorm", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("znorm", error_message, error_code, -1);
    }
}

void znorm_in_place(khiva_array *tss, double *epsilon, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*tss);
        khiva::normalization::znormInPlace(var, *epsilon);
        af_retain_array(tss, var.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("znorm_in_place", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("znorm_in_place", error_message, error_code, -1);
    }
}
