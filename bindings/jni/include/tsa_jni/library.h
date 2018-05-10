// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief JNI interface to get the devices info.
 */
JNIEXPORT void JNICALL Java_com_gcatsoft_tsa_Library_info(JNIEnv *, jobject);

/**
 * @brief JNI interface to set the backend.
 *
 * @param backend The desired backend.
 */
JNIEXPORT void JNICALL Java_com_gcatsoft_tsa_Library_setBackend(JNIEnv *, jobject, jint backend);

/**
 * @brief JNI interface to get the active backend.
 *
 * @return The active backend.
 */
JNIEXPORT int JNICALL Java_com_gcatsoft_tsa_Library_getBackend(JNIEnv *, jobject);

/**
 * @brief JNI interface to get the available backends.
 *
 * @return The available backends.
 */
JNIEXPORT int JNICALL Java_com_gcatsoft_tsa_Library_getBackends(JNIEnv *, jobject);

/**
 * @brief JNI interface to set the device.
 *
 * @param device The desired device.
 */
JNIEXPORT void JNICALL Java_com_gcatsoft_tsa_Library_setDevice(JNIEnv *, jobject, jint device);

/**
 * @brief JNI interface to get the active device.
 *
 * @return The active device.
 */
JNIEXPORT int JNICALL Java_com_gcatsoft_tsa_Library_getDeviceID(JNIEnv *, jobject);

/**
 * @brief JNI interface to get the device count.
 *
 * @return The device count.
 */
JNIEXPORT int JNICALL Java_com_gcatsoft_tsa_Library_getDeviceCount(JNIEnv *, jobject);

/**
 * @brief Returns a string with the current version of the library.
 *
 * @return A byte array with the current version of the library.
 */
JNIEXPORT jbyteArray JNICALL Java_com_gcatsoft_tsa_Library_version(JNIEnv *env, jobject);

#ifdef __cplusplus
}
#endif
