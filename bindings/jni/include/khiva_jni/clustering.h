// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <jni.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /**
 * @brief Calculates the kMeans algorithm.
 *
 * [1] S. Lloyd. 1982. Least squares quantization in PCM. IEEE Transactions on Information Theory, 28, 2,
 * Pages 129-137.
 *
 * @param tss                   Expects an input array whose dimension zero is the length of the time series (all the
 * same) and dimension one indicates the number of time series.
 * @brief Calculates            The clusterization based on SBD.
 * @param k                     The number of means to be computed.
 * @param tolerance             The error tolerance to stop the computation of the centroids.
 * @param maxIterations         The maximum number of iterations allowed.
 */
    JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Clustering_kMeans(JNIEnv *env, jobject, jlong ref_tss, jint k,
                                                                           jfloat tolerance, jint maxIterations);

    /**
 * @brief Calculates the kShape algorithm.
 *
 * [1] John Paparrizos and Luis Gravano. 2016. k-Shape: Efficient and Accurate Clustering of Time Series.
 * SIGMOD Rec. 45, 1 (June 2016), 69-76.
 *
 * @param tss                   Expects an input array whose dimension zero is the length of the time series (all the
 * same) and dimension one indicates the number of time series.
 * @brief Calculates            The clusterization based on SBD.
 * @param k                     The number of means to be computed.
 * @param tolerance             The error tolerance to stop the computation of the centroids.
 * @param maxIterations         The maximum number of iterations allowed.
 */
    JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Clustering_kShape(JNIEnv *env, jobject, jlong ref_tss, jint k,
                                                                           jfloat tolerance, jint maxIterations);

#ifdef __cplusplus
}
#endif
