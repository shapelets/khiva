// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "khiva/internal/matrixInternal.h"

#include <SCAMP/src/SCAMP.h>
#include <SCAMP/src/common.h>
#include <SCAMP/src/scamp_exception.h>
#include <khiva/internal/libraryInternal.h>
#include <khiva/internal/vectorUtil.h>
#include <khiva/library.h>
#include <khiva/normalization.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <limits>
#include <set>
#include <thread>
#include <utility>

namespace {
using namespace khiva::matrix::internal;

constexpr double EPSILON = 1e-8;

void getMinDistance(af::array distances, af::array &minDistances, af::array &index) {
    af::min(minDistances, index, distances, 2);
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

void InitProfileMemory(SCAMP::SCAMPArgs &args) {
    switch (args.profile_type) {
        case SCAMP::PROFILE_TYPE_1NN_INDEX: {
            SCAMP::mp_entry e;
            e.floats[0] = std::numeric_limits<float>::lowest();
            e.ints[1] = -1u;
            args.profile_a.data.emplace_back();
            args.profile_a.data[0].uint64_value.resize(args.timeseries_a.size() - args.window + 1, e.ulong);
            if (args.keep_rows_separate) {
                auto b_size = args.has_b ? args.timeseries_b.size() : args.timeseries_a.size();
                args.profile_b.data.emplace_back();
                args.profile_b.data[0].uint64_value.resize(b_size - args.window + 1, e.ulong);
            }
            break;
        }
        // case SCAMP::PROFILE_TYPE_SUM_THRESH: {
        //    args.profile_a.data.emplace_back();
        //    args.profile_a.data[0].double_value.resize(args.timeseries_a.size() - args.window + 1, 0);
        //    if (args.has_b) {
        //        args.profile_b.data.emplace_back();
        //        args.profile_b.data[0].double_value.resize(args.timeseries_b.size() - args.window + 1, 0);
        //    }
        //    break;
        //}
        default:
            break;
    }
}

SCAMP::SCAMPArgs getDefaultArgs() {
    SCAMP::SCAMPArgs args;
    args.max_tile_size = 1 << 20;
    args.distributed_start_row = -1;
    args.distributed_start_col = -1;
    args.distance_threshold = std::numeric_limits<double>::max();
    args.computing_columns = true;
    args.computing_rows = true;
    args.profile_a.type = SCAMP::PROFILE_TYPE_1NN_INDEX;
    args.profile_b.type = SCAMP::PROFILE_TYPE_1NN_INDEX;
    args.precision_type = SCAMP::PRECISION_DOUBLE;
    args.profile_type = SCAMP::PROFILE_TYPE_1NN_INDEX;
    args.keep_rows_separate = false;
    args.is_aligned = false;
    args.silent_mode = true;
    return args;
}

float convertToEuclidean(float val, uint64_t window) {
    // If there was no match, we can't do a valid conversion, just return NaN
    if (val < -1) {
        return std::numeric_limits<float>::max();
    }
    return std::sqrt(std::max(2.0 * window * (1.0 - val), 0.0));
}

MatrixProfilePair getProfileOutput(const SCAMP::Profile &p, uint64_t window) {
    DistancesVector distances;
    IndexesVector indexes;

    const auto &arr = p.data[0].uint64_value;
    distances.resize(arr.size());
    indexes.resize(arr.size());

    for (int i = 0; i < arr.size(); ++i) {
        SCAMP::mp_entry e;
        e.ulong = arr[i];
        distances[i] = static_cast<double>(convertToEuclidean(e.floats[0], window));
        indexes[i] = (e.floats[0] < -1) ? -1 : e.ints[1];
    }
    return std::make_pair(std::move(distances), std::move(indexes));
}

void runScamp(SCAMP::SCAMPArgs &args) {
    std::vector<int> devices;
#ifdef _HAS_CUDA_
    // Use all available devices
    int num_dev;
    cudaGetDeviceCount(&num_dev);
    for (int i = 0; i < num_dev; ++i) {
        devices.push_back(i);
    }
    // When using GPUs do not use CPU workers as they are much slower currently
    // and can cause unnecessary latency
    int numWorkersCPU = 0;
    if (khiva::library::getBackend() == khiva::library::Backend::KHIVA_BACKEND_CPU) {
        devices.clear();
        numWorkersCPU = std::thread::hardware_concurrency();
    }
#else
    int numWorkersCPU = std::thread::hardware_concurrency();
#endif

    InitProfileMemory(args);

    try {
        SCAMP::do_SCAMP(&args, devices, numWorkersCPU);
    } catch (SCAMPException &e) {
        return;
    }
}

MatrixProfilePair scamp(std::vector<double> &&tss, long m) {
    auto args = getDefaultArgs();
    args.window = m;
    args.has_b = false;
    args.timeseries_a = std::move(tss);
    runScamp(args);
    return getProfileOutput(args.profile_a, args.window);
}

MatrixProfilePair scamp(std::vector<double> &&ta, std::vector<double> &&tb, long m) {
    auto args = getDefaultArgs();
    args.window = m;
    args.has_b = true;
    args.timeseries_a = std::move(ta);
    args.timeseries_b = std::move(tb);
    runScamp(args);
    return getProfileOutput(args.profile_a, args.window);
}

void sortChains(ChainVector &chains) {
    chains.erase(std::remove_if(chains.begin(), chains.end(), [](const Chain &currChain) { return currChain.empty(); }),
                 chains.end());
    std::sort(chains.begin(), chains.end(), [](const Chain &lhs, const Chain &rhs) { return lhs.size() > rhs.size(); });
}

std::pair<std::vector<unsigned int>, std::vector<unsigned int>> buildFlattenedWithIndexes(const ChainVector &chains) {
    std::pair<std::vector<unsigned int>, std::vector<unsigned int>> retPair;
    auto &flattenChains = retPair.first;
    auto &chainIndexes = retPair.second;
    int chainIdx = 1;
    for (const auto &currChain : chains) {
        std::fill_n(std::back_inserter(chainIndexes), currChain.size(), chainIdx++);
        std::copy(currChain.begin(), currChain.end(), std::back_inserter(flattenChains));
    }
    return retPair;
}

}  // namespace

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

void scamp(af::array tss, long m, af::array &profile, af::array &index) {
    if (tss.dims(2) > 1 || tss.dims(3) > 1) {
        throw std::invalid_argument("Dimension 2 o dimension 3 is bigger than 1");
    }

    profile = af::array(tss.dims(0) - m + 1, tss.dims(1), f64);
    index = af::array(tss.dims(0) - m + 1, tss.dims(1), u32);

    tss = tss.as(f64);
    for (dim_t tssIdx = 0; tssIdx < tss.dims(1); ++tssIdx) {
        auto vect = khiva::vectorutil::get<double>(tss(af::span, tssIdx));
        auto res = ::scamp(std::move(vect), m);
        profile(af::span, tssIdx) = khiva::vectorutil::createArray<double>(res.first);
        index(af::span, tssIdx) = khiva::vectorutil::createArray<unsigned int>(res.second);
    }
}

void scamp(af::array ta, af::array tb, long m, af::array &profile, af::array &index) {
    if (ta.dims(2) > 1 || ta.dims(3) > 1 || tb.dims(2) > 1 || tb.dims(3) > 1) {
        throw std::invalid_argument("Dimension 2 o dimension 3 is bigger than 1");
    }

    profile = af::array(tb.dims(0) - m + 1, ta.dims(1), tb.dims(1), f64);
    index = af::array(tb.dims(0) - m + 1, ta.dims(1), tb.dims(1), u32);

    ta = ta.as(f64);
    tb = tb.as(f64);

    for (dim_t tbIdx = 0; tbIdx < tb.dims(1); ++tbIdx) {
        for (dim_t taIdx = 0; taIdx < ta.dims(1); ++taIdx) {
            auto vectA = khiva::vectorutil::get<double>(ta(af::span, taIdx));
            auto vectB = khiva::vectorutil::get<double>(tb(af::span, tbIdx));
            auto res = ::scamp(std::move(vectB), std::move(vectA), m);
            profile(af::span, taIdx, tbIdx) = khiva::vectorutil::createArray<double>(res.first);
            index(af::span, taIdx, tbIdx) = khiva::vectorutil::createArray<unsigned int>(res.second);
        }
    }
}

LeftRightProfilePair scampLR(std::vector<double> &&ta, long m) {
    auto args = getDefaultArgs();
    args.window = m;
    args.has_b = false;
    args.timeseries_a = std::move(ta);
    args.keep_rows_separate = true;
    runScamp(args);
    return std::make_pair(getProfileOutput(args.profile_a, args.window), getProfileOutput(args.profile_b, args.window));
}

void scampLR(af::array tss, long m, af::array &profileLeft, af::array &indexLeft, af::array &profileRight,
             af::array &indexRight) {
    if (tss.dims(2) > 1 || tss.dims(3) > 1) {
        throw std::invalid_argument("Dimension 2 o dimension 3 is bigger than 1");
    }

    profileLeft = af::array(tss.dims(0) - m + 1, tss.dims(1), f64);
    profileRight = af::array(tss.dims(0) - m + 1, tss.dims(1), f64);
    indexLeft = af::array(tss.dims(0) - m + 1, tss.dims(1), u32);
    indexRight = af::array(tss.dims(0) - m + 1, tss.dims(1), u32);

    auto typeBefore = tss.type();
    tss = tss.as(f64);
    for (dim_t tssIdx = 0; tssIdx < tss.dims(1); ++tssIdx) {
        auto vect = khiva::vectorutil::get<double>(tss(af::span, tssIdx));
        auto res = ::scampLR(std::move(vect), m);
        profileLeft(af::span, tssIdx) = khiva::vectorutil::createArray<double>(res.first.first);
        indexLeft(af::span, tssIdx) = khiva::vectorutil::createArray<unsigned int>(res.first.second);
        profileRight(af::span, tssIdx) = khiva::vectorutil::createArray<double>(res.second.first);
        indexRight(af::span, tssIdx) = khiva::vectorutil::createArray<unsigned int>(res.second.second);
    }

    auto invalidIndex = tss.dims(0);
    af::replace(indexLeft, indexLeft != std::numeric_limits<unsigned int>::max(), invalidIndex);
    af::replace(indexRight, indexRight != std::numeric_limits<unsigned int>::max(), invalidIndex);

    profileLeft = profileLeft.as(typeBefore);
    profileRight = profileRight.as(typeBefore);
}

ChainVector extractAllChains(const IndexesVector &profileLeft, const IndexesVector &profileRight) {
    ChainVector chains;
    std::vector<int> chainLenghts(profileRight.size(), 1);
    for (int anchorIdx = 0; anchorIdx < profileRight.size(); ++anchorIdx) {
        if (chainLenghts[anchorIdx] == 1) {
            chains.emplace_back();
            auto &currChain = chains.back();
            auto linkIdx = anchorIdx;
            while (linkIdx != std::numeric_limits<unsigned int>::max() && linkIdx < profileRight.size() &&
                   profileRight[linkIdx] != std::numeric_limits<unsigned int>::max() &&
                   profileLeft[profileRight[linkIdx]] == linkIdx) {
                if (currChain.empty()) {
                    currChain.emplace_back(anchorIdx);
                }
                linkIdx = profileRight[linkIdx];
                chainLenghts[linkIdx] = -1;
                chainLenghts[anchorIdx] += 1;
                currChain.emplace_back(linkIdx);
            }
        }
    }
    return chains;
}

void getChains(af::array tss, long m, af::array &chains) {
    if (tss.dims(2) > 1 || tss.dims(3) > 1) {
        throw std::invalid_argument("Dimension 2 o dimension 3 is bigger than 1");
    }

    chains = af::constant(0, tss.dims(0) - m + 1, 2, tss.dims(1), u32);

    tss = tss.as(f64);
    for (dim_t tssIdx = 0; tssIdx < tss.dims(1); ++tssIdx) {
        auto vect = khiva::vectorutil::get<double>(tss(af::span, tssIdx));
        auto res = ::scampLR(std::move(vect), m);
        auto currArrChains = extractAllChains(res.first.second, res.second.second);
        sortChains(currArrChains);
        auto flattenedIndexesPair = buildFlattenedWithIndexes(currArrChains);
        chains(af::seq(flattenedIndexesPair.first.size()), 0, tssIdx) =
            khiva::vectorutil::createArray<unsigned int>(flattenedIndexesPair.first);
        chains(af::seq(flattenedIndexesPair.second.size()), 1, tssIdx) =
            khiva::vectorutil::createArray<unsigned int>(flattenedIndexesPair.second);
    }
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

}  // namespace internal
}  // namespace matrix
}  // namespace khiva
