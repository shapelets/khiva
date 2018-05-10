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
 * @brief Calculates euclidean distances between time series.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 *
 * @return The updated reference and an upper triangular matrix where each position corresponds to the distance between
 * two time series. Diagonal elements will be zero. For example: Position row 0 column 1 records the distance between
 * time series 0 and time series 1.
 */
JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Distances_euclidean(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Calculates the Dynamic Time Warping Distance.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 *
 * @return result The updated ref and an upper triangular matrix where each position corresponds to the distance between
 * two time series. Diagonal elements will be zero. For example: Position row 0 column 1 records the
 * distance between time series 0 and time series 1.
 */
JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Distances_dtw(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Calculates Hamming distances between time series.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 *
 * @return The updated ref and an upper triangular matrix where each position corresponds to the
 * distance between two time series. Diagonal elements will be zero. For example: Position row 0 column 1 records the
 * distance between time series 0 and time series 1.
 */
JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Distances_hamming(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Calculates Manhattan distances between time series.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 *
 * @return The updated ref and an upper triangular matrix where each position corresponds to the distance between two
 * time series. Diagonal elements will be zero. For example: Position row 0 column 1 records the distance between time
 * series 0 and time series 1.
 */
JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Distances_manhattan(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Calculates the non squared version of the euclidean distance.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 *
 * @return result The updated reference and an upper triangular matrix where each position corresponds to the distance
 * between two time series. Diagonal elements will be zero. For example: Position row 0 column 1 records the distance
 * between time series 0 and time series 1.
 */
JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Distances_squaredEuclidean(JNIEnv *env, jobject, jlong ref);

#ifdef __cplusplus
}
#endif
