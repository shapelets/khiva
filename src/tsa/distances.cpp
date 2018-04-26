// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa/distances.h>

af::array tsa::distances::squaredEuclidean(af::array tss) {
    // get the number of time series
    auto numOfTs = tss.dims(1);
    // the result is a squared matrix of dimensions numOfTs x numOfTs
    // which is initialised as zero.
    auto result = af::constant(0, numOfTs, numOfTs, tss.type());

    // for each time series, calculate in parallel all distances
    for (auto currentCol = 0; currentCol < numOfTs - 1; currentCol++) {
        gfor(af::seq otherCol, currentCol + 1, numOfTs - 1) {
            result(currentCol, otherCol) = af::sum(af::pow(tss(af::span, currentCol) - tss(af::span, otherCol), 2));
        }
    }

    return result;
}

af::array tsa::distances::euclidean(af::array tss) {
    // simply invokes non squared version and completes with
    // an elementwise sqrt operation.
    return af::sqrt(tsa::distances::squaredEuclidean(tss));
}