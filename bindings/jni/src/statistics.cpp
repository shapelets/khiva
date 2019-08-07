// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <jni.h>
#include <khiva/statistics.h>
#include <khiva_jni/statistics.h>
#include <khiva_jni/util.h>

jlongArray JNICALL Java_io_shapelets_khiva_Statistics_covariance(JNIEnv *env, jobject, jlong ref, jboolean unbiased) {
    try {
        const jint l = 2;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        af_array arr = (af_array) ref;
        af::array var = af::array(arr);

        jlong raw_pointer = 0;
        af_array af_p = (af_array) raw_pointer;

        af_retain_array(&arr, var.get());
        af_retain_array(&af_p, khiva::statistics::covariance(var, unbiased).get());

        tmp[0] = (jlong) arr;
        tmp[1] = (jlong) af_p;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_getChains. Unknown reason");
    }
    return NULL;
}

jlongArray JNICALL Java_io_shapelets_khiva_Statistics_moment(JNIEnv *env, jobject, jlong ref, jint k) {
    try {
        const jint l = 2;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        af_array arr = (af_array) ref;
        af::array var = af::array(arr);

        jlong raw_pointer = 0;
        af_array af_p = (af_array) raw_pointer;

        af_retain_array(&arr, var.get());
        af_retain_array(&af_p, khiva::statistics::moment(var, k).get());

        tmp[0] = (jlong) arr;
        tmp[1] = (jlong) af_p;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_getChains. Unknown reason");
    }
    return NULL;
}

jlongArray JNICALL Java_io_shapelets_khiva_Statistics_sampleStdev(JNIEnv *env, jobject, jlong ref) {
    try {
        const jint l = 2;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        af_array arr = (af_array) ref;
        af::array var = af::array(arr);

        jlong raw_pointer = 0;
        af_array af_p = (af_array) raw_pointer;

        af_retain_array(&arr, var.get());
        af_retain_array(&af_p, khiva::statistics::sampleStdev(var).get());

        tmp[0] = (jlong) arr;
        tmp[1] = (jlong) af_p;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_getChains. Unknown reason");
    }
    return NULL;
}

jlongArray JNICALL Java_io_shapelets_khiva_Statistics_kurtosis(JNIEnv *env, jobject, jlong ref) {
    try {
        const jint l = 2;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        af_array arr = (af_array) ref;
        af::array var = af::array(arr);

        jlong raw_pointer = 0;
        af_array af_p = (af_array) raw_pointer;

        af_retain_array(&arr, var.get());
        af_retain_array(&af_p, khiva::statistics::kurtosis(var).get());

        tmp[0] = (jlong) arr;
        tmp[1] = (jlong) af_p;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_getChains. Unknown reason");
    }
    return NULL;
}

jlongArray JNICALL Java_io_shapelets_khiva_Statistics_skewness(JNIEnv *env, jobject, jlong ref) {
    try {
        const jint l = 2;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        af_array arr = (af_array) ref;
        af::array var = af::array(arr);

        jlong raw_pointer = 0;
        af_array af_p = (af_array) raw_pointer;

        af_retain_array(&arr, var.get());
        af_retain_array(&af_p, khiva::statistics::skewness(var).get());

        tmp[0] = (jlong) arr;
        tmp[1] = (jlong) af_p;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_getChains. Unknown reason");
    }
    return NULL;
}

jlongArray JNICALL Java_io_shapelets_khiva_Statistics_quantile(JNIEnv *env, jobject, jlong ref, jlong ref_q,
                                                               jfloat precision) {
    try {
        const jint l = 3;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        af_array arr = (af_array) ref;
        af::array var;
        af_array arr_q = (af_array) ref_q;
        af::array var_q;

        jlong raw_pointer = 0;
        af_array af_p = (af_array) raw_pointer;

        check_and_retain_arrays(arr, arr_q, var, var_q);
        af_retain_array(&af_p, khiva::statistics::quantile(var, var_q, precision).get());

        tmp[0] = (jlong) arr;
        tmp[1] = (jlong) arr_q;
        tmp[2] = (jlong) af_p;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_getChains. Unknown reason");
    }
    return NULL;
}

jlongArray JNICALL Java_io_shapelets_khiva_Statistics_quantilesCut(JNIEnv *env, jobject, jlong ref, jfloat quantiles,
                                                                   jfloat precision) {
    try {
        const jint l = 2;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        af_array arr = (af_array) ref;
        af::array var = af::array(arr);

        jlong raw_pointer = 0;
        af_array af_p = (af_array) raw_pointer;

        af_retain_array(&arr, var.get());
        af_retain_array(&af_p, khiva::statistics::quantilesCut(var, quantiles, precision).get());

        tmp[0] = (jlong) arr;
        tmp[1] = (jlong) af_p;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_getChains. Unknown reason");
    }
    return NULL;
}

jlongArray JNICALL Java_io_shapelets_khiva_Statistics_ljungBox(JNIEnv *env, jobject, jlong ref, jlong lags) {
    try {
        const jint l = 2;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        af_array arr = (af_array) ref;
        af::array var = af::array(arr);

        jlong raw_pointer = 0;
        af_array af_p = (af_array) raw_pointer;

        af_retain_array(&arr, var.get());
        af_retain_array(&af_p, khiva::statistics::ljungBox(var, lags).get());

        tmp[0] = (jlong) arr;
        tmp[1] = (jlong) af_p;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_getChains. Unknown reason");
    }
    return NULL;
}
