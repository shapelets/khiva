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

void lls(af_array *a, af_array *b, af_array *result) {
    af::array var_a = af::array(*a);
    af_retain_array(a, var_a.get());
    af::array var_b = af::array(*b);
    af_retain_array(b, var_b.get());
    af_retain_array(result, tsa::linalg::lls(var_a, var_b).get());
}

#ifdef __cplusplus
}
#endif