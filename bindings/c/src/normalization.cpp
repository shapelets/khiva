// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa/normalization.h>
#include <tsa_c/normalization.h>

#ifdef __cplusplus
extern "C" {
#endif

void znorm(double *tss, long *tss_l, long *tss_n, double *epsilon, double *result) {
    af::array primitive_result;
    primitive_result = tsa::normalization::znorm(af::array(*tss_l, *tss_n, tss), *epsilon);
    primitive_result.host(result);
}
#ifdef __cplusplus
}
#endif