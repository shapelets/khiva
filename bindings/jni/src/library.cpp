// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <string.h>
#include <tsa/library.h>
#include <tsa/version.h>
#include <tsa_jni/library.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_com_gcatsoft_tsa_Library_info(JNIEnv *env, jobject thisObj) { tsa::library::backendInfo(); }

JNIEXPORT void JNICALL Java_com_gcatsoft_tsa_Library_setBackend(JNIEnv *env, jobject thisObj, jint backend) {
    tsa::library::setBackend(static_cast<tsa::library::Backend>(backend));
}

JNIEXPORT int JNICALL Java_com_gcatsoft_tsa_Library_getBackend(JNIEnv *env, jobject thisObj) {
    return static_cast<int>(tsa::library::getBackend());
}

JNIEXPORT int JNICALL Java_com_gcatsoft_tsa_Library_getBackends(JNIEnv *env, jobject thisObj) {
    return tsa::library::getBackends();
}

JNIEXPORT void JNICALL Java_com_gcatsoft_tsa_Library_setDevice(JNIEnv *env, jobject thisObj, jint device) {
    tsa::library::setDevice(device);
}

JNIEXPORT int JNICALL Java_com_gcatsoft_tsa_Library_getDeviceID(JNIEnv *env, jobject thisObj) {
    return tsa::library::getDevice();
}

JNIEXPORT int JNICALL Java_com_gcatsoft_tsa_Library_getDeviceCount(JNIEnv *env, jobject thisObj) {
    return tsa::library::getDeviceCount();
}

JNIEXPORT jbyteArray JNICALL Java_com_gcatsoft_tsa_Library_version(JNIEnv *env, jobject thisObj) {
    const char *v = tsa::version();
    size_t l = strlen(v);
    jbyteArray result = env->NewByteArray(l);
    env->SetByteArrayRegion(result, 0, l, (jbyte *)v);

    return result;
}

#ifdef __cplusplus
}
#endif