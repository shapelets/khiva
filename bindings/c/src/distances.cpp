// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/distances.h>
#include <khiva_c/distances.h>
#include <khiva_c/internal/util.h>

void euclidean(khiva_array *tss, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*tss);
        af_retain_array(tss, var.get());
        af_retain_array(result, khiva::distances::euclidean(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("euclidean", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("euclidean", error_message, error_code, -1);
    }
}

void dtw(khiva_array *tss, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*tss);
        af_retain_array(tss, var.get());
        af_retain_array(result, khiva::distances::dtw(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("dtw", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("dtw", error_message, error_code, -1);
    }
}

void hamming(khiva_array *tss, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*tss);
        af_retain_array(tss, var.get());
        af_retain_array(result, khiva::distances::hamming(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("hamming", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("hamming", error_message, error_code, -1);
    }
}

void manhattan(khiva_array *tss, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*tss);
        af_retain_array(tss, var.get());
        af_retain_array(result, khiva::distances::manhattan(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("manhattan", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("manhattan", error_message, error_code, -1);
    }
}

void sbd(khiva_array *tss, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*tss);
        af_retain_array(tss, var.get());
        af_retain_array(result, khiva::distances::sbd(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("sbd", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("sbd", error_message, error_code, -1);
    }
}

void squared_euclidean(khiva_array *tss, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*tss);
        af_retain_array(tss, var.get());
        af_retain_array(result, khiva::distances::squaredEuclidean(var).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("squared_euclidean", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("squared_euclidean", error_message, error_code, -1);
    }
}
