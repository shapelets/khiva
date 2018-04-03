// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <tsa/statistics.h>
#include "tsaTest.h"

void covarianceUnbiased() {
    float dataX[] = {-2.1, -1, 4.3, 3, 1.1, 0.12, 3, 1.1, 0.12};
    af::array tss(3, 3, dataX);

    float dataExpected[] = {11.70999999, -4.286, -4.286,     -4.286,    2.14413333,
                            2.14413333,  -4.286, 2.14413333, 2.14413333};

    float *result = tsa::statistics::covariance(tss, true).host<float>();

    for (int i = 0; i < 9; i++) {
        ASSERT_NEAR(dataExpected[i], result[i], EPSILON);
    }
}

void covarianceBiased() {
    float dataX[] = {-2.1, -1, 4.3, 3, 1.1, 0.12, 3, 1.1, 0.12};
    af::array tss(3, 3, dataX);

    float dataExpected[] = {7.80666667, -2.85733333, -2.85733333, -2.85733333, 1.42942222,
                            1.42942222, -2.85733333, 1.42942222,  1.42942222};

    float *result = tsa::statistics::covariance(tss, false).host<float>();

    for (int i = 0; i < 9; i++) {
        ASSERT_NEAR(dataExpected[i], result[i], EPSILON);
    }
}

void moment() {
    float dataX[] = {0, 1, 2, 3, 4, 5};
    af::array x(6, dataX);
    af::array xss = af::tile(x, 1, 2);

    float dataExpected = 9.166666666;

    float *result = tsa::statistics::moment(xss, 2).host<float>();

    ASSERT_NEAR(result[0], dataExpected, EPSILON);
    ASSERT_NEAR(result[1], dataExpected, EPSILON);

    dataExpected = 163.1666666666;

    result = tsa::statistics::moment(xss, 4).host<float>();

    ASSERT_NEAR(result[0], dataExpected, EPSILON * 1e2);
    ASSERT_NEAR(result[1], dataExpected, EPSILON * 1e2);
}

void sampleStdev() {
    float data[] = {0, 1, 2, 3, 4, 5, 2, 2, 2, 20, 30, 25};
    af::array tss(6, 2, data);

    float dataExpected[] = {1.870828693, 12.988456413};

    float *result = tsa::statistics::sampleStdev(tss).host<float>();

    ASSERT_NEAR(result[0], dataExpected[0], EPSILON);
    ASSERT_NEAR(result[1], dataExpected[1], EPSILON);
}

void kurtosis() {
    float data[] = {0, 1, 2, 3, 4, 5, 2, 2, 2, 20, 30, 25};
    af::array tss(6, 2, data);

    float dataExpected[] = {-1.2, -2.66226722};

    float *result = tsa::statistics::kurtosis(tss).host<float>();

    for (int i = 0; i < 2; i++) {
        ASSERT_NEAR(dataExpected[i], result[i], EPSILON * 1e2);
    }
}

void quantile() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(6, 2, data);

    float quantiles[] = {0.1, 0.2};

    af::array q = af::array(2, quantiles);

    float *calculated = tsa::statistics::quantile(tss, q).host<float>();

    float expected[] = {0.5, 1.0, 6.5, 7.0};

    ASSERT_EQ(calculated[0], expected[0]);
    ASSERT_EQ(calculated[1], expected[1]);
}

void quantilesCut2() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(6, 2, data);

    float quantiles = 2;

    af::array result = af::transpose(tsa::statistics::quantilesCut(tss, quantiles));

    float *calculated = result.host<float>();

    float expected[] = {-0.00000001, 2.5, -0.00000001, 2.5, -0.00000001, 2.5, 2.5, 5.0,  2.5, 5.0,  2.5, 5.0,
                        6.0,         8.5, 6.0,         8.5, 6.0,         8.5, 8.5, 11.0, 8.5, 11.0, 8.5, 11.0};

    for (int i = 0; i < 24; i++) {
        ASSERT_NEAR(expected[i], calculated[i], EPSILON);
    }
}

void quantilesCut3() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(6, 2, data);

    float quantiles = 3;

    af::array result = af::transpose(tsa::statistics::quantilesCut(tss, quantiles));

    float *calculated = result.host<float>();

    float expected[] = {-0.00000001, 1.66666667, -0.00000001, 1.6666667, 1.6666667, 3.3333333,  1.6666667, 3.3333333,
                        3.3333333,   5.0,        3.3333333,   5.0,       5.9999999, 7.66666667, 5.9999999, 7.6666667,
                        7.6666667,   9.3333333,  7.6666667,   9.3333333, 9.3333333, 11.0,       9.3333333, 11.0};

    for (int i = 0; i < 24; i++) {
        ASSERT_NEAR(expected[i], calculated[i], EPSILON);
    }
}

void quantilesCut7() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(6, 2, data);

    float quantiles = 7;

    af::array result = af::transpose(tsa::statistics::quantilesCut(tss, quantiles));

    float *calculated = result.host<float>();

    float expected[] = {0,         0.7142857, 0.7142857, 1.4285715, 1.4285715, 2.1428573,  2.8571429,  3.5714288,
                        3.5714288, 4.2857146, 4.2857146, 5,         5.9999999, 6.7142857,  6.7142857,  7.4285715,
                        7.4285715, 8.1428573, 8.8571429, 9.5714288, 9.5714288, 10.2857146, 10.2857146, 11};

    for (int i = 0; i < 24; i++) {
        ASSERT_NEAR(expected[i], calculated[i], EPSILON);
    }
}

TSA_TEST(StatisticsTests, CovarianceUnbiased, covarianceUnbiased);
TSA_TEST(StatisticsTests, CovarianceBiased, covarianceBiased);
TSA_TEST(StatisticsTests, Moment, moment);
TSA_TEST(StatisticsTests, SampleStdev, sampleStdev);
TSA_TEST(StatisticsTests, Kurtosis, kurtosis);
TSA_TEST(StatisticsTests, Quantile, quantile);
TSA_TEST(StatisticsTests, QuantilesCut2, quantilesCut2);
TSA_TEST(StatisticsTests, QuantilesCut3, quantilesCut3);
TSA_TEST(StatisticsTests, QuantilesCut7, quantilesCut7);
