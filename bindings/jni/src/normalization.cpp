// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/normalization.h>
#include <khiva_jni/normalization.h>

jlongArray JNICALL Java_io_shapelets_khiva_Normalization_decimalScalingNorm(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::normalization::decimalScalingNorm(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlong JNICALL Java_io_shapelets_khiva_Normalization_decimalScalingNormInPlace(JNIEnv *, jobject, jlong ref) {
    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    khiva::normalization::decimalScalingNormInPlace(var);
    af_retain_array(&arr, var.get());
    return (jlong)arr;
}

jlongArray JNICALL Java_io_shapelets_khiva_Normalization_maxMinNorm(JNIEnv *env, jobject, jlong ref, jdouble high,
                                                                    jdouble low, jdouble epsilon) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::normalization::maxMinNorm(var, high, low, epsilon).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlong JNICALL Java_io_shapelets_khiva_Normalization_maxMinNormInPlace(JNIEnv *, jobject, jlong ref, jdouble high,
                                                                      jdouble low, jdouble epsilon) {
    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    khiva::normalization::maxMinNormInPlace(var, high, low, epsilon);
    af_retain_array(&arr, var.get());
    return (jlong)arr;
}

jlongArray JNICALL Java_io_shapelets_khiva_Normalization_meanNorm(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::normalization::meanNorm(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlong JNICALL Java_io_shapelets_khiva_Normalization_meanNormInPlace(JNIEnv *, jobject, jlong ref) {
    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    khiva::normalization::meanNormInPlace(var);
    af_retain_array(&arr, var.get());
    return (jlong)arr;
}

jlongArray JNICALL Java_io_shapelets_khiva_Normalization_znorm(JNIEnv *env, jobject, jlong ref, jdouble epsilon) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::normalization::znorm(var, epsilon).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlong JNICALL Java_io_shapelets_khiva_Normalization_znormInPlace(JNIEnv *, jobject, jlong ref, jdouble epsilon) {
    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    khiva::normalization::znormInPlace(var, epsilon);
    af_retain_array(&arr, var.get());
    return (jlong)arr;
}
