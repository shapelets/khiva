// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa/library.h>
#include <tsa_jni/library.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_tsa_Library_info(JNIEnv *env, jobject thisObj) { tsa::library::backendInfo(); }

JNIEXPORT void JNICALL Java_tsa_Library_setBackend(JNIEnv *env, jobject thisObj, jint backend) {
    tsa::library::setBackend(static_cast<tsa::library::Backend>(backend));
}

JNIEXPORT void JNICALL Java_tsa_Library_getBackend(JNIEnv *env, jobject thisObj, jint backend) {
    backend = static_cast<int>(tsa::library::getBackend());
}

JNIEXPORT void JNICALL Java_tsa_Library_getBackends(JNIEnv *env, jobject thisObj, jint backends) {
    backends = tsa::library::getBackends();
}

JNIEXPORT void JNICALL Java_tsa_Library_setDevice(JNIEnv *env, jobject thisObj, jint device) {
    tsa::library::setDevice(device);
}

JNIEXPORT void JNICALL Java_tsa_Library_getDevice(JNIEnv *env, jobject thisObj, jint device) {
    device = tsa::library::getDevice();
}

#ifdef __cplusplus
}
#endif