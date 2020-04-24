// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/array.h>
#include <khiva/regression.h>
#include <khiva/internal/util.h>
#include <khiva_c/regression.h>
#include <khiva_c/internal/util.h>

using namespace khiva;
using namespace khiva::util;

void linear(const khiva_array *xss, const khiva_array *yss, khiva_array *slope, khiva_array *intercept, khiva_array *rvalue,
            khiva_array *pvalue, khiva_array *stderrest, int *error_code, char *error_message) {
    try {
        auto var_xss = array::from_af_array(*xss);
        auto var_yss = array::from_af_array(*yss);
        
        af::array slope_primitive;
        af::array intercept_primtive;
        af::array rvalue_primitive;
        af::array pvalue_primitive;
        af::array stderrest_primitive;

        khiva::regression::linear(var_xss, var_yss, slope_primitive, intercept_primtive, rvalue_primitive,
                                  pvalue_primitive, stderrest_primitive);

        *slope = util::increment_ref_count(slope_primitive.get());
        *intercept = util::increment_ref_count(intercept_primtive.get());
        *rvalue = util::increment_ref_count(rvalue_primitive.get());
        *pvalue = util::increment_ref_count(pvalue_primitive.get());
        *stderrest = util::increment_ref_count(stderrest_primitive.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}
