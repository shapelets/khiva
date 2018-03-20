// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa/features.h>
#include <tsa/statistics.h>

af::array tsa::statistics::covariance(af::array tss, bool unbiased) {
    long n = tss.dims(0);

    af::array result = tsa::features::crossCovariance(tss, tss) * n / (n - unbiased);

    return af::reorder(result(0, span, span), 1, 2, 0, 3);
}

af::array tsa::statistics::moment(af::array tss, int k) {
    double n = tss.dims(0);

    return af::sum(af::pow(tss, k), 0) / n;
}

af::array tsa::statistics::sampleStdev(af::array tss) {
    double n = tss.dims(0);
    af::array mean = af::mean(tss, 0);

    return af::sqrt(af::sum(af::pow(tss - af::tile(mean, tss.dims(0)), 2), 0) / (n - 1));
}

af::array tsa::statistics::kurtosis(af::array tss) {
    double n = tss.dims(0);

    double a = (n * (n + 1)) / ((n - 1) * (n - 2) * (n - 3));
    af::array tssMinusMean = (tss - af::tile(af::mean(tss, 0), tss.dims(0)));
    af::array sampleStdev = af::tile(tsa::statistics::sampleStdev(tss), tss.dims(0));
    af::array b = af::sum(af::pow(tssMinusMean / sampleStdev, 4), 0);
    double c = (3 * std::pow(n - 1, 2)) / ((n - 2) * (n - 3));

    return a * b - c;
}