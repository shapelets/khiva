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

af::array tsa::statistics::quantile(af::array tss, af::array q, float precision) {
    long n = tss.dims(0);

    af::array idx = q * (n - 1);
    af::array idxAsInt = idx.as(af::dtype::u32);

    af::array a = af::tile(idxAsInt == idx, 1, tss.dims(1)) * tss(idx, span);
    af::array fraction = (idx * precision) % precision / precision;

    af::array b = af::tile(idxAsInt != idx, 1, tss.dims(1)) * tss(idxAsInt, span) +
                  (tss(idxAsInt + 1, span) - tss(idxAsInt, span)) * af::tile(fraction, 1, tss.dims(1));
    return a + b;
}

af::array searchSorted(af::array tss, af::array qs) {
    af::array input = af::tile(tss, 1, 1, qs.dims(0));
    af::array qsReordered = af::tile(af::reorder(qs, 2, 1, 0, 3), tss.dims(0));

    af::array result = af::flip(af::sum(input < qsReordered, 2), 0);

    result(0, span) += 1;

    return result;
}

af::array tsa::statistics::quantilesCut(af::array tss, float quantiles, float precision) {
    af::array q = af::seq(0, 1, 1 / (double)quantiles);

    af::array qs = tsa::statistics::quantile(tss, q);

    af::array ss = searchSorted(tss, qs);

    af::array qcut = af::array(qs.dims(0) - 1, 2, qs.dims(1), qs.type());
    qcut(span, 0, span) = af::reorder(qs(af::seq(0, qs.dims(0) - 2), span), 0, 2, 1, 3);
    qcut(span, 1, span) = af::reorder(qs(af::seq(1, qs.dims(0) - 1), span), 0, 2, 1, 3);

    qcut(0, 0, span) -= precision;

    af::array result = af::array(tss.dims(0), 2, tss.dims(1), tss.type());

    // With a parallel GFOR we cannot index by the matrix ss. It flattens it by default
    // gfor(af::seq i, tss.dims(1)) {
    for (int i = 0; i < tss.dims(1); i++) {
        result(span, span, i) = qcut(ss(span, i) - 1, span, i);
    }

    return result;
}