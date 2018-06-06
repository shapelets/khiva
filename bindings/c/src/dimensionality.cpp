// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/dimensionality.h>
#include <khiva_c/dimensionality.h>

#ifdef __cplusplus
extern "C" {
#endif

KHIVAAPI void paa(khiva_array *a, int *bins, khiva_array *result) {
    af::array var = af::array(*a);
    af_retain_array(a, var.get());
    af_retain_array(result, khiva::dimensionality::PAA(var, *bins).get());
}

KHIVAAPI void pip(khiva_array *a, int *number_ips, khiva_array *result) {
    af::array var = af::array(*a);
    af_retain_array(a, var.get());
    af_retain_array(result, khiva::dimensionality::PIP(var, *number_ips).get());
}

KHIVAAPI void pla_bottom_up(khiva_array *ts, float *max_error, khiva_array *result) {
    af::array var = af::array(*ts);
    af_retain_array(ts, var.get());
    af_retain_array(result, khiva::dimensionality::PLABottomUp(var, *max_error).get());
}

KHIVAAPI void pla_sliding_window(khiva_array *ts, float *max_error, khiva_array *result) {
    af::array var = af::array(*ts);
    af_retain_array(ts, var.get());
    af_retain_array(result, khiva::dimensionality::PLASlidingWindow(var, *max_error).get());
}

KHIVAAPI void ramer_douglas_peucker(khiva_array *points, double *epsilon, khiva_array *res_points) {
    af::array var = af::array(*points);
    af_retain_array(points, var.get());
    af_retain_array(res_points, khiva::dimensionality::ramerDouglasPeucker(var, *epsilon).get());
}

KHIVAAPI void sax(khiva_array *a, int *alphabet_size, khiva_array *result) {
    af::array var = af::array(*a);
    af_retain_array(a, var.get());
    af_retain_array(result, khiva::dimensionality::SAX(var, *alphabet_size).get());
}

KHIVAAPI void visvalingam(khiva_array *points, int *num_points, khiva_array *res_points) {
    af::array var = af::array(*points);
    af_retain_array(points, var.get());
    af_retain_array(res_points, khiva::dimensionality::visvalingam(var, *num_points).get());
}

#ifdef __cplusplus
}
#endif
