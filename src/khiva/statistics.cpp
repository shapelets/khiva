// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/features.h>
#include <khiva/statistics.h>

af::array khiva::statistics::covariance(af::array tss, bool unbiased) {
    long n = static_cast<long>(tss.dims(0));

    af::array result = khiva::features::crossCovariance(tss, tss) * n / (n - unbiased);

    return af::reorder(result(0, af::span, af::span), 1, 2, 0, 3);
}

af::array khiva::statistics::kurtosis(af::array tss) {
    double n = static_cast<double>(tss.dims(0));

    double a = (n * (n + 1)) / ((n - 1) * (n - 2) * (n - 3));
    af::array tssMinusMean = (tss - af::tile(af::mean(tss, 0), static_cast<unsigned int>(tss.dims(0))));
    af::array sampleStdev = af::tile(khiva::statistics::sampleStdev(tss), static_cast<unsigned int>(tss.dims(0)));
    af::array b = af::sum(af::pow(tssMinusMean / sampleStdev, 4), 0);
    double c = (3 * std::pow(n - 1, 2)) / ((n - 2) * (n - 3));

    return a * b - c;
}

af::array khiva::statistics::moment(af::array tss, int k) {
    double n = static_cast<double>(tss.dims(0));

    return af::sum(af::pow(tss, k), 0) / n;
}

af::array khiva::statistics::ljungBox(af::array tss, long lags) {
    long n = tss.dims(0);
    const double e = 2;
    af::array ac = khiva::features::autoCorrelation(tss, lags + 1);
    af::array acp = af::pow(ac(af::seq(1, af::end), af::span), e);
    af::array r = af::range(acp.dims(0), acp.dims(1), acp.dims(2), acp.dims(3)) + 1;
    af::array d = acp / (n - r);
    return af::sum(d) * n * (n + 2);
}

af::array khiva::statistics::quantile(af::array tss, af::array q, float precision) {
    long n = static_cast<long>(tss.dims(0));

    af::array idx = q * (n - 1);
    af::array idxAsInt = idx.as(af::dtype::u32);

    af::array a = af::tile(idxAsInt == idx, 1, static_cast<unsigned int>(tss.dims(1))) * tss(idx, af::span);
    af::array fraction = (idx * precision) % precision / precision;

    af::array b = af::tile(idxAsInt != idx, 1, static_cast<unsigned int>(tss.dims(1))) * tss(idxAsInt, af::span) +
                  (tss(idxAsInt + 1, af::span) - tss(idxAsInt, af::span)) *
                      af::tile(fraction, 1, static_cast<unsigned int>(tss.dims(1)));
    return a + b;
}

af::array searchSorted(af::array tss, af::array qs) {
    af::array input = af::tile(tss, 1, 1, static_cast<unsigned int>(qs.dims(0)));
    af::array qsReordered = af::tile(af::reorder(qs, 2, 1, 0, 3), static_cast<unsigned int>(tss.dims(0)));

    af::array result = af::flip(af::sum(input < qsReordered, 2), 0);

    result(0, af::span) += 1;

    return result;
}

af::array khiva::statistics::quantilesCut(af::array tss, float quantiles, float precision) {
    af::array q = af::seq(0, 1, 1 / (double)quantiles);

    af::array qs = khiva::statistics::quantile(tss, q);

    af::array ss = searchSorted(tss, qs);

    af::array qcut = af::array(qs.dims(0) - 1, 2, qs.dims(1), qs.type());
    qcut(af::span, 0, af::span) =
        af::reorder(qs(af::seq(0, static_cast<double>(qs.dims(0)) - 2), af::span), 0, 2, 1, 3);
    qcut(af::span, 1, af::span) =
        af::reorder(qs(af::seq(1, static_cast<double>(qs.dims(0)) - 1), af::span), 0, 2, 1, 3);

    qcut(0, 0, af::span) -= precision;

    af::array result = af::array(tss.dims(0), 2, tss.dims(1), tss.type());

    // With a parallel GFOR we cannot index by the matrix ss. It flattens it by default
    // gfor(af::seq i, tss.dims(1)) {
    for (int i = 0; i < tss.dims(1); i++) {
        result(af::span, af::span, i) = qcut(ss(af::span, i) - 1, af::span, i);
    }

    return result;
}

af::array khiva::statistics::sampleStdev(af::array tss) {
    double n = static_cast<double>(tss.dims(0));
    af::array mean = af::mean(tss, 0);

    return af::sqrt(af::sum(af::pow(tss - af::tile(mean, static_cast<unsigned int>(tss.dims(0))), 2), 0) / (n - 1));
}

af::array khiva::statistics::skewness(af::array tss) {
    float n = static_cast<float>(tss.dims(0));
    af::array tssMinusMean = (tss - af::tile(af::mean(tss, 0), static_cast<unsigned int>(tss.dims(0))));
    af::array m3 = khiva::statistics::moment(tssMinusMean, 3);
    af::array s3 = af::pow(khiva::statistics::sampleStdev(tss), 3);
    return (std::pow(n, 2.0) / ((n - 1) * (n - 2))) * m3 / s3;
}
