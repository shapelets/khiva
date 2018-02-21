// Copyright (c) 2018 Grumpy Cat Software S.L.
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "tsa.h"
#include "gtest/gtest.h"

TEST(NormalizationTests, ZNorm)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    af::array tss(4, 2, data);

    auto result = tsa::normalization::znorm(tss);

    ASSERT_EQ(tss.dims(), result.dims());

    double expected[] = { -1.341640786499870,-0.447213595499958,0.447213595499958,1.341640786499870 };
    double* host_col1 = result.col(0).host<double>();
    double* host_col2 = result.col(1).host<double>();
    for (int i=0; i<4; i++) {
        ASSERT_NEAR(host_col1[i], expected[i], 0.00000001);
        ASSERT_NEAR(host_col2[i], expected[i], 0.00000001);
    }
}

TEST(NormalizationTests, ZNormInPlace)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    af::array tss(4, 2, data);

    tsa::normalization::znormInPlace(tss);
    
    double expected[] = { -1.341640786499870,-0.447213595499958,0.447213595499958,1.341640786499870 };
    double* host_col1 = tss.col(0).host<double>();
    double* host_col2 = tss.col(1).host<double>();
    for (int i=0; i<4; i++) {
        ASSERT_NEAR(host_col1[i], expected[i], 0.00000001);
        ASSERT_NEAR(host_col2[i], expected[i], 0.00000001);
    }
}


TEST(NormalizationTests, MaxMinNorm)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    af::array tss(4, 2, data);

    auto result = tsa::normalization::maxMinNorm(tss, 2.0, 1.0);

    ASSERT_EQ(tss.dims(), result.dims());

    double expected[] = { 1.0, 1.3333333333333, 1.66666667, 2.0 };
    double* host_col1 = result.col(0).host<double>();
    double* host_col2 = result.col(1).host<double>();
    for (int i=0; i<4; i++) {
        ASSERT_NEAR(host_col1[i], expected[i], 0.00000001);
        ASSERT_NEAR(host_col2[i], expected[i], 0.00000001);
    }
}

TEST(NormalizationTests, MaxMinNormInPlace)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    af::array tss(4, 2, data);

    tsa::normalization::maxMinNormInPlace(tss, 2.0, 1.0);

    double expected[] = { 1.0, 1.3333333333333, 1.66666667, 2.0 };
    double* host_col1 = tss.col(0).host<double>();
    double* host_col2 = tss.col(1).host<double>();
    for (int i=0; i<4; i++) {
        ASSERT_NEAR(host_col1[i], expected[i], 0.00000001);
        ASSERT_NEAR(host_col2[i], expected[i], 0.00000001);
    }
}


TEST(NormalizationTests, DecimalScalingNorm)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {0, 1, -2, 3, 40, 50, 60, -70};
    af::array tss(4, 2, data);

    auto result = tsa::normalization::decimalScalingNorm(tss);

    ASSERT_EQ(tss.dims(), result.dims());

    double expected[] = { 0.0, 0.1, -0.2, 0.3,  0.4, 0.5, 0.6, -0.7};
    double* host = result.host<double>();
    for (int i=0; i<8; i++) {
        ASSERT_NEAR(host[i], expected[i], 0.00000001);
    }
}

TEST(NormalizationTests, DecimalScalingNormInPlace)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {0, 1, -2, 3, 40, 50, 60, -70};
    af::array tss(4, 2, data);

    tsa::normalization::decimalScalingNormInPlace(tss);

    double expected[] = { 0.0, 0.1, -0.2, 0.3,  0.4, 0.5, 0.6, -0.7};
    double* host = tss.host<double>();
    for (int i=0; i<8; i++) {
        ASSERT_NEAR(host[i], expected[i], 0.00000001);
    }
}