// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_CORE_CLUSTERING_H
#define KHIVA_CORE_CLUSTERING_H

#include <arrayfire.h>
#include <vector>

namespace khiva
{
namespace clustering
{

/**
 * @brief Calculates the k-means algorithm.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @param k The number of means to be computed.
 * @param The resulting means or centroids.
 * @param The resulting labels of each time series which is the closest centroid.
 */
void kmeans(af::array tss, int k, af::array &means, af::array &labels);

} // namespace clustering
} // namespace khiva

#endif