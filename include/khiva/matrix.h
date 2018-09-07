// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>

namespace khiva {

namespace matrix {
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
af::array slidingDotProduct(af::array q, af::array t);

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
void meanStdev(af::array t, af::array &a, long m, af::array &mean, af::array &stdev);

/**
 * @brief Calculates the moving average and standard deviation of the time series 't'.
 *
 * @param t Input time series. Multiple time series.
 * @param m Window size.
 * @param mean Output array containing the moving average.
 * @param stdev Output array containing the moving standard deviation.
 */
void meanStdev(af::array t, long m, af::array &mean, af::array &stdev);

/**
 * @brief Function to generate a band matrix of batchSizeXtsLength with the offset batchStart.
 *
 * @param m Subsequence length used to generate a band of m/2 at each side.
 * @param batchSize Size of the first dimension.
 * @param batchStart Offset of the band matrix.
 * @param tsLength Size of the second dimension of the matrix.
 * @param nTimeSeries Number of time series to generate the mask for.
 *
 * @return af::array With the resulting band.
 */
af::array generateMask(long m, long batchSize, long batchStart, long tsLength, long nTimeSeries = 1);

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
 * @param distance Resulting minimal distance.
 * @param index Position where the minimum is occurring.
 */
void calculateDistanceProfile(af::array qt, af::array a, af::array sum_q, af::array sum_q2, af::array mean_t,
                              af::array sigma_t, af::array mask, af::array &distance, af::array &index);

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
 * @param distance Resulting minimal distance.
 * @param index Position where the minimum is occurring.
 */
void calculateDistanceProfile(af::array qt, af::array a, af::array sum_q, af::array sum_q2, af::array mean_t,
                              af::array sigma_t, af::array &distance, af::array &index);

/**
 * @brief Calculates the Mueen distance.
 * @param q Array whose first dimension is the length of the query time series and the last dimension is the number of
 * time series to calculate.
 * @param t Array with the second time series in the first dimension.
 * @param a Auxiliary array computed using the meanStdev function. This array contains a precomputed fixed value to
 * speed up the distance calculation.
 * @param mean_t Moving average of 't' using a window size equal to the number of elements in 'q'.
 * @param sigma_t Moving standard deviation of 't' using a window size equal to the number of elements in 'q'.
 * @param mask Specifies the elements that should not be considered in the computation.
 * @param distance Resulting minimal distance.
 * @param index Position where the minimum is occurring.
 */
void mass(af::array q, af::array t, af::array a, af::array mean_t, af::array sigma_t, af::array mask,
          af::array &distance, af::array &index);

/**
 * @brief Calculates the Mueen distance.
 *
 * @param q Array whose first dimension is the length of the query time series and the last dimension is the number of
 * time series to calculate.
 * @param t Array with the second time series in the first dimension.
 * @param a Auxiliary array computed using the meanStdev function. This array contains a precomputed fixed value to
 * speed up the distance calculation.
 * @param mean_t Moving average of 't' using a window size equal to the number of elements in 'q'.
 * @param sigma_t Moving standard deviation of 't' using a window size equal to the number of elements in 'q'.
 * @param distance Resulting minimal distance.
 * @param index Position where the minimum is occurring.
 */
void mass(af::array q, af::array t, af::array a, af::array mean_t, af::array sigma_t, af::array &distance,
          af::array &index);

/**
 * @brief STOMP algorithm to calculate the matrix profile between 'ta' and 'tb' using a subsequence length of 'm'.
 *
 * [1] Yan Zhu, Zachary Zimmerman, Nader Shakibay Senobari, Chin-Chia Michael Yeh, Gareth Funning, Abdullah Mueen,
 * Philip Brisk and Eamonn Keogh (2016). Matrix Profile II: Exploiting a Novel Algorithm and GPUs to break the one
 * Hundred Million Barrier for Time Series Motifs and Joins. IEEE ICDM 2016.
 *
 * @param ta Query time series.
 * @param tb Reference time series.
 * @param m Subsequence length.
 * @param profile The matrix profile, which reflects the distance to the closer element of the subsequence from 'ta'
 * in 'tb'.
 * @param index The matrix profile index, which points to where the aforementioned minimum is located.
 */
void stomp(af::array ta, af::array tb, long m, af::array &profile, af::array &index);

/**
 * @brief STOMP algorithm to calculate the matrix profile between 't' and itself using a subsequence length of 'm'.
 * This method filters the trivial matches.
 *
 * [1] Yan Zhu, Zachary Zimmerman, Nader Shakibay Senobari, Chin-Chia Michael Yeh, Gareth Funning, Abdullah Mueen,
 * Philip Brisk and Eamonn Keogh (2016). Matrix Profile II: Exploiting a Novel Algorithm and GPUs to break the one
 * Hundred Million Barrier for Time Series Motifs and Joins. IEEE ICDM 2016.
 *
 * @param t Query and reference time series.
 * @param m Subsequence length.
 * @param profile The matrix profile, which reflects the distance to the closer element of the subsequence from 't' in a
 * different location of itself.
 * @param index The matrix profile index, which points to where the aforementioned minimum is located.
 */
void stomp(af::array t, long m, af::array &profile, af::array &index);

/**
 * @brief This function extracts the best N motifs from a previously calculated matrix profile.
 *
 * @param profile The matrix profile containing the minimum distance of each subsequence.
 * @param index The matrix profile index containing where each minimum occurs.
 * @param m Subsequence length value used to calculate the input matrix profile.
 * @param n Number of motifs to extract.
 * @param motifs The distance of the best N motifs.
 * @param motifsIndices The indices of the best N motifs.
 * @param subsequenceIndices The indices of the query sequences that produced the minimum reported in the motifs
 * output array.
 * @param selfJoin Indicates whether the input profile comes from a self join operation or not. It determines
 * whether the mirror similar region is included in the output or not.
 */
void findBestNMotifs(af::array profile, af::array index, long m, long n, af::array &motifs, af::array &motifsIndices,
                     af::array &subsequenceIndices, bool selfJoin = false);

/**
 * @brief This function extracts the best N discords from a previously calculated matrix profile.
 *
 * @param profile The matrix profile containing the minimum distance of each subsequence.
 * @param index The matrix profile index containing where each minimum occurs.
 * @param m Subsequence length value used to calculate the input matrix profile.
 * @param n Number of discords to extract.
 * @param discords The distance of the best N discords.
 * @param discordsIndices The indices of the best N discords.
 * @param subsequenceIndices The indices of the query sequences that produced the discords reported in the discords
 * output array.
 * @param selfJoin Indicates whether the input profile comes from a self join operation or not. It determines
 * whether the mirror similar region is included in the output or not.
 */
void findBestNDiscords(af::array profile, af::array index, long m, long n, af::array &discords,
                       af::array &discordsIndices, af::array &subsequenceIndices, bool selfJoin = false);

}  // namespace matrix
}  // namespace khiva
