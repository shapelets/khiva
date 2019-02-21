// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/clustering.h>
#include <khiva_c/clustering.h>
#include <iostream>

void k_means(khiva_array *tss, int *k, khiva_array *centroids, khiva_array *labels, float *tolerance,
             int *max_iterations) {
    af::array var_tss = af::array(*tss);
    af_retain_array(tss, var_tss.get());
    af::array primitive_labels;
    af::array primitive_centroids;

    khiva::clustering::kMeans(var_tss, *k, primitive_centroids, primitive_labels, *tolerance, *max_iterations);

    af_retain_array(labels, primitive_labels.get());
    af_retain_array(centroids, primitive_centroids.get());
}

void k_means_initial_values(khiva_array *tss, int *k, khiva_array *initial_centroids, khiva_array *centroids,
                            khiva_array *initial_labels, khiva_array *labels, float *tolerance, int *max_iterations) {
    af::array var_tss = af::array(*tss);
    af_retain_array(tss, var_tss.get());

    af::array var_initial_centroids = af::array(*initial_centroids);
    af_retain_array(initial_centroids, var_initial_centroids.get());

    af::array var_initial_labels = af::array(*initial_labels);
    af_retain_array(tss, var_initial_labels.get());

    khiva::clustering::kMeans(var_tss, *k, var_initial_centroids, var_initial_labels, *tolerance, *max_iterations);

    af_retain_array(labels, var_initial_labels.get());
    af_retain_array(centroids, var_initial_centroids.get());
}

void k_shape(khiva_array *tss, int *k, khiva_array *centroids, khiva_array *labels, float *tolerance,
             int *max_iterations) {
    af::array var_tss = af::array(*tss);
    af_retain_array(tss, var_tss.get());
    af::array primitive_labels;
    af::array primitive_centroids;

    khiva::clustering::kShape(var_tss, *k, primitive_centroids, primitive_labels, *tolerance, *max_iterations);

    af_retain_array(labels, primitive_labels.get());
    af_retain_array(centroids, primitive_centroids.get());
}

void k_shape_initial_values(khiva_array *tss, int *k, khiva_array *initial_centroids, khiva_array *centroids,
                            khiva_array *initial_labels, khiva_array *labels, float *tolerance, int *max_iterations) {
    af::array var_tss = af::array(*tss);
    af_retain_array(tss, var_tss.get());

    af::array var_initial_centroids = af::array(*initial_centroids);
    af_retain_array(initial_centroids, var_initial_centroids.get());

    af::array var_initial_labels = af::array(*initial_labels);
    af_retain_array(tss, var_initial_labels.get());

    khiva::clustering::kShape(var_tss, *k, var_initial_centroids, var_initial_labels, *tolerance, *max_iterations);

    af_retain_array(labels, var_initial_labels.get());
    af_retain_array(centroids, var_initial_centroids.get());
}
