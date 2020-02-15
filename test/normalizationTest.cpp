// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <khiva/normalization.h>
#include <khiva/internal/scopedHostPtr.h>
#include "khivaTest.h"

void decimalScalingNorm() {
    float data[] = {0, 1, -2, 3, 40, 50, 60, -70};
    af::array tss(4, 2, data);

    auto result = khiva::normalization::decimalScalingNorm(tss);

    ASSERT_EQ(tss.dims(), result.dims());

    float expected[] = {0.0f, 0.1f, -0.2f, 0.3f, 0.4f, 0.5f, 0.6f, -0.7f};
    auto host = khiva::utils::makeScopedHostPtr(result.host<float>());
    for (int i = 0; i < 8; i++) {
        ASSERT_NEAR(host[i], expected[i], EPSILON);
    }
}

void decimalScalingNormInPlace() {
    float data[] = {0, 1, -2, 3, 40, 50, 60, -70};
    af::array tss(4, 2, data);

    khiva::normalization::decimalScalingNormInPlace(tss);

    float expected[] = {0.0f, 0.1f, -0.2f, 0.3f, 0.4f, 0.5f, 0.6f, -0.7f};
    auto host = khiva::utils::makeScopedHostPtr(tss.host<float>());
    for (int i = 0; i < 8; i++) {
        ASSERT_NEAR(host[i], expected[i], EPSILON);
    }
}

void maxMinNorm() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    af::array tss(4, 2, data);

    auto result = khiva::normalization::maxMinNorm(tss, 2.0, 1.0);

    ASSERT_EQ(tss.dims(), result.dims());

    float expected[] = {1.0f, 1.3333333333333f, 1.66666667f, 2.0f};
    auto host_col1 = khiva::utils::makeScopedHostPtr(result.col(0).host<float>());
    auto host_col2 = khiva::utils::makeScopedHostPtr(result.col(1).host<float>());
    for (int i = 0; i < 4; i++) {
        ASSERT_NEAR(host_col1[i], expected[i], EPSILON);
        ASSERT_NEAR(host_col2[i], expected[i], EPSILON);
    }
}

void maxMinNormInPlace() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    af::array tss(4, 2, data);

    khiva::normalization::maxMinNormInPlace(tss, 2.0, 1.0);

    float expected[] = {1.0f, 1.3333333333333f, 1.66666667f, 2.0f};
    auto host_col1 = khiva::utils::makeScopedHostPtr(tss.col(0).host<float>());
    auto host_col2 = khiva::utils::makeScopedHostPtr(tss.col(1).host<float>());
    for (int i = 0; i < 4; i++) {
        ASSERT_NEAR(host_col1[i], expected[i], EPSILON);
        ASSERT_NEAR(host_col2[i], expected[i], EPSILON);
    }
}

void meanNorm() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    af::array tss(4, 2, data);

    auto res = khiva::normalization::meanNorm(tss);

    float expected[] = {-0.5f, -0.166666667f, 0.166666667f, 0.5f};
    float expected2[] = {-0.5f, -0.166666667f, 0.166666667f, 0.5f};

    auto host_col1 = khiva::utils::makeScopedHostPtr(res.col(0).host<float>());
    auto host_col2 = khiva::utils::makeScopedHostPtr(res.col(1).host<float>());

    ASSERT_NEAR(host_col1[0], expected[0], EPSILON);
    ASSERT_NEAR(host_col2[0], expected2[0], EPSILON);

    ASSERT_NEAR(host_col1[1], expected[1], EPSILON);
    ASSERT_NEAR(host_col2[1], expected2[1], EPSILON);

    ASSERT_NEAR(host_col1[2], expected[2], EPSILON);
    ASSERT_NEAR(host_col2[2], expected2[2], EPSILON);

    ASSERT_NEAR(host_col1[3], expected[3], EPSILON);
    ASSERT_NEAR(host_col2[3], expected2[3], EPSILON);
}

void meanNormInPlace() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    af::array tss(4, 2, data);

    khiva::normalization::meanNormInPlace(tss);

    float expected[] = {-0.5f, -0.166666667f, 0.166666667f, 0.5f};
    float expected2[] = {-0.5f, -0.166666667f, 0.166666667f, 0.5f};

    auto host_col1 = khiva::utils::makeScopedHostPtr(tss.col(0).host<float>());
    auto host_col2 = khiva::utils::makeScopedHostPtr(tss.col(1).host<float>());

    ASSERT_NEAR(host_col1[0], expected[0], EPSILON);
    ASSERT_NEAR(host_col2[0], expected2[0], EPSILON);

    ASSERT_NEAR(host_col1[1], expected[1], EPSILON);
    ASSERT_NEAR(host_col2[1], expected2[1], EPSILON);

    ASSERT_NEAR(host_col1[2], expected[2], EPSILON);
    ASSERT_NEAR(host_col2[2], expected2[2], EPSILON);

    ASSERT_NEAR(host_col1[3], expected[3], EPSILON);
    ASSERT_NEAR(host_col2[3], expected2[3], EPSILON);
}

void zNorm() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    af::array tss(4, 2, data);

    auto result = khiva::normalization::znorm(tss);

    ASSERT_EQ(tss.dims(), result.dims());

    float expected[] = {-1.341640786499870f, -0.447213595499958f, 0.447213595499958f, 1.341640786499870f};
    auto host_col1 = khiva::utils::makeScopedHostPtr(result.col(0).host<float>());
    auto host_col2 = khiva::utils::makeScopedHostPtr(result.col(1).host<float>());
    for (int i = 0; i < 4; i++) {
        ASSERT_NEAR(host_col1[i], expected[i], EPSILON);
        ASSERT_NEAR(host_col2[i], expected[i], EPSILON);
    }
}

void zNormInPlace() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    af::array tss(4, 2, data);

    khiva::normalization::znormInPlace(tss);

    float expected[] = {-1.341640786499870f, -0.447213595499958f, 0.447213595499958f, 1.341640786499870f};
    auto host_col1 = khiva::utils::makeScopedHostPtr(tss.col(0).host<float>());
    auto host_col2 = khiva::utils::makeScopedHostPtr(tss.col(1).host<float>());
    for (int i = 0; i < 4; i++) {
        ASSERT_NEAR(host_col1[i], expected[i], EPSILON);
        ASSERT_NEAR(host_col2[i], expected[i], EPSILON);
    }
}

KHIVA_TEST(NormalizationTests, DecimalScalingNorm, decimalScalingNorm)
KHIVA_TEST(NormalizationTests, DecimalScalingNormInPlace, decimalScalingNormInPlace)
KHIVA_TEST(NormalizationTests, MaxMinNorm, maxMinNorm)
KHIVA_TEST(NormalizationTests, MaxMinNormInPlace, maxMinNormInPlace)
KHIVA_TEST(NormalizationTests, MeanNorm, meanNorm)
KHIVA_TEST(NormalizationTests, MeanNormInPlace, meanNormInPlace)
KHIVA_TEST(NormalizationTests, ZNorm, zNorm)
KHIVA_TEST(NormalizationTests, ZNormInPlace, zNormInPlace)
