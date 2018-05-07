// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa/dimensionality.h>
#include <tsa_c/dimensionality.h>

#ifdef __cplusplus
extern "C" {
#endif

void ramer_douglas_peucker(af_array *points, double *epsilon, af_array *res_points) {
    af::array var = af::array(*points);
    af_retain_array(points, var.get());
    af_retain_array(res_points, tsa::dimensionality::ramerDouglasPeucker(var, *epsilon).get());
}

void visvalingam(af_array *points, int *num_points, af_array *res_points) {
    af::array var = af::array(*points);
    af_retain_array(points, var.get());
    af_retain_array(res_points, tsa::dimensionality::visvalingam(var, *num_points).get());
}

void paa(af_array *a, int *bins, af_array *result) {
    af::array var = af::array(*a);
    af_retain_array(a, var.get());
    af_retain_array(result, tsa::dimensionality::PAA(var, *bins).get());
}

void sax(af_array *a, int *alphabet_size, af_array *result) {
    af::array var = af::array(*a);
    af_retain_array(a, var.get());
    af_retain_array(result, tsa::dimensionality::SAX(var, *alphabet_size).get());
}

void pip(af_array *a, int *number_ips, af_array *result) {
    af::array var = af::array(*a);
    af_retain_array(a, var.get());
    af_retain_array(result, tsa::dimensionality::PIP(var, *number_ips).get());
}

#ifdef __cplusplus
}
#endif