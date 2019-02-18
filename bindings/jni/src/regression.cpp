// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <jni.h>
#include <khiva/regression.h>
#include <khiva_jni/regression.h>
#include <khiva_jni/util.h>

jlongArray JNICALL Java_io_shapelets_khiva_Regression_linear(JNIEnv *env, jobject, jlong ref_xss, jlong ref_yss) {
    const jint l = 7;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr_xss = (af_array)ref_xss;
    af::array var_xss;

    af_array arr_yss = (af_array)ref_yss;
    af::array var_yss;

    jlong raw_pointer_pvalue = 0;
    af_array af_p_pvalue = (af_array)raw_pointer_pvalue;

    jlong raw_pointer_rvalue = 0;
    af_array af_p_rvalue = (af_array)raw_pointer_rvalue;

    jlong raw_pointer_intercept = 0;
    af_array af_p_intercept = (af_array)raw_pointer_intercept;

    jlong raw_pointer_slope = 0;
    af_array af_p_slope = (af_array)raw_pointer_slope;

    jlong raw_pointer_stderr = 0;
    af_array af_p_stderr = (af_array)raw_pointer_stderr;

    check_and_retain_arrays(arr_xss, arr_yss, var_xss, var_yss);

    af::array primitive_pvalue;
    af::array primitive_rvalue;
    af::array primitive_intercept;
    af::array primitive_slope;
    af::array primitive_stderr;

    khiva::regression::linear(var_xss, var_yss, primitive_slope, primitive_intercept, primitive_rvalue,
                              primitive_pvalue, primitive_stderr);

    af_retain_array(&af_p_pvalue, primitive_pvalue.get());
    af_retain_array(&af_p_rvalue, primitive_rvalue.get());
    af_retain_array(&af_p_intercept, primitive_intercept.get());
    af_retain_array(&af_p_slope, primitive_slope.get());
    af_retain_array(&af_p_stderr, primitive_stderr.get());

    tmp[0] = (jlong)arr_xss;
    tmp[1] = (jlong)arr_yss;
    tmp[2] = (jlong)af_p_slope;
    tmp[3] = (jlong)af_p_intercept;
    tmp[4] = (jlong)af_p_rvalue;
    tmp[5] = (jlong)af_p_pvalue;
    tmp[6] = (jlong)af_p_stderr;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
    return pointers;
}
