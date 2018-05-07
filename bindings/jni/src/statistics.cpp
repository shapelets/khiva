// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <jni.h>
#include <tsa/statistics.h>
#include <tsa_jni/statistics.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlongArray JNICALL Java_tsa_Statistics_covariance(JNIEnv *env, jobject thisObj, jlong ref,
                                                            jboolean unbiased) {
    jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, tsa::statistics::covariance(var, unbiased).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
    return pointers;
}

JNIEXPORT jlongArray JNICALL Java_tsa_Statistics_moment(JNIEnv *env, jobject thisObj, jlong ref, jint k) {
    jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, tsa::statistics::moment(var, k).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
    return pointers;
}

JNIEXPORT jlongArray JNICALL Java_tsa_Statistics_sampleStdev(JNIEnv *env, jobject thisObj, jlong ref) {
    jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, tsa::statistics::sampleStdev(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
    return pointers;
}

JNIEXPORT jlongArray JNICALL Java_tsa_Statistics_kurtosis(JNIEnv *env, jobject thisObj, jlong ref) {
    jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, tsa::statistics::kurtosis(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
    return pointers;
}

JNIEXPORT jlongArray JNICALL Java_tsa_Statistics_skewness(JNIEnv *env, jobject thisObj, jlong ref) {
    jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, tsa::statistics::skewness(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
    return pointers;
}

JNIEXPORT jlongArray JNICALL Java_tsa_Statistics_quantile(JNIEnv *env, jobject thisObj, jlong ref, jlong ref_q,
                                                          jfloat precision) {
    jint l = 3;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);
    af_array arr_q = (af_array)ref_q;
    af::array var_q = af::array(arr_q);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr_q, var.get());
    af_retain_array(&af_p, tsa::statistics::quantile(var, var_q, precision).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)arr_q;
    tmp[2] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
    return pointers;
}

JNIEXPORT jlongArray JNICALL Java_tsa_Statistics_quantilesCut(JNIEnv *env, jobject thisObj, jlong ref, jfloat quantiles,
                                                              jfloat precision) {
    jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, tsa::statistics::quantilesCut(var, quantiles, precision).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
    return pointers;
}

#ifdef __cplusplus
}
#endif