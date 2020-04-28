// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/array.h>
#include <khiva/internal/util.h>
#include <khiva/linalg.h>
#include <khiva_c/internal/util.h>
#include <khiva_c/linalg.h>

using namespace khiva;
using namespace khiva::util;

void lls(const khiva_array *a, const khiva_array *b, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var_a = array::from_af_array(*a);
        auto var_b = array::from_af_array(*b);
        auto res = khiva::linalg::lls(var_a, var_b);
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
