// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <jni.h>

namespace tsa {

namespace matrix {

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief JNI interface of findBestNMotifs function.
 *
 * @param profile The matrix profile containing the minimum distance of each
 * subsequence
 * @param index The matrix profile index containing where each minimum occurs
 * @param lengthProfile Length of the matrix profile
 * @param n Number of motifs to extract
 * @param jMotifDistances The distance of the best N motifs
 * @param jMotifIndices The indices of the best N motifs
 * @param jSubsequenceIndices The indices of the query sequences that produced
 * the minimum reported in the motifs
 */
JNIEXPORT void JNICALL Java_tsa_Matrix_findBestNMotifs(JNIEnv *env, jobject thisObj, jdoubleArray profile,
                                                       jintArray index, jlong lengthProfile, jlong n,
                                                       jdoubleArray jMotifDistances, jintArray jMotifIndices,
                                                       jintArray jSubsequenceIndices);

/**
 * @brief JNI interface of findBestNDiscords function.
 *
 * @param profile The matrix profile containing the minimum distance of each
 * subsequence
 * @param index The matrix profile index containing where each maximum occurs
 * @param lengthProfile Length of the matrix profile
 * @param n Number of discords to extract
 * @param jDiscordDistances The distance of the best N discords
 * @param jDiscordIndices The indices of the best N discords
 * @param jSubsequenceIndices The indices of the query sequences that produced
 * the "N" bigger discords.
 */
JNIEXPORT void JNICALL Java_tsa_Matrix_findBestNDiscords(JNIEnv *env, jobject thisObj, jdoubleArray profile,
                                                         jintArray index, jlong lengthProfile, jlong n,
                                                         jdoubleArray jDiscordDistances, jintArray jDiscordIndices,
                                                         jintArray jSubsequenceIndices);

/**
 * @brief JNI interface of the STOMP algorithm.
 *
 * @param ta Jarray of doubles with the first time series values.
 * @param tb Jarray of doubles with the second time series values.
 * @param lta Jinteger with the length of the first time series.
 * @param ltb Jinteger with the length of the second time series.
 * @param m Jong with the length of the subsequence.
 * @param p initialized Jarray of doubles for storing the distance profile.
 * @param i initialized Jarray of doubles for storing the index profile.
 */
JNIEXPORT void JNICALL Java_tsa_Matrix_stomp(JNIEnv *env, jobject thisObj, jdoubleArray ta, jdoubleArray tb, jlong lta,
                                             jlong ltb, jlong m, jdoubleArray p, jintArray i);

/**
 * @brief JNI interface of the STOMP Self Join algorithm.
 *
 * @param ta Jarray of doubles with the first time series values.
 * @param lta Jinteger with the length of the first time series.
 * @param m Jlong with the length of the subsequence.
 * @param p Jarray of doubles for storing the distance profile.
 * @param i Jarray of doubles for storing the index profile.
 */
JNIEXPORT void JNICALL Java_tsa_Matrix_stompSelfJoin(JNIEnv *env, jobject thisObj, jdoubleArray ta, jlong lta, jlong m,
                                                     jdoubleArray p, jintArray i);

/**
 * @brief JNI interface to get the devices info.
 */
JNIEXPORT void JNICALL Java_tsa_Library_info(JNIEnv *env, jobject thisObj);

/**
 * @brief JNI interface to set the back-end.
 *
 * @param backend The desired back-end.
 */
JNIEXPORT void JNICALL Java_tsa_Library_setBackend(JNIEnv *env, jobject thisObj, jint backend);

/**
 * @brief JNI interface to set the device.
 *
 * @param device The desired device.
 */
JNIEXPORT void JNICALL Java_tsa_Library_setDevice(JNIEnv *env, jobject thisObj, jint device);

#ifdef __cplusplus
}
#endif
};  // namespace matrix
};  // namespace tsa