// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_BINDINGJAVA_DISTANCES_H
#define KHIVA_BINDINGJAVA_DISTANCES_H

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
 * @return A reference to an upper triangular matrix where each position corresponds to the distance between
 * two time series. Diagonal elements will be zero. For example: Position row 0 column 1 records the distance between
 * time series 0 and time series 1.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Distances_euclidean(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Calculates the Dynamic Time Warping Distance.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 *
 * @return A reference to an upper triangular matrix where each position corresponds to the distance between
 * two time series. Diagonal elements will be zero. For example: Position row 0 column 1 records the
 * distance between time series 0 and time series 1.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Distances_dtw(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Calculates Hamming distances between time series.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 *
 * @return A reference to an upper triangular matrix where each position corresponds to the
 * distance between two time series. Diagonal elements will be zero. For example: Position row 0 column 1 records the
 * distance between time series 0 and time series 1.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Distances_hamming(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Calculates Manhattan distances between time series.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 *
 * @return A reference to an upper triangular matrix where each position corresponds to the distance between two
 * time series. Diagonal elements will be zero. For example: Position row 0 column 1 records the distance between time
 * series 0 and time series 1.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Distances_manhattan(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Calculates the Shape-Based distance (SBD). It computes the normalized cross-correlation and it returns 1.0
 * minus the value that maximizes the correlation value between each pair of time series.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 *
 * @return A reference to an upper triangular matrix where each position corresponds to the distance
 * between two time series. Diagonal elements will be zero. For example: Position row 0 column 1 records the distance
 * between time series 0 and time series 1.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Distances_sbd(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Calculates the non squared version of the euclidean distance.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 *
 * @return A reference to an upper triangular matrix where each position corresponds to the distance
 * between two time series. Diagonal elements will be zero. For example: Position row 0 column 1 records the distance
 * between time series 0 and time series 1.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Distances_squaredEuclidean(JNIEnv *env, jobject, jlong ref);

#ifdef __cplusplus
}
#endif

#endif
