// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/array.h>
#include <khiva/distances.h>
#include <khiva/internal/util.h>
#include <khiva_c/distances.h>
#include <khiva_c/internal/util.h>

using namespace khiva;
using namespace khiva::util;

void euclidean(const khiva_array *tss, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto array = array::from_af_array(*tss);
        auto r = khiva::distances::euclidean(array);
        *result = util::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void dtw(const khiva_array *tss, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto array = array::from_af_array(*tss);
        auto r = khiva::distances::dtw(array);
        *result = util::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void hamming(const khiva_array *tss, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto array = array::from_af_array(*tss);
        auto r = khiva::distances::hamming(array);
        *result = util::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void manhattan(const khiva_array *tss, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto array = array::from_af_array(*tss);
        auto r = khiva::distances::manhattan(array);
        *result = util::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void sbd(const khiva_array *tss, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto array = array::from_af_array(*tss);
        auto r = khiva::distances::sbd(array);
        *result = util::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void squared_euclidean(const khiva_array *tss, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto array = array::from_af_array(*tss);
        auto r = khiva::distances::squaredEuclidean(array);
        *result = util::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}
