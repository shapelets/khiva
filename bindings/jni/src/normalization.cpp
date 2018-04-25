// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa/normalization.h>
#include <tsa_jni/normalization.h>

#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT jlongArray JNICALL Java_tsa_Normalization_znorm(JNIEnv *env, jobject thisObj, jlong ref, jdouble epsilon) {
    jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, tsa::normalization::znorm(var, epsilon).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

JNIEXPORT jlong JNICALL Java_tsa_Normalization_znormInPlace(JNIEnv *env, jobject thisObj, jlong ref, jdouble epsilon) {
    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;
    tsa::normalization::znormInPlace(var, epsilon);
    af_retain_array(&arr, var.get());
    return (jlong)arr;
}

#ifdef __cplusplus
}
#endif