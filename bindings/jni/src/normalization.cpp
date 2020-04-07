// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/normalization.h>
#include <khiva_jni/normalization.h>

jlongArray JNICALL Java_io_shapelets_khiva_Normalization_decimalScalingNorm(JNIEnv *env, jobject, jlong ref) {
    try {
        const jint l = 2;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        auto arr = (af_array) ref;
        af::array var = af::array(arr);

        jlong raw_pointer = 0;
        auto af_p = (af_array) raw_pointer;

        af_retain_array(&arr, var.get());
        af_retain_array(&af_p, khiva::normalization::decimalScalingNorm(var).get());

        tmp[0] = (jlong) arr;
        tmp[1] = (jlong) af_p;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Normalization_decimalScalingNorm. Unknown reason");
    }
    return nullptr;
}

jlong JNICALL Java_io_shapelets_khiva_Normalization_decimalScalingNormInPlace(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = (af_array) ref;
        af::array var = af::array(arr);

        khiva::normalization::decimalScalingNormInPlace(var);
        af_retain_array(&arr, var.get());
        return (jlong) arr;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Normalization_decimalScalingNormInPlace. Unknown reason");
    }
    return 0;
}

jlongArray JNICALL Java_io_shapelets_khiva_Normalization_maxMinNorm(JNIEnv *env, jobject, jlong ref, jdouble high,
                                                                    jdouble low, jdouble epsilon) {
    try {
        const jint l = 2;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        auto arr = (af_array) ref;
        af::array var = af::array(arr);

        jlong raw_pointer = 0;
        auto af_p = (af_array) raw_pointer;

        af_retain_array(&arr, var.get());
        af_retain_array(&af_p, khiva::normalization::maxMinNorm(var, high, low, epsilon).get());

        tmp[0] = (jlong) arr;
        tmp[1] = (jlong) af_p;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Normalization_maxMinNorm. Unknown reason");
    }
    return nullptr;
}

jlong JNICALL Java_io_shapelets_khiva_Normalization_maxMinNormInPlace(JNIEnv *env, jobject, jlong ref, jdouble high,
                                                                      jdouble low, jdouble epsilon) {
    try {
        auto arr = (af_array) ref;
        af::array var = af::array(arr);

        khiva::normalization::maxMinNormInPlace(var, high, low, epsilon);
        af_retain_array(&arr, var.get());
        return (jlong) arr;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in maxMinNormInPlace. Unknown reason");
    }
    return 0;
}

jlongArray JNICALL Java_io_shapelets_khiva_Normalization_meanNorm(JNIEnv *env, jobject, jlong ref) {
    try {
        const jint l = 2;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        auto arr = (af_array) ref;
        af::array var = af::array(arr);

        jlong raw_pointer = 0;
        auto af_p = (af_array) raw_pointer;

        af_retain_array(&arr, var.get());
        af_retain_array(&af_p, khiva::normalization::meanNorm(var).get());

        tmp[0] = (jlong) arr;
        tmp[1] = (jlong) af_p;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Normalization_meanNorm. Unknown reason");
    }
    return nullptr;
}

jlong JNICALL Java_io_shapelets_khiva_Normalization_meanNormInPlace(JNIEnv *env, jobject, jlong ref) {
    try {
        auto arr = (af_array) ref;
        af::array var = af::array(arr);

        khiva::normalization::meanNormInPlace(var);
        af_retain_array(&arr, var.get());
        return (jlong) arr;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Normalization_meanNormInPlace. Unknown reason");
    }
    return 0;
}

jlongArray JNICALL Java_io_shapelets_khiva_Normalization_znorm(JNIEnv *env, jobject, jlong ref, jdouble epsilon) {
    try {
        const jint l = 2;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        auto arr = (af_array) ref;
        af::array var = af::array(arr);

        jlong raw_pointer = 0;
        auto af_p = (af_array) raw_pointer;

        af_retain_array(&arr, var.get());
        af_retain_array(&af_p, khiva::normalization::znorm(var, epsilon).get());

        tmp[0] = (jlong) arr;
        tmp[1] = (jlong) af_p;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in MatrixNormalization_znorm. Unknown reason");
    }
    return nullptr;
}

jlong JNICALL Java_io_shapelets_khiva_Normalization_znormInPlace(JNIEnv *env, jobject, jlong ref, jdouble epsilon) {
    try {
        auto arr = (af_array) ref;
        af::array var = af::array(arr);

        khiva::normalization::znormInPlace(var, epsilon);
        af_retain_array(&arr, var.get());
        return (jlong) arr;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Normalization_znormInPlace. Unknown reason");
    }
    return 0;
}
