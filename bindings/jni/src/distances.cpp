// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <jni.h>
#include <khiva/distances.h>
#include <khiva_jni/distances.h>

jlongArray JNICALL Java_io_shapelets_khiva_Distances_euclidean(JNIEnv *env, jobject, jlong ref) {
    try {
        const jint l = 2;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        auto arr = (af_array) ref;
        af::array var = af::array(arr);

        jlong raw_pointer = 0;
        auto af_p = (af_array) raw_pointer;

        af_retain_array(&arr, var.get());
        af_retain_array(&af_p, khiva::distances::euclidean(var).get());

        tmp[0] = (jlong) arr;
        tmp[1] = (jlong) af_p;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Distances_euclidean. Unknown reason");
    }
    return nullptr;
}

jlongArray JNICALL Java_io_shapelets_khiva_Distances_dtw(JNIEnv *env, jobject, jlong ref) {
    try {
        const jint l = 2;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        auto arr = (af_array) ref;
        af::array var = af::array(arr);

        jlong raw_pointer = 0;
        auto af_p = (af_array) raw_pointer;

        af_retain_array(&arr, var.get());
        af_retain_array(&af_p, khiva::distances::dtw(var).get());

        tmp[0] = (jlong) arr;
        tmp[1] = (jlong) af_p;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Distances_dtw. Unknown reason");
    }
    return nullptr;
}

jlongArray JNICALL Java_io_shapelets_khiva_Distances_hamming(JNIEnv *env, jobject, jlong ref) {
    try {
        const jint l = 2;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        auto arr = (af_array) ref;
        af::array var = af::array(arr);

        jlong raw_pointer = 0;
        auto af_p = (af_array) raw_pointer;

        af_retain_array(&arr, var.get());
        af_retain_array(&af_p, khiva::distances::hamming(var).get());

        tmp[0] = (jlong) arr;
        tmp[1] = (jlong) af_p;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Distances_hamming. Unknown reason");
    }
    return nullptr;
}

jlongArray JNICALL Java_io_shapelets_khiva_Distances_manhattan(JNIEnv *env, jobject, jlong ref) {
    try {
        const jint l = 2;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        auto arr = (af_array) ref;
        af::array var = af::array(arr);

        jlong raw_pointer = 0;
        auto af_p = (af_array) raw_pointer;

        af_retain_array(&arr, var.get());
        af_retain_array(&af_p, khiva::distances::manhattan(var).get());

        tmp[0] = (jlong) arr;
        tmp[1] = (jlong) af_p;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Distances_manhattan. Unknown reason");
    }
    return nullptr;
}

jlongArray JNICALL Java_io_shapelets_khiva_Distances_sbd(JNIEnv *env, jobject, jlong ref) {
    try {
        const jint l = 2;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        auto arr = (af_array) ref;
        af::array var = af::array(arr);

        jlong raw_pointer = 0;
        auto af_p = (af_array) raw_pointer;

        af_retain_array(&arr, var.get());
        af_retain_array(&af_p, khiva::distances::sbd(var).get());

        tmp[0] = (jlong) arr;
        tmp[1] = (jlong) af_p;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Distances_sbd. Unknown reason");
    }
    return nullptr;
}

jlongArray JNICALL Java_io_shapelets_khiva_Distances_squaredEuclidean(JNIEnv *env, jobject, jlong ref) {
    try {
        const jint l = 2;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        auto arr = (af_array) ref;
        af::array var = af::array(arr);

        jlong raw_pointer = 0;
        auto af_p = (af_array) raw_pointer;

        af_retain_array(&arr, var.get());
        af_retain_array(&af_p, khiva::distances::squaredEuclidean(var).get());

        tmp[0] = (jlong) arr;
        tmp[1] = (jlong) af_p;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Distances_squaredEuclidean. Unknown reason");
    }
    return nullptr;
}
