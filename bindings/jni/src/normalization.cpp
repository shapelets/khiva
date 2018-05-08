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

JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Normalization_decimalScalingNorm(JNIEnv *env, jobject thisObj,
                                                                                    jlong ref) {
    jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, tsa::normalization::decimalScalingNorm(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

JNIEXPORT jlong JNICALL Java_com_gcatsoft_tsa_Normalization_decimalScalingNormInPlace(JNIEnv *env, jobject thisObj,
                                                                                      jlong ref) {
    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;
    tsa::normalization::decimalScalingNormInPlace(var);
    af_retain_array(&arr, var.get());
    return (jlong)arr;
}

JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Normalization_maxMinNorm(JNIEnv *env, jobject thisObj, jlong ref,
                                                                            jdouble high, jdouble low,
                                                                            jdouble epsilon) {
    jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, tsa::normalization::maxMinNorm(var, high, low, epsilon).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

JNIEXPORT jlong JNICALL Java_com_gcatsoft_tsa_Normalization_maxMinNormInPlace(JNIEnv *env, jobject thisObj, jlong ref,
                                                                              jdouble high, jdouble low,
                                                                              jdouble epsilon) {
    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;
    tsa::normalization::maxMinNormInPlace(var, high, low, epsilon);
    af_retain_array(&arr, var.get());
    return (jlong)arr;
}

JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Normalization_meanNorm(JNIEnv *env, jobject thisObj, jlong ref) {
    jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, tsa::normalization::meanNorm(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

JNIEXPORT jlong JNICALL Java_com_gcatsoft_tsa_Normalization_meanNormInPlace(JNIEnv *env, jobject thisObj, jlong ref) {
    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;
    tsa::normalization::meanNormInPlace(var);
    af_retain_array(&arr, var.get());
    return (jlong)arr;
}

JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Normalization_znorm(JNIEnv *env, jobject thisObj, jlong ref,
                                                                       jdouble epsilon) {
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

JNIEXPORT jlong JNICALL Java_com_gcatsoft_tsa_Normalization_znormInPlace(JNIEnv *env, jobject thisObj, jlong ref,
                                                                         jdouble epsilon) {
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