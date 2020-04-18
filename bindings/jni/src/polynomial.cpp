// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/polynomial.h>
#include <khiva_jni/polynomial.h>

jlong JNICALL Java_io_shapelets_khiva_Polynomial_polyfit(JNIEnv *env, jobject, jlong refX, jlong refY, jint deg) {
    try {
        auto arr_x = *reinterpret_cast<af::array *>(refX);        
        auto arr_y = *reinterpret_cast<af::array *>(refY);
        auto result = khiva::polynomial::polyfit(arr_x, arr_y, deg);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Polynomial_polyfit. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Polynomial_roots(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::polynomial::roots(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Polynomial_roots. Unknown reason");
    }
    return 0;
}
