// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <tsa.h>

TEST(FeaturesTests, absEnergy) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    af::array tss(10, 1, data);

    auto result = tsa::features::absEnergy(tss);

    double expected[] = {385};
    double *host_res = result.host<double>();

    for (int i = 0; i < 1; i++) {
        ASSERT_NEAR(host_res[i], expected[i], 0.00000001);
    }
}

TEST(FeaturesTests, absEnergy2) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    float data[] = {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4};
    af::array tss(4, 3, data);

    auto result = tsa::features::absEnergy(tss);

    float expected[] = {30, 30, 30};
    float *host_res = result.row(0).host<float>();

    for (int i = 0; i < 3; i++) {
        ASSERT_NEAR(host_res[i], expected[i], 0.00000001);
    }
}

TEST(FeaturesTests, AbsoluteSumOfChanges) {
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
    double *hostResult = asoc.host<double>();
    ASSERT_EQ(3, hostResult[0]);
    ASSERT_EQ(6, hostResult[1]);
    ASSERT_EQ(9, hostResult[2]);
}

TEST(FeaturesTests, AggregatedCorrelationMean) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    af::array tss(6, 2, data);

    af::array res = tsa::features::aggregatedAutocorrelation(tss, af::mean);
    float *r = res.host<float>();
    float a[] = {-0.6571428571428571, -0.6571428571428571};
    ASSERT_NEAR(r[0], a[0], 1e-9);
    ASSERT_NEAR(r[1], a[1], 1e-9);
}

TEST(FeaturesTests, AggregatedCorrelationMedian) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    af::array tss(6, 2, data);

    af::array res = tsa::features::aggregatedAutocorrelation(tss, af::median);
    float *r = res.host<float>();
    float a[] = {-0.54285717010498047, -0.54285717010498047};
    ASSERT_NEAR(r[0], a[0], 1e-9);
    ASSERT_NEAR(r[1], a[1], 1e-9);
}

TEST(FeaturesTests, AggregatedCorrelationMin) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    af::array tss(6, 2, data);

    af::array res = tsa::features::aggregatedAutocorrelation(tss, af::min);
    float *r = res.host<float>();
    float a[] = {-2.142857142857143, -2.142857142857143};
    ASSERT_NEAR(r[0], a[0], 1e-9);
    ASSERT_NEAR(r[1], a[1], 1e-9);
}

TEST(FeaturesTests, AggregatedCorrelationMax) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    af::array tss(6, 2, data);

    af::array res = tsa::features::aggregatedAutocorrelation(tss, af::max);
    float *r = res.host<float>();
    float a[] = {0.6, 0.6};
    ASSERT_NEAR(r[0], a[0], 1e-9);
    ASSERT_NEAR(r[1], a[1], 1e-9);
}

TEST(FeaturesTests, AggregatedCorrelationStdev) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    af::array tss(6, 2, data);

    af::array res = tsa::features::aggregatedAutocorrelation(tss, af::stdev);
    float *r = res.host<float>();
    float a[] = {0.9744490855905009, 0.9744490855905009};
    ASSERT_NEAR(r[0], a[0], 1e-7);
    ASSERT_NEAR(r[1], a[1], 1e-7);
}

TEST(FeaturesTests, AggregatedCorrelationVar) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    af::array tss(6, 2, data);

    af::array res = tsa::features::aggregatedAutocorrelation(tss, af::var);
    float *r = res.host<float>();
    float a[] = {0.9495510204081633, 0.9495510204081633};
    ASSERT_NEAR(r[0], a[0], 1e-7);
    ASSERT_NEAR(r[1], a[1], 1e-7);
}

TEST(FeaturesTests, AggregatedLinearTrendMean) {
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

TEST(FeaturesTests, AggregatedLinearTrendMin) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5};
    af::array tss(12, data);

    af::array slope, intercept, rvalue, pvalue, stderrest;

    tsa::features::aggregatedLinearTrend(tss, 3, af::min, slope, intercept, rvalue, pvalue, stderrest);

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

TEST(FeaturesTests, AggregatedLinearTrendMultipleSeriesMean) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5};
    af::array t(12, data);
    af::array tss = af::tile(t, 1, 2);

    af::array slope, intercept, rvalue, pvalue, stderrest;

    tsa::features::aggregatedLinearTrend(tss, 3, af::mean, slope, intercept, rvalue, pvalue, stderrest);

    double *slopeCalculated = slope.host<double>();
    double *interceptCalculated = intercept.host<double>();
    double *rvalueCalculated = rvalue.host<double>();
    double *pvalueCalculated = pvalue.host<double>();
    double *stderrestCalculated = stderrest.host<double>();

    ASSERT_EQ(slopeCalculated[0], 1.0);
    ASSERT_EQ(slopeCalculated[1], 1.0);
    ASSERT_EQ(interceptCalculated[0], 2.0);
    ASSERT_EQ(interceptCalculated[1], 2.0);
    ASSERT_EQ(rvalueCalculated[0], 1.0);
    ASSERT_EQ(rvalueCalculated[1], 1.0);
    ASSERT_EQ(pvalueCalculated[0], 0.0);
    ASSERT_EQ(pvalueCalculated[1], 0.0);
    ASSERT_EQ(stderrestCalculated[0], 0.0);
    ASSERT_EQ(stderrestCalculated[1], 0.0);
}

TEST(FeaturesTests, AggregatedLinearTrendMultipleSeriesMin) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5};
    af::array t(12, data);
    af::array tss = af::tile(t, 1, 2);

    af::array slope, intercept, rvalue, pvalue, stderrest;

    tsa::features::aggregatedLinearTrend(tss, 3, af::min, slope, intercept, rvalue, pvalue, stderrest);

    double *slopeCalculated = slope.host<double>();
    double *interceptCalculated = intercept.host<double>();
    double *rvalueCalculated = rvalue.host<double>();
    double *pvalueCalculated = pvalue.host<double>();
    double *stderrestCalculated = stderrest.host<double>();

    ASSERT_EQ(slopeCalculated[0], 1.0);
    ASSERT_EQ(slopeCalculated[1], 1.0);
    ASSERT_EQ(interceptCalculated[0], 2.0);
    ASSERT_EQ(interceptCalculated[1], 2.0);
    ASSERT_EQ(rvalueCalculated[0], 1.0);
    ASSERT_EQ(rvalueCalculated[1], 1.0);
    ASSERT_EQ(pvalueCalculated[0], 0.0);
    ASSERT_EQ(pvalueCalculated[1], 0.0);
    ASSERT_EQ(stderrestCalculated[0], 0.0);
    ASSERT_EQ(stderrestCalculated[1], 0.0);
}

TEST(FeaturesTests, ApproximateEntropy) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    float data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int m = 4;
    float r = 0.5;
    af::array a(10, data);
    a = af::tile(a, 1, 2);
    a(span, 1) += 10;

    af::array res = tsa::features::approximateEntropy(a, m, r);

    float *resCalculated = res.host<float>();

    float expected[] = {0.13484275341033936, 0.13484275341033936};

    ASSERT_NEAR(resCalculated[0], expected[0], 1e-9);
    ASSERT_NEAR(resCalculated[1], expected[1], 1e-9);
}

TEST(FeaturesTests, Autocorrelation) {
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

TEST(FeaturesTests, BinnedEntropy) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);

    double ts1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    double ts2[] = {1, 1, 3, 10, 5, 6, 1, 8, 9, 10, 11, 1, 13, 14, 10, 16, 17, 10, 19, 20};
    af::array h_data(20, 1, ts1);
    af::array h_data2(20, 1, ts2);
    af::array tss = af::join(1, h_data, h_data2);

    af::array output = tsa::features::binnedEntropy(tss, 5);

    float *h_out = output.host<float>();
    float a[] = {1.6094379124341005, 1.5614694247763998};
    ASSERT_NEAR(h_out[0], a[0], 1e-9);
    ASSERT_NEAR(h_out[1], a[1], 1e-6);
}

TEST(FeaturesTests, C3) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);

    double data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(6, 2, data);

    af::array c3Result = tsa::features::c3(tss, 2);

    double *c3Calculated = c3Result.host<double>();

    ASSERT_EQ(c3Calculated[0], 7.5);
    ASSERT_EQ(c3Calculated[1], 586.5);
}

TEST(FeaturesTests, CidCe) {
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

TEST(FeaturesTests, CountAboveMean) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);

    double data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(6, 2, data);

    af::array countAboveMeanResult = tsa::features::countBelowMean(tss);

    unsigned int *countAboveMeanCalculated = countAboveMeanResult.host<unsigned int>();

    ASSERT_EQ(countAboveMeanCalculated[0], 3);
    ASSERT_EQ(countAboveMeanCalculated[1], 3);
}

TEST(FeaturesTests, CountBelowMean) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);

    double data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(6, 2, data);

    af::array countBelowMeanResult = tsa::features::countBelowMean(tss);

    unsigned int *countBelowMeanCalculated = countBelowMeanResult.host<unsigned int>();

    ASSERT_EQ(countBelowMeanCalculated[0], 3);
    ASSERT_EQ(countBelowMeanCalculated[1], 3);
}

TEST(FeaturesTests, EnergyRatioByChunk) {
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

TEST(FeaturesTests, FftCoefficient) {
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

TEST(FeaturesTests, FirstLocationOfMaximum) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);

    float data[] = {5, 4, 3, 5, 0, 1, 5, 3, 2, 1, 2, 4, 3, 5, 2, 5, 4, 3, 5, 2};
    af::array tss(10, 2, data);

    af::array result = tsa::features::firstLocationOfMaximum(tss);

    float *hr = result.host<float>();

    ASSERT_EQ(hr[0], 0.0f);
    ASSERT_EQ(hr[1], 0.3f);
}

TEST(FeaturesTests, FirstLocationOfMinimum) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);

    double data[] = {5, 4, 3, 0, 0, 1, 5, 4, 3, 0, 2, 1};
    af::array tss(6, 2, data);

    af::array result = tsa::features::firstLocationOfMinimum(tss);

    double *firstMinimumCalculated = result.host<double>();

    ASSERT_EQ(firstMinimumCalculated[0], 0.5);
    ASSERT_EQ(firstMinimumCalculated[1], 0.5);
}

TEST(FeaturesTests, HasDuplicates) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);

    double data[] = {5, 4, 3, 0, 0, 1, 5, 4, 3, 0, 2, 1};
    af::array tss(6, 2, data);

    af::array duplicates = tsa::features::hasDuplicates(tss);

    bool *duplicatesCalculated = (bool *)duplicates.host<char>();

    ASSERT_EQ(duplicatesCalculated[0], true);
    ASSERT_EQ(duplicatesCalculated[1], false);
}

TEST(FeaturesTests, HasDuplicateMax) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);

    double data[] = {5, 4, 3, 0, 5, 1, 5, 4, 3, 0, 2, 1};
    af::array tss(6, 2, data);

    af::array out = tsa::features::hasDuplicateMax(tss);

    bool *hout = (bool *)out.host<char>();

    ASSERT_EQ(hout[0], true);
    ASSERT_EQ(hout[1], false);
}

TEST(FeaturesTests, HasDuplicateMin) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);

    double data[] = {5, 4, 3, 0, 0, 1, 5, 4, 3, 0, 2, 1};
    af::array tss(6, 2, data);

    af::array duplicateMin = tsa::features::hasDuplicateMin(tss);

    bool *duplicateMinCalculated = (bool *)duplicateMin.host<char>();

    ASSERT_EQ(duplicateMinCalculated[0], true);
    ASSERT_EQ(duplicateMinCalculated[1], false);
}

TEST(FeaturesTests, IndexMaxQuantile) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    float data[] = {5, 4, 3, 0, 0, 1, 5, 4, 0, 0, 2, 1};
    af::array tss(6, 2, data);
    float q = 0.5;

    af::array result = tsa::features::indexMaxQuantile(tss, q);

    float *hresult = result.host<float>();
    float expected[] = {0.333333333, 0.3333333333};

    ASSERT_NEAR(hresult[0], expected[0], 1e-8);
    ASSERT_NEAR(hresult[1], expected[1], 1e-8);
}

TEST(FeaturesTests, Kurtosis) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {0, 1, 2, 3, 4, 5, 2, 2, 2, 20, 30, 25};
    af::array tss(6, 2, data);

    double dataExpected[] = {-1.2, -2.66226722};

    double *result = tsa::features::kurtosis(tss).host<double>();

    for (int i = 0; i < 2; i++) {
        ASSERT_NEAR(dataExpected[i], result[i], 1e-8);
    }
}

TEST(FeaturesTests, LastLocationOfMaximum) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);

    double data[] = {0, 4, 3, 5, 5, 1, 0, 4, 3, 2, 5, 1};
    af::array tss(6, 2, data);

    af::array result = tsa::features::lastLocationOfMaximum(tss);

    double *lastMaximumCalculated = result.host<double>();

    ASSERT_EQ(lastMaximumCalculated[0], 0.8333333333333334);
    ASSERT_EQ(lastMaximumCalculated[1], 0.8333333333333334);
}

TEST(FeaturesTests, Length) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);

    double data[] = {0, 4, 3, 5, 5, 1, 0, 4, 3, 2, 5, 1};
    af::array tss(6, 2, data);

    af::array result = tsa::features::length(tss);

    int *lengthCalculated = result.host<int>();

    ASSERT_EQ(lengthCalculated[0], 6);
    ASSERT_EQ(lengthCalculated[1], 6);
}

TEST(FeaturesTests, LinearTrend) {
    af::setBackend(af::Backend::AF_BACKEND_CPU);

    double data[] = {0, 4, 3, 5, 5, 1, 0, 4, 3, 2, 5, 1};
    af::array tss(6, 2, data);

    af::array pvalue, rvalue, intercept, slope, stderr;
    tsa::features::linearTrend(tss, pvalue, rvalue, intercept, slope, stderr);

    ASSERT_EQ(6, 6);
}