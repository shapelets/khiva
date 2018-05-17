// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa/distances.h>
#include <algorithm>
#include <limits>

double distance(double x, double y) { return std::sqrt(std::pow((x - y), 2)); }

double tsa::distances::dtw(std::vector<double> t0, std::vector<double> t1) {
    int m = static_cast<int>(t0.size());
    int n = static_cast<int>(t1.size());

    // Allocate the cost Matrix
    std::vector<std::vector<double>> cost(m, std::vector<double>(n));

    cost[0][0] = distance(t0[0], t1[0]);

    // Calculate the first column
    for (int i = 1; i < m; i++) {
        cost[i][0] = cost[i - 1][0] + distance(t0[i], t1[0]);
    }

    // Calculate the first row
    for (int j = 1; j < n; j++) {
        cost[0][j] = cost[0][j - 1] + distance(t0[0], t1[j]);
    }

    // Computing the remaining values (we could apply the wavefront parallel pattern, to comput it in parallel)
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            cost[i][j] =
                std::min(cost[i - 1][j], std::min(cost[i][j - 1], cost[i - 1][j - 1])) + distance(t0[i], t1[j]);
        }
    }

    return cost[m - 1][n - 1];
}

af::array distance(af::array a, af::array bss) {
    return af::sqrt(af::pow(af::tile(a, 1, static_cast<unsigned int>(bss.dims(1))) - bss, 2));
}

af::array dtwInternal(af::array a, af::array bss) {
    int m = static_cast<int>(a.dims(0));
    int n = static_cast<int>(bss.dims(0));

    // Allocate the cost Matrix:
    af::array cost = af::constant(0, m, n, bss.dims(1));
    cost(0, 0, af::span) = af::reorder(distance(a(0), bss(0, af::span)), 0, 2, 1, 3);

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

af::array tsa::distances::dtw(af::array tss) {
    // get the number of time series
    auto numOfTs = tss.dims(1);
    // the result is a squared matrix of dimensions numOfTs x numOfTs
    // which is initialised as zero.
    auto result = af::constant(0, numOfTs, numOfTs, tss.type());

    // for each time series, calculate in parallel all distances
    for (int currentCol = 0; currentCol < numOfTs - 1; currentCol++) {
        gfor(af::seq otherCol, currentCol + 1, static_cast<double>(numOfTs - 1)) {
            result(currentCol, otherCol) =
                dtwInternal(tss(af::span, currentCol), af::reorder(tss(af::span, otherCol), 0, 3, 1, 2));
        }
    }

    return result;
}

af::array tsa::distances::euclidean(af::array tss) {
    // simply invokes non squared version and completes with
    // an elementwise sqrt operation.
    return af::sqrt(tsa::distances::squaredEuclidean(tss));
}

af::array tsa::distances::hamming(af::array tss) {
    // get the number of time series
    auto numOfTs = tss.dims(1);
    // the result is a squared matrix of dimensions numOfTs x numOfTs
    // which is initialised as zero.
    auto result = af::constant(0, numOfTs, numOfTs, tss.type());

    // for each time series, calculate in parallel all distances
    for (auto currentCol = 0; currentCol < numOfTs - 1; currentCol++) {
        gfor(af::seq otherCol, currentCol + 1, static_cast<double>(numOfTs - 1)) {
            result(currentCol, otherCol) =
                af::sum((tss(af::span, currentCol) != tss(af::span, otherCol)).as(af::dtype::s32));
        }
    }
    return result;
}

af::array tsa::distances::manhattan(af::array tss) {
    // get the number of time series
    auto numOfTs = tss.dims(1);
    // the result is a squared matrix of dimensions numOfTs x numOfTs
    // which is initialised as zero.
    auto result = af::constant(0, numOfTs, numOfTs, tss.type());

    // for each time series, calculate in parallel all distances
    for (auto currentCol = 0; currentCol < numOfTs - 1; currentCol++) {
        gfor(af::seq otherCol, currentCol + 1, static_cast<double>(numOfTs - 1)) {
            result(currentCol, otherCol) = af::sum(af::abs(tss(af::span, currentCol) - tss(af::span, otherCol)));
        }
    }
    return result;
}

af::array tsa::distances::squaredEuclidean(af::array tss) {
    // get the number of time series
    auto numOfTs = tss.dims(1);
    // the result is a squared matrix of dimensions numOfTs x numOfTs
    // which is initialised as zero.
    auto result = af::constant(0, numOfTs, numOfTs, tss.type());

    // for each time series, calculate in parallel all distances
    for (auto currentCol = 0; currentCol < numOfTs - 1; currentCol++) {
        gfor(af::seq otherCol, currentCol + 1, static_cast<double>(numOfTs - 1)) {
            result(currentCol, otherCol) = af::sum(af::pow(tss(af::span, currentCol) - tss(af::span, otherCol), 2));
        }
    }

    return result;
}
