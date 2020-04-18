// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/dimensionality.h>
#include <khiva_jni/dimensionality.h>
#include <stdexcept>

jlong JNICALL Java_io_shapelets_khiva_Dimensionality_paa(JNIEnv *env, jobject, jlong ref, jint bins) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);               
        auto paa = khiva::dimensionality::PAA(arr, bins);     
        return reinterpret_cast<jlong>(new af::array(paa));
    } catch (std::invalid_argument &ia) {
        auto message = ia.what();
        auto exClass = env->FindClass("java/lang/RuntimeException");
        env->ThrowNew(exClass, message);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Dimensionality_paa. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Dimensionality_pip(JNIEnv *env, jobject, jlong ref, jint numberIPs) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto pip = khiva::dimensionality::PIP(arr, numberIPs);
        return reinterpret_cast<jlong>(new af::array(pip));
    } catch (std::invalid_argument &ia) {
        auto message = ia.what();
        auto exClass = env->FindClass("java/lang/RuntimeException");
        env->ThrowNew(exClass, message);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Dimensionality_pip. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Dimensionality_PLABottomUp(JNIEnv *env, jobject, jlong ref,
                                                                      jfloat maxError) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto pla = khiva::dimensionality::PLABottomUp(arr, maxError);
        return reinterpret_cast<jlong>(new af::array(pla));
    } catch (std::invalid_argument &ia) {
        auto message = ia.what();
        auto exClass = env->FindClass("java/lang/RuntimeException");
        env->ThrowNew(exClass, message);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Dimensionality_PLABottomUp. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Dimensionality_PLASlidingWindow(JNIEnv *env, jobject, jlong ref,
                                                                           jfloat maxError) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto pla = khiva::dimensionality::PLASlidingWindow(arr, maxError);
        return reinterpret_cast<jlong>(new af::array(pla));
    } catch (std::invalid_argument &ia) {
        auto message = ia.what();
        auto exClass = env->FindClass("java/lang/RuntimeException");
        env->ThrowNew(exClass, message);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Dimensionality_PLASlidingWindow. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Dimensionality_ramerDouglasPeucker(JNIEnv *env, jobject, jlong ref,
                                                                              jdouble epsilon) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::dimensionality::ramerDouglasPeucker(arr, epsilon);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (std::invalid_argument &ia) {
        auto message = ia.what();
        auto exClass = env->FindClass("java/lang/RuntimeException");
        env->ThrowNew(exClass, message);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Dimensionality_ramerDouglasPeucker. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Dimensionality_sax(JNIEnv *env, jobject, jlong ref, jint alphabetSize) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::dimensionality::SAX(arr, alphabetSize);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (std::invalid_argument &ia) {
        auto message = ia.what();
        auto exClass = env->FindClass("java/lang/RuntimeException");
        env->ThrowNew(exClass, message);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Dimensionality_sax. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Dimensionality_visvalingam(JNIEnv *env, jobject, jlong ref, jint numPoints) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = khiva::dimensionality::visvalingam(arr, numPoints);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (std::invalid_argument &ia) {
        auto message = ia.what();
        auto exClass = env->FindClass("java/lang/RuntimeException");
        env->ThrowNew(exClass, message);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Dimensionality_visvalingam. Unknown reason");
    }
    return 0;
}
