// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa/linalg.h>
#include <tsa_c/linalg.h>

#ifdef __cplusplus
extern "C" {
#endif

void lls(double *a, long *a_l, long *a_n, double *b, long *b_l, double *result) {
    af::array primitive_result;
    primitive_result = tsa::linalg::lls(af::array(*a_l, *a_n, a), af::array(*b_l, b));
    primitive_result.host(result);
}

#ifdef __cplusplus
}
#endif