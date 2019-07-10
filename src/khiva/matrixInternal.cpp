// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "matrixInternal.h"
#include <khiva/normalization.h>
#include <cmath>

namespace {
constexpr double EPSILON = 1e-8;
}

namespace khiva {
namespace matrix {
namespace internal {

af::array slidingDotProduct(af::array q, af::array t) {
    long n = static_cast<long>(t.dims(0));
    long m = static_cast<long>(q.dims(0));

    // Flipping all the query sequences contained in q
    af::array qr = af::flip(q, 0);

    // Calculating the convolve of all the query sequences contained in qr
    // against all the time series contained in t
    af::array qt = af::real(af::convolve(t, qr, AF_CONV_EXPAND));

    return qt(af::seq(m - 1, n - 1), af::span, af::span, af::span);
}

void meanStdev(af::array t, af::array &a, long m, af::array &mean, af::array &stdev) {
    long na = static_cast<long>(t.dims(0));

    af::array tmp = af::constant(0, 1, t.dims(1), t.type());

    // Cumulative sum of all the time series contained in t
    af::array cumulative_sum_t = af::join(0, tmp, af::accum(t, 0));
    // Cumulative sum of the square of all the time series contained in t
    af::array cumulative_sum_t2 = af::join(0, tmp, af::accum(af::pow(t, 2), 0));

    af::array sum_t = cumulative_sum_t(af::seq(m, na), af::span) - cumulative_sum_t(af::seq(0, na - m), af::span);
    // Cumulative sum of the element-wise square of each subsequence of all the time series contained in t
    af::array sum_t2 = cumulative_sum_t2(af::seq(m, na), af::span) - cumulative_sum_t2(af::seq(0, na - m), af::span);

    // Mean of each subsequence of all the time series
    mean = sum_t / m;
    // Mean of the element-wise square of each subsequence of t
    af::array mean_t2 = sum_t2 / m;
    // Square of the mean
    af::array mean_t_p2 = af::pow(mean, 2);
    // Variance
    af::array sigma_t2 = mean_t2 - mean_t_p2;
    // Standard deviation 
    double eps = (sigma_t2.type() == 0) ? EPSILON * 1e4 : EPSILON; 
    af::array lessThanEpsilon = eps >= sigma_t2;
    sigma_t2 = lessThanEpsilon * lessThanEpsilon.as(sigma_t2.type()) + !lessThanEpsilon * sigma_t2;
    stdev = af::sqrt(sigma_t2);

    // Auxiliary variable to be used for the distance calculation
    a = (sum_t2 - 2 * sum_t * mean + m * mean_t_p2) / sigma_t2;
}

void meanStdev(af::array t, long m, af::array &mean, af::array &stdev) {
    long na = static_cast<long>(t.dims(0));

    af::array tmp = af::constant(0, 1, t.dims(1), t.type());

    // Cumulative sum of all the time series contained in t
    af::array cumulative_sum_t = af::join(0, tmp, af::accum(t, 0));
    // Cumulative sum of the square of all the time series contained in t
    af::array cumulative_sum_t2 = af::join(0, tmp, af::accum(af::pow(t, 2), 0));

    af::array sum_t = cumulative_sum_t(af::seq(m, na), af::span) - cumulative_sum_t(af::seq(0, na - m), af::span);
    // Cumulative sum of the element-wise square of each subsequence of all the time series contained in t
    af::array sum_t2 = cumulative_sum_t2(af::seq(m, na), af::span) - cumulative_sum_t2(af::seq(0, na - m), af::span);

    // Mean of each subsequence of all the time series
    mean = sum_t / m;
    // Mean of the element-wise square of each subsequence of t
    af::array mean_t2 = sum_t2 / m;
    // Square of the mean
    af::array mean_t_p2 = af::pow(mean, 2);
    // Variance
    af::array sigma_t2 = mean_t2 - mean_t_p2;
    // Standard deviation
    stdev = af::sqrt(sigma_t2);
}

void calculateDistances(af::array qt, af::array a, af::array sum_q, af::array sum_q2, af::array mean_t,
                        af::array sigma_t, af::array mask, af::array &distances) {
    long batchSize = static_cast<long>(qt.dims(3));
    long tsLength = static_cast<long>(qt.dims(0));
    long nTimeSeries = static_cast<long>(qt.dims(1));

    // Tiling the input data to match the batch size, the time series length and the number of time series
    af::array a_tiled = af::tile(a, 1, 1, 1, static_cast<unsigned int>(batchSize));
    af::array sum_q_tiled =
        af::tile(sum_q, static_cast<unsigned int>(tsLength), static_cast<unsigned int>(nTimeSeries));
    af::array sum_q2_tiled =
        af::tile(sum_q2, static_cast<unsigned int>(tsLength), static_cast<unsigned int>(nTimeSeries));
    af::array mean_t_tiled = af::tile(mean_t, 1, 1, 1, static_cast<unsigned int>(batchSize));
    af::array sigma_t_tiled = af::tile(sigma_t, 1, 1, 1, static_cast<unsigned int>(batchSize));

    // Required to avoid a division by zero when the standard deviation is zero
    double eps = (sigma_t_tiled.type() == 0) ? EPSILON * 1e4 : EPSILON;
    af::array lessThanEpsilon = eps >= sigma_t_tiled;
    sigma_t_tiled = lessThanEpsilon * lessThanEpsilon.as(sigma_t_tiled.type()) + !lessThanEpsilon * sigma_t_tiled;
    // Computing the distance
    af::array dist = a_tiled + (-2 * (qt - sum_q_tiled * mean_t_tiled) / sigma_t_tiled) + sum_q2_tiled;
    dist = af::sqrt(af::abs(dist));

    // The 1st dimension reflects the number of subsequences of the reference time series
    // The 2nd dimension reflects the number of query time series
    // The 3rd dimension reflects the number of reference time series
    // The 4th dimension reflects the batch size of query subsequences from the query time series
    // Reordering to match the mask band matrix dimensions
    dist = af::reorder(dist, 3, 0, 1, 2);

    // Increasing the distance using the mask band matrix to filter trivial matches
    dist += 1 / EPSILON * mask.as(qt.type());

    // The 1st dimension reflects the number of subsequences of the reference time series
    // The 2nd dimension reflects the number of reference time series
    // The 3rd dimension reflects the batch size of query subsequences from the query time series
    // The 4th dimension reflects the number of query time series
    distances = af::reorder(dist, 0, 2, 1, 3);
}

void calculateDistances(af::array qt, af::array a, af::array sum_q, af::array sum_q2, af::array mean_t,
                        af::array sigma_t, af::array &distances) {
    long batchSize = static_cast<long>(qt.dims(3));
    long tsLength = static_cast<long>(qt.dims(0));
    long nTimeSeries = static_cast<long>(qt.dims(1));

    // Tiling the input data to match the batch size, the time series length and the number of time series
    af::array a_tiled = af::tile(a, 1, 1, 1, static_cast<unsigned int>(batchSize));
    af::array sum_q_tiled =
        af::tile(sum_q, static_cast<unsigned int>(tsLength), static_cast<unsigned int>(nTimeSeries));
    af::array sum_q2_tiled =
        af::tile(sum_q2, static_cast<unsigned int>(tsLength), static_cast<unsigned int>(nTimeSeries));
    af::array mean_t_tiled = af::tile(mean_t, 1, 1, 1, static_cast<unsigned int>(batchSize));
    af::array sigma_t_tiled = af::tile(sigma_t, 1, 1, 1, static_cast<unsigned int>(batchSize));

    // Required to avoid a division by zero when the standard deviation is zero
    double eps = (sigma_t_tiled.type() == 0) ? EPSILON * 1e4 : EPSILON;
    af::array lessThanEpsilon = eps >= sigma_t_tiled;
    sigma_t_tiled = lessThanEpsilon * lessThanEpsilon.as(sigma_t_tiled.type()) + !lessThanEpsilon * sigma_t_tiled;

    // Computing the distance
    af::array dist = a_tiled + (-2 * (qt - sum_q_tiled * mean_t_tiled) / sigma_t_tiled) + sum_q2_tiled;
    dist = af::sqrt(af::abs(dist));

    // The 1st dimension reflects the number of subsequences of the reference time series.
    // The 2nd dimension reflects the number of reference time series.
    // The 3rd dimension reflects the number of query time series
    // The 4th dimension reflects the batch size of query subsequences from the query time series
    distances = af::reorder(dist, 3, 1, 0, 2);
}

bool tileIsFarFromDiagonal(long bandSize, long numRows, long row, long numColumns, long column) {
    // Check if the band would cross the tile
    return !(std::abs(row - column) < bandSize ||                     // Upper-Left corner
             std::abs(row + numRows - 1 - column) < bandSize ||       // Lower-Left corner
             std::abs(row - (column + numColumns - 1)) < bandSize ||  // Upper-Right corner
             (row - column) * (row + numRows - 1 - column) < 0 ||     // Cross the Left side
             (row - column) * (row - (column + numColumns - 1)) < 0   // Cross the Upper side
    );
}

af::array generateMask(long m, long numRows, long row, long numColumns, long column, long nTimeSeries) {
    auto bandSize = static_cast<long>(std::ceil(m / 2.0f)) + 1;
    if (tileIsFarFromDiagonal(bandSize, numRows, row, numColumns, column)) {
        return af::constant(0, numRows, numColumns, nTimeSeries);
    }

    // Expand the identity by a band in the four side of the tail.
    auto expandedSizeB = numRows + 2 * bandSize;
    auto expandedSizeA = numColumns + 2 * bandSize;
    auto identity = af::identity(expandedSizeB, expandedSizeA);

    // Check what side cross the diagonal: Upper, Left, the Upper-Left corner
    auto shifted = identity;
    auto shifting = std::abs(column - row);
    if (row > column) {
        // Crossing upper side
        shifted = af::shift(identity, 0, shifting);
        shifted(af::span, af::seq(0, shifting - 1)) = af::constant(0, expandedSizeB, shifting);
    } else if (row < column) {
        // Crossing left side
        shifted = af::shift(identity, shifting, 0);
        shifted(af::seq(0, shifting - 1), af::span) = af::constant(0, shifting, expandedSizeA);
    }
    // else: Matching the diagonal -> No shift

    auto kernel = af::constant(1, bandSize, bandSize);
    auto convolved = af::convolve2(shifted, kernel) > 0;
    auto mask = convolved(af::seq(bandSize, bandSize + numRows - 1), af::seq(bandSize, bandSize + numColumns - 1));

    return af::tile(mask, 1, 1, static_cast<unsigned int>(nTimeSeries));
}

void massWithMask(af::array q, af::array t, af::array a, af::array mean_t, af::array sigma_t, af::array mask,
                  af::array &distances) {
    // Normalizing the query sequence. q can contain query sequences from multiple series
    q = khiva::normalization::znorm(q, EPSILON);

    // Sliding dot product of the subsequence q of all the query time series against all the reference time series
    // contained in t
    af::array qt = slidingDotProduct(q, t);
    // Cumulative sum of all the elements contained in q (for each time series, that is why it is done using the first
    // dimension)
    af::array sum_q = af::sum(q, 0);
    // Cumulative sum of squares of all the elements contained in q (for each time series, that is why it is done using
    // the first dimension)
    af::array sum_q2 = af::sum(af::pow(q, 2), 0);

    // Calculate the distance and index profiles for all the combinations of query sequences and reference time series
    calculateDistances(qt, a, sum_q, sum_q2, mean_t, sigma_t, mask, distances);
}

void mass(af::array q, af::array t, af::array a, af::array mean_t, af::array sigma_t, af::array &distances) {
    // Normalizing the query sequence. q can contain query sequences from multiple series
    q = khiva::normalization::znorm(q, EPSILON);

    // Sliding dot product of the subsequence q of all the query time series against all the reference time series
    // contained in t
    af::array qt = slidingDotProduct(q, t);
    // Cumulative sum of all the elements contained in q (for each time series, that is why it is done using the first
    // dimension)
    af::array sum_q = af::sum(q, 0);
    // Cumulative sum of squares of all the elements contained in q (for each time series, that is why it is done using
    // the first dimension)
    af::array sum_q2 = af::sum(af::pow(q, 2), 0);

    // Calculate the distance and index profiles for all the combinations of query sequences and reference time series
    calculateDistances(qt, a, sum_q, sum_q2, mean_t, sigma_t, distances);
}

}  // namespace internal
}  // namespace matrix
}  // namespace khiva
