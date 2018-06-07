// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/linalg.h>
#include <khiva_c/linalg.h>

#ifdef __cplusplus
extern "C" {
#endif

KHIVAAPI void lls(khiva_array *a, khiva_array *b, khiva_array *result) {
    af::array var_a = af::array(*a);
    af_retain_array(a, var_a.get());
    af::array var_b = af::array(*b);
    af_retain_array(b, var_b.get());
    af_retain_array(result, khiva::linalg::lls(var_a, var_b).get());
}

#ifdef __cplusplus
}
#endif
