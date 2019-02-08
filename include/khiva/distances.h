// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_CORE_DISTANCES_H
#define KHIVA_CORE_DISTANCES_H

#include <arrayfire.h>

namespace khiva {

namespace distances {

/**
 * @brief Calculates the Dynamic Time Warping Distance.
 *
 * @param a The input time series of reference.
 * @param b The input query.
 *
 * @return array The resulting distance between a and b.
 */
double dtw(std::vector<double> a, std::vector<double> b);

/**
 * @brief Calculates the Dynamic Time Warping Distance.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 *
 * @return af::array An upper triangular matrix where each position corresponds to the distance between
 * two time series. Diagonal elements will be zero. For example: Position row 0 column 1 records the
 * distance between time series 0 and time series 1.
 */
af::array dtw(af::array tss);

/**
 * @brief Calculates euclidean distances between time series.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 *
 * @return af::array An upper triangular matrix where each position corresponds to the distance between two
 * time series. Diagonal elements will be zero. For example: Position row 0 column 1 records the distance
 * between time series 0 and time series 1.
 */
af::array euclidean(af::array tss);

/**
 * @brief Calculates hamming distances between time series.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 *
 * @return af::array An upper triangular matrix where each position corresponds to the distance between two
 * time series. Diagonal elements will be zero. For example: Position row 0 column 1 records the distance
 * between time series 0 and time series 1.
 */
af::array hamming(af::array tss);

/**
 * @brief Calculates manhattan distances between time series.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 *
 * @return af::array An upper triangular matrix where each position corresponds to the distance between two
 * time series. Diagonal elements will be zero. For example: Position row 0 column 1 records the distance
 * between time series 0 and time series 1.
 */
af::array manhattan(af::array tss);

/**
 * @brief Calculates the Shape-Based distance (SBD). It computes the normalized cross-correlation and it returns 1.0
 * minus the value that maximizes the correlation value between each pair of time series.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 *
 * @return array An upper triangular matrix where each position corresponds to the distance between two time series.
 * Diagonal elements will be zero. For example: Position row 0 column 1 records the distance between time series 0
 * and time series 1.
 */
af::array sbd(af::array tss);

/**
 * @brief Calculates non squared version of the euclidean distance.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 *
 * @return array An upper triangular matrix where each position corresponds to the distance between two time series.
 * Diagonal elements will be zero. For example: Position row 0 column 1 records the distance between time series 0
 * and time series 1.
 */
af::array squaredEuclidean(af::array tss);

}  // namespace distances
}  // namespace khiva

#endif