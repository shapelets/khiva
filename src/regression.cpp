// Copyright (c) 2018 Grumpy Cat Software S.L.
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa.h>
#include <boost/math/distributions/students_t.hpp>

#define EPSILON 1e-20

void tsa::regression::linear(af::array x, af::array y, af::array &slope, af::array &intercept, af::array &rvalue, af::array &pvalue, af::array &stderrest) {
    long n = x.dims(0);

    af::array meanX = af::mean(x);
    af::array meanY = af::mean(y);

    af::array sumSquares = af::flat(tsa::statistics::covariance(x, y, true));

    af::array ssxm = sumSquares(0);
    af::array ssxym = sumSquares(1);
    af::array ssyxm = sumSquares(2);
    af::array ssym = sumSquares(3);

    af::array rNum = ssxym;

    af::array rDen = af::sqrt(ssxm * ssym);

    af::array r = af::array(1, 0.0);
    r = (rDen > 0.0) * rNum / rDen;
    r = af::min(r, 1.0);
    r = af::max(r, -1.0);
    rvalue = r;

    long df = n - 2;
    slope = rNum / ssxm;
    intercept = meanY - slope*meanX;

    boost::math::students_t dist(df);

    af::array t = r * af::sqrt(df / ((1.0 - r + EPSILON)*(1.0 + r + EPSILON)));
    //Using boost to compute the CDF of the T-Student distribution
    //It would be better to move this computation to the GPU
    double *aux = af::abs(t).host<double>();
    *aux = 2.0 * (1 - boost::math::cdf(dist, *aux));
    pvalue = af::array(1, aux);
    stderrest = af::sqrt((1 - af::pow(r, 2)) * ssym / ssxm / df);
}