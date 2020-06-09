// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/array.h>
#include <khiva/clustering.h>
#include <khiva/internal/util.h>
#include <khiva_c/clustering.h>
#include <khiva_c/internal/util.h>

using namespace khiva;
using namespace khiva::util;

void k_means(const khiva_array *tss, const int *k, khiva_array *centroids, khiva_array *labels, const float *tolerance,
             const int *max_iterations, int *error_code, char *error_message) {
    try {
        auto var_tss = array::from_af_array(*tss);
        af::array primitive_labels;
        af::array primitive_centroids;

        khiva::clustering::kMeans(var_tss, *k, primitive_centroids, primitive_labels, *tolerance, *max_iterations);

        *labels = array::increment_ref_count(primitive_labels.get());
        *centroids = array::increment_ref_count(primitive_centroids.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void k_shape(const khiva_array *tss, const int *k, khiva_array *centroids, khiva_array *labels, const float *tolerance,
             const int *max_iterations, int *error_code, char *error_message) {
    try {
        auto var_tss = array::from_af_array(*tss);
        af::array primitive_labels;
        af::array primitive_centroids;

        khiva::clustering::kShape(var_tss, *k, primitive_centroids, primitive_labels, *tolerance, *max_iterations);

        *labels = array::increment_ref_count(primitive_labels.get());
        *centroids = array::increment_ref_count(primitive_centroids.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}
