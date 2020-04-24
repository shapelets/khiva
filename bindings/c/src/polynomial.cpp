/**
 * Copyright (c) 2019 Shapelets.io
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <khiva/array.h>
#include <khiva/internal/util.h>
#include <khiva/polynomial.h>
#include <khiva_c/internal/util.h>
#include <khiva_c/polynomial.h>

using namespace khiva;
using namespace khiva::util;

void polyfit(const khiva_array *x, const khiva_array *y, const int *deg, khiva_array *result, int *error_code,
             char *error_message) {
    try {
        auto var_x = array::from_af_array(*x);
        auto var_y = array::from_af_array(*y);
        auto res = khiva::polynomial::polyfit(var_x, var_y, *deg);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void roots(const khiva_array *p, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*p);
        auto res = khiva::polynomial::roots(var);
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}
