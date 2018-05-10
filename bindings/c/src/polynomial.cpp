/**
 * Copyright (c) 2018 Grumpy Cat Software S.L.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <tsa/polynomial.h>
#include <tsa_c/polynomial.h>

#ifdef __cplusplus
extern "C" {
#endif

TSAAPI void polyfit(af_array *x, af_array *y, int *deg, af_array *result) {
    af::array xx = af::array(*x);
    af_retain_array(x, xx.get());
    af::array yy = af::array(*y);
    af_retain_array(y, yy.get());
    af_retain_array(result, tsa::polynomial::polyfit(xx, yy, *deg).get());
}

TSAAPI void roots(af_array *p, af_array *result) {
    af::array var = af::array(*p);
    af_retain_array(p, var.get());
    af_retain_array(result, tsa::polynomial::roots(var).get());
}

#ifdef __cplusplus
}
#endif