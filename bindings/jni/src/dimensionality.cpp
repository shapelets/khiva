// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/dimensionality.h>
#include <khiva_jni/dimensionality.h>

jlongArray JNICALL Java_io_shapelets_khiva_Dimensionality_paa(JNIEnv *env, jobject, jlong ref, jint bins) {
    try {
        const jint l = 2;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        af_array arr = (af_array) ref;
        af::array var = af::array(arr);

        jlong raw_pointer = 0;
        af_array af_p = (af_array) raw_pointer;

        char const *className = "java/lang/RuntimeException";
        jclass exClass = env->FindClass(className);

        af_retain_array(&arr, var.get());
        try {
            af_retain_array(&af_p, khiva::dimensionality::PAA(var, bins).get());
        } catch (std::invalid_argument &ia) {
            char const *message = ia.what();
            env->ThrowNew(exClass, message);
        }
        tmp[0] = (jlong) arr;
        tmp[1] = (jlong) af_p;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Dimensionality_paa. Unknown reason");
    }
    return NULL;
}

jlongArray JNICALL Java_io_shapelets_khiva_Dimensionality_pip(JNIEnv *env, jobject, jlong ref, jint numberIPs) {
    try {
        const jint l = 2;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        af_array arr = (af_array) ref;
        af::array var = af::array(arr);

        jlong raw_pointer = 0;
        af_array af_p = (af_array) raw_pointer;

        char const *className = "java/lang/RuntimeException";
        jclass exClass = env->FindClass(className);

        af_retain_array(&arr, var.get());
        try {
            af_retain_array(&af_p, khiva::dimensionality::PIP(var, numberIPs).get());
        } catch (std::invalid_argument &ia) {
            char const *message = ia.what();
            env->ThrowNew(exClass, message);
        }

        tmp[0] = (jlong) arr;
        tmp[1] = (jlong) af_p;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Dimensionality_pip. Unknown reason");
    }
    return NULL;
}

jlongArray JNICALL Java_io_shapelets_khiva_Dimensionality_PLABottomUp(JNIEnv *env, jobject, jlong ref,
                                                                      jfloat maxError) {
    try {
        const jint l = 2;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        af_array arr = (af_array) ref;
        af::array var = af::array(arr);

        jlong raw_pointer = 0;
        af_array af_p = (af_array) raw_pointer;

        char const *className = "java/lang/RuntimeException";
        jclass exClass = env->FindClass(className);

        af_retain_array(&arr, var.get());
        try {
            af_retain_array(&af_p, khiva::dimensionality::PLABottomUp(var, maxError).get());
        } catch (std::invalid_argument &ia) {
            char const *message = ia.what();
            env->ThrowNew(exClass, message);
        }

        tmp[0] = (jlong) arr;
        tmp[1] = (jlong) af_p;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Dimensionality_PLABottomUp. Unknown reason");
    }
    return NULL;
}

jlongArray JNICALL Java_io_shapelets_khiva_Dimensionality_PLASlidingWindow(JNIEnv *env, jobject, jlong ref,
                                                                           jfloat maxError) {
    try {
        const jint l = 2;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        af_array arr = (af_array) ref;
        af::array var = af::array(arr);

        jlong raw_pointer = 0;
        af_array af_p = (af_array) raw_pointer;

        char const *className = "java/lang/RuntimeException";
        jclass exClass = env->FindClass(className);

        af_retain_array(&arr, var.get());
        try {
            af_retain_array(&af_p, khiva::dimensionality::PLASlidingWindow(var, maxError).get());
        } catch (std::invalid_argument &ia) {
            char const *message = ia.what();
            env->ThrowNew(exClass, message);
        }

        tmp[0] = (jlong) arr;
        tmp[1] = (jlong) af_p;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Dimensionality_PLASlidingWindow. Unknown reason");
    }
    return NULL;
}

jlongArray JNICALL Java_io_shapelets_khiva_Dimensionality_ramerDouglasPeucker(JNIEnv *env, jobject, jlong ref,
                                                                              jdouble epsilon) {
    try {
        const jint l = 2;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        af_array arr = (af_array) ref;
        af::array var = af::array(arr);

        jlong raw_pointer = 0;
        af_array af_p = (af_array) raw_pointer;

        char const *className = "java/lang/RuntimeException";
        jclass exClass = env->FindClass(className);

        af_retain_array(&arr, var.get());
        try {
            af_retain_array(&af_p, khiva::dimensionality::ramerDouglasPeucker(var, epsilon).get());
        } catch (std::invalid_argument &ia) {
            char const *message = ia.what();
            env->ThrowNew(exClass, message);
        }

        tmp[0] = (jlong) arr;
        tmp[1] = (jlong) af_p;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Dimensionality_ramerDouglasPeucker. Unknown reason");
    }
    return NULL;
}

jlongArray JNICALL Java_io_shapelets_khiva_Dimensionality_sax(JNIEnv *env, jobject, jlong ref, jint alphabetSize) {
    try {
        const jint l = 2;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        af_array arr = (af_array) ref;
        af::array var = af::array(arr);

        jlong raw_pointer = 0;
        af_array af_p = (af_array) raw_pointer;

        char const *className = "java/lang/RuntimeException";
        jclass exClass = env->FindClass(className);

        af_retain_array(&arr, var.get());
        try {
            af_retain_array(&af_p, khiva::dimensionality::SAX(var, alphabetSize).get());
        } catch (std::invalid_argument &ia) {
            char const *message = ia.what();
            env->ThrowNew(exClass, message);
        }

        tmp[0] = (jlong) arr;
        tmp[1] = (jlong) af_p;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Dimensionality_sax. Unknown reason");
    }
    return NULL;
}

jlongArray JNICALL Java_io_shapelets_khiva_Dimensionality_visvalingam(JNIEnv *env, jobject, jlong ref, jint numPoints) {
    try {
        const jint l = 2;
        jlong tmp[l];
        jlongArray pointers = env->NewLongArray(l);

        af_array arr = (af_array) ref;
        af::array var = af::array(arr);

        jlong raw_pointer = 0;
        af_array af_p = (af_array) raw_pointer;

        char const *className = "java/lang/RuntimeException";
        jclass exClass = env->FindClass(className);

        af_retain_array(&arr, var.get());
        try {
            af_retain_array(&af_p, khiva::dimensionality::visvalingam(var, numPoints).get());
        } catch (std::invalid_argument &ia) {
            char const *message = ia.what();
            env->ThrowNew(exClass, message);
        }

        tmp[0] = (jlong) arr;
        tmp[1] = (jlong) af_p;

        env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Dimensionality_visvalingam. Unknown reason");
    }
    return NULL;
}
