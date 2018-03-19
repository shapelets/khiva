// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <tsa.h>
#include "tsatest.h"

void zNorm() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    af::array tss(4, 2, data);

    auto result = tsa::normalization::znorm(tss);

    ASSERT_EQ(tss.dims(), result.dims());

    float expected[] = {-1.341640786499870, -0.447213595499958, 0.447213595499958, 1.341640786499870};
    float *host_col1 = result.col(0).host<float>();
    float *host_col2 = result.col(1).host<float>();
    for (int i = 0; i < 4; i++) {
        ASSERT_NEAR(host_col1[i], expected[i], EPSILON);
        ASSERT_NEAR(host_col2[i], expected[i], EPSILON);
    }
}

void zNormInPlace() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    af::array tss(4, 2, data);

    tsa::normalization::znormInPlace(tss);

    float expected[] = {-1.341640786499870, -0.447213595499958, 0.447213595499958, 1.341640786499870};
    float *host_col1 = tss.col(0).host<float>();
    float *host_col2 = tss.col(1).host<float>();
    for (int i = 0; i < 4; i++) {
        ASSERT_NEAR(host_col1[i], expected[i], EPSILON);
        ASSERT_NEAR(host_col2[i], expected[i], EPSILON);
    }
}

void maxMinNorm() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    af::array tss(4, 2, data);

    auto result = tsa::normalization::maxMinNorm(tss, 2.0, 1.0);

    ASSERT_EQ(tss.dims(), result.dims());

    float expected[] = {1.0, 1.3333333333333, 1.66666667, 2.0};
    float *host_col1 = result.col(0).host<float>();
    float *host_col2 = result.col(1).host<float>();
    for (int i = 0; i < 4; i++) {
        ASSERT_NEAR(host_col1[i], expected[i], EPSILON);
        ASSERT_NEAR(host_col2[i], expected[i], EPSILON);
    }
}

void maxMinNormInPlace() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    af::array tss(4, 2, data);

    tsa::normalization::maxMinNormInPlace(tss, 2.0, 1.0);

    float expected[] = {1.0, 1.3333333333333, 1.66666667, 2.0};
    float *host_col1 = tss.col(0).host<float>();
    float *host_col2 = tss.col(1).host<float>();
    for (int i = 0; i < 4; i++) {
        ASSERT_NEAR(host_col1[i], expected[i], EPSILON);
        ASSERT_NEAR(host_col2[i], expected[i], EPSILON);
    }
}

void decimalScalingNorm() {
    float data[] = {0, 1, -2, 3, 40, 50, 60, -70};
    af::array tss(4, 2, data);

    auto result = tsa::normalization::decimalScalingNorm(tss);

    ASSERT_EQ(tss.dims(), result.dims());

    float expected[] = {0.0, 0.1, -0.2, 0.3, 0.4, 0.5, 0.6, -0.7};
    float *host = result.host<float>();
    for (int i = 0; i < 8; i++) {
        ASSERT_NEAR(host[i], expected[i], EPSILON);
    }
}

void decimalScalingNormInPlace() {
    float data[] = {0, 1, -2, 3, 40, 50, 60, -70};
    af::array tss(4, 2, data);

    tsa::normalization::decimalScalingNormInPlace(tss);

    float expected[] = {0.0, 0.1, -0.2, 0.3, 0.4, 0.5, 0.6, -0.7};
    float *host = tss.host<float>();
    for (int i = 0; i < 8; i++) {
        ASSERT_NEAR(host[i], expected[i], EPSILON);
    }
}

TSA_TEST(NormalizationTests, ZNorm, zNorm);
TSA_TEST(NormalizationTests, ZNormInPlace, zNormInPlace);
TSA_TEST(NormalizationTests, MaxMinNorm, maxMinNorm);
TSA_TEST(NormalizationTests, MaxMinNormInPlace, maxMinNormInPlace);
TSA_TEST(NormalizationTests, DecimalScalingNorm, decimalScalingNorm);
TSA_TEST(NormalizationTests, DecimalScalingNormInPlace, decimalScalingNormInPlace);
