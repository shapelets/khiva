// Copyright (c) 2018 Grumpy Cat Software S.L.
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa.h>

af::array tsa::statistics::covariance(af::array xss, af::array yss) {
    long n = xss.dims(0);
    af::array result = af::constant(0, 2, 2, xss.dims(1), xss.type());

    //using a regular for loop since the matmul operation is not supported inside GFOR
    for(long currentCol = 0; currentCol < xss.dims(1); currentCol++) {
        af::array input = af::join(1, xss(span, currentCol), yss(span, currentCol));

        input -= af::tile(af::mean(input, 0), n, 1, 1);

        result(span, span, currentCol) = af::matmul(af::transpose(input), af::conjg(input)) / 2;
    }

    return result;
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
    af::array b = af::sum(af::pow((tss - af::tile(af::mean(tss, 0), tss.dims(0))) / af::tile(tsa::statistics::sampleStdev(tss), tss.dims(0)), 4), 0);
    double c = (3 * std::pow(n - 1, 2)) / ((n - 2) * (n - 3));

    return a * b - c;
}