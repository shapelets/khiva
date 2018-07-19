// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/linalg.h>
#include <khiva_c/linalg.h>
#include <khiva_c/util.h>

void lls(khiva_array *a, khiva_array *b, khiva_array *result) {
    af::array var_a;
    af::array var_b;
    check_and_retain_arrays(a, b, var_a, var_b);
    af_retain_array(result, khiva::linalg::lls(var_a, var_b).get());
}
