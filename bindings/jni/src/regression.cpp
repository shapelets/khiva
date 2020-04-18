// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <jni.h>
#include <khiva/regression.h>
#include <khiva_jni/regression.h>
#include <array>

jlongArray JNICALL Java_io_shapelets_khiva_Regression_linear(JNIEnv *env, jobject, jlong ref_xss, jlong ref_yss) {
    try {
        auto arr_xss = *reinterpret_cast<af::array *>(ref_xss);
        auto arr_yss = *reinterpret_cast<af::array *>(ref_yss);

        af::array primitive_pvalue;
        af::array primitive_rvalue;
        af::array primitive_intercept;
        af::array primitive_slope;
        af::array primitive_stderr;
        khiva::regression::linear(arr_xss, arr_yss, primitive_slope, primitive_intercept, primitive_rvalue,
                                  primitive_pvalue, primitive_stderr);
        constexpr auto output_size = 5;
        std::array<jlong, output_size> output;
        output[0] = reinterpret_cast<jlong>(new af::array(primitive_slope));
        output[1] = reinterpret_cast<jlong>(new af::array(primitive_intercept));
        output[2] = reinterpret_cast<jlong>(new af::array(primitive_rvalue));
        output[3] = reinterpret_cast<jlong>(new af::array(primitive_pvalue));
        output[4] = reinterpret_cast<jlong>(new af::array(primitive_stderr));

        auto pointers = env->NewLongArray(output_size);
        env->SetLongArrayRegion(pointers, 0, output_size, output.data());
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Regression_linear. Unknown reason");
    }
    return nullptr;
}
