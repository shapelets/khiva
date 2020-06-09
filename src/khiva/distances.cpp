// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/distances.h>
#include <khiva/normalization.h>

#include <algorithm>

namespace {

double distance(double x, double y) { return std::sqrt(std::pow((x - y), 2)); }

af::array distance(const af::array &a, const af::array &bss) {
    return af::sqrt(af::pow(af::tile(a, 1, static_cast<unsigned int>(bss.dims(1))) - bss, 2));
}

af::array dtwInternal(const af::array &a, const af::array &bss) {
    auto m = a.dims(0);
    auto n = bss.dims(0);

    // Allocate the cost Matrix:
    af::array cost = af::constant(0, m, n, bss.dims(1));
    auto d = distance(a(0), bss(0, af::span));
    cost(0, 0, af::span) = af::reorder(d, 0, 2, 1, 3);

    // Calculate the first column
    for (int i = 1; i < m; i++) {
        cost(i, 0, af::span) = cost(i - 1, 0, af::span) + af::reorder(distance(a(i), bss(0, af::span)), 0, 2, 1, 3);
    }

    // Calculate the first row
    for (int j = 1; j < n; j++) {
        cost(0, j, af::span) = cost(0, j - 1, af::span) + af::reorder(distance(a(0), bss(j, af::span)), 0, 2, 1, 3);
    }

    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            cost(i, j, af::span) =
                af::min(cost(i - 1, j, af::span), af::min(cost(i, j - 1, af::span), cost(i - 1, j - 1, af::span))) +
                af::reorder(distance(a(i), bss(j, af::span)), 0, 2, 1, 3);
        }
    }
    return af::reorder(cost(m - 1, n - 1, af::span), 0, 2, 1, 3);
}

}  // namespace

double khiva::distances::dtw(const std::vector<double> &t0, const std::vector<double> &t1) {
    auto m = t0.size();
    auto n = t1.size();

    // Allocate the cost Matrix
    std::vector<std::vector<double>> cost(m, std::vector<double>(n));

    cost[0][0] = distance(t0[0], t1[0]);

    // Calculate the first column
    for (size_t i = 1; i < m; i++) {
        cost[i][0] = cost[i - 1][0] + distance(t0[i], t1[0]);
    }

    // Calculate the first row
    for (size_t j = 1; j < n; j++) {
        cost[0][j] = cost[0][j - 1] + distance(t0[0], t1[j]);
    }

    // Computing the remaining values (we could apply the wavefront parallel pattern, to compute it in parallel)
    for (size_t i = 1; i < m; i++) {
        for (size_t j = 1; j < n; j++) {
            cost[i][j] =
                std::min(cost[i - 1][j], std::min(cost[i][j - 1], cost[i - 1][j - 1])) + distance(t0[i], t1[j]);
        }
    }

    return cost[m - 1][n - 1];
}

af::array khiva::distances::dtw(const af::array &tss) {
    // get the number of time series
    auto numOfTs = tss.dims(1);
    // the result is a squared matrix of dimensions numOfTs x numOfTs
    // which is initialised as zero.
    auto result = af::constant(0, numOfTs, numOfTs, tss.type());

    // for each time series, calculate in parallel all distances
    for (dim_t currentCol = 0; currentCol < numOfTs - 1; currentCol++) {
        gfor(af::seq otherCol, currentCol + 1, static_cast<double>(numOfTs - 1)) {
            auto currentSpan = tss(af::span, currentCol);
            auto otherSpan = tss(af::span, otherCol);
            result(currentCol, otherCol) = dtwInternal(currentSpan, af::reorder(otherSpan, 0, 3, 1, 2));
        }
    }

    return result;
}

af::array khiva::distances::euclidean(const af::array &tss) {
    // simply invokes non squared version and completes with
    // an elementwise sqrt operation.
    return af::sqrt(khiva::distances::squaredEuclidean(tss));
}

af::array khiva::distances::hamming(const af::array &tss) {
    // get the number of time series
    auto numOfTs = tss.dims(1);
    // the result is a squared matrix of dimensions numOfTs x numOfTs
    // which is initialised as zero.
    auto result = af::constant(0, numOfTs, numOfTs, tss.type());

    // for each time series, calculate in parallel all distances
    for (dim_t currentCol = 0; currentCol < numOfTs - 1; currentCol++) {
        gfor(af::seq otherCol, currentCol + 1, static_cast<double>(numOfTs - 1)) {
            result(currentCol, otherCol) =
                af::sum((tss(af::span, currentCol) != tss(af::span, otherCol)).as(af::dtype::s32));
        }
    }
    return result;
}

af::array khiva::distances::manhattan(const af::array &tss) {
    // get the number of time series
    auto numOfTs = tss.dims(1);
    // the result is a squared matrix of dimensions numOfTs x numOfTs
    // which is initialised as zero.
    auto result = af::constant(0, numOfTs, numOfTs, tss.type());

    // for each time series, calculate in parallel all distances
    for (dim_t currentCol = 0; currentCol < numOfTs - 1; currentCol++) {
        gfor(af::seq otherCol, currentCol + 1, static_cast<double>(numOfTs - 1)) {
            result(currentCol, otherCol) = af::sum(af::abs(tss(af::span, currentCol) - tss(af::span, otherCol)));
        }
    }
    return result;
}

af::array khiva::distances::sbd(const af::array &tss) {
    // get the number of time series
    auto numOfTs = tss.dims(1);
    // the result is a squared matrix of dimensions numOfTs x numOfTs
    // which is initialised as zero.
    auto result = af::constant(0, numOfTs, numOfTs, tss.type());

    // for each time series, calculate in parallel all distances
    for (dim_t currentCol = 0; currentCol < numOfTs - 1; currentCol++) {
        gfor(af::seq otherCol, currentCol + 1, numOfTs - 1) {
            af::array xZNorm = khiva::normalization::znorm(tss(af::span, currentCol));
            af::array yZNorm = khiva::normalization::znorm(tss(af::span, otherCol));
            af::array xNorm = af::sqrt(af::sum(af::pow(xZNorm, 2), 0));
            af::array yNorm = af::sqrt(af::sum(af::pow(yZNorm, 2), 0));
            result(currentCol, otherCol) =
                1.0 - af::max(af::convolve(xZNorm, af::flip(yZNorm, 0), AF_CONV_EXPAND), 0) / (xNorm * yNorm);
        }
    }

    return result;
}

af::array khiva::distances::squaredEuclidean(const af::array &tss) {
    // get the number of time series
    auto numOfTs = tss.dims(1);
    // the result is a squared matrix of dimensions numOfTs x numOfTs
    // which is initialised as zero.
    auto result = af::constant(0, numOfTs, numOfTs, tss.type());

    // for each time series, calculate in parallel all distances
    for (dim_t currentCol = 0; currentCol < numOfTs - 1; currentCol++) {
        gfor(af::seq otherCol, currentCol + 1, static_cast<double>(numOfTs - 1)) {
            result(currentCol, otherCol) = af::sum(af::pow(tss(af::span, currentCol) - tss(af::span, otherCol), 2));
        }
    }

    return result;
}
