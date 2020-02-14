// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/regression.h>
#include <khiva_c/regression.h>
#include <khiva_c/internal/util.h>

void linear(khiva_array *xss, khiva_array *yss, khiva_array *slope, khiva_array *intercept, khiva_array *rvalue,
            khiva_array *pvalue, khiva_array *stderrest, int *error_code, char *error_message) {
    try {
        af::array var_xss;
        af::array var_yss;
        check_and_retain_arrays(xss, yss, var_xss, var_yss);

        af::array slope_primitive;
        af::array intercept_primtive;
        af::array rvalue_primitive;
        af::array pvalue_primitive;
        af::array stderrest_primitive;

        khiva::regression::linear(var_xss, var_yss, slope_primitive, intercept_primtive, rvalue_primitive,
                                  pvalue_primitive, stderrest_primitive);

        af_retain_array(slope, slope_primitive.get());
        af_retain_array(intercept, intercept_primtive.get());
        af_retain_array(rvalue, rvalue_primitive.get());
        af_retain_array(pvalue, pvalue_primitive.get());
        af_retain_array(stderrest, stderrest_primitive.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("linear", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("linear", error_message, error_code, -1);
    }
}
