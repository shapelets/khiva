// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/library.h>
#include <khiva/version.h>
#include <khiva_jni/library.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL Java_io_shapelets_khiva_Library_backendInfo(JNIEnv * env, jobject) {
    return env->NewStringUTF(khiva::library::backendInfo().c_str());
}

JNIEXPORT void JNICALL Java_io_shapelets_khiva_Library_setBackend(JNIEnv *, jobject, jint backend) {
    khiva::library::setBackend(static_cast<khiva::library::Backend>(backend));
}

JNIEXPORT int JNICALL Java_io_shapelets_khiva_Library_getBackend(JNIEnv *, jobject) {
    return static_cast<int>(khiva::library::getBackend());
}

JNIEXPORT int JNICALL Java_io_shapelets_khiva_Library_getBackends(JNIEnv *, jobject) {
    return khiva::library::getBackends();
}

JNIEXPORT void JNICALL Java_io_shapelets_khiva_Library_setDevice(JNIEnv *, jobject, jint device) {
    khiva::library::setDevice(device);
}

JNIEXPORT int JNICALL Java_io_shapelets_khiva_Library_getDeviceID(JNIEnv *, jobject) {
    return khiva::library::getDevice();
}

JNIEXPORT int JNICALL Java_io_shapelets_khiva_Library_getDeviceCount(JNIEnv *, jobject) {
    return khiva::library::getDeviceCount();
}

JNIEXPORT jstring JNICALL Java_io_shapelets_khiva_Library_version(JNIEnv *env, jobject) {
    return env->NewStringUTF(khiva::version().c_str());
}

#ifdef __cplusplus
}
#endif
