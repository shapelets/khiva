// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/normalization.h>
#include <khiva_jni/normalization.h>
#include <khiva/internal/vectorUtil.h>

jlong JNICALL Java_io_shapelets_khiva_Normalization_decimalScalingNorm(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::normalization::decimalScalingNorm(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Normalization_decimalScalingNorm. Unknown reason");
    }
    return 0;
}

void JNICALL Java_io_shapelets_khiva_Normalization_decimalScalingNormInPlace(JNIEnv *env, jobject, jlong ref) {
    try {
        auto& arr = *reinterpret_cast<af::array *>(ref);
        khiva::normalization::decimalScalingNormInPlace(arr);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Normalization_decimalScalingNormInPlace. Unknown reason");
    }
}

jlong JNICALL Java_io_shapelets_khiva_Normalization_maxMinNorm(JNIEnv *env, jobject, jlong ref, jdouble high,
                                                               jdouble low, jdouble epsilon) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::normalization::maxMinNorm(arr, high, low, epsilon);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Normalization_maxMinNorm. Unknown reason");
    }
    return 0;
}

void JNICALL Java_io_shapelets_khiva_Normalization_maxMinNormInPlace(JNIEnv *env, jobject, jlong ref, jdouble high,
                                                                     jdouble low, jdouble epsilon) {
    try {
        auto& arr = *reinterpret_cast<af::array *>(ref);
        khiva::normalization::maxMinNormInPlace(arr, high, low, epsilon);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Normalization_maxMinNormInPlace. Unknown reason");
    }
}

jlong JNICALL Java_io_shapelets_khiva_Normalization_meanNorm(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::normalization::meanNorm(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Normalization_meanNorm. Unknown reason");
    }
    return 0;
}

void JNICALL Java_io_shapelets_khiva_Normalization_meanNormInPlace(JNIEnv *env, jobject, jlong ref) {
    try {
        auto& arr = *reinterpret_cast<af::array *>(ref);
        khiva::normalization::meanNormInPlace(arr);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Normalization_meanNormInPlace. Unknown reason");
    }
}

jlong JNICALL Java_io_shapelets_khiva_Normalization_znorm(JNIEnv *env, jobject, jlong ref, jdouble epsilon) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::normalization::znorm(arr, epsilon);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Normalization_znorm. Unknown reason");
    }
    return 0;
}

void JNICALL Java_io_shapelets_khiva_Normalization_znormInPlace(JNIEnv *env, jobject, jlong ref, jdouble epsilon) {
    try {
        auto& arr = *reinterpret_cast<af::array*>(ref);
        khiva::normalization::znormInPlace(arr, epsilon);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Normalization_znormInPlace. Unknown reason");
    }
}
