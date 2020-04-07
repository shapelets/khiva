// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_CORE_CLUSTERING_H
#define KHIVA_CORE_CLUSTERING_H

#include <arrayfire.h>
#include <khiva/defines.h>

#include <vector>

namespace khiva {
namespace clustering {

/**
 * @brief Calculates the k-means algorithm.
 *
 * [1] S. Lloyd. 1982. Least squares quantization in PCM. IEEE Transactions on Information Theory, 28, 2,
 * Pages 129-137.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @param k The number of means to be computed.
 * @param centroids The resulting means or centroids.
 * @param labels The resulting labels of each time series which is the closest centroid.
 * @param tolerance The error tolerance to stop the computation of the centroids.
 * @param maxIterations The maximum number of iterations allowed.
 */
KHIVAAPI void kMeans(const af::array &tss, int k, af::array &centroids, af::array &labels,
                     float tolerance = 0.0000000001, int maxIterations = 100);

/**
 * @brief Calculates the k-shape algorithm.
 *
 * [1] John Paparrizos and Luis Gravano. 2016. k-Shape: Efficient and Accurate Clustering of Time Series.
 * SIGMOD Rec. 45, 1 (June 2016), 69-76.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @param k The number of means to be computed.
 * @param centroids The resulting means or centroids.
 * @param labels The resulting labels of each time series which is the closest centroid.
 * @param tolerance The error tolerance to stop the computation of the centroids.
 * @param maxIterations The maximum number of iterations allowed.
 */
KHIVAAPI void kShape(const af::array &tss, int k, af::array &centroids, af::array &labels,
                     float tolerance = 0.0000000001, int maxIterations = 100);

}  // namespace clustering
}  // namespace khiva

#endif
