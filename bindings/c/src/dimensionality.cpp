// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/dimensionality.h>
#include <khiva_c/dimensionality.h>
#include <iostream>
#include <khiva_c/internal/util.h>

void paa(khiva_array *a, int *bins, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*a);
        af_retain_array(a, var.get());
        af_retain_array(result, khiva::dimensionality::PAA(var, *bins).get());
    } catch (const std::exception &e) {
        fill_error("PAA", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("PAA", error_message, error_code, -1);
    }
}

void pip(khiva_array *a, int *number_ips, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*a);
        af_retain_array(a, var.get());
        af_retain_array(result, khiva::dimensionality::PIP(var, *number_ips).get());
    } catch (const std::exception &e) {
        fill_error("PIP", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("PIP", error_message, error_code, -1);
    }
}

void pla_bottom_up(khiva_array *ts, float *max_error, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*ts);
        af_retain_array(ts, var.get());
        af_retain_array(result, khiva::dimensionality::PLABottomUp(var, *max_error).get());

    } catch (const std::exception &e) {
        fill_error("PLA_BOTTOM_UP", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("PLA_BOTTOM_UP", error_message, error_code, -1);
    }
}

void pla_sliding_window(khiva_array *ts, float *max_error, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*ts);
        af_retain_array(ts, var.get());
        af_retain_array(result, khiva::dimensionality::PLASlidingWindow(var, *max_error).get());

    } catch (const std::exception &e) {
        fill_error("PLA_SLIDING_WINDOW", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("PLA_SLIDING_WINDOW", error_message, error_code, -1);
    }
}

void ramer_douglas_peucker(khiva_array *points, double *epsilon, khiva_array *res_points, int *error_code,
                           char *error_message) {
    try {
        af::array var = af::array(*points);
        af_retain_array(points, var.get());
        af_retain_array(res_points, khiva::dimensionality::ramerDouglasPeucker(var, *epsilon).get());
    } catch (const std::exception &e) {
        fill_error("RDP", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("RDP", error_message, error_code, -1);
    }
}

void sax(khiva_array *a, int *alphabet_size, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*a);
        af_retain_array(a, var.get());
        af_retain_array(result, khiva::dimensionality::SAX(var, *alphabet_size).get());

    } catch (const std::exception &e) {
        fill_error("SAX", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("SAX", error_message, error_code, -1);
    }
}

void visvalingam(khiva_array *points, int *num_points, khiva_array *res_points, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*points);
        af_retain_array(points, var.get());
        af_retain_array(res_points, khiva::dimensionality::visvalingam(var, *num_points).get());
    } catch (const std::exception &e) {
        fill_error("Visvalingam", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("Visvalingam", error_message, error_code, -1);
    }
}
