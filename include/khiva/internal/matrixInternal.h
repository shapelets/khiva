// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_CORE_MATRIX_INTERNAL_H
#define KHIVA_CORE_MATRIX_INTERNAL_H

#ifndef BUILDING_KHIVA
#error Internal headers cannot be included from user code
#endif

#include <khiva/defines.h>

#include <arrayfire.h>

#include <utility>
#include <vector>

namespace khiva {
namespace matrix {
namespace internal {

using DistancesVector = std::vector<double>;
using IndexesVector = std::vector<unsigned int>;
using MatrixProfilePair = std::pair<DistancesVector, IndexesVector>;
using LeftRightProfilePair = std::pair<MatrixProfilePair, MatrixProfilePair>;
using Chain = std::vector<unsigned int>;
using ChainVector = std::vector<Chain>;
using SumCorrelationsVector = std::vector<double>;

/**
 * @brief Calculates the sliding dot product of the time series 'q' against t.
 *
 * @param q Array whose first dimension is the length of the query time series  and the last dimension is the number of
 * time series to calculate.
 * @param t Array with the second time series in the first dimension.
 *
 * @return array Returns an array with as many elements as 't' in the first dimension and as many elements as the last
 * dimension of 'q' in the last dimension.
 */
KHIVAAPI af::array slidingDotProduct(af::array q, af::array t);

/**
 * @brief Calculates the moving average and standard deviation of the time series 't'.
 *
 * @param t Input time series. Multiple time series.
 * @param a Auxiliary array to be used in the function calculateDistanceProfile. Use the overloaded method without
 * this parameter.
 * @param m Window size.
 * @param mean Output array containing the moving average.
 * @param stdev Output array containing the moving standard deviation.
 */
KHIVAAPI void meanStdev(af::array t, af::array &a, long m, af::array &mean, af::array &stdev);

/**
 * @brief Calculates the moving average and standard deviation of the time series 't'.
 *
 * @param t Input time series. Multiple time series.
 * @param m Window size.
 * @param mean Output array containing the moving average.
 * @param stdev Output array containing the moving standard deviation.
 */
KHIVAAPI void meanStdev(af::array t, long m, af::array &mean, af::array &stdev);

/**
 * @brief Calculates the distance between 'q' and the time series 't', which produced the sliding. Multiple queries can
 * be computed simultaneously in the last dimension of 'q'.
 *
 * @param qt The sliding dot product of 'q' and 't'.
 * @param a Auxiliary array computed using the meanStdev function. This array contains a precomputed fixed value to
 * speed up the distance calculation.
 * @param sum_q Sum of the values contained in 'q'.
 * @param sum_q2 Sum of squaring the values contained in 'q'.
 * @param mean_t Moving average of 't' using a window size equal to the number of elements in 'q'.
 * @param sigma_t Moving standard deviation of 't' using a window size equal to the number of elements in 'q'.
 * @param mask Mask band matrix to filter the trivial match of a subsequence with itself.
 * @param distances Resulting distances.
 */
KHIVAAPI void calculateDistances(af::array qt, af::array a, af::array sum_q, af::array sum_q2, af::array mean_t,
                                 af::array sigma_t, af::array mask, af::array &distances);

/**
 * @brief Calculates the distance between 'q' and the time series 't', which produced the sliding. Multiple queries can
 * be computed simultaneously in the last dimension of 'q'.
 *
 * @param qt The sliding dot product of 'q' and 't'.
 * @param a Auxiliary array computed using the meanStdev function. This array contains a precomputed fixed value to
 * speed up the distance calculation.
 * @param sum_q Sum of the values contained in 'q'.
 * @param sum_q2 Sum of squaring the values contained in 'q'.
 * @param mean_t Moving average of 't' using a window size equal to the number of elements in 'q'.
 * @param sigma_t Moving standard deviation of 't' using a window size equal to the number of elements in 'q'.
 * @param distances Resulting distances.
 */
KHIVAAPI void calculateDistances(af::array qt, af::array a, af::array sum_q, af::array sum_q2, af::array mean_t,
                                 af::array sigma_t, af::array &distances);

/**
 * @brief Given a tile indices and sizes it returns true when tile would not be affected
 * by a identity band matrix
 *
 * @param bandSize The band size.
 * @param numRows Number of rows of the tile.
 * @param row Starting row of the tile.
 * @param numColumns Number of columns of the tile.
 * @param column Starting column of the tile.
 *
 * @return If it is far or not.
 */
KHIVAAPI bool tileIsFarFromDiagonal(long bandSize, long numRows, long row, long numColumns, long column);

/**
 * @brief Generate an identity band matrix for a given tile indices.
 *
 * @param m The query size.
 * @param numRows Number of rows of the tile.
 * @param row Starting row of the tile.
 * @param numColumns Number of columns of the tile.
 * @param column Starting column of the tile.
 * @param nTimeSeries Number of time series.
 *
 * @return The mask.
 */
KHIVAAPI af::array generateMask(long m, long numRows, long row, long numColumns, long column, long nTimeSeries = 1);

/**
 * @brief Calculates the Mueen distance.
 *
 * [1] Chin-Chia Michael Yeh, Yan Zhu, Liudmila Ulanova, Nurjahan Begum, Yifei Ding, Hoang Anh Dau, Diego Furtado Silva,
 * Abdullah Mueen, Eamonn Keogh (2016). Matrix Profile I: All Pairs Similarity Joins for Time Series: A Unifying View
 * that Includes Motifs, Discords and Shapelets. IEEE ICDM 2016.
 *
 * @param q Array whose first dimension is the length of the query time series and the last dimension is the number of
 * time series to calculate.
 * @param t Array with the second time series in the first dimension.
 * @param a Auxiliary array computed using the meanStdev function. This array contains a precomputed fixed value to
 * speed up the distance calculation.
 * @param mean_t Moving average of 't' using a window size equal to the number of elements in 'q'.
 * @param sigma_t Moving standard deviation of 't' using a window size equal to the number of elements in 'q'.
 * @param mask Specifies the elements that should not be considered in the computation.
 * @param distances Resulting distances.
 */
KHIVAAPI void massWithMask(af::array q, af::array t, af::array a, af::array mean_t, af::array sigma_t, af::array mask,
                           af::array &distances);

/**
 * @brief Mueen's Algorithm for Similarity Search.
 *
 * @param q Array whose first dimension is the length of the query time series and the last dimension is the number of
 * time series to calculate.
 * @param t Array with the second time series in the first dimension.
 * @param a Auxiliary array computed using the meanStdev function. This array contains a precomputed fixed value to
 * speed up the distance calculation.
 * @param mean_t Moving average of 't' using a window size equal to the number of elements in 'q'.
 * @param sigma_t Moving standard deviation of 't' using a window size equal to the number of elements in 'q'.
 * @param distances Resulting distances.
 */
KHIVAAPI void mass(af::array q, af::array t, af::array a, af::array mean_t, af::array sigma_t, af::array &distance);

KHIVAAPI void stomp_batched(af::array ta, af::array tb, long m, long batch_size, af::array &profile, af::array &index);

KHIVAAPI void stomp_batched_two_levels(af::array ta, af::array tb, long m, long batch_size_b, long batch_size_a,
                                       af::array &profile, af::array &index);

KHIVAAPI void stomp_parallel(af::array ta, af::array tb, long m, af::array &profile, af::array &index);

KHIVAAPI void stomp_batched_two_levels(af::array t, long m, long batch_size_b, long batch_size_a, af::array &profile,
                                       af::array &index);

KHIVAAPI void stomp_parallel(af::array t, long m, af::array &profile, af::array &index);

KHIVAAPI void findBestN(af::array profile, af::array index, long m, long n, af::array &distance, af::array &indices,
                        af::array &subsequenceIndices, bool selfJoin, bool lookForMotifs);

KHIVAAPI void scamp(af::array tss, long m, af::array &profile, af::array &index);

KHIVAAPI void scamp(af::array ta, af::array tb, long m, af::array &profile, af::array &index);

KHIVAAPI void getChains(af::array tss, long m, af::array &chains);

KHIVAAPI ChainVector extractAllChains(const IndexesVector &profileLeft, const IndexesVector &profileRight);

KHIVAAPI LeftRightProfilePair scampLR(std::vector<double> &&ta, long m);

KHIVAAPI void scampLR(af::array tss, long m, af::array &profileLeft, af::array &indexLeft, af::array &profileRight,
                      af::array &indexRight);

KHIVAAPI void scampThresh(af::array tss, long m, double threshold, af::array &sumCorrelation);

KHIVAAPI void scampThresh(af::array ta, af::array tb, long m, double threshold, af::array &sumCorrelation);

}  // namespace internal
}  // namespace matrix
}  // namespace khiva

#endif
