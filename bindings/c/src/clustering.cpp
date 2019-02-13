// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/clustering.h>
#include <khiva_c/clustering.h>

void kMeans(khiva_array *tss, int *k, khiva_array *centroids, khiva_array *labels, float *tolerance, int *maxIterations){
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af::array primitive_labels;
    af::array primitive_centroids;

    khiva::clustering::kMeans(var, *k, primitive_centroids, primitive_labels, *tolerance, *maxIterations);

    af_retain_array(labels, primitive_labels.get());
    af_retain_array(centroids, primitive_centroids.get());
}


void kShape(khiva_array *tss, int *k, khiva_array *centroids, khiva_array *labels, float *tolerance, int *maxIterations){
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af::array primitive_labels;
    af::array primitive_centroids;

    khiva::clustering::kShape(var, *k, primitive_centroids, primitive_labels, *tolerance, *maxIterations);

    af_retain_array(labels, primitive_labels.get());
    af_retain_array(centroids, primitive_centroids.get());
}