// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/library.h>
#include <khiva/version.h>
#include <khiva_jni/library.h>

jstring JNICALL Java_io_shapelets_khiva_Library_backendInfo(JNIEnv *env, jobject) {
    return env->NewStringUTF(khiva::library::backendInfo().c_str());
}

void JNICALL Java_io_shapelets_khiva_Library_setBackend(JNIEnv *, jobject, jint backend) {
    khiva::library::setBackend(static_cast<khiva::library::Backend>(backend));
}

int JNICALL Java_io_shapelets_khiva_Library_getBackend(JNIEnv *, jobject) {
    return static_cast<int>(khiva::library::getBackend());
}

int JNICALL Java_io_shapelets_khiva_Library_getBackends(JNIEnv *, jobject) { return khiva::library::getBackends(); }

void JNICALL Java_io_shapelets_khiva_Library_setDevice(JNIEnv *, jobject, jint device) {
    khiva::library::setDevice(device);
}

int JNICALL Java_io_shapelets_khiva_Library_getDeviceID(JNIEnv *, jobject) { return khiva::library::getDevice(); }

int JNICALL Java_io_shapelets_khiva_Library_getDeviceCount(JNIEnv *, jobject) {
    return khiva::library::getDeviceCount();
}

jstring JNICALL Java_io_shapelets_khiva_Library_version(JNIEnv *env, jobject) {
    return env->NewStringUTF(khiva::version().c_str());
}
