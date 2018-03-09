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

TEST(FeaturesTests, Autocorrelation)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);

    double data[] = {0, 1, 2, 3, 4, 6, 8, 10, 11, 14, 17, 20};
    af::array tss(4, 3, data);

    af::array calculated2 = tsa::features::autocorrelation(tss, 2);

    double *calculated2Host = calculated2.host<double>();

    // Expected results obtained using tsfresh
    ASSERT_EQ(calculated2Host[0], -0.6);
    ASSERT_EQ(calculated2Host[1], -0.6);
    ASSERT_EQ(calculated2Host[2], -0.6);

    af::array calculated3 = tsa::features::autocorrelation(tss, 3);

    double *calculated3Host = calculated3.host<double>();

    // Expected results obtained using tsfresh
    ASSERT_EQ(calculated3Host[0], -1.8);
    ASSERT_EQ(calculated3Host[1], -1.8);
    ASSERT_EQ(calculated3Host[2], -1.8);
}

TEST(FeaturesTests, C3)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);

    double data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(6, 2, data);

    af::array c3Result = tsa::features::c3(tss, 2);

    double *c3Calculated = c3Result.host<double>();

    ASSERT_EQ(c3Calculated[0], 7.5);
    ASSERT_EQ(c3Calculated[1], 586.5);
}

TEST(FeaturesTests, CidCe)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);

    double data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(6, 2, data);

    af::array cidCeResult = tsa::features::cidCe(tss);

    double *cidCeCalculated = cidCeResult.host<double>();

    ASSERT_NEAR(cidCeCalculated[0], 2.23606797749979, 1e-9);
    ASSERT_NEAR(cidCeCalculated[1], 2.23606797749979, 1e-9);

    af::array cidCeResult2 = tsa::features::cidCe(tss, true);

    double *cidCeCalculated2 = cidCeResult2.host<double>();

    ASSERT_NEAR(cidCeCalculated2[0], 1.30930734141595, 1e-9);
    ASSERT_NEAR(cidCeCalculated2[1], 1.30930734141595, 1e-9);
}

TEST(FeaturesTests, CountBelowMean)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);

    double data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(6, 2, data);

    af::array countBelowMeanResult = tsa::features::countBelowMean(tss);

    unsigned int *countBelowMeanCalculated = countBelowMeanResult.host<unsigned int>();

    ASSERT_EQ(countBelowMeanCalculated[0], 3);
    ASSERT_EQ(countBelowMeanCalculated[1], 3);
}

TEST(FeaturesTests, EnergyRatioByChunk)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);

    double data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(6, 2, data);

    af::array energyRatioByChunkResult = tsa::features::energyRatioByChunks(tss, 2, 0);

    double *energyRatioByChunkCalculated = energyRatioByChunkResult.host<double>();

    ASSERT_NEAR(energyRatioByChunkCalculated[0], 0.090909091, 1e-9);
    ASSERT_NEAR(energyRatioByChunkCalculated[1], 0.330376940, 1e-9);

    af::array energyRatioByChunkResult2 = tsa::features::energyRatioByChunks(tss, 2, 1);

    double *energyRatioByChunkCalculated2 = energyRatioByChunkResult2.host<double>();

    ASSERT_NEAR(energyRatioByChunkCalculated2[0], 0.909090909, 1e-9);
    ASSERT_NEAR(energyRatioByChunkCalculated2[1], 0.669623060, 1e-9);
}

TEST(FeaturesTests, FftCoefficient)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);

    double data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(6, 2, data);

    af::array real, imag, _abs, angle;

    tsa::features::fftCoefficient(tss, 0, real, imag, _abs, angle);

    double *realCalculated = real.host<double>();
    double *imagCalculated = imag.host<double>();
    double *_absCalculated = _abs.host<double>();
    double *angleCalculated = angle.host<double>();

    ASSERT_EQ(realCalculated[0], 15.0);
    ASSERT_EQ(realCalculated[1], 51.0);
    ASSERT_EQ(imagCalculated[0], 0.0);
    ASSERT_EQ(imagCalculated[1], 0.0);
    ASSERT_EQ(_absCalculated[0], 15.0);
    ASSERT_EQ(_absCalculated[1], 51.0);
    ASSERT_EQ(angleCalculated[0], 0.0);
    ASSERT_EQ(angleCalculated[1], 0.0);
}

TEST(FeaturesTests, FirstLocationOfMinimum)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);

    double data[] = {5, 4, 3, 0, 0, 1, 5, 4, 3, 0, 2, 1};
    af::array tss(6, 2, data);

    af::array result = tsa::features::firstLocationOfMinimum(tss);
    
    double *firstMinimumCalculated = result.host<double>();

    ASSERT_EQ(firstMinimumCalculated[0], 0.5);
    ASSERT_EQ(firstMinimumCalculated[1], 0.5);
}