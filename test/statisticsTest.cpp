// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <khiva/statistics.h>
#include "khivaTest.h"

void covarianceBiased() {
    float dataX[] = {-2.1f, -1, 4.3f, 3, 1.1f, 0.12f, 3, 1.1f, 0.12f};
    af::array tss(3, 3, dataX);

    float dataExpected[] = {7.80666667f, -2.85733333f, -2.85733333f, -2.85733333f, 1.42942222f,
                            1.42942222f, -2.85733333f, 1.42942222f,  1.42942222f};

    auto *result = khiva::statistics::covariance(tss, false).host<float>();

    for (int i = 0; i < 9; i++) {
        ASSERT_NEAR(dataExpected[i], result[i], EPSILON);
    }
    af::freeHost(result);
}

void covarianceUnbiased() {
    float dataX[] = {-2.1f, -1, 4.3f, 3, 1.1f, 0.12f, 3, 1.1f, 0.12f};
    af::array tss(3, 3, dataX);

    float dataExpected[] = {11.70999999f, -4.286f, -4.286f,     -4.286f,    2.14413333f,
                            2.14413333f,  -4.286f, 2.14413333f, 2.14413333f};

    auto *result = khiva::statistics::covariance(tss, true).host<float>();

    for (int i = 0; i < 9; i++) {
        ASSERT_NEAR(dataExpected[i], result[i], EPSILON);
    }
    af::freeHost(result);

}

void kurtosis() {
    float data[] = {0, 1, 2, 3, 4, 5, 2, 2, 2, 20, 30, 25};
    af::array tss(6, 2, data);

    float dataExpected[] = {-1.2f, -2.66226722f};

    auto *result = khiva::statistics::kurtosis(tss).host<float>();

    for (int i = 0; i < 2; i++) {
        ASSERT_NEAR(dataExpected[i], result[i], EPSILON * 1e2);
    }
    af::freeHost(result);
}

void ljungBox() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    af::array tss(4, 2, data);

    af::array result = khiva::statistics::ljungBox(tss, 3);
    auto *calculated = result.host<float>();

    float expected[] = {6.4400f, 6.4400f};
    ASSERT_NEAR(expected[0], calculated[0], EPSILON);
    ASSERT_NEAR(expected[1], calculated[1], EPSILON);
    af::freeHost(calculated);
}

void moment() {
    float dataX[] = {0, 1, 2, 3, 4, 5};
    af::array x(6, dataX);
    af::array xss = af::tile(x, 1, 2);

    float dataExpected = 9.166666666f;

    auto *result_a = khiva::statistics::moment(xss, 2).host<float>();

    ASSERT_NEAR(result_a[0], dataExpected, EPSILON);
    ASSERT_NEAR(result_a[1], dataExpected, EPSILON);
    af::freeHost(result_a);

    dataExpected = 163.1666666666f;

    auto *result_b = khiva::statistics::moment(xss, 4).host<float>();

    ASSERT_NEAR(result_b[0], dataExpected, EPSILON * 1e2);
    ASSERT_NEAR(result_b[1], dataExpected, EPSILON * 1e2);
    af::freeHost(result_b);
}

void quantile() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(6, 2, data);

    float quantiles[] = {0.1f, 0.2f};

    af::array q = af::array(2, quantiles);

    auto *calculated = khiva::statistics::quantile(tss, q).host<float>();

    float expected[] = {0.5, 1.0, 6.5, 7.0};

    ASSERT_EQ(calculated[0], expected[0]);
    ASSERT_EQ(calculated[1], expected[1]);
    af::freeHost(calculated);
}

void quantilesCut2() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(6, 2, data);

    float quantiles = 2;

    af::array result = af::transpose(khiva::statistics::quantilesCut(tss, quantiles));

    auto *calculated = result.host<float>();

    float expected[] = {-0.00000001f, 2.5f, -0.00000001f, 2.5f,  -0.00000001f, 2.5f,  2.5f, 5.0f,
                        2.5f,         5.0f, 2.5f,         5.0f,  6.0f,         8.5f,  6.0f, 8.5f,
                        6.0f,         8.5f, 8.5f,         11.0f, 8.5f,         11.0f, 8.5f, 11.0f};

    for (int i = 0; i < 24; i++) {
        ASSERT_NEAR(expected[i], calculated[i], EPSILON);
    }
    af::freeHost(calculated);
}

void quantilesCut3() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(6, 2, data);

    float quantiles = 3;

    af::array result = af::transpose(khiva::statistics::quantilesCut(tss, quantiles));

    auto *calculated = result.host<float>();

    float expected[] = {-0.00000001f, 1.66666667f, -0.00000001f, 1.6666667f, 1.6666667f, 3.3333333f,
                        1.6666667f,   3.3333333f,  3.3333333f,   5.0f,       3.3333333f, 5.0f,
                        5.9999999f,   7.66666667f, 5.9999999f,   7.6666667f, 7.6666667f, 9.3333333f,
                        7.6666667f,   9.3333333f,  9.3333333f,   11.0f,      9.3333333f, 11.0f};

    for (int i = 0; i < 24; i++) {
        ASSERT_NEAR(expected[i], calculated[i], EPSILON);
    }
    af::freeHost(calculated);
}

void quantilesCut7() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(6, 2, data);

    float quantiles = 7;

    af::array result = af::transpose(khiva::statistics::quantilesCut(tss, quantiles));

    auto *calculated = result.host<float>();

    float expected[] = {0,          0.7142857f, 0.7142857f, 1.4285715f,  1.4285715f,  2.1428573f,
                        2.8571429f, 3.5714288f, 3.5714288f, 4.2857146f,  4.2857146f,  5,
                        5.9999999f, 6.7142857f, 6.7142857f, 7.4285715f,  7.4285715f,  8.1428573f,
                        8.8571429f, 9.5714288f, 9.5714288f, 10.2857146f, 10.2857146f, 11};

    for (int i = 0; i < 24; i++) {
        ASSERT_NEAR(expected[i], calculated[i], EPSILON);
    }
    af::freeHost(calculated);
}

void sampleStdev() {
    float data[] = {0, 1, 2, 3, 4, 5, 2, 2, 2, 20, 30, 25};
    af::array tss(6, 2, data);

    float dataExpected[] = {1.870828693f, 12.988456413f};

    auto *result = khiva::statistics::sampleStdev(tss).host<float>();

    ASSERT_NEAR(result[0], dataExpected[0], EPSILON);
    ASSERT_NEAR(result[1], dataExpected[1], EPSILON);
    af::freeHost(result);
}

void skewness() {
    float data[] = {0, 1, 2, 3, 4, 5, 2, 2, 2, 20, 30, 25};
    af::array tss(6, 2, data);

    float dataExpected[] = {0.0f, 0.236177069879499f};

    auto *result = khiva::statistics::skewness(tss).host<float>();

    for (int i = 0; i < 2; i++) {
        ASSERT_NEAR(dataExpected[i], result[i], EPSILON * 1e2);
    }
    af::freeHost(result);
}

KHIVA_TEST(StatisticsTests, CovarianceBiased, covarianceBiased)
KHIVA_TEST(StatisticsTests, CovarianceUnbiased, covarianceUnbiased)
KHIVA_TEST(StatisticsTests, Kurtosis, kurtosis)
KHIVA_TEST(StatisticsTests, LjungBox, ljungBox)
KHIVA_TEST(StatisticsTests, Moment, moment)
KHIVA_TEST(StatisticsTests, Quantile, quantile)
KHIVA_TEST(StatisticsTests, QuantilesCut2, quantilesCut2)
KHIVA_TEST(StatisticsTests, QuantilesCut3, quantilesCut3)
KHIVA_TEST(StatisticsTests, QuantilesCut7, quantilesCut7)
KHIVA_TEST(StatisticsTests, SampleStdev, sampleStdev)
KHIVA_TEST(StatisticsTests, Skewness, skewness)
