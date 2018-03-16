// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <tsa.h>
#include <boost/math/distributions/normal.hpp>
#include <boost/math/distributions/students_t.hpp>

TEST(StatsTests, NormalCDF) {
    // Select a few input values
    double x[] = {-3, -1, 0.0, 0.5, 2.1};

    // Output computed by Mathematica
    // y = Phi[x]
    double y[] = {0.0013499, 0.1586553, 0.5, 0.6914625, 0.9821356};

    boost::math::normal dist(0.0f, 1.0f);

    int numTests = sizeof(x) / sizeof(double);

    for (int i = 0; i < numTests; ++i) {
        ASSERT_NEAR(y[i], boost::math::cdf(dist, x[i]), 1e-6);
    }
}

TEST(StatsTests, TStudentCDF) {
    boost::math::students_t dist(5);

    // Select a few input values
    double x[] = {-3, -1, 0.0, 0.5, 2.1};

    // Output computed by Mathematica
    // y = Phi[x]
    double y[] = {0.0150496, 0.181609, 0.5, 0.680851, 0.955123};

    int numTests = sizeof(x) / sizeof(double);

    for (int i = 0; i < numTests; ++i) {
        ASSERT_NEAR(y[i], boost::math::cdf(dist, x[i]), 1e-6);
    }
}

TEST(StatsTests, ComplementaryCDF) {
    boost::math::students_t dist(1);

    double x = 3.078;

    double y = 0.099990381;

    ASSERT_NEAR(y, 1 - boost::math::cdf(dist, x), 1e-6);
}

TEST(StatsTests, CovarianceUnbiased) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double dataX[] = {-2.1, -1, 4.3, 3, 1.1, 0.12, 3, 1.1, 0.12};
    af::array tss(3, 3, dataX);

    double dataExpected[] = {11.70999999, -4.286, -4.286,     -4.286,    2.14413333,
                             2.14413333,  -4.286, 2.14413333, 2.14413333};

    double *result = tsa::statistics::covariance(tss, true).host<double>();

    for (int i = 0; i < 9; i++) {
        ASSERT_NEAR(dataExpected[i], result[i], 1e-8);
    }
}

TEST(StatsTests, CovarianceBiased) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double dataX[] = {-2.1, -1, 4.3, 3, 1.1, 0.12, 3, 1.1, 0.12};
    af::array tss(3, 3, dataX);

    double dataExpected[] = {7.80666667, -2.85733333, -2.85733333, -2.85733333, 1.42942222,
                             1.42942222, -2.85733333, 1.42942222,  1.42942222};

    double *result = tsa::statistics::covariance(tss, false).host<double>();

    for (int i = 0; i < 9; i++) {
        ASSERT_NEAR(dataExpected[i], result[i], 1e-8);
    }
}

TEST(StatsTests, Moment) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double dataX[] = {0, 1, 2, 3, 4, 5};
    af::array x(6, dataX);
    af::array xss = af::tile(x, 1, 2);

    double dataExpected = 9.166666666;

    double *result = tsa::statistics::moment(xss, 2).host<double>();

    ASSERT_NEAR(result[0], dataExpected, 1e-9);
    ASSERT_NEAR(result[1], dataExpected, 1e-9);

    dataExpected = 163.1666666666;

    result = tsa::statistics::moment(xss, 4).host<double>();

    ASSERT_NEAR(result[0], dataExpected, 1e-9);
    ASSERT_NEAR(result[1], dataExpected, 1e-9);
}

TEST(StatsTests, SampleStdev) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {0, 1, 2, 3, 4, 5, 2, 2, 2, 20, 30, 25};
    af::array tss(6, 2, data);

    double dataExpected[] = {1.870828693, 12.988456413};

    double *result = tsa::statistics::sampleStdev(tss).host<double>();

    ASSERT_NEAR(result[0], dataExpected[0], 1e-9);
    ASSERT_NEAR(result[1], dataExpected[1], 1e-9);
}

TEST(StatsTests, Kurtosis) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {0, 1, 2, 3, 4, 5, 2, 2, 2, 20, 30, 25};
    af::array tss(6, 2, data);

    double dataExpected[] = {-1.2, -2.66226722};

    double *result = tsa::statistics::kurtosis(tss).host<double>();

    for (int i = 0; i < 2; i++) {
        ASSERT_NEAR(dataExpected[i], result[i], 1e-8);
    }
}