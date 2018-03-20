// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <tsa_jni/library.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_tsa_Library_info(JNIEnv *env, jobject thisObj) { af::info(); }

JNIEXPORT void JNICALL Java_tsa_Library_setBackend(JNIEnv *env, jobject thisObj, jint backend) {
    af::setBackend(static_cast<af::Backend>(backend));
}
JNIEXPORT void JNICALL Java_tsa_Library_setDevice(JNIEnv *env, jobject thisObj, jint device) { af::setDevice(device); }

#ifdef __cplusplus
}
#endif