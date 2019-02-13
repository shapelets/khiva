// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/clustering.h>
#include <khiva_c/clustering.h>

void kShape(khiva_array *tss, int *k, float *tolerance, khiva_array *idx, khiva_array *centroids) {
    af::array var = af::array(*tss);
    af_retain_array(tss, var.get());
    af::array primitive_idx;
    af::array primitive_centroids;

    khiva::clustering::kShape(var, *k, *tolerance, primitive_idx, primitive_centroids);

    af_retain_array(idx, primitive_idx.get());
    af_retain_array(centroids, primitive_centroids.get());
}