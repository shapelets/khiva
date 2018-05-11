// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <tsa/regression.h>
#include <tsa_c/regression.h>

#ifdef __cplusplus
extern "C" {
#endif

TSAAPI void linear(tsa_array *xss, tsa_array *yss, tsa_array *slope, tsa_array *intercept, tsa_array *rvalue,
                   tsa_array *pvalue, tsa_array *stderrest) {
    af::array var_xss = af::array(*xss);
    af::array var_yss = af::array(*yss);
    af_retain_array(xss, var_xss.get());
    af_retain_array(yss, var_yss.get());

    af::array slope_primitive;
    af::array intercept_primtive;
    af::array rvalue_primitive;
    af::array pvalue_primitive;
    af::array stderrest_primitive;

    tsa::regression::linear(var_xss, var_yss, slope_primitive, intercept_primtive, rvalue_primitive, pvalue_primitive,
                            stderrest_primitive);

    af_retain_array(slope, slope_primitive.get());
    af_retain_array(intercept, intercept_primtive.get());
    af_retain_array(rvalue, rvalue_primitive.get());
    af_retain_array(pvalue, pvalue_primitive.get());
    af_retain_array(stderrest, stderrest_primitive.get());
}

#ifdef __cplusplus
}
#endif