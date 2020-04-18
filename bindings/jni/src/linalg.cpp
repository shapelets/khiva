// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/linalg.h>
#include <khiva_jni/linalg.h>

jlong JNICALL Java_io_shapelets_khiva_Linalg_lls(JNIEnv *env, jobject, jlong ref_a, jlong ref_b) {
    try {
        auto arr_a = *reinterpret_cast<af::array *>(ref_a);
        auto arr_b = *reinterpret_cast<af::array *>(ref_b);
        auto result = khiva::linalg::lls(arr_a, arr_b);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Linalg_lls. Unknown reason");
    }
    return 0;
}
