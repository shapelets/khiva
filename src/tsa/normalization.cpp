// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa/normalization.h>

af::array tsa::normalization::decimalScalingNorm(af::array tss) {
    auto maxAbs = af::max(af::abs(tss), 0);
    auto const10 = af::constant(10, 1, tss.dims(1));
    auto d = af::ceil(af::log10(maxAbs));
    auto divFactor = af::pow(const10, d);
    auto result = tss / af::tile(divFactor, tss.dims(0));
    return result;
}

void tsa::normalization::decimalScalingNormInPlace(af::array &tss) {
    auto maxAbs = af::max(af::abs(tss), 0);
    auto const10 = af::constant(10, 1, tss.dims(1));
    auto d = af::ceil(af::log10(maxAbs));
    auto divFactor = af::pow(const10, d);
    tss /= af::tile(divFactor, tss.dims(0));
}

af::array tsa::normalization::maxMinNorm(af::array tss, double high, double low, double epsilon) {
    auto max = af::tile(af::max(tss, 0), tss.dims(0));
    auto min = af::tile(af::min(tss, 0), tss.dims(0));
    auto scale = max - min;
    auto lessThanEpsilon = epsilon >= scale;
    scale = lessThanEpsilon * lessThanEpsilon.as(tss.type()) + !lessThanEpsilon * scale;
    return low + (((high - low) * (tss - min)) / scale);
}

void tsa::normalization::maxMinNormInPlace(af::array &tss, double high, double low, double epsilon) {
    auto max = af::tile(af::max(tss, 0), tss.dims(0));
    auto min = af::tile(af::min(tss, 0), tss.dims(0));
    auto scale = max - min;
    auto lessThanEpsilon = epsilon >= scale;
    scale = lessThanEpsilon * lessThanEpsilon.as(tss.type()) + !lessThanEpsilon * scale;
    tss -= min;
    tss *= (high - low);
    tss /= scale;
    tss += low;
}

af::array tsa::normalization::meanNorm(af::array tss) {
    auto max = af::tile(af::max(tss, 0), tss.dims(0));
    auto min = af::tile(af::min(tss, 0), tss.dims(0));
    auto mean = af::tile(af::mean(tss, 0), tss.dims(0));
    auto divider = max - min;
    auto dividing = tss - mean;
    return dividing / divider;
}

void tsa::normalization::meanNormInPlace(af::array &tss) {
    auto max = af::tile(af::max(tss, 0), tss.dims(0));
    auto min = af::tile(af::min(tss, 0), tss.dims(0));
    auto mean = af::tile(af::mean(tss, 0), tss.dims(0));
    auto divider = max - min;
    tss = tss - mean;
    tss = tss / divider;
}

af::array tsa::normalization::znorm(af::array tss, double epsilon) {
    auto mean = af::tile(af::mean(tss, 0), tss.dims(0));
    auto stdev = af::stdev(tss, 0);
    auto lessThanEpsilon = epsilon >= stdev;
    stdev = af::tile(lessThanEpsilon * lessThanEpsilon.as(tss.type()) + !lessThanEpsilon * stdev, tss.dims(0));
    return (tss - mean) / stdev;
}

void tsa::normalization::znormInPlace(af::array &tss, double epsilon) {
    auto mean = af::tile(af::mean(tss, 0), tss.dims(0));
    auto stdev = af::stdev(tss, 0);
    auto lessThanEpsilon = epsilon >= stdev;
    stdev = af::tile(lessThanEpsilon * lessThanEpsilon.as(tss.type()) + !lessThanEpsilon * stdev, tss.dims(0));
    tss -= mean;
    tss /= stdev;
}
