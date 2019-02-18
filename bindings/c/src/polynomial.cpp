/**
 * Copyright (c) 2019 Shapelets.io
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <arrayfire.h>
#include <khiva/polynomial.h>
#include <khiva_c/polynomial.h>
#include <khiva_c/util.h>

void polyfit(khiva_array *x, khiva_array *y, int *deg, khiva_array *result) {
    af::array xx;
    af::array yy;
    check_and_retain_arrays(x, y, xx, yy);
    af_retain_array(result, khiva::polynomial::polyfit(xx, yy, *deg).get());
}

void roots(khiva_array *p, khiva_array *result) {
    af::array var = af::array(*p);
    af_retain_array(p, var.get());
    af_retain_array(result, khiva::polynomial::roots(var).get());
}
