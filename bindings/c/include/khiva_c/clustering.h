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
 * @param tss            Expects an input array whose dimension zero is the length of the time series (all the same) and
 *                       dimension one indicates the number of time series.
 * @param k              The number of means to be computed.
 * @param centroids      The resulting means or centroids.
 * @param labels         The resulting labels of each time series which is the closest centroid.
 * @param tolerance      The error tolerance to stop the computation of the centroids.
 * @param max_iterations The maximum number of iterations allowed.
 */
KHIVAAPI void k_means(khiva_array *tss, int *k, khiva_array *centroids, khiva_array *labels, float *tolerance,
                      int *max_iterations);

/**
 * @brief Calculates the K-Shape algorithm.
 *
 * @param tss            Expects an input array whose dimension zero is the length of the time series (all the same) and
 *                       dimension one indicates the number of time series.
 * @param k              The number of means to be computed.
 * @param centroids      The resulting means or centroids.
 * @param labels         The resulting labels of each time series which is the closest centroid.
 * @param tolerance      The error tolerance to stop the computation of the centroids.
 * @param max_iterations The maximum number of iterations allowed.
 */
KHIVAAPI void k_shape(khiva_array *tss, int *k, khiva_array *centroids, khiva_array *labels, float *tolerance,
                      int *max_iterations);

#ifdef __cplusplus
}
#endif
