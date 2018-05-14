// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <tsa/dimensionality.h>
#include <tsa_c/dimensionality.h>

#ifdef __cplusplus
extern "C" {
#endif

TSAAPI void paa(tsa_array *a, int *bins, tsa_array *result) {
    af::array var = af::array(*a);
    af_retain_array(a, var.get());
    af_retain_array(result, tsa::dimensionality::PAA(var, *bins).get());
}

TSAAPI void pip(tsa_array *a, int *number_ips, tsa_array *result) {
    af::array var = af::array(*a);
    af_retain_array(a, var.get());
    af_retain_array(result, tsa::dimensionality::PIP(var, *number_ips).get());
}

TSAAPI void pla_bottom_up(tsa_array *ts, float *max_error, tsa_array *result) {
    af::array var = af::array(*ts);
    af_retain_array(ts, var.get());
    af_retain_array(result, tsa::dimensionality::PLABottomUp(var, *max_error).get());
}

TSAAPI void pla_sliding_window(tsa_array *ts, float *max_error, tsa_array *result) {
    af::array var = af::array(*ts);
    af_retain_array(ts, var.get());
    af_retain_array(result, tsa::dimensionality::PLASlidingWindow(var, *max_error).get());
}

TSAAPI void ramer_douglas_peucker(tsa_array *points, double *epsilon, tsa_array *res_points) {
    af::array var = af::array(*points);
    af_retain_array(points, var.get());
    af_retain_array(res_points, tsa::dimensionality::ramerDouglasPeucker(var, *epsilon).get());
}

TSAAPI void sax(tsa_array *a, int *alphabet_size, tsa_array *result) {
    af::array var = af::array(*a);
    af_retain_array(a, var.get());
    af_retain_array(result, tsa::dimensionality::SAX(var, *alphabet_size).get());
}

TSAAPI void visvalingam(tsa_array *points, int *num_points, tsa_array *res_points) {
    af::array var = af::array(*points);
    af_retain_array(points, var.get());
    af_retain_array(res_points, tsa::dimensionality::visvalingam(var, *num_points).get());
}

#ifdef __cplusplus
}
#endif