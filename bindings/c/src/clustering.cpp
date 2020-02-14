// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/clustering.h>
#include <khiva_c/clustering.h>
#include <khiva_c/internal/util.h>
#include <iostream>

void k_means(khiva_array *tss, int *k, khiva_array *centroids, khiva_array *labels, float *tolerance,
             int *max_iterations, int *error_code, char *error_message) {
    try {
        af::array var_tss = af::array(*tss);
        af_retain_array(tss, var_tss.get());
        af::array primitive_labels;
        af::array primitive_centroids;

        khiva::clustering::kMeans(var_tss, *k, primitive_centroids, primitive_labels, *tolerance, *max_iterations);

        af_retain_array(labels, primitive_labels.get());
        af_retain_array(centroids, primitive_centroids.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("k_means", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("k_means", error_message, error_code, -1);
    }
}

void k_shape(khiva_array *tss, int *k, khiva_array *centroids, khiva_array *labels, float *tolerance,
             int *max_iterations, int *error_code, char *error_message) {
    try {
        af::array var_tss = af::array(*tss);
        af_retain_array(tss, var_tss.get());
        af::array primitive_labels;
        af::array primitive_centroids;

        khiva::clustering::kShape(var_tss, *k, primitive_centroids, primitive_labels, *tolerance, *max_iterations);

        af_retain_array(labels, primitive_labels.get());
        af_retain_array(centroids, primitive_centroids.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("k_shape", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("k_shape", error_message, error_code, -1);
    }
}
