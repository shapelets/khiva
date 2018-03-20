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

TSA_TEST(StatisticsTests, CovarianceUnbiased, covarianceUnbiased);
TSA_TEST(StatisticsTests, CovarianceBiased, covarianceBiased);
TSA_TEST(StatisticsTests, Moment, moment);
TSA_TEST(StatisticsTests, SampleStdev, sampleStdev);
TSA_TEST(StatisticsTests, Kurtosis, kurtosis);
