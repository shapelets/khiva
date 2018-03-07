// Copyright (c) 2018 Grumpy Cat Software S.L.
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa.h>
#include <gtest/gtest.h>

TEST(FeatureTests, absEnergy)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    af::array tss(10, 1, data);

    auto result = tsa::features::absEnergy(tss);

    double expected[] = {385};
    double* host_res = result.host<double>();
    
    for (int i=0; i<1; i++) {
        ASSERT_NEAR(host_res[i], expected[i], 0.00000001);
    }
}

TEST(FeatureTests, absEnergy2)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    float data[] = {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4};
    af::array tss(4, 3, data);

    auto result = tsa::features::absEnergy(tss);

    float expected[] = {30, 30, 30};
    float* host_res = result.row(0).host<float>();
    
    for (int i=0; i<3; i++) {
        ASSERT_NEAR(host_res[i], expected[i], 0.00000001);
    }
}

TEST(FeaturesTests, AbsoluteSumOfChanges)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {0, 1, 2, 3, 4, 6, 8, 10, 11, 14, 17, 20};
    af::array tss(4, 3, data);

    af::array asoc = tsa::features::absoluteSumOfChanges(tss);

    // check dimensions
    af::dim4 dims = asoc.dims();
    ASSERT_EQ(dims[0], 1);
    ASSERT_EQ(dims[1], 3);
    ASSERT_EQ(dims[2], 1);
    ASSERT_EQ(dims[3], 1);

    // check distances
    double* hostResult = asoc.host<double>();    
    ASSERT_EQ(3, hostResult[0]);
    ASSERT_EQ(6, hostResult[1]);
    ASSERT_EQ(9, hostResult[2]);
}

TEST(FeaturesTests, AggregatedLinearTrend)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5};
    af::array tss(12, data);

    af::array slope, intercept, rvalue, pvalue, stderrest;

    tsa::features::aggregatedLinearTrend(tss, 3, af::mean, slope, intercept, rvalue, pvalue, stderrest);

    double slopeCalculated, interceptCalculated, rvalueCalculated, pvalueCalculated, stderrestCalculated;

    slope.host(&slopeCalculated);
    intercept.host(&interceptCalculated);
    rvalue.host(&rvalueCalculated);
    pvalue.host(&pvalueCalculated);
    stderrest.host(&stderrestCalculated);

    ASSERT_EQ(slopeCalculated, 1.0);
    ASSERT_EQ(interceptCalculated, 2.0);
    ASSERT_EQ(rvalueCalculated, 1.0);
    ASSERT_EQ(pvalueCalculated, 0.0);
    ASSERT_EQ(stderrestCalculated, 0.0);
}