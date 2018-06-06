/**
 * Copyright (c) 2018 Shapelets.io
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <arrayfire.h>
#include <khiva/polynomial.h>
#include <khiva_c/polynomial.h>

#ifdef __cplusplus
extern "C" {
#endif

KHIVAAPI void polyfit(khiva_array *x, khiva_array *y, int *deg, khiva_array *result) {
    af::array xx = af::array(*x);
    af_retain_array(x, xx.get());
    af::array yy = af::array(*y);
    af_retain_array(y, yy.get());
    af_retain_array(result, khiva::polynomial::polyfit(xx, yy, *deg).get());
}

KHIVAAPI void roots(khiva_array *p, khiva_array *result) {
    af::array var = af::array(*p);
    af_retain_array(p, var.get());
    af_retain_array(result, khiva::polynomial::roots(var).get());
}

#ifdef __cplusplus
}
#endif
