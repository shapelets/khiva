// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <jni.h>
#include <khiva/statistics.h>
#include <khiva_jni/statistics.h>

jlong JNICALL Java_io_shapelets_khiva_Statistics_covariance(JNIEnv *env, jobject, jlong ref, jboolean unbiased) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::statistics::covariance(arr, unbiased);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Statistics_covariance. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Statistics_moment(JNIEnv *env, jobject, jlong ref, jint k) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::statistics::moment(arr, k);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Statistics_moment. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Statistics_sampleStdev(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::statistics::sampleStdev(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Statistics_sampleStdev. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Statistics_kurtosis(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::statistics::kurtosis(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Statistics_kurtosis. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Statistics_skewness(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::statistics::skewness(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Statistics_skewness. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Statistics_quantile(JNIEnv *env, jobject, jlong ref, jlong ref_q,
                                                               jfloat precision) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto arr_q = *reinterpret_cast<af::array *>(ref_q);
        auto result = khiva::statistics::quantile(arr, arr_q, precision);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Statistics_quantile. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Statistics_quantilesCut(JNIEnv *env, jobject, jlong ref, jfloat quantiles,
                                                                   jfloat precision) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::statistics::quantilesCut(arr, quantiles, precision);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Statistics_quantile. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Statistics_ljungBox(JNIEnv *env, jobject, jlong ref, jlong lags) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::statistics::ljungBox(arr, static_cast<long>(lags));
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Statistics_ljungBox. Unknown reason");
    }
    return 0;
}
