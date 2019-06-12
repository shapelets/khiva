// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/matrix.h>
#include <khiva/normalization.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <set>
#include "libraryInternal.h"
#include "matrixInternal.h"
#include "vector.h"

#include <SCAMP/src/common.h>
#include <SCAMP/src/SCAMP.h>

namespace {
constexpr long BATCH_SIZE_SQUARED = 2048;
constexpr long BATCH_SIZE_B = 1024;
constexpr long BATCH_SIZE_A = 8192;

void getMinDistance(af::array distances, af::array &minDistances, af::array &index) {
    af::min(minDistances, index, distances, 2);
}

void stomp_batched(af::array ta, af::array tb, long m, long batch_size, af::array &profile, af::array &index) {
    long nb = static_cast<long>(tb.dims(0));

    af::array aux;
    af::array mean;
    af::array stdev;

    profile = af::array(0, ta.type());
    index = af::array(0, af::dtype::u32);

    // Computing the mean and standard deviation of all the reference time series contained in ta
    khiva::matrix::internal::meanStdev(ta, aux, m, mean, stdev);

    // The chunk size cannot be greater than the length of the input time series tb minus m + 1
    long chunkSize = std::min(nb - m + 1, batch_size);

    // Array that will hold all the query sequences for the given chunk. One per column
    af::array input = af::array(m, chunkSize, tb.dims(1), tb.type());

    for (long i = 0; i < (nb - m + 1); i += chunkSize) {
        // The iteration space cannot be greater than what is left (nb - m - i + 1)
        long iterationSize = std::min(chunkSize, nb - m - i + 1);

        // If the iteration size has changed, resize input array
        if (iterationSize != chunkSize) {
            input = af::array(m, iterationSize, tb.dims(1), tb.type());
        }

        // Store all the subsequences of all the time series from t in input
        for (long j = 0; j < m; j++) {
            input(static_cast<int>(j), af::span, af::span, af::span) =
                af::reorder(tb(af::seq(i + j, i + j + iterationSize - 1), af::span), 2, 0, 1, 3);
        }

        // For all the subsequences in input for the given batch
        gfor(af::seq idx, iterationSize) {
            af::array distances;
            af::array minDistance;
            af::array pidx;

            // Compute the distance and index profiles using Mueens algorithm for similarity search
            khiva::matrix::internal::mass(input(af::span, idx, af::span, af::span), ta, aux, mean, stdev, distances);

            // Get minimium distance and index
            getMinDistance(distances, minDistance, pidx);

            // Concat the profiles of the given chunk to the general result
            profile = join(0, profile, minDistance);
            index = join(0, index, pidx);
        }

        // The 1st dimension reflects the batch size of query subsequences from the query time series
        // The 2nd dimension reflects the number of reference time series.
        // The 3rd dimension reflects the number of query time series
        profile = af::reorder(profile, 0, 1, 3, 2);
        index = af::reorder(index, 0, 1, 3, 2);

        af::sync();
    }
}

void stomp_batched_two_levels(af::array ta, af::array tb, long m, long batch_size_b, long batch_size_a,
                              af::array &profile, af::array &index) {
    long nb = static_cast<long>(tb.dims(0));
    long na = static_cast<long>(ta.dims(0));
    long nTimeSeriesA = static_cast<long>(ta.dims(1));
    long nTimeSeriesB = static_cast<long>(tb.dims(1));

    profile = af::array(0, ta.type());
    index = af::array(0, af::dtype::u32);

    // The chunk size cannot be greater than the length of the input time series tb minus m + 1
    long chunkSizeB = std::min(nb - m + 1, batch_size_b);
    // The chunk size cannot be greater than the length of the input time series ta
    long chunkSizeA = std::min(na, batch_size_a);
    chunkSizeA = std::max(m, chunkSizeA);

    // Array that will hold all the query sequences for the given chunk. One per column
    af::array input = af::array(m, chunkSizeB, nTimeSeriesB, tb.type());

    for (long i = 0; i < (nb - m + 1); i += chunkSizeB) {
        // The iteration space cannot be greater than what is left (nb - m - i + 1)
        long iterationSizeB = std::min(chunkSizeB, nb - m - i + 1);

        // If the iteration size has changed, resize input array
        if (iterationSizeB != chunkSizeB) {
            input = af::array(m, iterationSizeB, nTimeSeriesB, tb.type());
        }

        // Store all the subsequences of all the time series from t in input
        for (long j = 0; j < m; j++) {
            input(static_cast<int>(j), af::span, af::span, af::span) =
                af::reorder(tb(af::seq(i + j, i + j + iterationSizeB - 1), af::span), 2, 0, 1, 3);
        }

        af::array distance = af::array(0, ta.type());
        af::array pidx = af::array(0, af::dtype::u32);

        long iterationSizeA = std::min(chunkSizeA, na);
        long end = 0;

        // Splitting the reference time series
        for (long start = 0; end < na - 1; start += (iterationSizeA - m + 1)) {
            // The iteration space cannot be greater than what is left (na - start)
            iterationSizeA = std::min(chunkSizeA, na - start);
            // End of the given time series chunk
            end = start + iterationSizeA - 1;

            // Reference time series chunk to compare to
            af::array taChunk = ta(af::seq(start, end), af::span);

            af::array aux;
            af::array mean;
            af::array stdev;
            // Computing the mean and standard deviation of all the reference time series contained in taChunk
            khiva::matrix::internal::meanStdev(taChunk, aux, m, mean, stdev);
            // For all the subsequences in input for the given batch
            gfor(af::seq idx, iterationSizeB) {
                af::array distancesTmp;
                af::array minDistanceTmp;
                af::array pidxTmp;

                // Compute the distance and index profiles using Mueens algorithm for similarity search
                khiva::matrix::internal::mass(input(af::span, idx, af::span, af::span), taChunk, aux, mean, stdev,
                                              distancesTmp);

                getMinDistance(distancesTmp, minDistanceTmp, pidxTmp);

                // Leaving 2nd dimension blank to join the partial results using it
                minDistanceTmp = af::reorder(minDistanceTmp, 0, 2, 1, 3);
                pidxTmp = af::reorder(pidxTmp, 0, 2, 1, 3);

                // Adding the offset of the chunk to the index profile
                pidxTmp += start;

                // Concat the profiles of the given chunk to a partial result for the batch of tb
                distance = af::join(1, distance, minDistanceTmp);
                pidx = af::join(1, pidx, pidxTmp);
            }
            af::sync();
        }

        af::array idx;
        af::array min;

        // Calculating the minimum distance of the ta chunks
        af::min(min, idx, distance, 1);

        // The second dimension is not useful anymore after calculating the min over it, moving it to the 4th dimension
        min = af::reorder(min, 0, 2, 3, 1);
        idx = af::reorder(idx, 0, 2, 3, 1);

        // Auxiliary variables to add to the index in order to obtain the real index where the minimum occurs
        af::array toSum = af::seq(0, (nTimeSeriesA * nTimeSeriesB - 1) * static_cast<double>(distance.dims(1)),
                                  static_cast<double>(distance.dims(1)));
        af::array aux = af::transpose(toSum).as(idx.type());
        aux = af::moddims(aux, 1, idx.dims(1), idx.dims(2), 1);
        aux = af::tile(aux, static_cast<unsigned int>(idx.dims(0)));

        // Adding the offset to the intermediate index
        idx += aux;

        af::dim4 dims = min.dims();
        float sliceStride = static_cast<float>(dims[0]);

        // Offset inside the batch
        af::array bidx = af::tile(af::iota(af::dim4(dims[0])), 1, static_cast<unsigned int>(idx.dims(1)),
                                  static_cast<unsigned int>(nTimeSeriesB));

        // Flat array containing the real indices to obtain from the index profile
        af::array flatIndices = af::flat(idx * sliceStride + bidx);

        // Flat index profile
        af::array flatPidx = af::flat(pidx);
        // Indexing the profile index with the flat array containing the real indices
        af::array vFromPidx = flatPidx(flatIndices);

        // Setting the actual outputs (profile and index)
        profile = af::join(0, profile, min);
        index = af::join(0, index, af::moddims(vFromPidx, af::dim4(dims[0], dims[1], dims[2], 1)));
    }
}

void stomp_parallel(af::array ta, af::array tb, long m, af::array &profile, af::array &index) {
    long nb = static_cast<long>(tb.dims(0));

    af::array aux;
    af::array mean;
    af::array stdev;

    // Computing the mean and standard deviation of all the reference time series contained in ta
    khiva::matrix::internal::meanStdev(ta, aux, m, mean, stdev);

    // If the iteration size has changed, resize input array
    af::array input = af::array(m, nb - m + 1, tb.dims(1), tb.type());

    // Store all the subsequences of all the time series from tb in input
    for (int i = 0; i < m; i++) {
        input(i, af::span, af::span, af::span) = af::reorder(tb(af::seq(i, nb - m + i), af::span), 2, 0, 1, 3);
    }

    // For all the subsequences of tb
    gfor(af::seq idx, nb - m + 1) {
        af::array distances;
        // Compute the distance and index profiles using Mueens algorithm for similarity search
        khiva::matrix::internal::mass(input(af::span, idx, af::span, af::span), ta, aux, mean, stdev, distances);

        getMinDistance(distances, profile, index);
    }

    // Moving the number of time series in tb, which is in the 4th dimension to the 3rd dimension
    profile = af::reorder(profile, 0, 1, 3, 2);
    index = af::reorder(index, 0, 1, 3, 2);

    af::sync();
}

void stomp_batched_two_levels(af::array t, long m, long batch_size_b, long batch_size_a, af::array &profile,
                              af::array &index) {
    long n = static_cast<long>(t.dims(0));
    long nTimeSeries = static_cast<long>(t.dims(1));

    profile = af::array(0, t.type());
    index = af::array(0, af::dtype::u32);

    // The chunk size cannot be greater than the length of the input time series tb minus m + 1
    long chunkSizeB = std::min(n - m + 1, batch_size_b);
    // The chunk size cannot be greater than the length of the input time series ta
    long chunkSizeA = std::min(n, batch_size_a);
    chunkSizeA = std::max(m, chunkSizeA);

    // Array that will hold all the query sequences for the given chunk. One per column
    af::array input = af::array(m, chunkSizeB, nTimeSeries, t.type());

    for (long i = 0; i < (n - m + 1); i += chunkSizeB) {
        // The iteration space cannot be greater than what is left (nb - m - i + 1)
        long iterationSizeB = std::min(chunkSizeB, n - m - i + 1);

        // If the iteration size has changed, resize input array
        if (iterationSizeB != chunkSizeB) {
            input = af::array(m, iterationSizeB, nTimeSeries, t.type());
        }

        // Store all the subsequences of all the time series from t in input
        for (long j = 0; j < m; j++) {
            input(static_cast<int>(j), af::span, af::span, af::span) =
                af::reorder(t(af::seq(i + j, i + j + iterationSizeB - 1), af::span), 2, 0, 1, 3);
        }

        af::array distance = af::array(0, t.type());
        af::array pidx = af::array(0, af::dtype::u32);

        long iterationSizeA = std::min(chunkSizeA, n);
        long end = 0;

        // Splitting the reference time series
        for (long start = 0; end < n - 1; start += (iterationSizeA - m + 1)) {
            // The iteration space cannot be greater than what is left (na - start)
            iterationSizeA = std::min(chunkSizeA, n - start);
            // End of the given time series chunk
            end = start + iterationSizeA - 1;

            // Reference time series chunk to compare to
            af::array tChunk = t(af::seq(start, end), af::span);

            af::array aux;
            af::array mean;
            af::array stdev;
            // Computing the mean and standard deviation of all the reference time series contained in taChunk
            khiva::matrix::internal::meanStdev(tChunk, aux, m, mean, stdev);
            // For all the subsequences in input for the given batch
            gfor(af::seq idx, iterationSizeB) {
                af::array distancesTmp;
                af::array minDistanceTmp;
                af::array pidxTmp;

                // Calculating the mask required to filter the trivial matches
                auto mask = khiva::matrix::internal::generateMask(m, iterationSizeB, i, iterationSizeA - m + 1, start,
                                                                  nTimeSeries);
                // Compute the distance and index profiles using Mueens algorithm for similarity search
                khiva::matrix::internal::massWithMask(input(af::span, idx, af::span, af::span), tChunk, aux, mean,
                                                      stdev, mask, distancesTmp);

                getMinDistance(distancesTmp, minDistanceTmp, pidxTmp);

                // Leaving 2nd dimension blank to join the partial results using it. Using the diag method because
                // we only want the distances of a time series with itself
                minDistanceTmp = af::reorder(af::diag(af::reorder(minDistanceTmp, 3, 1, 0, 2)), 2, 1, 0, 3);
                pidxTmp = af::reorder(af::diag(af::reorder(pidxTmp, 3, 1, 0, 2)), 2, 1, 0, 3);

                // Adding the offset of the chunk to the index profile
                pidxTmp += start;

                // Concat the profiles of the given chunk to a partial result for the batch of tb
                distance = af::join(1, distance, minDistanceTmp);
                pidx = af::join(1, pidx, pidxTmp);
            }
            af::sync();
        }

        af::array idx;
        af::array min;

        // Calculating the minimum distance of the ta chunks
        af::min(min, idx, distance, 1);

        // The second dimension is not useful anymore after calculating the min over it, moving it to the 4th dimension
        min = af::reorder(min, 0, 2, 1, 3);
        idx = af::reorder(idx, 0, 2, 1, 3);

        // Auxiliary variables to add to the index in order to obtain the real index where the minimum occurs
        af::array toSum = af::seq(0, (nTimeSeries - 1) * static_cast<double>(distance.dims(1)),
                                  static_cast<double>(distance.dims(1)));
        af::array aux = af::transpose(toSum).as(idx.type());
        aux = af::tile(aux, static_cast<unsigned int>(idx.dims(0)));

        // Adding the offset to the intermediate index
        idx += aux;

        af::dim4 dims = min.dims();
        float sliceStride = static_cast<float>(dims[0]);

        // Offset inside the batch
        af::array bidx = af::tile(af::iota(af::dim4(dims[0])), 1, static_cast<unsigned int>(nTimeSeries));

        // Flat array containing the real indices to obtain from the index profile
        af::array flatIndices = af::flat(idx * sliceStride + bidx);

        // Flat index profile
        af::array flatPidx = af::flat(pidx);
        // Indexing the profile index with the flat array containing the real indices
        af::array vFromPidx = flatPidx(flatIndices);

        // Setting the actual outputs (profile and index)
        profile = af::join(0, profile, min);
        index = af::join(0, index, af::moddims(vFromPidx, af::dim4(dims[0], dims[1])));
    }
}

void stomp_parallel(af::array t, long m, af::array &profile, af::array &index) {
    long n = static_cast<long>(t.dims(0));
    long nTimeSeries = static_cast<long>(t.dims(1));

    af::array aux;
    af::array mean;
    af::array stdev;

    // Computing the mean and standard deviation of all the reference time series contained in ta
    khiva::matrix::internal::meanStdev(t, aux, m, mean, stdev);

    // If the iteration size has changed, resize input array
    af::array input = af::array(m, n - m + 1, nTimeSeries, t.type());

    // Store all the subsequences of all the time series from tb in input
    for (int i = 0; i < m; i++) {
        input(i, af::span, af::span, af::span) = af::reorder(t(af::seq(i, n - m + i), af::span), 2, 0, 1, 3);
    }

    // Calculating the mask required to filter the trivial matches
    auto mask = khiva::matrix::internal::generateMask(m, n - m + 1, 0, n - m + 1, 0, nTimeSeries);

    // For all the subsequences of tb
    gfor(af::seq idx, n - m + 1) {
        af::array distances;
        // Compute the distance and index profiles using Mueens algorithm for similarity search
        khiva::matrix::internal::massWithMask(input(af::span, idx, af::span, af::span), t, aux, mean, stdev, mask,
                                              distances);

        getMinDistance(distances, profile, index);
    }

    // Using the diag method because
    // we only want the distances of a time series with itself
    profile = af::reorder(af::diag(af::reorder(profile, 1, 3, 0, 2)), 2, 0, 1, 3);
    index = af::reorder(af::diag(af::reorder(index, 1, 3, 0, 2)), 2, 0, 1, 3);

    af::sync();
}

/**
 * @brief Private function to determine if the given motif/discord is consecutive or not, or if it is a mirror of
 * any of the best motifs/discords.
 *
 * @param pairs Set of best motifs/discords.
 * @param pair Given motif/discord.
 * @param m Subsequence length used to calculate the matrix profile.
 * @return True if the motif/discord should be filtered and false otherwise.
 */
bool isFiltered(std::set<std::pair<unsigned int, unsigned int>> pairs, std::pair<unsigned int, unsigned int> pair,
                long m) {
    unsigned int startQ = static_cast<unsigned int>(std::max(static_cast<long>(pair.first) - m / 2, 0L));
    unsigned int startR = static_cast<unsigned int>(std::max(static_cast<long>(pair.second) - m / 2, 0L));
    unsigned int endQ = pair.first + static_cast<unsigned int>(m / 2);
    unsigned int endR = pair.second + static_cast<unsigned int>(m / 2);
    for (unsigned int i = startQ; i <= endQ; i++) {
        for (unsigned int j = startR; j <= endR; j++) {
            if (std::find(pairs.begin(), pairs.end(), std::make_pair(i, j)) != pairs.end()) {
                return true;
            }
        }
    }
    return false;
}

void findBestN(af::array profile, af::array index, long m, long n, af::array &distance, af::array &indices,
               af::array &subsequenceIndices, bool selfJoin, bool lookForMotifs) {
    std::string aux = (lookForMotifs) ? "motifs" : "discords";
    if (n > std::max(static_cast<int>(std::ceil(profile.dims(0) / std::ceil(m / 2.0f))), 1)) {
        throw std::invalid_argument("You cannot retrieve more than (L-m+1)/(m/2) " + aux +
                                    ", since there cannot be consecutive " + aux +
                                    " in m/2 before and after a given one. L refers to the time series length.");
    }

    // Repeat the profile in the second dimension
    af::array profileTiled = af::tile(profile, 1, 1, 1, 2);
    // Joining it with an array from 1 to n in order to obtain the query subsequence index later on
    af::array joined = af::join(3, index, af::range(index.dims(), -1, index.type()));
    af::array sortedDistances;
    af::array sortedIndices;

    // Sort the profile and the indices using the profile as keys
    af::sort(sortedDistances, sortedIndices, profileTiled, joined, 0, lookForMotifs);

    // Defining output variables
    // Distance of the best n
    distance = sortedDistances(af::seq(n), af::span, af::span, 0);
    // Index of the reference subsequence producing the minimum
    indices = sortedIndices(af::seq(n), af::span, af::span, 0);
    // Index of the query subsequences producing the minimum
    subsequenceIndices = sortedIndices(af::seq(n), af::span, af::span, 1);

    // For each reference time series
    for (int i = 0; i < profile.dims(1); i++) {
        // For each query time series
        for (int j = 0; j < profile.dims(2); j++) {
            // Initializing variables
            std::vector<unsigned int> mIndices(sortedIndices.dims(0));
            sortedIndices(af::span, i, j, 0).host(&mIndices[0]);
            std::vector<unsigned int> sIndices(sortedIndices.dims(0));
            sortedIndices(af::span, i, j, 1).host(&sIndices[0]);

            std::vector<std::pair<unsigned int, unsigned int>> target;
            target.reserve(mIndices.size());
            std::transform(mIndices.begin(), mIndices.end(), sIndices.begin(), std::back_inserter(target),
                           [](unsigned int a, unsigned int b) { return std::make_pair(a, b); });

            std::vector<unsigned int> resIndices(n);
            std::vector<unsigned int> resSubsequenceIndices(n);

            std::vector<int> positions;

            resIndices[0] = target[0].first;
            resSubsequenceIndices[0] = target[0].second;
            positions.push_back(0);
            std::set<std::pair<unsigned int, unsigned int>> resIndicesPairs;
            resIndicesPairs.insert(target[0]);

            // Calculate the best N motifs
            int k = 1, l = 1;
            while (l < target.size() && k < n) {
                if (!isFiltered(resIndicesPairs, target[l], m) &&
                    (!selfJoin || !isFiltered(resIndicesPairs, std::make_pair(target[l].second, target[l].first), m))) {
                    // If the distance is lower than the threshold of m/2 (and is not a mirror)
                    // Add it to the resulting set
                    resIndices[k] = target[l].first;
                    resSubsequenceIndices[k] = target[l].second;
                    resIndicesPairs.insert(target[l]);
                    positions.push_back(l);

                    // Increment the number of resulting best n so far
                    k++;
                }
                l++;
            }

            if (l >= target.size() && k < n) {
                // If we enter here, it is because there have been too many mirrors, which cannot be known a priori
                // The consecutive best n check is done at the beginning of the function
                throw std::runtime_error("Only " + std::to_string(k) + " out of the best " + std::to_string(n) + " " +
                                         aux + " can be calculated. The resulting " + std::to_string(n - k) + " " +
                                         aux + " were not included because they are mirror " + aux + ".");
            }

            // From host to device (distances, motifsIndices, subsequenceIndices)
            // Distances
            af::array distancePositions = af::array(positions.size(), &positions[0]);
            distance(af::span, i, j) = sortedDistances(distancePositions, i, j, 0);
            // Indices
            indices(af::span, i, j) = af::array(resIndices.size(), &resIndices[0]);
            // Subsequence Indices
            subsequenceIndices(af::span, i, j) = af::array(resSubsequenceIndices.size(), &resSubsequenceIndices[0]);
        }
    }
}

}  // namespace

namespace khiva {
namespace matrix {

void mass(af::array q, af::array t, af::array &distances) {
    af::array aux, mean, stdev;
    const long long n = t.dims(0);

    q = af::reorder(q, 0, 3, 2, 1);
    const long long m = q.dims(0);
    internal::meanStdev(t, aux, m, mean, stdev);
    internal::mass(q, t, aux, mean, stdev, distances);
    distances = af::reorder(distances, 2, 0, 1, 3);
}

void findBestNOccurrences(af::array q, af::array t, long n, af::array &distances, af::array &indexes) {
    if (n > t.dims(0) - q.dims(0) + 1) {
        throw std::invalid_argument("You cannot retrieve more than (L-m+1) occurrences.");
    }

    if (n < 1) {
        throw std::invalid_argument("You cannot retrieve less than one occurrences.");
    }

    af::array distancesGlobal;

    khiva::matrix::mass(q, t, distancesGlobal);

    af::array sortedDistances;
    af::array sortedIndexes;

    af::sort(sortedDistances, sortedIndexes, distancesGlobal);

    indexes = sortedIndexes(af::seq(n), af::span, af::span);
    distances = sortedDistances(af::seq(n), af::span, af::span);
}

void stomp(af::array ta, af::array tb, long m, af::array &profile, af::array &index) {
    auto batchSizeSquared = library::internal::getValueScaledToMemoryDevice(
        BATCH_SIZE_SQUARED, khiva::library::internal::Complexity::CUADRATIC);
    if (tb.dims(0) > batchSizeSquared) {
        if (ta.dims(0) > batchSizeSquared) {
            // Calculates the distance and index profiles using a double batching strategy. First by the number of query
            // sequences from tb to compare simultaneously; and second, the chunk size of the reference time series ta
            return stomp_batched_two_levels(ta, tb, m, batchSizeSquared, batchSizeSquared, profile, index);
        } else {
            // Calculates the distance and index profiles using a batching strategy by the number of query
            // sequences from tb to compare simultaneously
            return stomp_batched(ta, tb, m, batchSizeSquared, profile, index);
        }
    } else {
        // Doing it in parallel
        return stomp_parallel(ta, tb, m, profile, index);
    }
}

void stomp(af::array t, long m, af::array &profile, af::array &index) {
    const auto batchSizeSquared = library::internal::getValueScaledToMemoryDevice(
        BATCH_SIZE_SQUARED, khiva::library::internal::Complexity::CUADRATIC);

    const auto batchSizeB =
        library::internal::getValueScaledToMemoryDevice(BATCH_SIZE_B, khiva::library::internal::Complexity::CUADRATIC);

    const auto batchSizeA =
        library::internal::getValueScaledToMemoryDevice(BATCH_SIZE_A, khiva::library::internal::Complexity::CUADRATIC);
    if (t.dims(0) > batchSizeSquared) {
        // Calculates the distance and index profiles using a double batching strategy. First by the number of query
        // sequences from t to compare simultaneously; and second, the chunk size of the reference time series t
        return stomp_batched_two_levels(t, m, batchSizeB, batchSizeA, profile, index);
    } else {
        // Doing it in parallel
        return stomp_parallel(t, m, profile, index);
    }
}

void findBestNMotifs(af::array profile, af::array index, long m, long n, af::array &motifs, af::array &motifsIndices,
                     af::array &subsequenceIndices, bool selfJoin) {
    findBestN(profile, index, m, n, motifs, motifsIndices, subsequenceIndices, selfJoin, true);
}

void findBestNDiscords(af::array profile, af::array index, long m, long n, af::array &discords,
                       af::array &discordsIndices, af::array &subsequenceIndices, bool selfJoin) {
    findBestN(profile, index, m, n, discords, discordsIndices, subsequenceIndices, selfJoin, false);
}

// TODO: Check if the if statements checking the self_join flag are correct 
void InitProfileMemory(SCAMP::SCAMPArgs &args) {
  switch (args.profile_type) {
    case SCAMP::PROFILE_TYPE_1NN_INDEX: {
      SCAMP::mp_entry e;
      e.floats[0] = std::numeric_limits<float>::lowest();
      e.ints[1] = -1u;
      args.profile_a.data.emplace_back();
      args.profile_a.data[0].uint64_value.resize(
          args.timeseries_a.size() - args.window + 1, e.ulong);
      if (args.has_b) {
        args.profile_b.data.emplace_back();
        args.profile_b.data[0].uint64_value.resize(
            args.timeseries_b.size() - args.window + 1, e.ulong);
      }
    }
    case SCAMP::PROFILE_TYPE_1NN: {
      args.profile_a.data.emplace_back();
      args.profile_a.data[0].float_value.resize(
          args.timeseries_a.size() - args.window + 1,
          std::numeric_limits<float>::lowest());
      if (args.has_b) {
        args.profile_b.data.emplace_back();
        args.profile_b.data[0].float_value.resize(
            args.timeseries_b.size() - args.window + 1,
            std::numeric_limits<float>::lowest());
      }
    }
    case SCAMP::PROFILE_TYPE_SUM_THRESH: {
      args.profile_a.data.emplace_back();
      args.profile_a.data[0].double_value.resize(
          args.timeseries_a.size() - args.window + 1, 0);
      if (args.has_b) {
        args.profile_b.data.emplace_back();
        args.profile_b.data[0].double_value.resize(
            args.timeseries_b.size() - args.window + 1, 0);
      }
    }
    default:
      break;
  }
}


float convertToEuclidean(float val, uint64_t window) {
	// If there was no match, we can't do a valid conversion, just return NaN
	if (val < -1) {
		return std::numeric_limits<float>::max();
	}
	return std::sqrt(std::max(2.0 * window * (1.0 - val), 0.0));

}

std::pair<std::vector<double>, std::vector<unsigned int>> getProfileOutput(const SCAMP::Profile& p, uint64_t window) {
	std::vector<double> distances;
	std::vector<unsigned int> indexes;

	const auto& arr = p.data[0].uint64_value; 
	distances.resize(arr.size());
	indexes.resize(arr.size());

	for (int i = 0; i < arr.size(); ++i) {
		SCAMP::mp_entry e;
		e.ulong = arr[i];
		distances[i] = static_cast<double>(convertToEuclidean(e.floats[0], window));
		indexes[i] = (e.floats[0] < -1) ? -1 : e.ints[1] + 1;

		//if (FLAGS_output_pearson) {
		//	mp_out << std::setprecision(10) << e.floats[0] << std::endl;
		//} else {
		//	mp_out << std::setprecision(10)
		//		<< ConvertToEuclidean<float>(e.floats[0]) << std::endl;
		//}
		//int index;
		//// If there was no match, set index to -1
		//if (e.floats[0] < -1) {
		//	index = -1;
		//} else {
		//	index = e.ints[1] + 1;
		//}
		//mpi_out << index << std::endl;
	}
	return std::make_pair(std::move(distances), std::move(indexes));
}


std::pair<std::vector<double>, std::vector<unsigned int>> matrixProfile(std::vector<double>&& tss, long m) {
	int n_x = tss.size() - m + 1;
	int n_y = n_x;
//	int n_y;
//	if (self_join) {
//		n_y = n_x;
//	} else {
//		n_y = Tb_h.size() - FLAGS_window + 1;
//	}

	std::vector<int> devices;
#ifdef _HAS_CUDA_
	// Use all available devices
	int num_dev;
	cudaGetDeviceCount(&num_dev);
	for (int i = 0; i < num_dev; ++i) {
		devices.push_back(i);
	}
	// TODO: set numWorkersCPU as param
	const int numWorkersCPU = 0;
	auto precision = SCAMP::PRECISION_SINGLE;
#else
	// TODO: set numWorkersCPU as param
	const int numWorkersCPU = 1; 
	auto precision = SCAMP::PRECISION_DOUBLE;
#endif

	SCAMP::SCAMPArgs args;
	args.window = m;
	args.max_tile_size = 1 << 20;
	args.has_b = false;
	args.distributed_start_row = -1;
	args.distributed_start_col = -1;
	args.distance_threshold = std::numeric_limits<double>::max();
	args.computing_columns = true;
	args.computing_rows = true;
	args.profile_a.type = SCAMP::PROFILE_TYPE_1NN_INDEX;
	args.profile_b.type = SCAMP::PROFILE_TYPE_1NN_INDEX;
	args.precision_type = precision;
	args.profile_type = SCAMP::PROFILE_TYPE_1NN_INDEX;
	args.keep_rows_separate = false;
	args.is_aligned = false;
	args.timeseries_a = std::move(tss);

	InitProfileMemory(args);

	SCAMP::do_SCAMP(&args, devices, numWorkersCPU);

	return getProfileOutput(args.profile_a, args.window);
}

void matrixProfile(af::array tss, long m, af::array& profile, af::array& index) {
	if(tss.dims(2) > 1 || tss.dims(3) > 1) {
        throw std::invalid_argument("Dimension 2 o dimension 3 is bigger than 1");
	}
	
	profile = af::array(tss.dims(0) - m + 1, tss.dims(1), f64);
	index = af::array(tss.dims(0) - m + 1, tss.dims(1), u32);

	tss = tss.as(f64);
	for(dim_t tssIdx = 0; tssIdx < tss.dims(1); ++tssIdx ) {
		auto vect = khiva::vector::get<double>(tss(af::span, tssIdx));
		auto res = matrixProfile(std::move(vect), m);
		profile(af::span, tssIdx) = khiva::vector::createArray<double>(res.first);
		index(af::span, tssIdx) = khiva::vector::createArray<unsigned int>(res.second);
	}
}


}  // namespace matrix
}  // namespace khiva
