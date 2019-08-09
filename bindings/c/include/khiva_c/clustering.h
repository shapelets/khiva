// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva_c/defines.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Calculates the k-means algorithm.
 *
 * [1] S. Lloyd. 1982. Least squares quantization in PCM. IEEE Transactions on Information Theory, 28, 2,
 * Pages 129-137.
 *
 * @param tss            Expects an input array whose dimension zero is the length of the time series (all the same) and
 *                       dimension one indicates the number of time series.
 * @param k              The number of means to be computed.
 * @param centroids      The resulting means or centroids.
 * @param labels         The resulting labels of each time series which is the closest centroid.
 * @param tolerance      The error tolerance to stop the computation of the centroids.
 * @param max_iterations The maximum number of iterations allowed.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void k_means(khiva_array *tss, int *k, khiva_array *centroids, khiva_array *labels, float *tolerance,
                         int *max_iterations, int *error_code, char *error_message);

/**
 * @brief Calculates the K-Shape algorithm.
 *
 * [1] John Paparrizos and Luis Gravano. 2016. k-Shape: Efficient and Accurate Clustering of Time Series.
 * SIGMOD Rec. 45, 1 (June 2016), 69-76.
 *
 * @param tss            Expects an input array whose dimension zero is the length of the time series (all the same) and
 *                       dimension one indicates the number of time series.
 * @param k              The number of means to be computed.
 * @param centroids      The resulting means or centroids.
 * @param labels         The resulting labels of each time series which is the closest centroid.
 * @param tolerance      The error tolerance to stop the computation of the centroids.
 * @param max_iterations The maximum number of iterations allowed.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void k_shape(khiva_array *tss, int *k, khiva_array *centroids, khiva_array *labels, float *tolerance,
                         int *max_iterations, int *error_code, char *error_message);

#ifdef __cplusplus
}
#endif
