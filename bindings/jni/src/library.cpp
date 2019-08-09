// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/library.h>
#include <khiva/version.h>
#include <khiva_jni/library.h>

jstring JNICALL Java_io_shapelets_khiva_Library_backendInfo(JNIEnv *env, jobject) {
    try {
        return env->NewStringUTF(khiva::library::backendInfo().c_str());
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Library_backendInfo. Unknown reason");
    }
    return NULL;
}

void JNICALL Java_io_shapelets_khiva_Library_setBackend(JNIEnv *env, jobject, jint backend) {
    try {
        khiva::library::setBackend(static_cast<khiva::library::Backend>(backend));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Library_setBackend. Unknown reason");
    }
}

int JNICALL Java_io_shapelets_khiva_Library_getBackend(JNIEnv *env, jobject) {
    try {
        return static_cast<int>(khiva::library::getBackend());
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Library_getBackend. Unknown reason");
    }
    // It shouldn't reach this point
    return -1;
}

int JNICALL Java_io_shapelets_khiva_Library_getBackends(JNIEnv *env, jobject) {
    try {
        return khiva::library::getBackends();
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Library_getBackends. Unknown reason");
    }
    // It shouldn't reach this point
    return -1;
}

void JNICALL Java_io_shapelets_khiva_Library_setDevice(JNIEnv *env, jobject, jint device) {
    try {
        khiva::library::setDevice(device);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Library_setDevice. Unknown reason");
    }
}

int JNICALL Java_io_shapelets_khiva_Library_getDeviceID(JNIEnv *env, jobject) {
    try {
        return khiva::library::getDevice();
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Library_getDeviceID. Unknown reason");
    }
    // It shouldn't reach this point
    return -1;
}

int JNICALL Java_io_shapelets_khiva_Library_getDeviceCount(JNIEnv *env, jobject) {
    try {
        return khiva::library::getDeviceCount();
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Library_getDeviceCount. Unknown reason");
    }
    // It shouldn't reach this point
    return -1;
}

void JNICALL Java_io_shapelets_khiva_Library_setDeviceMemoryInGB(JNIEnv *env, jobject, jdouble memory) {
    try {
        khiva::library::setDeviceMemoryInGB(memory);
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Library_setDeviceMemoryInGB. Unknown reason");
    }
}

jstring JNICALL Java_io_shapelets_khiva_Library_version(JNIEnv *env, jobject) {
    try {
        return env->NewStringUTF(khiva::version().c_str());
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Library_version. Unknown reason");
    }
    return NULL;
}
