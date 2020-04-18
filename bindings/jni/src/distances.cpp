// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <jni.h>
#include <khiva/distances.h>
#include <khiva_jni/distances.h>

jlong JNICALL Java_io_shapelets_khiva_Distances_euclidean(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::distances::euclidean(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Distances_euclidean. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Distances_dtw(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::distances::dtw(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Distances_dtw. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Distances_hamming(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::distances::hamming(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Distances_hamming. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Distances_manhattan(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::distances::manhattan(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Distances_manhattan. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Distances_sbd(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::distances::sbd(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Distances_sbd. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Distances_squaredEuclidean(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::distances::squaredEuclidean(arr);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Distances_squaredEuclidean. Unknown reason");
    }
    return 0;
}
