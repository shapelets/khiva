// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Calculates the kMeans algorithm.
 *
 * @param tss            Expects an input array whose dimension zero is the length of the time series (all the same) and
 *                       dimension one indicates the number of time series.
 * @brief Calculates     The clusterization based on SBD.
 * @param k              The number of means to be computed.
 * @param ref_centroids  The resulting means or centroids.
 * @param ref_labels     The resulting labels of each time series which is the closest centroid.
 * @param tolerance      The error tolerance to stop the computation of the centroids.
 * @param maxIterations  The maximum number of iterations allowed.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Clustering_kMeans(JNIEnv *env, jobject, jlong ref_tss, jint k,
                                                                       jlong ref_centroids, jlong ref_labels,
                                                                       jfloat tolerance, jint maxIterations);

/**
 * @brief Computes the kShape algorithm.
 *
 * @param tss            Expects an input array whose dimension zero is the length of the time series (all the same) and
 *                       dimension one indicates the number of time series.
 * @brief Calculates     The clusterization based on SBD.
 * @param k              The number of means to be computed.
 * @param ref_centroids  The resulting means or centroids.
 * @param ref_labels     The resulting labels of each time series which is the closest centroid.
 * @param tolerance      The error tolerance to stop the computation of the centroids.
 * @param maxIterations  The maximum number of iterations allowed.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Clustering_kShape(JNIEnv *env, jobject, jlong ref_tss, jint k,
                                                                       jlong ref_centroids, jlong ref_labels,
                                                                       jfloat tolerance, jint maxIterations);

#ifdef __cplusplus
}
#endif