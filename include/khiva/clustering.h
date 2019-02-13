// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_CORE_CLUSTERING_H
#define KHIVA_CORE_CLUSTERING_H

#include <arrayfire.h>
#include <vector>

namespace khiva {
namespace clustering {

/**
 * @brief Calculates the k-means algorithm.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @param k The number of means to be computed.
 * @param centroids The resulting means or centroids.
 * @param labels The resulting labels of each time series which is the closest centroid.
 * @param tolerance The error tolerance to stop the computation of the centroids.
 * @param maxIterations The maximum number of iterations allowed.
 */
void kMeans(af::array tss, int k, af::array &centroids, af::array &labels, float tolerance = 0.0000000001, int maxIterations = 100);

/**
 * @brief Calculates the k-shape algorithm.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @param k The number of means to be computed.
 * @param centroids The resulting means or centroids.
 * @param labels The resulting labels of each time series which is the closest centroid.
 * @param tolerance The error tolerance to stop the computation of the centroids.
 * @param maxIterations The maximum number of iterations allowed.
 */
void kShape(af::array tss, int k, af::array &centroids, af::array &labels, float tolerance = 0.0000000001, int maxIterations = 100);

}  // namespace clustering
}  // namespace khiva

#endif