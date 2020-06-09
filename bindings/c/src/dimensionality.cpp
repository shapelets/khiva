// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/array.h>
#include <khiva/dimensionality.h>
#include <khiva/internal/util.h>
#include <khiva_c/dimensionality.h>
#include <khiva_c/internal/util.h>

using namespace khiva;
using namespace khiva::util;

void paa(const khiva_array *a, const int *bins, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto array = array::from_af_array(*a);
        auto r = khiva::dimensionality::PAA(array, *bins);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void pip(const khiva_array *a, const int *number_ips, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto array = array::from_af_array(*a);
        auto r = khiva::dimensionality::PIP(array, *number_ips);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void pla_bottom_up(const khiva_array *ts, const float *max_error, khiva_array *result, int *error_code,
                   char *error_message) {
    try {
        auto array = array::from_af_array(*ts);
        auto r = khiva::dimensionality::PLABottomUp(array, *max_error);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void pla_sliding_window(const khiva_array *ts, const float *max_error, khiva_array *result, int *error_code,
                        char *error_message) {
    try {
        auto array = array::from_af_array(*ts);
        auto r = khiva::dimensionality::PLASlidingWindow(array, *max_error);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void ramer_douglas_peucker(const khiva_array *points, const double *epsilon, khiva_array *res_points, int *error_code,
                           char *error_message) {
    try {
        auto array = array::from_af_array(*points);
        auto r = khiva::dimensionality::ramerDouglasPeucker(array, *epsilon);
        *res_points = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void sax(const khiva_array *a, const int *alphabet_size, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto array = array::from_af_array(*a);
        auto r = khiva::dimensionality::SAX(array, *alphabet_size);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void visvalingam(const khiva_array *points, const int *num_points, khiva_array *res_points, int *error_code,
                 char *error_message) {
    try {
        auto array = array::from_af_array(*points);
        auto r = khiva::dimensionality::visvalingam(array, *num_points);
        *res_points = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}
