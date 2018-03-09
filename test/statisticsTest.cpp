// Copyright (c) 2018 Grumpy Cat Software S.L.
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa.h>
#include <gtest/gtest.h>
#include <boost/math/distributions/students_t.hpp>
#include <boost/math/distributions/normal.hpp>

TEST(StatsTests, NormalCDF)
{
    // Select a few input values
    double x[] = { -3, -1, 0.0, 0.5, 2.1 };

    // Output computed by Mathematica
    // y = Phi[x]
    double y[] = { 0.0013499, 0.1586553, 0.5, 0.6914625, 0.9821356 };

    boost::math::normal dist(0.0f, 1.0f);

    int numTests = sizeof(x)/sizeof(double);

    for (int i = 0; i < numTests; ++i) {
        ASSERT_NEAR(y[i], boost::math::cdf(dist, x[i]), 1e-6);
    }
}

TEST(StatsTests, TStudentCDF)
{
    boost::math::students_t dist(5);
    
    // Select a few input values
    double x[] = { -3, -1, 0.0, 0.5, 2.1 };

    // Output computed by Mathematica
    // y = Phi[x]
    double y[] = { 0.0150496, 0.181609, 0.5, 0.680851, 0.955123 };

    int numTests = sizeof(x)/sizeof(double);

    for (int i = 0; i < numTests; ++i) {
        ASSERT_NEAR(y[i], boost::math::cdf(dist, x[i]), 1e-6);
    }
}

TEST(StatsTests, ComplementaryCDF)
{
    boost::math::students_t dist(1);
    
    double x = 3.078;

    double y = 0.099990381;

    ASSERT_NEAR(y, 1 - boost::math::cdf(dist, x), 1e-6);
}

TEST(StatsTests, Covariance)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double dataX[] = {-2.1, -1,  4.3};
    af::array x(3, dataX);
    af::array xss = af::tile(x, 1, 2);

    double dataY[] = {3,  1.1,  0.12};
    af::array y(3, dataY);
    af::array yss = af::tile(y, 1, 2);

    double dataExpected[] = {11.70999999, -4.286, -4.286, 2.14413333};

    double *result = tsa::statistics::covariance(xss, yss).host<double>();

    for(int i = 0; i < 8; i++) {
        ASSERT_NEAR(dataExpected[i%4], result[i%4], 1e-8);
    }
}