// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <khiva/features.h>
#include <khiva/internal/scopedHostPtr.h>

#include "khivaTest.h"

void absEnergy() {
    float data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    af::array tss(10, 1, data);

    auto result = khiva::features::absEnergy(tss);

    float expected[] = {385};
    auto host_res = khiva::utils::makeScopedHostPtr(result.host<float>());

    for (int i = 0; i < 1; i++) {
        ASSERT_NEAR(host_res[i], expected[i], EPSILON);
    }
}

void absEnergy2() {
    float data[] = {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4};
    af::array tss(4, 3, data);

    auto result = khiva::features::absEnergy(tss);

    float expected[] = {30, 30, 30};
    auto host_res = khiva::utils::makeScopedHostPtr(result.row(0).host<float>());

    for (int i = 0; i < 3; i++) {
        ASSERT_NEAR(host_res[i], expected[i], EPSILON);
    }
}

void absoluteSumOfChanges() {
    float data[] = {0, 1, 2, 3, 4, 6, 8, 10, 11, 14, 17, 20};
    af::array tss(4, 3, data);

    af::array asoc = khiva::features::absoluteSumOfChanges(tss);

    // check dimensions
    af::dim4 dims = asoc.dims();
    ASSERT_EQ(dims[0], 1);
    ASSERT_EQ(dims[1], 3);
    ASSERT_EQ(dims[2], 1);
    ASSERT_EQ(dims[3], 1);

    // check distances
    auto hostResult = khiva::utils::makeScopedHostPtr(asoc.host<float>());
    ASSERT_EQ(3, hostResult[0]);
    ASSERT_EQ(6, hostResult[1]);
    ASSERT_EQ(9, hostResult[2]);
}

void aggregatedCorrelationMean() {
    float data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    af::array tss(6, 2, data);

    af::array res = khiva::features::aggregatedAutocorrelation(tss, af::mean);
    auto r = khiva::utils::makeScopedHostPtr(res.host<float>());
    float a[] = {-0.6571428571428571f, -0.6571428571428571f};
    ASSERT_NEAR(r[0], a[0], EPSILON);
    ASSERT_NEAR(r[1], a[1], EPSILON);
}

void aggregatedCorrelationMedian() {
    float data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    af::array tss(6, 2, data);

    af::array res = khiva::features::aggregatedAutocorrelation(tss, af::median);
    auto r = khiva::utils::makeScopedHostPtr(res.host<float>());
    float a[] = {-0.54285717010498047, -0.54285717010498047};
    ASSERT_NEAR(r[0], a[0], EPSILON);
    ASSERT_NEAR(r[1], a[1], EPSILON);
}

void aggregatedCorrelationMin() {
    float data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    af::array tss(6, 2, data);

    af::array res = khiva::features::aggregatedAutocorrelation(tss, af::min);
    auto r = khiva::utils::makeScopedHostPtr(res.host<float>());
    float a[] = {-2.142857142857143f, -2.142857142857143f};
    ASSERT_NEAR(r[0], a[0], EPSILON * 2);
    ASSERT_NEAR(r[1], a[1], EPSILON * 2);
}

void aggregatedCorrelationMax() {
    float data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    af::array tss(6, 2, data);

    af::array res = khiva::features::aggregatedAutocorrelation(tss, af::max);
    auto r = khiva::utils::makeScopedHostPtr(res.host<float>());
    float a[] = {0.6f, 0.6f};
    ASSERT_NEAR(r[0], a[0], EPSILON);
    ASSERT_NEAR(r[1], a[1], EPSILON);
}

void aggregatedCorrelationStdev() {
    float data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    af::array tss(6, 2, data);

    af::array res = khiva::features::aggregatedAutocorrelation(tss, af::stdev);
    auto r = khiva::utils::makeScopedHostPtr(res.host<float>());
    float a[] = {0.9744490855905009f, 0.9744490855905009f};
    ASSERT_NEAR(r[0], a[0], EPSILON);
    ASSERT_NEAR(r[1], a[1], EPSILON);
}

void aggregatedCorrelationVar() {
    float data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    af::array tss(6, 2, data);

    af::array res = khiva::features::aggregatedAutocorrelation(tss, af::var);
    auto r = khiva::utils::makeScopedHostPtr(res.host<float>());
    float a[] = {0.9495510204081633f, 0.9495510204081633f};
    ASSERT_NEAR(r[0], a[0], EPSILON);
    ASSERT_NEAR(r[1], a[1], EPSILON);
}

void aggregatedLinearTrendMean() {
    float data[] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5};
    af::array tss(12, data);

    af::array slope, intercept, rvalue, pvalue, stderrest;

    khiva::features::aggregatedLinearTrend(tss, 3, af::mean, slope, intercept, rvalue, pvalue, stderrest);

    float slopeCalculated, interceptCalculated, rvalueCalculated, pvalueCalculated, stderrestCalculated;

    slope.host(&slopeCalculated);
    intercept.host(&interceptCalculated);
    rvalue.host(&rvalueCalculated);
    pvalue.host(&pvalueCalculated);
    stderrest.host(&stderrestCalculated);

    ASSERT_NEAR(slopeCalculated, 1.0, EPSILON);
    ASSERT_NEAR(interceptCalculated, 2.0, EPSILON);
    ASSERT_NEAR(rvalueCalculated, 1.0, EPSILON);
    ASSERT_NEAR(pvalueCalculated, 0.0, EPSILON);
    ASSERT_NEAR(stderrestCalculated, 0.0, EPSILON);
}

void aggregatedLinearTrendMin() {
    float data[] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5};
    af::array tss(12, data);

    af::array slope, intercept, rvalue, pvalue, stderrest;

    khiva::features::aggregatedLinearTrend(tss, 3, af::min, slope, intercept, rvalue, pvalue, stderrest);

    float slopeCalculated, interceptCalculated, rvalueCalculated, pvalueCalculated, stderrestCalculated;

    slope.host(&slopeCalculated);
    intercept.host(&interceptCalculated);
    rvalue.host(&rvalueCalculated);
    pvalue.host(&pvalueCalculated);
    stderrest.host(&stderrestCalculated);

    ASSERT_NEAR(slopeCalculated, 1.0, EPSILON);
    ASSERT_NEAR(interceptCalculated, 2.0, EPSILON);
    ASSERT_NEAR(rvalueCalculated, 1.0, EPSILON);
    ASSERT_NEAR(pvalueCalculated, 0.0, EPSILON);
    ASSERT_NEAR(stderrestCalculated, 0.0, EPSILON * 1e3);
}

void aggregatedLinearTrendMultipleSeriesMean() {
    float data[] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5};
    af::array t(12, data);
    af::array tss = af::tile(t, 1, 2);

    af::array slope, intercept, rvalue, pvalue, stderrest;

    khiva::features::aggregatedLinearTrend(tss, 3, af::mean, slope, intercept, rvalue, pvalue, stderrest);

    auto slopeCalculated = khiva::utils::makeScopedHostPtr(slope.host<float>());
    auto interceptCalculated = khiva::utils::makeScopedHostPtr(intercept.host<float>());
    auto rvalueCalculated = khiva::utils::makeScopedHostPtr(rvalue.host<float>());
    auto pvalueCalculated = khiva::utils::makeScopedHostPtr(pvalue.host<float>());
    auto stderrestCalculated = khiva::utils::makeScopedHostPtr(stderrest.host<float>());

    ASSERT_NEAR(slopeCalculated[0], 1.0, EPSILON);
    ASSERT_NEAR(interceptCalculated[0], 2.0, EPSILON);
    ASSERT_NEAR(rvalueCalculated[0], 1.0, EPSILON);
    ASSERT_NEAR(pvalueCalculated[0], 0.0, EPSILON);
    ASSERT_NEAR(stderrestCalculated[0], 0.0, EPSILON);
    ASSERT_NEAR(slopeCalculated[1], 1.0, EPSILON);
    ASSERT_NEAR(interceptCalculated[1], 2.0, EPSILON);
    ASSERT_NEAR(rvalueCalculated[1], 1.0, EPSILON);
    ASSERT_NEAR(pvalueCalculated[1], 0.0, EPSILON);
    ASSERT_NEAR(stderrestCalculated[1], 0.0, EPSILON);
}

void aggregatedLinearTrendMultipleSeriesMin() {
    float data[] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5};
    af::array t(12, data);
    af::array tss = af::tile(t, 1, 2);

    af::array slope, intercept, rvalue, pvalue, stderrest;

    khiva::features::aggregatedLinearTrend(tss, 3, af::mean, slope, intercept, rvalue, pvalue, stderrest);

    auto slopeCalculated = khiva::utils::makeScopedHostPtr(slope.host<float>());
    auto interceptCalculated = khiva::utils::makeScopedHostPtr(intercept.host<float>());
    auto rvalueCalculated = khiva::utils::makeScopedHostPtr(rvalue.host<float>());
    auto pvalueCalculated = khiva::utils::makeScopedHostPtr(pvalue.host<float>());
    auto stderrestCalculated = khiva::utils::makeScopedHostPtr(stderrest.host<float>());

    ASSERT_NEAR(slopeCalculated[0], 1.0, EPSILON);
    ASSERT_NEAR(interceptCalculated[0], 2.0, EPSILON);
    ASSERT_NEAR(rvalueCalculated[0], 1.0, EPSILON);
    ASSERT_NEAR(pvalueCalculated[0], 0.0, EPSILON);
    ASSERT_NEAR(stderrestCalculated[0], 0.0, EPSILON);
    ASSERT_NEAR(slopeCalculated[1], 1.0, EPSILON);
    ASSERT_NEAR(interceptCalculated[1], 2.0, EPSILON);
    ASSERT_NEAR(rvalueCalculated[1], 1.0, EPSILON);
    ASSERT_NEAR(pvalueCalculated[1], 0.0, EPSILON);
    ASSERT_NEAR(stderrestCalculated[1], 0.0, EPSILON);
}

void approximateEntropy() {
    float data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    int m = 4;
    float r = 0.5;
    af::array a(10, data);
    a = af::tile(a, 1, 2);
    a(af::span, 1) += 10;

    af::array res = khiva::features::approximateEntropy(a, m, r);

    auto resCalculated = khiva::utils::makeScopedHostPtr(res.host<float>());

    float expected[] = {0.13484275341033936, 0.13484275341033936};

    ASSERT_NEAR(resCalculated[0], expected[0], EPSILON);
    ASSERT_NEAR(resCalculated[1], expected[1], EPSILON);
}

void crossCovariance() {
    float data1[] = {0, 1, 2, 3, 10, 11, 12, 13};
    af::array xss(4, 2, data1);

    float data2[] = {4, 6, 8, 10, 12, 14, 16, 18, 20, 22};
    af::array yss(5, 2, data2);

    af::array calculated = khiva::features::crossCovariance(xss, yss, false);

    auto calculatedHost = khiva::utils::makeScopedHostPtr(calculated.host<float>());

    // Expected results obtained using statsmodels
    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(calculatedHost[(i * 5)], 2.5);
        ASSERT_EQ(calculatedHost[(i * 5) + 1], 2.5);
        ASSERT_EQ(calculatedHost[(i * 5) + 2], 0.25);
        ASSERT_EQ(calculatedHost[(i * 5) + 3], -1.25);
        ASSERT_EQ(calculatedHost[(i * 5) + 4], -1.5);
    }
}

void crossCovarianceBiased() {
    auto data1 = std::vector<float>{0, 1, 2, 3, 10, 11, 12, 13};
    af::array xss(4, 2, data1.data());

    auto data2 = std::vector<float>{4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 0};
    af::array yss(6, 2, data2.data());
    af::array calculated = khiva::features::crossCovariance(xss, yss, false);
    auto calculatedHost = khiva::utils::makeScopedHostPtr(calculated.host<float>());
    // Expected results obtained using statsmodels.
    auto expected =
        std::vector<float>{2.5f, 2.5f, 2.5f, -0.125f, -1.75f, -1.875f, 2.5f, 2.5f, -7.25f, -5.f, -0.666666f, 6.25f};
    int i = 0;
    for (const auto value : expected) {
        EXPECT_NEAR(calculatedHost[i + 12], value, 1e-4);
        EXPECT_NEAR(calculatedHost[i++], value, 1e-4);
    }
}

void crossCovarianceUnbiased() {
    float data1[] = {0, 1, 2, 3, 10, 11, 12, 13};
    af::array xss(4, 2, data1);

    float data2[] = {4, 6, 8, 10, 14, 16, 18, 20};
    af::array yss(4, 2, data2);

    af::array calculated = khiva::features::crossCovariance(xss, yss, true);

    auto calculatedHost = khiva::utils::makeScopedHostPtr(calculated.host<float>());

    // Expected results obtained using statsmodels
    for (int i = 0; i < 4; i++) {
        ASSERT_EQ(calculatedHost[(i * 4)], 2.5);
        ASSERT_NEAR(calculatedHost[(i * 4) + 1], 0.833333333, EPSILON);
        ASSERT_EQ(calculatedHost[(i * 4) + 2], -1.5);
        ASSERT_EQ(calculatedHost[(i * 4) + 3], -4.5);
    }
}

void autoCovariance() {
    float data[] = {0, 1, 2, 3, 10, 11, 12, 13};
    af::array tss(4, 2, data);

    af::array calculated = khiva::features::autoCovariance(tss);

    auto calculatedHost = khiva::utils::makeScopedHostPtr(calculated.host<float>());

    // Expected results obtained using statsmodels
    ASSERT_EQ(calculatedHost[0], 1.25);
    ASSERT_EQ(calculatedHost[1], 0.3125);
    ASSERT_EQ(calculatedHost[2], -0.375);
    ASSERT_EQ(calculatedHost[3], -0.5625);
    ASSERT_EQ(calculatedHost[4], 1.25);
    ASSERT_EQ(calculatedHost[5], 0.3125);
    ASSERT_EQ(calculatedHost[6], -0.375);
    ASSERT_EQ(calculatedHost[7], -0.5625);
}

void crossCorrelation() {
    float data1[] = {0, 1, 2, 3, 0, 1, 2, 3};
    af::array xs(4, 2, data1);

    float data2[] = {4, 6, 8, 10, 12, 4, 6, 8, 10, 12};
    af::array ys(5, 2, data2);

    af::array calculated = khiva::features::crossCorrelation(xs, ys, false);

    auto calculatedHost = khiva::utils::makeScopedHostPtr(calculated.host<float>());

    // // Expected results obtained using statsmodels
    for (int i = 0; i < 4; i++) {
        ASSERT_NEAR(calculatedHost[(i * 5)], 0.790569415, EPSILON);
        ASSERT_NEAR(calculatedHost[(i * 5) + 1], 0.790569415, EPSILON);
        ASSERT_NEAR(calculatedHost[(i * 5) + 2], 0.079056941, EPSILON);
        ASSERT_NEAR(calculatedHost[(i * 5) + 3], -0.395284707, EPSILON);
        ASSERT_NEAR(calculatedHost[(i * 5) + 4], -0.474341649, EPSILON);
    }
}

void autoCorrelation() {
    float data[] = {0, 1, 2, 3, 10, 11, 12, 13};
    af::array tss(4, 2, data);

    af::array calculated2 = khiva::features::autoCorrelation(tss, 4);

    auto calculated2Host = khiva::utils::makeScopedHostPtr(calculated2.host<float>());

    // Expected results obtained using tsfresh
    ASSERT_EQ(calculated2Host[0], 1.0);
    ASSERT_EQ(calculated2Host[1], 0.25);
    ASSERT_NEAR(calculated2Host[2], -0.3, EPSILON);
    ASSERT_NEAR(calculated2Host[3], -0.45, EPSILON);
    ASSERT_EQ(calculated2Host[4], 1.0);
    ASSERT_EQ(calculated2Host[5], 0.25);
    ASSERT_NEAR(calculated2Host[6], -0.3, EPSILON);
    ASSERT_NEAR(calculated2Host[7], -0.45, EPSILON);
}

void binnedEntropy() {
    float ts1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    float ts2[] = {1, 1, 3, 10, 5, 6, 1, 8, 9, 10, 11, 1, 13, 14, 10, 16, 17, 10, 19, 20};
    af::array h_data(20, 1, ts1);
    af::array h_data2(20, 1, ts2);
    af::array tss = af::join(1, h_data, h_data2);

    af::array output = khiva::features::binnedEntropy(tss, 5);

    auto h_out = khiva::utils::makeScopedHostPtr(output.host<float>());
    float a[] = {1.6094379124341005f, 1.5614694247763998f};
    ASSERT_NEAR(h_out[0], a[0], EPSILON);
    ASSERT_NEAR(h_out[1], a[1], EPSILON);
}

void c3() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(6, 2, data);

    af::array c3Result = khiva::features::c3(tss, 2);

    auto c3Calculated = khiva::utils::makeScopedHostPtr(c3Result.host<float>());

    ASSERT_EQ(c3Calculated[0], 7.5);
    ASSERT_EQ(c3Calculated[1], 586.5);
}

void cidCe() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(6, 2, data);

    af::array cidCeResult = khiva::features::cidCe(tss);

    auto cidCeCalculated = khiva::utils::makeScopedHostPtr(cidCeResult.host<float>());

    ASSERT_NEAR(cidCeCalculated[0], 2.23606797749979, EPSILON);
    ASSERT_NEAR(cidCeCalculated[1], 2.23606797749979, EPSILON);

    af::array cidCeResult2 = khiva::features::cidCe(tss, true);

    auto cidCeCalculated2 = khiva::utils::makeScopedHostPtr(cidCeResult2.host<float>());

    ASSERT_NEAR(cidCeCalculated2[0], 1.30930734141595, EPSILON);
    ASSERT_NEAR(cidCeCalculated2[1], 1.30930734141595, EPSILON);
}

void countAboveMean() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(6, 2, data);

    af::array countAboveMeanResult = khiva::features::countAboveMean(tss);

    auto countAboveMeanCalculated = khiva::utils::makeScopedHostPtr(countAboveMeanResult.host<unsigned int>());

    ASSERT_EQ(countAboveMeanCalculated[0], 3);
    ASSERT_EQ(countAboveMeanCalculated[1], 3);
}

void countBelowMean() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(6, 2, data);

    af::array countBelowMeanResult = khiva::features::countBelowMean(tss);

    auto countBelowMeanCalculated = khiva::utils::makeScopedHostPtr(countBelowMeanResult.host<unsigned int>());

    ASSERT_EQ(countBelowMeanCalculated[0], 3);
    ASSERT_EQ(countBelowMeanCalculated[1], 3);
}

void cwtCoefficients() {
    float data[] = {0.1f, 0.2f, 0.3f, 0.1f, 0.2f, 0.3f};
    int widths[] = {1, 2, 3};
    af::array data_d(3, 2, data);
    af::array widths_d(3, 1, widths);
    af::array result = khiva::features::cwtCoefficients(data_d, widths_d, 2, 2);

    auto cwt = khiva::utils::makeScopedHostPtr(result.host<float>());

    float r0 = 0.26517161726951599;
    float r1 = 0.26517161726951599;

    ASSERT_NEAR(r0, cwt[0], EPSILON);
    ASSERT_NEAR(r1, cwt[1], EPSILON);
}

void energyRatioByChunk() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(6, 2, data);

    af::array energyRatioByChunkResult = khiva::features::energyRatioByChunks(tss, 2, 0);

    auto energyRatioByChunkCalculated = khiva::utils::makeScopedHostPtr(energyRatioByChunkResult.host<float>());

    ASSERT_NEAR(energyRatioByChunkCalculated[0], 0.090909091, EPSILON);
    ASSERT_NEAR(energyRatioByChunkCalculated[1], 0.330376940, EPSILON);

    af::array energyRatioByChunkResult2 = khiva::features::energyRatioByChunks(tss, 2, 1);

    auto energyRatioByChunkCalculated2 = khiva::utils::makeScopedHostPtr(energyRatioByChunkResult2.host<float>());

    ASSERT_NEAR(energyRatioByChunkCalculated2[0], 0.909090909, EPSILON);
    ASSERT_NEAR(energyRatioByChunkCalculated2[1], 0.669623060, EPSILON);
}

void fftAggregated() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    af::array tss(10, 2, data);

    af::array fftAgg = khiva::features::fftAggregated(tss);

    auto fft = khiva::utils::makeScopedHostPtr(fftAgg.host<float>());
    float f1 = 1.135143f;
    float f2 = 2.368324f;
    float f3 = 1.248777f;
    float f4 = 3.642666f;

    ASSERT_NEAR(fft[0], f1, EPSILON);
    ASSERT_NEAR(fft[1], f2, EPSILON);
    ASSERT_NEAR(fft[2], f3, EPSILON);
    ASSERT_NEAR(fft[3], f4, EPSILON);

    ASSERT_NEAR(fft[4], f1, EPSILON);
    ASSERT_NEAR(fft[5], f2, EPSILON);
    ASSERT_NEAR(fft[6], f3, EPSILON);
    ASSERT_NEAR(fft[7], f4, EPSILON);
}

void fftCoefficient() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(6, 2, data);

    af::array real, imag, _abs, angle;

    khiva::features::fftCoefficient(tss, 0, real, imag, _abs, angle);

    auto realCalculated = khiva::utils::makeScopedHostPtr(real.host<float>());
    auto imagCalculated = khiva::utils::makeScopedHostPtr(imag.host<float>());
    auto _absCalculated = khiva::utils::makeScopedHostPtr(_abs.host<float>());
    auto angleCalculated = khiva::utils::makeScopedHostPtr(angle.host<float>());

    ASSERT_EQ(realCalculated[0], 15.0);
    ASSERT_EQ(realCalculated[1], 51.0);
    ASSERT_EQ(imagCalculated[0], 0.0);
    ASSERT_EQ(imagCalculated[1], 0.0);
    ASSERT_EQ(_absCalculated[0], 15.0);
    ASSERT_EQ(_absCalculated[1], 51.0);
    ASSERT_EQ(angleCalculated[0], 0.0);
    ASSERT_EQ(angleCalculated[1], 0.0);
}

void firstLocationOfMaximum() {
    float data[] = {5, 4, 3, 5, 0, 1, 5, 3, 2, 1, 2, 4, 3, 5, 2, 5, 4, 3, 5, 2};
    af::array tss(10, 2, data);

    af::array result = khiva::features::firstLocationOfMaximum(tss);

    auto hr = khiva::utils::makeScopedHostPtr(result.host<float>());

    ASSERT_EQ(hr[0], 0.0f);
    ASSERT_EQ(hr[1], 0.3f);
}

void firstLocationOfMinimum() {
    float data[] = {5, 4, 3, 0, 0, 1, 5, 4, 3, 0, 2, 1};
    af::array tss(6, 2, data);

    af::array result = khiva::features::firstLocationOfMinimum(tss);

    auto firstMinimumCalculated = khiva::utils::makeScopedHostPtr(result.host<float>());

    ASSERT_NEAR(firstMinimumCalculated[0], 0.5, EPSILON);
    ASSERT_NEAR(firstMinimumCalculated[1], 0.5, EPSILON);
}

void friedrichCoefficients() {
    float data[] = {0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5};
    af::array tss(6, 2, data);

    int m = 4;
    float r = 2;
    af::array result = khiva::features::friedrichCoefficients(tss, m, r);

    auto calculated = khiva::utils::makeScopedHostPtr(result.host<float>());

    ASSERT_NEAR(calculated[0], -0.00099125632550567389, EPSILON);
    ASSERT_NEAR(calculated[1], -0.0027067768387496471, EPSILON);
    ASSERT_NEAR(calculated[2], -0.00015192681166809052, EPSILON);
    ASSERT_NEAR(calculated[3], 0.10512571036815643, EPSILON);
    ASSERT_NEAR(calculated[4], 0.89872437715530396, EPSILON);
}

void hasDuplicates() {
    float data[] = {5, 4, 3, 0, 0, 1, 5, 4, 3, 0, 2, 1};
    af::array tss(6, 2, data);

    af::array duplicates = khiva::features::hasDuplicates(tss);

    auto duplicatesCalculated = khiva::utils::makeScopedHostPtr(duplicates.host<char>());

    ASSERT_EQ(duplicatesCalculated[0], true);
    ASSERT_EQ(duplicatesCalculated[1], false);
}

void hasDuplicateMax() {
    float data[] = {5, 4, 3, 0, 5, 1, 5, 4, 3, 0, 2, 1};
    af::array tss(6, 2, data);

    af::array out = khiva::features::hasDuplicateMax(tss);

    auto hout = khiva::utils::makeScopedHostPtr(out.host<char>());

    ASSERT_EQ(hout[0], true);
    ASSERT_EQ(hout[1], false);
}

void hasDuplicateMin() {
    float data[] = {5, 4, 3, 0, 0, 1, 5, 4, 3, 0, 2, 1};
    af::array tss(6, 2, data);

    af::array duplicateMin = khiva::features::hasDuplicateMin(tss);

    auto duplicateMinCalculated = khiva::utils::makeScopedHostPtr(duplicateMin.host<char>());

    ASSERT_EQ(duplicateMinCalculated[0], true);
    ASSERT_EQ(duplicateMinCalculated[1], false);
}

void indexMassQuantile() {
    float data[] = {5, 4, 3, 0, 0, 1, 5, 4, 0, 0, 2, 1};
    af::array tss(6, 2, data);
    float q = 0.5;

    af::array result = khiva::features::indexMassQuantile(tss, q);

    auto hresult = khiva::utils::makeScopedHostPtr(result.host<float>());
    float expected[] = {0.333333333f, 0.3333333333f};

    ASSERT_NEAR(hresult[0], expected[0], EPSILON);
    ASSERT_NEAR(hresult[1], expected[1], EPSILON);
}

void kurtosis() {
    float data[] = {0, 1, 2, 3, 4, 5, 2, 2, 2, 20, 30, 25};
    af::array tss(6, 2, data);

    float dataExpected[] = {-1.2f, -2.66226722f};

    auto result = khiva::utils::makeScopedHostPtr(khiva::features::kurtosis(tss).host<float>());

    for (int i = 0; i < 2; i++) {
        ASSERT_NEAR(dataExpected[i], result[i], EPSILON * 1e1);
    }
}

void largeStandardDeviation() {
    float data[] = {-1, -1, -1, 1, 1, 1, 4, 6, 8, 4, 5, 4};
    af::array tss(6, 2, data);
    float r = 0.4f;

    auto result = khiva::utils::makeScopedHostPtr(khiva::features::largeStandardDeviation(tss, r).host<char>());

    ASSERT_EQ(result[0], true);
    ASSERT_EQ(result[1], false);
}

void lastLocationOfMaximum() {
    float data[] = {0, 4, 3, 5, 5, 1, 0, 4, 3, 2, 5, 1};
    af::array tss(6, 2, data);

    af::array result = khiva::features::lastLocationOfMaximum(tss);

    auto lastMaximumCalculated = khiva::utils::makeScopedHostPtr(result.host<float>());

    ASSERT_NEAR(lastMaximumCalculated[0], 0.8333333333333334, EPSILON);
    ASSERT_NEAR(lastMaximumCalculated[1], 0.8333333333333334, EPSILON);
}

void lastLocationOfMinimum() {
    af::setBackend(af::Backend::AF_BACKEND_CPU);

    float data[] = {0, 4, 3, 5, 5, 1, 0, 4, 3, 2, 5, 1, 4, 5, 1, 2};
    af::array tss(8, 2, data);

    af::array result = khiva::features::lastLocationOfMinimum(tss);

    auto out = khiva::utils::makeScopedHostPtr(result.host<float>());

    ASSERT_EQ(out[0], 0.875f);
    ASSERT_EQ(out[1], 0.875f);
}

void length() {
    float data[] = {0, 4, 3, 5, 5, 1, 0, 4, 3, 2, 5, 1};
    af::array tss(6, 2, data);

    af::array result = khiva::features::length(tss);

    auto lengthCalculated = khiva::utils::makeScopedHostPtr(result.host<int>());

    ASSERT_EQ(lengthCalculated[0], 6);
    ASSERT_EQ(lengthCalculated[1], 6);
}

void linearTrend() {
    float data[] = {0, 4, 3, 5, 5, 1, 2, 4, 1, 2, 5, 3};
    af::array tss(6, 2, data);

    af::array pvalue, rvalue, intercept, slope, stder;
    khiva::features::linearTrend(tss, pvalue, rvalue, intercept, slope, stder);

    auto hpvalue = khiva::utils::makeScopedHostPtr(pvalue.host<float>());
    ASSERT_NEAR(hpvalue[0], 0.6260380997892747, EPSILON);
    ASSERT_NEAR(hpvalue[1], 0.5272201945463578, EPSILON);

    auto hrvalue = khiva::utils::makeScopedHostPtr(rvalue.host<float>());
    ASSERT_NEAR(hrvalue[0], 0.2548235957188128, EPSILON);
    ASSERT_NEAR(hrvalue[1], 0.3268228676411533, EPSILON);

    auto hintercept = khiva::utils::makeScopedHostPtr(intercept.host<float>());
    ASSERT_NEAR(hintercept[0], 2.2857142857142856, EPSILON);
    ASSERT_NEAR(hintercept[1], 2.1904761904761907, EPSILON);

    auto hslope = khiva::utils::makeScopedHostPtr(slope.host<float>());
    ASSERT_NEAR(hslope[0], 0.2857142857142857, EPSILON);
    ASSERT_NEAR(hslope[1], 0.2571428571428572, EPSILON);

    auto hstder = khiva::utils::makeScopedHostPtr(stder.host<float>());
    ASSERT_NEAR(hstder[0], 0.5421047417431507, EPSILON);
    ASSERT_NEAR(hstder[1], 0.37179469135129783, EPSILON);
}

void localMaximals() {
    float data[] = {0.0, 4.0, 3.0, 5.0, 4.0, 1.0, 0.0, 6.0, 0.0, 4.0, 3.0, 5.0, 4.0, 1.0, 0.0, 6.0};
    af::array tss(8, 2, data);

    af::array result = khiva::features::localMaximals(tss);

    auto lm = khiva::utils::makeScopedHostPtr(result.host<float>());

    ASSERT_EQ(lm[0], 0.0);
    ASSERT_EQ(lm[1], 1.0);
    ASSERT_EQ(lm[2], 0.0);
    ASSERT_EQ(lm[3], 1.0);
    ASSERT_EQ(lm[4], 0.0);
    ASSERT_EQ(lm[5], 0.0);
    ASSERT_EQ(lm[6], 0.0);
    ASSERT_EQ(lm[7], 1.0);
}

void longestStrikeAboveMean() {
    float data[] = {20, 20, 20, 1, 1, 1, 20, 20, 20, 20, 1, 1, 1, 1, 1, 1, 1, 1, 20, 20,
                    20, 20, 20, 1, 1, 1, 20, 20, 20, 1,  1, 1, 1, 1, 1, 1, 1, 1, 20, 20};
    af::array tss(20, 2, data);

    af::array result = khiva::features::longestStrikeAboveMean(tss);
    auto longestCalculated = khiva::utils::makeScopedHostPtr(result.host<float>());

    ASSERT_EQ(longestCalculated[0], 4);
    ASSERT_EQ(longestCalculated[1], 3);
}

void longestStrikeBelowMean() {
    float data[] = {20, 20, 20, 1, 1, 1, 20, 20, 20, 20, 1, 1, 1, 1, 1, 1, 1, 1, 20, 20,
                    20, 20, 20, 1, 1, 1, 20, 20, 20, 1,  1, 1, 1, 1, 1, 1, 1, 1, 20, 20};
    af::array tss(20, 2, data);

    af::array result = khiva::features::longestStrikeBelowMean(tss);
    auto longestCalculated = khiva::utils::makeScopedHostPtr(result.host<float>());

    ASSERT_EQ(longestCalculated[0], 8);
    ASSERT_EQ(longestCalculated[1], 9);
}

void maxLangevinFixedPoint() {
    float data[] = {0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5};
    af::array tss(6, 2, data);

    af::array result = khiva::features::maxLangevinFixedPoint(tss, 7, 2);

    auto calculated = khiva::utils::makeScopedHostPtr(result.host<float>());

    float expected[] = {4.562970585f, 4.562970585f};

    ASSERT_NEAR(calculated[0], expected[0], EPSILON * 1e4);
    ASSERT_NEAR(calculated[1], expected[1], EPSILON * 1e4);
}

void maximum() {
    float data[] = {20, 20, 20, 18, 25, 19, 20, 20, 20, 20, 40, 30, 1,  50, 1, 1,  5, 1, 20, 20,
                    20, 20, 20, 2,  19, 1,  20, 20, 20, 1,  15, 1,  30, 1,  1, 18, 4, 1, 20, 20};
    af::array tss(20, 2, data);

    af::array result = khiva::features::maximum(tss);

    auto maximum = khiva::utils::makeScopedHostPtr(result.host<float>());

    ASSERT_EQ(maximum[0], 50);
    ASSERT_EQ(maximum[1], 30);
}

void mean() {
    float data[] = {20, 20, 20, 18, 25, 19, 20, 20, 20, 20, 40, 30, 1,  50, 1, 1,  5, 1, 20, 20,
                    20, 20, 20, 2,  19, 1,  20, 20, 20, 1,  15, 1,  30, 1,  1, 18, 4, 1, 20, 20};
    af::array tss(20, 2, data);

    af::array result = khiva::features::mean(tss);
    auto mean = khiva::utils::makeScopedHostPtr(result.host<float>());

    ASSERT_NEAR(mean[0], 18.55, EPSILON * 2);
    ASSERT_NEAR(mean[1], 12.7, EPSILON * 2);
}

void meanAbsoluteChange() {
    float data[] = {0, 1, 2, 3, 4, 5, 8, 10, 12, 14, 16, 18};
    af::array tss(6, 2, data);

    af::array result = khiva::features::meanAbsoluteChange(tss);

    // check distances
    float r = 5.0f / 6.0f;
    auto hostResult = khiva::utils::makeScopedHostPtr(result.host<float>());
    ASSERT_NEAR(r, hostResult[0], EPSILON);
    ASSERT_NEAR(r * 2.0, hostResult[1], EPSILON);
}

void meanChange() {
    float data[] = {0, 1, 2, 3, 4, 5, 8, 10, 12, 14, 16, 18};
    af::array tss(6, 2, data);

    af::array result = khiva::features::meanChange(tss);

    // check distances
    float r = 5.0f / 6.0f;
    auto hostResult = khiva::utils::makeScopedHostPtr(result.host<float>());
    ASSERT_NEAR(r, hostResult[0], EPSILON);
    ASSERT_NEAR(r * 2.0, hostResult[1], EPSILON);
}

void meanSecondDerivativeCentral() {
    float data[] = {1, 3, 7, 4, 8, 2, 5, 1, 7, 4};
    af::array tss(5, 2, data);

    af::array result = khiva::features::meanSecondDerivativeCentral(tss);

    // check distances
    float r0 = 1.0f / 5.0f;
    float r1 = -3.0f / 5.0f;
    auto hostResult = khiva::utils::makeScopedHostPtr(result.host<float>());
    ASSERT_NEAR(r0, hostResult[0], EPSILON);
    ASSERT_NEAR(r1, hostResult[1], EPSILON);
}

void median() {
    float data[] = {20, 20, 20, 18, 25, 19, 20, 20, 20, 20, 40, 30, 1,  50, 1, 1,  5, 1, 20, 20,
                    20, 20, 20, 2,  19, 1,  20, 20, 20, 1,  15, 1,  30, 1,  1, 18, 4, 1, 20, 20};
    af::array tss(20, 2, data);

    af::array result = khiva::features::median(tss);

    auto median = khiva::utils::makeScopedHostPtr(result.host<float>());

    ASSERT_NEAR(median[0], 20, EPSILON * 2);
    ASSERT_NEAR(median[1], 18.5, EPSILON * 2);
}

void minimum() {
    float data[] = {20, 20, 20, 18, 25, 19, 20, 20, 20, 20, 40, 30, 1,  50, 13, 15, 5, 16, 20, 20,
                    20, 20, 20, 2,  19, 4,  20, 20, 20, 4,  15, 6,  30, 7,  9,  18, 4, 10, 20, 20};
    af::array tss(20, 2, data);

    af::array result = khiva::features::minimum(tss);

    auto minimum = khiva::utils::makeScopedHostPtr(result.host<float>());

    ASSERT_EQ(minimum[0], 1);
    ASSERT_EQ(minimum[1], 2);
}

void numberCrossingM() {
    float data[] = {1, 2, 1, 1, -3, -4, 7, 8, 9, 10, -2, 1, -3, 5, 6, 7, -10,
                    1, 2, 1, 1, -3, -4, 7, 8, 9, 10, -2, 1, -3, 5, 6, 7, -10};
    af::array tss(17, 2, data);

    af::array result = khiva::features::numberCrossingM(tss, 0);

    auto ncm = khiva::utils::makeScopedHostPtr(result.host<float>());

    ASSERT_EQ(ncm[0], 7);
    ASSERT_EQ(ncm[1], 7);
}

void numberCwtPeaks() {
    float data[] = {1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 1, 1, 1, 1, 5, 1, 1, 1, 1, 1, 1,
                    1, 1, 1, 1, 1, 1, 1, 5, 1, 1, 1, 1, 1, 1, 5, 1, 1, 1, 1, 1, 1};
    af::array tss(21, 2, data);

    af::array result = khiva::features::numberCwtPeaks(tss, 2);

    auto ncp = khiva::utils::makeScopedHostPtr(result.host<float>());

    ASSERT_EQ(ncp[0], 2);
    ASSERT_EQ(ncp[1], 2);
}

void numberPeaks() {
    float data[] = {3, 0, 0, 4, 0, 0, 13, 3, 0, 0, 4, 0, 0, 13};
    af::array tss(7, 2, data);

    af::array result = khiva::features::numberPeaks(tss, 2);

    auto np = khiva::utils::makeScopedHostPtr(result.host<float>());

    ASSERT_EQ(np[0], 1);
    ASSERT_EQ(np[1], 1);
}

void partialAutocorrelation() {
    auto len = 3000;
    std::vector<float> input;
    input.reserve(len);
    float step = 1.0f / (len - 1);
    int j = 0;
    std::generate_n(std::back_inserter(input), len, [&j, step]() { return step * j++; });

    af::array ts(len, 1, input.data());
    af::array tss = af::tile(ts, 1, 2);

    int lags[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    af::array lags_d(10, 1, lags);

    af::array result = khiva::features::partialAutocorrelation(tss, lags_d);
    auto pa = khiva::utils::makeScopedHostPtr(result.col(0).host<float>());

    ASSERT_NEAR(pa[0], 1.0, 1e-3);
    ASSERT_NEAR(pa[1], 0.9993331432342529, 1e-3);
    ASSERT_NEAR(pa[2], -0.0006701064994559, 1e-3);
    ASSERT_NEAR(pa[3], -0.0006701068487018, 1e-3);
    ASSERT_NEAR(pa[4], -0.0008041285327636, 1e-3);
    ASSERT_NEAR(pa[5], -0.0005360860959627, 1e-3);
    ASSERT_NEAR(pa[6], -0.0007371186511591, 1e-3);
    ASSERT_NEAR(pa[7], -0.0004690756904893, 1e-3);
    ASSERT_NEAR(pa[8], -0.0008041299879551, 1e-3);
    ASSERT_NEAR(pa[9], -0.0007371196406893, 1e-3);
}

void percentageOfReoccurringDatapointsToAllDatapoints() {
    float data[] = {3, 0, 0, 4, 0, 0, 13, 3, 0, 0, 4, 0, 0, 13};
    af::array tss(7, 2, data);

    af::array result = khiva::features::percentageOfReoccurringDatapointsToAllDatapoints(tss, false);

    auto calculated = khiva::utils::makeScopedHostPtr(result.host<float>());

    float expected[] = {0.25, 0.25};

    ASSERT_EQ(calculated[0], expected[0]);
    ASSERT_EQ(calculated[1], expected[1]);
}

void percentageOfReoccurringValuesToAllValues() {
    float data[] = {1, 1, 2, 3, 4, 4, 5, 6, 1, 2, 2, 3, 4, 5, 6, 7};
    af::array tss(8, 2, data);

    af::array result = khiva::features::percentageOfReoccurringValuesToAllValues(tss, false);

    auto calculated = khiva::utils::makeScopedHostPtr(result.host<float>());

    float expected[] = {4.0 / 8.0, 2.0 / 8.0};

    ASSERT_EQ(calculated[0], expected[0]);
    ASSERT_EQ(calculated[1], expected[1]);
}

void quantile() {
    float data[] = {3, 0, 0, 4, 0, 0, 13, 3, 0, 0, 4, 0, 0, 13};
    af::array tss(7, 2, data);

    tss = af::sort(tss, 0);

    float q[] = {0.6f};
    af::array qq = af::array(1, q);

    af::array result = khiva::features::quantile(tss, qq);

    auto calculated = khiva::utils::makeScopedHostPtr(result.host<float>());

    float expected[] = {1.79999999f, 1.79999999f};

    ASSERT_NEAR(calculated[0], expected[0], EPSILON);
    ASSERT_NEAR(calculated[1], expected[1], EPSILON);
}

void rangeCount() {
    float data[] = {3, 0, 0, 4, 0, 0, 13, 3, 0, 5, 4, 0, 0, 13};
    af::array tss(7, 2, data);

    af::array result = khiva::features::rangeCount(tss, 2, 12);

    auto calculated = khiva::utils::makeScopedHostPtr(result.host<float>());

    float expected[] = {2, 3};

    ASSERT_EQ(calculated[0], expected[0]);
    ASSERT_EQ(calculated[1], expected[1]);
}

void ratioBeyondRSigma() {
    float data[] = {3, 0, 0, 4, 0, 0, 13, 3, 0, 0, 4, 0, 0, 13};
    af::array tss(7, 2, data);

    af::array result = khiva::features::ratioBeyondRSigma(tss, 0.5);

    auto calculated = khiva::utils::makeScopedHostPtr(result.host<float>());

    float expected[] = {0.7142857142857143f, 0.7142857142857143f};

    ASSERT_NEAR(calculated[0], expected[0], EPSILON);
    ASSERT_NEAR(calculated[1], expected[1], EPSILON);
}

void ratioValueNumberToTimeSeriesLength() {
    float data[] = {3, 0, 0, 4, 0, 0, 13, 3, 5, 0, 4, 6, 0, 13};
    af::array tss(7, 2, data);

    af::array result = khiva::features::ratioValueNumberToTimeSeriesLength(tss);

    auto calculated = khiva::utils::makeScopedHostPtr(result.host<float>());

    float expected[] = {4.0f / 7.0f, 6.0f / 7.0f};

    ASSERT_NEAR(calculated[0], expected[0], EPSILON);
    ASSERT_NEAR(calculated[1], expected[1], EPSILON);
}

void sampleEntropy() {
    float data[] = {3, 0, 0, 4, 0, 0, 13, 3, 0, 0, 4, 0, 0, 13};
    af::array tss(7, 2, data);

    af::array result = khiva::features::sampleEntropy(tss);

    auto calculated = khiva::utils::makeScopedHostPtr(result.host<float>());

    float expected[] = {1.252762968495368f, 1.252762968495368f};

    ASSERT_NEAR(calculated[0], expected[0], EPSILON);
    ASSERT_NEAR(calculated[1], expected[1], EPSILON);
}

void skewness() {
    float data[] = {3, 0, 0, 4, 0, 0, 13, 3, 0, 0, 4, 0, 0, 13};
    af::array tss(7, 2, data);

    af::array result = khiva::features::skewness(tss);

    auto calculated = khiva::utils::makeScopedHostPtr(result.host<float>());

    float expected[] = {2.038404735373753f, 2.038404735373753f};

    ASSERT_NEAR(calculated[0], expected[0], EPSILON);
    ASSERT_NEAR(calculated[1], expected[1], EPSILON);
}

void spktWelchDensity() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    af::array tss(10, 2, data);
    int coeff = 0;

    af::array result = khiva::features::spktWelchDensity(tss, coeff);
    auto calculated = khiva::utils::makeScopedHostPtr(result.host<float>());

    float expected[] = {1.6666667461395264, 1.6666667461395264};

    ASSERT_NEAR(calculated[0], expected[0], 1e-5);
    ASSERT_NEAR(calculated[1], expected[1], 1e-5);
}

void standardDeviation() {
    float data[] = {20, 20, 20, 18, 25, 19, 20, 20, 20, 20, 40, 30, 1,  50, 1, 1,  5, 1, 20, 20,
                    20, 20, 20, 2,  19, 1,  20, 20, 20, 1,  15, 1,  30, 1,  1, 18, 4, 1, 20, 20};
    af::array tss(20, 2, data);

    af::array result = khiva::features::standardDeviation(tss);

    auto stdev = khiva::utils::makeScopedHostPtr(result.host<float>());

    ASSERT_NEAR(stdev[0], 12.363150892875165, EPSILON);
    ASSERT_NEAR(stdev[1], 9.51367436903324, EPSILON);
}

void sumOfReoccurringDatapoints() {
    float data[] = {3, 3, 0, 4, 0, 13, 13, 3, 3, 0, 4, 0, 13, 13};
    af::array tss(7, 2, data);

    af::array result = khiva::features::sumOfReoccurringDatapoints(tss, false);

    auto calculated = khiva::utils::makeScopedHostPtr(result.host<float>());

    float expected[] = {32, 32};

    ASSERT_EQ(calculated[0], expected[0]);
    ASSERT_EQ(calculated[1], expected[1]);
}

void sumOfReoccurringValues() {
    float data[] = {4, 4, 6, 6, 7, 4, 7, 7, 8, 8};
    af::array tss(5, 2, data);

    af::array result = khiva::features::sumOfReoccurringValues(tss, false);

    auto calculated = khiva::utils::makeScopedHostPtr(result.host<float>());

    float expected[] = {10, 15};

    ASSERT_EQ(calculated[0], expected[0]);
    ASSERT_EQ(calculated[1], expected[1]);
}

void sumValues() {
    float data[] = {1, 2, 3, 4.1f, -1.2f, -2, -3, -4};
    af::array tss(4, 2, data);

    af::array result = khiva::features::sumValues(tss);

    auto sv = khiva::utils::makeScopedHostPtr(result.host<float>());
    float expected[] = {10.1f, -10.2f};

    ASSERT_EQ(sv[0], expected[0]);
    ASSERT_EQ(sv[1], expected[1]);
}

void symmetryLooking() {
    float data[] = {20, 20, 20, 18, 25, 19, 20, 20, 20, 20, 40, 30, 1,  50, 1, 1,  5, 1, 20, 20,
                    20, 20, 20, 2,  19, 1,  20, 20, 20, 1,  15, 1,  30, 1,  1, 18, 4, 1, 20, 20};
    af::array tss(20, 2, data);

    af::array result = khiva::features::symmetryLooking(tss, 0.1f);

    auto sl = khiva::utils::makeScopedHostPtr(result.host<char>());

    ASSERT_EQ(sl[0], 1);
    ASSERT_EQ(sl[1], 0);
}

void timeReversalAsymmetryStatistic() {
    float data[] = {1,  2,  3,  4, 5,  6, 7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
                    20, 20, 20, 2, 19, 1, 20, 20, 20, 1,  15, 1,  30, 1,  1,  18, 4,  1,  20, 20};
    af::array tss(20, 2, data);

    af::array result = khiva::features::timeReversalAsymmetryStatistic(tss, 2);

    auto r = khiva::utils::makeScopedHostPtr(result.host<float>());

    ASSERT_EQ(r[0], 1052);
    ASSERT_EQ(r[1], -150.625);
}

void valueCount() {
    float data[] = {20, 20, 20, 18, 25, 19, 20, 20, 20, 20, 40, 30, 1,  50, 1, 1,  5, 1, 20, 20,
                    20, 20, 20, 2,  19, 1,  20, 20, 20, 1,  15, 1,  30, 1,  1, 18, 4, 1, 20, 20};
    af::array tss(20, 2, data);

    af::array result = khiva::features::valueCount(tss, 20);

    auto vc = khiva::utils::makeScopedHostPtr(result.host<unsigned int>());

    ASSERT_EQ(vc[0], 9);
    ASSERT_EQ(vc[1], 8);
}

void variance() {
    float data[] = {1, 1, -1, -1, 1, 2, -2, -1};
    af::array tss(4, 2, data);

    af::array result = khiva::features::variance(tss);

    auto v = khiva::utils::makeScopedHostPtr(result.host<float>());

    ASSERT_EQ(v[0], 1.0);
    ASSERT_EQ(v[1], 2.5);
}

void varianceLargerThanStandardDeviation() {
    float data[] = {20, 20, 20, 18, 25, 19, 20, 20, 20, 20, 40, 30, 1,  50, 1, 1,  5, 1, 20, 20,
                    20, 20, 20, 2,  19, 1,  20, 20, 20, 1,  15, 1,  30, 1,  1, 18, 4, 1, 20, 20};
    af::array tss(20, 2, data);

    af::array result = khiva::features::varianceLargerThanStandardDeviation(tss);

    auto vlts = khiva::utils::makeScopedHostPtr(result.host<char>());

    ASSERT_EQ(vlts[0], 1);
    ASSERT_EQ(vlts[1], 1);
}

KHIVA_TEST(FeaturesTests, AbsEnergy, absEnergy)
KHIVA_TEST(FeaturesTests, AbsEnergy2, absEnergy2)
KHIVA_TEST(FeaturesTests, AbsoluteSumOfChanges, absoluteSumOfChanges)
KHIVA_TEST(FeaturesTests, AggregatedCorrelationMean, aggregatedCorrelationMean)
KHIVA_TEST(FeaturesTests, AggregatedCorrelationMedian, aggregatedCorrelationMedian)
KHIVA_TEST(FeaturesTests, AggregatedCorrelationMin, aggregatedCorrelationMin)
KHIVA_TEST(FeaturesTests, AggregatedCorrelationMax, aggregatedCorrelationMax)
KHIVA_TEST(FeaturesTests, AggregatedCorrelationStdev, aggregatedCorrelationStdev)
KHIVA_TEST(FeaturesTests, AggregatedCorrelationVar, aggregatedCorrelationVar)
KHIVA_TEST(FeaturesTests, AggregatedLinearTrendMean, aggregatedLinearTrendMean)
KHIVA_TEST(FeaturesTests, AggregatedLinearTrendMin, aggregatedLinearTrendMin)
KHIVA_TEST(FeaturesTests, AggregatedLinearTrendMultipleSeriesMean, aggregatedLinearTrendMultipleSeriesMean)
KHIVA_TEST(FeaturesTests, AggregatedLinearTrendMultipleSeriesMin, aggregatedLinearTrendMultipleSeriesMin)
KHIVA_TEST(FeaturesTests, ApproximateEntropy, approximateEntropy)
KHIVA_TEST(FeaturesTests, CrossCovariance, crossCovariance)
KHIVA_TEST(FeaturesTests, CrossCovarianceBiased, crossCovarianceBiased)
KHIVA_TEST(FeaturesTests, CrossCovarianceUnbiased, crossCovarianceUnbiased)
KHIVA_TEST(FeaturesTests, AutoCovariance, autoCovariance)
KHIVA_TEST(FeaturesTests, CrossCorrelation, crossCorrelation)
KHIVA_TEST(FeaturesTests, AutoCorrelation, autoCorrelation)
KHIVA_TEST(FeaturesTests, BinnedEntropy, binnedEntropy)
KHIVA_TEST(FeaturesTests, C3, c3)
KHIVA_TEST(FeaturesTests, CidCe, cidCe)
KHIVA_TEST(FeaturesTests, CountAboveMean, countAboveMean)
KHIVA_TEST(FeaturesTests, CountBelowMean, countBelowMean)
KHIVA_TEST(FeaturesTests, CwtCoefficients, cwtCoefficients)
KHIVA_TEST(FeaturesTests, EnergyRatioByChunk, energyRatioByChunk)
KHIVA_TEST(FeaturesTests, FftAggregated, fftAggregated)
KHIVA_TEST(FeaturesTests, FftCoefficient, fftCoefficient)
KHIVA_TEST(FeaturesTests, FirstLocationOfMaximum, firstLocationOfMaximum)
KHIVA_TEST(FeaturesTests, FirstLocationOfMinimum, firstLocationOfMinimum)
KHIVA_TEST(FeaturesTests, FriedrichCoefficients, friedrichCoefficients)
KHIVA_TEST(FeaturesTests, HasDuplicates, hasDuplicates)
KHIVA_TEST(FeaturesTests, HasDuplicateMax, hasDuplicateMax)
KHIVA_TEST(FeaturesTests, HasDuplicateMin, hasDuplicateMin)
KHIVA_TEST(FeaturesTests, IndexMassQuantile, indexMassQuantile)
KHIVA_TEST(FeaturesTests, Kurtosis, kurtosis)
KHIVA_TEST(FeaturesTests, LargeStandardDeviation, largeStandardDeviation)
KHIVA_TEST(FeaturesTests, LastLocationOfMaximum, lastLocationOfMaximum)
KHIVA_TEST(FeaturesTests, LastLocationOfMinimum, lastLocationOfMinimum)
KHIVA_TEST(FeaturesTests, Length, length)
KHIVA_TEST(FeaturesTests, LinearTrend, linearTrend)
KHIVA_TEST(FeaturesTests, LocalMaximals, localMaximals)
KHIVA_TEST(FeaturesTests, LongestStrikeAboveMean, longestStrikeAboveMean)
KHIVA_TEST(FeaturesTests, LongestStrikeBelowMean, longestStrikeBelowMean)
KHIVA_TEST(FeaturesTests, MaxLangevinFixedPoint, maxLangevinFixedPoint)
KHIVA_TEST(FeaturesTests, Maximum, maximum)
KHIVA_TEST(FeaturesTests, Mean, mean)
KHIVA_TEST(FeaturesTests, MeanAbsoluteChange, meanAbsoluteChange)
KHIVA_TEST(FeaturesTests, MeanChange, meanChange)
KHIVA_TEST(FeaturesTests, MeanSecondDerivativeCentral, meanSecondDerivativeCentral)
KHIVA_TEST(FeaturesTests, Median, median)
KHIVA_TEST(FeaturesTests, Minimum, minimum)
KHIVA_TEST(FeaturesTests, NumberCrossingM, numberCrossingM)
KHIVA_TEST(FeaturesTests, NumberCwtPeaks, numberCwtPeaks)
KHIVA_TEST(FeaturesTests, NumberPeaks, numberPeaks)
KHIVA_TEST(FeaturesTests, PartialAutocorrelation, partialAutocorrelation)
KHIVA_TEST(FeaturesTests, PercentageOfReoccurringDatapointsToAllDatapoints,
           percentageOfReoccurringDatapointsToAllDatapoints)
KHIVA_TEST(FeaturesTests, PercentageOfReoccurringValuesToAllValues, percentageOfReoccurringValuesToAllValues)
KHIVA_TEST(FeaturesTests, Quantile, quantile)
KHIVA_TEST(FeaturesTests, RangeCount, rangeCount)
KHIVA_TEST(FeaturesTests, RatioBeyondRSigma, ratioBeyondRSigma)
KHIVA_TEST(FeaturesTests, RatioValueNumberToTimeSeriesLength, ratioValueNumberToTimeSeriesLength)
KHIVA_TEST(FeaturesTests, SampleEntropy, sampleEntropy)
KHIVA_TEST(FeaturesTests, Skewness, skewness)
KHIVA_TEST(FeaturesTests, SpktWelchDensity, spktWelchDensity)
KHIVA_TEST(FeaturesTests, StandardDeviation, standardDeviation)
KHIVA_TEST(FeaturesTests, SumOfReoccurringDatapoints, sumOfReoccurringDatapoints)
KHIVA_TEST(FeaturesTests, SumOfReoccurringValues, sumOfReoccurringValues)
KHIVA_TEST(FeaturesTests, SumValues, sumValues)
KHIVA_TEST(FeaturesTests, SymmetryLooking, symmetryLooking)
KHIVA_TEST(FeaturesTests, TimeReversalAsymmetryStatistic, timeReversalAsymmetryStatistic)
KHIVA_TEST(FeaturesTests, ValueCount, valueCount)
KHIVA_TEST(FeaturesTests, Variance, variance)
KHIVA_TEST(FeaturesTests, VarianceLargerThanStandardDeviation, varianceLargerThanStandardDeviation)
