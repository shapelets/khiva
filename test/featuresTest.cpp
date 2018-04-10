// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <tsa/features.h>
#include "tsaTest.h"

void absEnergy() {
    float data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    af::array tss(10, 1, data);

    auto result = tsa::features::absEnergy(tss);

    float expected[] = {385};
    float *host_res = result.host<float>();

    for (int i = 0; i < 1; i++) {
        ASSERT_NEAR(host_res[i], expected[i], EPSILON);
    }
}

void absEnergy2() {
    float data[] = {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4};
    af::array tss(4, 3, data);

    auto result = tsa::features::absEnergy(tss);

    float expected[] = {30, 30, 30};
    float *host_res = result.row(0).host<float>();

    for (int i = 0; i < 3; i++) {
        ASSERT_NEAR(host_res[i], expected[i], EPSILON);
    }
}

void absoluteSumOfChanges() {
    float data[] = {0, 1, 2, 3, 4, 6, 8, 10, 11, 14, 17, 20};
    af::array tss(4, 3, data);

    af::array asoc = tsa::features::absoluteSumOfChanges(tss);

    // check dimensions
    af::dim4 dims = asoc.dims();
    ASSERT_EQ(dims[0], 1);
    ASSERT_EQ(dims[1], 3);
    ASSERT_EQ(dims[2], 1);
    ASSERT_EQ(dims[3], 1);

    // check distances
    float *hostResult = asoc.host<float>();
    ASSERT_EQ(3, hostResult[0]);
    ASSERT_EQ(6, hostResult[1]);
    ASSERT_EQ(9, hostResult[2]);
}

void aggregatedCorrelationMean() {
    float data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    af::array tss(6, 2, data);

    af::array res = tsa::features::aggregatedAutocorrelation(tss, af::mean);
    float *r = res.host<float>();
    float a[] = {-0.6571428571428571, -0.6571428571428571};
    ASSERT_NEAR(r[0], a[0], EPSILON);
    ASSERT_NEAR(r[1], a[1], EPSILON);
}

void aggregatedCorrelationMedian() {
    float data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    af::array tss(6, 2, data);

    af::array res = tsa::features::aggregatedAutocorrelation(tss, af::median);
    float *r = res.host<float>();
    float a[] = {-0.54285717010498047, -0.54285717010498047};
    ASSERT_NEAR(r[0], a[0], EPSILON);
    ASSERT_NEAR(r[1], a[1], EPSILON);
}

void aggregatedCorrelationMin() {
    float data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    af::array tss(6, 2, data);

    af::array res = tsa::features::aggregatedAutocorrelation(tss, af::min);
    float *r = res.host<float>();
    float a[] = {-2.142857142857143, -2.142857142857143};
    ASSERT_NEAR(r[0], a[0], EPSILON * 2);
    ASSERT_NEAR(r[1], a[1], EPSILON * 2);
}

void aggregatedCorrelationMax() {
    float data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    af::array tss(6, 2, data);

    af::array res = tsa::features::aggregatedAutocorrelation(tss, af::max);
    float *r = res.host<float>();
    float a[] = {0.6, 0.6};
    ASSERT_NEAR(r[0], a[0], EPSILON);
    ASSERT_NEAR(r[1], a[1], EPSILON);
}

void aggregatedCorrelationStdev() {
    float data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    af::array tss(6, 2, data);

    af::array res = tsa::features::aggregatedAutocorrelation(tss, af::stdev);
    float *r = res.host<float>();
    float a[] = {0.9744490855905009, 0.9744490855905009};
    ASSERT_NEAR(r[0], a[0], EPSILON);
    ASSERT_NEAR(r[1], a[1], EPSILON);
}

void aggregatedCorrelationVar() {
    float data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    af::array tss(6, 2, data);

    af::array res = tsa::features::aggregatedAutocorrelation(tss, af::var);
    float *r = res.host<float>();
    float a[] = {0.9495510204081633, 0.9495510204081633};
    ASSERT_NEAR(r[0], a[0], EPSILON);
    ASSERT_NEAR(r[1], a[1], EPSILON);
}

void aggregatedLinearTrendMean() {
    float data[] = {2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5};
    af::array tss(12, data);

    af::array slope, intercept, rvalue, pvalue, stderrest;

    tsa::features::aggregatedLinearTrend(tss, 3, af::mean, slope, intercept, rvalue, pvalue, stderrest);

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

    tsa::features::aggregatedLinearTrend(tss, 3, af::min, slope, intercept, rvalue, pvalue, stderrest);

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

    tsa::features::aggregatedLinearTrend(tss, 3, af::mean, slope, intercept, rvalue, pvalue, stderrest);

    float *slopeCalculated = slope.host<float>();
    float *interceptCalculated = intercept.host<float>();
    float *rvalueCalculated = rvalue.host<float>();
    float *pvalueCalculated = pvalue.host<float>();
    float *stderrestCalculated = stderrest.host<float>();

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

    tsa::features::aggregatedLinearTrend(tss, 3, af::mean, slope, intercept, rvalue, pvalue, stderrest);

    float *slopeCalculated = slope.host<float>();
    float *interceptCalculated = intercept.host<float>();
    float *rvalueCalculated = rvalue.host<float>();
    float *pvalueCalculated = pvalue.host<float>();
    float *stderrestCalculated = stderrest.host<float>();

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
    a(span, 1) += 10;

    af::array res = tsa::features::approximateEntropy(a, m, r);

    float *resCalculated = res.host<float>();

    float expected[] = {0.13484275341033936, 0.13484275341033936};

    ASSERT_NEAR(resCalculated[0], expected[0], EPSILON);
    ASSERT_NEAR(resCalculated[1], expected[1], EPSILON);
}

void crossCovariance() {
    float data1[] = {0, 1, 2, 3, 10, 11, 12, 13};
    af::array xss(4, 2, data1);

    float data2[] = {4, 6, 8, 10, 12, 14, 16, 18, 20, 22};
    af::array yss(5, 2, data2);

    af::array calculated = tsa::features::crossCovariance(xss, yss, false);

    float *calculatedHost = calculated.host<float>();

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
    float data1[] = {0, 1, 2, 3, 10, 11, 12, 13};
    af::array xss(4, 2, data1);

    float data2[] = {4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24};
    af::array yss(6, 2, data2);

    af::array calculated = tsa::features::crossCovariance(xss, yss, false);

    float *calculatedHost = calculated.host<float>();

    // Expected results obtained using statsmodels
    for (int i = 0; i < 2; i++) {
        ASSERT_EQ(calculatedHost[(i * 12)], 2.5);
        ASSERT_NEAR(calculatedHost[(i * 12) + 1], 2.499999999, EPSILON);
        ASSERT_EQ(calculatedHost[(i * 12) + 2], 2.5);
        ASSERT_NEAR(calculatedHost[(i * 12) + 3], -0.124999999, EPSILON * 1e3);
        ASSERT_NEAR(calculatedHost[(i * 12) + 4], -1.75, EPSILON * 1e1);
        ASSERT_NEAR(calculatedHost[(i * 12) + 5], -1.874999999, EPSILON);
        ASSERT_NEAR(calculatedHost[(i * 12) + 6], 2.5, EPSILON);
        ASSERT_NEAR(calculatedHost[(i * 12) + 7], 2.5, EPSILON);
        ASSERT_EQ(calculatedHost[(i * 12) + 8], -7.25);
        ASSERT_NEAR(calculatedHost[(i * 12) + 9], -5, EPSILON * 1e1);
        ASSERT_NEAR(calculatedHost[(i * 12) + 10], -0.666666666, EPSILON * 1e1);
        ASSERT_NEAR(calculatedHost[(i * 12) + 11], 6.25, EPSILON);
    }
}

void crossCovarianceUnbiased() {
    float data1[] = {0, 1, 2, 3, 10, 11, 12, 13};
    af::array xss(4, 2, data1);

    float data2[] = {4, 6, 8, 10, 14, 16, 18, 20};
    af::array yss(4, 2, data2);

    af::array calculated = tsa::features::crossCovariance(xss, yss, true);

    float *calculatedHost = calculated.host<float>();

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

    af::array calculated = tsa::features::autoCovariance(tss);

    float *calculatedHost = calculated.host<float>();

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
    float data1[] = {0, 1, 2, 3};
    af::array xs(4, data1);

    float data2[] = {4, 6, 8, 10, 12};
    af::array ys(5, data2);

    af::array calculated = tsa::features::crossCorrelation(xs, ys, false);

    float *calculatedHost = calculated.host<float>();

    // Expected results obtained using statsmodels
    ASSERT_NEAR(calculatedHost[0], 0.790569415, EPSILON);
    ASSERT_NEAR(calculatedHost[1], 0.790569415, EPSILON);
    ASSERT_NEAR(calculatedHost[2], 0.079056941, EPSILON);
    ASSERT_NEAR(calculatedHost[3], -0.395284707, EPSILON);
    ASSERT_NEAR(calculatedHost[4], -0.474341649, EPSILON);
}

void autoCorrelation() {
    float data[] = {0, 1, 2, 3, 10, 11, 12, 13};
    af::array tss(4, 2, data);

    af::array calculated2 = tsa::features::autoCorrelation(tss, 4);

    float *calculated2Host = calculated2.host<float>();

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

    af::array output = tsa::features::binnedEntropy(tss, 5);

    float *h_out = output.host<float>();
    float a[] = {1.6094379124341005, 1.5614694247763998};
    ASSERT_NEAR(h_out[0], a[0], EPSILON);
    ASSERT_NEAR(h_out[1], a[1], EPSILON);
}

void c3() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(6, 2, data);

    af::array c3Result = tsa::features::c3(tss, 2);

    float *c3Calculated = c3Result.host<float>();

    ASSERT_EQ(c3Calculated[0], 7.5);
    ASSERT_EQ(c3Calculated[1], 586.5);
}

void cidCe() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(6, 2, data);

    af::array cidCeResult = tsa::features::cidCe(tss);

    float *cidCeCalculated = cidCeResult.host<float>();

    ASSERT_NEAR(cidCeCalculated[0], 2.23606797749979, EPSILON);
    ASSERT_NEAR(cidCeCalculated[1], 2.23606797749979, EPSILON);

    af::array cidCeResult2 = tsa::features::cidCe(tss, true);

    float *cidCeCalculated2 = cidCeResult2.host<float>();

    ASSERT_NEAR(cidCeCalculated2[0], 1.30930734141595, EPSILON);
    ASSERT_NEAR(cidCeCalculated2[1], 1.30930734141595, EPSILON);
}

void countAboveMean() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(6, 2, data);

    af::array countAboveMeanResult = tsa::features::countBelowMean(tss);

    unsigned int *countAboveMeanCalculated = countAboveMeanResult.host<unsigned int>();

    ASSERT_EQ(countAboveMeanCalculated[0], 3);
    ASSERT_EQ(countAboveMeanCalculated[1], 3);
}

void countBelowMean() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(6, 2, data);

    af::array countBelowMeanResult = tsa::features::countBelowMean(tss);

    unsigned int *countBelowMeanCalculated = countBelowMeanResult.host<unsigned int>();

    ASSERT_EQ(countBelowMeanCalculated[0], 3);
    ASSERT_EQ(countBelowMeanCalculated[1], 3);
}

void energyRatioByChunk() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(6, 2, data);

    af::array energyRatioByChunkResult = tsa::features::energyRatioByChunks(tss, 2, 0);

    float *energyRatioByChunkCalculated = energyRatioByChunkResult.host<float>();

    ASSERT_NEAR(energyRatioByChunkCalculated[0], 0.090909091, EPSILON);
    ASSERT_NEAR(energyRatioByChunkCalculated[1], 0.330376940, EPSILON);

    af::array energyRatioByChunkResult2 = tsa::features::energyRatioByChunks(tss, 2, 1);

    float *energyRatioByChunkCalculated2 = energyRatioByChunkResult2.host<float>();

    ASSERT_NEAR(energyRatioByChunkCalculated2[0], 0.909090909, EPSILON);
    ASSERT_NEAR(energyRatioByChunkCalculated2[1], 0.669623060, EPSILON);
}

void fftAggregated() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    af::array tss(10, 2, data);

    af::array fftAgg = tsa::features::fftAggregated(tss);

    float *fft = fftAgg.host<float>();
    float f1 = 1.135143;
    float f2 = 2.368324;
    float f3 = 1.248777;
    float f4 = 3.642666;

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

    tsa::features::fftCoefficient(tss, 0, real, imag, _abs, angle);

    float *realCalculated = real.host<float>();
    float *imagCalculated = imag.host<float>();
    float *_absCalculated = _abs.host<float>();
    float *angleCalculated = angle.host<float>();

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

    af::array result = tsa::features::firstLocationOfMaximum(tss);

    float *hr = result.host<float>();

    ASSERT_EQ(hr[0], 0.0f);
    ASSERT_EQ(hr[1], 0.3f);
}

void firstLocationOfMinimum() {
    float data[] = {5, 4, 3, 0, 0, 1, 5, 4, 3, 0, 2, 1};
    af::array tss(6, 2, data);

    af::array result = tsa::features::firstLocationOfMinimum(tss);

    float *firstMinimumCalculated = result.host<float>();

    ASSERT_NEAR(firstMinimumCalculated[0], 0.5, EPSILON);
    ASSERT_NEAR(firstMinimumCalculated[1], 0.5, EPSILON);
}

void hasDuplicates() {
    float data[] = {5, 4, 3, 0, 0, 1, 5, 4, 3, 0, 2, 1};
    af::array tss(6, 2, data);

    af::array duplicates = tsa::features::hasDuplicates(tss);

    bool *duplicatesCalculated = (bool *)duplicates.host<char>();

    ASSERT_EQ(duplicatesCalculated[0], true);
    ASSERT_EQ(duplicatesCalculated[1], false);
}

void hasDuplicateMax() {
    float data[] = {5, 4, 3, 0, 5, 1, 5, 4, 3, 0, 2, 1};
    af::array tss(6, 2, data);

    af::array out = tsa::features::hasDuplicateMax(tss);

    bool *hout = (bool *)out.host<char>();

    ASSERT_EQ(hout[0], true);
    ASSERT_EQ(hout[1], false);
}

void hasDuplicateMin() {
    float data[] = {5, 4, 3, 0, 0, 1, 5, 4, 3, 0, 2, 1};
    af::array tss(6, 2, data);

    af::array duplicateMin = tsa::features::hasDuplicateMin(tss);

    bool *duplicateMinCalculated = (bool *)duplicateMin.host<char>();

    ASSERT_EQ(duplicateMinCalculated[0], true);
    ASSERT_EQ(duplicateMinCalculated[1], false);
}

void indexMaxQuantile() {
    float data[] = {5, 4, 3, 0, 0, 1, 5, 4, 0, 0, 2, 1};
    af::array tss(6, 2, data);
    float q = 0.5;

    af::array result = tsa::features::indexMaxQuantile(tss, q);

    float *hresult = result.host<float>();
    float expected[] = {0.333333333, 0.3333333333};

    ASSERT_NEAR(hresult[0], expected[0], EPSILON);
    ASSERT_NEAR(hresult[1], expected[1], EPSILON);
}

void kurtosis() {
    float data[] = {0, 1, 2, 3, 4, 5, 2, 2, 2, 20, 30, 25};
    af::array tss(6, 2, data);

    float dataExpected[] = {-1.2, -2.66226722};

    float *result = tsa::features::kurtosis(tss).host<float>();

    for (int i = 0; i < 2; i++) {
        ASSERT_NEAR(dataExpected[i], result[i], EPSILON * 1e1);
    }
}

void largeStandardDeviation() {
    float data[] = {-1, -1, -1, 1, 1, 1, 4, 6, 8, 4, 5, 4};
    af::array tss(6, 2, data);
    float r = 0.4;

    bool *result = (bool *)tsa::features::largeStandardDeviation(tss, r).host<char>();

    ASSERT_EQ(result[0], true);
    ASSERT_EQ(result[1], false);
}

void lastLocationOfMaximum() {
    float data[] = {0, 4, 3, 5, 5, 1, 0, 4, 3, 2, 5, 1};
    af::array tss(6, 2, data);

    af::array result = tsa::features::lastLocationOfMaximum(tss);

    float *lastMaximumCalculated = result.host<float>();

    ASSERT_NEAR(lastMaximumCalculated[0], 0.8333333333333334, EPSILON);
    ASSERT_NEAR(lastMaximumCalculated[1], 0.8333333333333334, EPSILON);
}

void lastLocationOfMinimum() {
    af::setBackend(af::Backend::AF_BACKEND_CPU);

    float data[] = {0, 4, 3, 5, 5, 1, 0, 4, 3, 2, 5, 1, 4, 5, 1, 2};
    af::array tss(8, 2, data);

    af::array result = tsa::features::lastLocationOfMinimum(tss);

    float *out = result.host<float>();

    ASSERT_EQ(out[0], 0.875f);
    ASSERT_EQ(out[1], 0.875f);
}

void length() {
    float data[] = {0, 4, 3, 5, 5, 1, 0, 4, 3, 2, 5, 1};
    af::array tss(6, 2, data);

    af::array result = tsa::features::length(tss);

    int *lengthCalculated = result.host<int>();

    ASSERT_EQ(lengthCalculated[0], 6);
    ASSERT_EQ(lengthCalculated[1], 6);
}

void linearTrend() {
    float data[] = {0, 4, 3, 5, 5, 1, 2, 4, 1, 2, 5, 3};
    af::array tss(6, 2, data);

    af::array pvalue, rvalue, intercept, slope, stderr;
    tsa::features::linearTrend(tss, pvalue, rvalue, intercept, slope, stderr);

    float *hpvalue = pvalue.host<float>();
    ASSERT_NEAR(hpvalue[0], 0.6260380997892747, EPSILON);
    ASSERT_NEAR(hpvalue[1], 0.5272201945463578, EPSILON);

    float *hrvalue = rvalue.host<float>();
    ASSERT_NEAR(hrvalue[0], 0.2548235957188128, EPSILON);
    ASSERT_NEAR(hrvalue[1], 0.3268228676411533, EPSILON);

    float *hintercept = intercept.host<float>();
    ASSERT_NEAR(hintercept[0], 2.2857142857142856, EPSILON);
    ASSERT_NEAR(hintercept[1], 2.1904761904761907, EPSILON);

    float *hslope = slope.host<float>();
    ASSERT_NEAR(hslope[0], 0.2857142857142857, EPSILON);
    ASSERT_NEAR(hslope[1], 0.2571428571428572, EPSILON);

    float *hstderr = stderr.host<float>();
    ASSERT_NEAR(hstderr[0], 0.5421047417431507, EPSILON);
    ASSERT_NEAR(hstderr[1], 0.37179469135129783, EPSILON);
}

void longestStrikeAboveMean() {
    float data[] = {20, 20, 20, 1, 1, 1, 20, 20, 20, 20, 1, 1, 1, 1, 1, 1, 1, 1, 20, 20,
                    20, 20, 20, 1, 1, 1, 20, 20, 20, 1,  1, 1, 1, 1, 1, 1, 1, 1, 20, 20};
    af::array tss(20, 2, data);

    af::array result = tsa::features::longestStrikeAboveMean(tss);

    float *longestCalculated = result.host<float>();

    ASSERT_EQ(longestCalculated[0], 4);
    ASSERT_EQ(longestCalculated[1], 3);
}

void longestStrikeBelowMean() {
    float data[] = {20, 20, 20, 1, 1, 1, 20, 20, 20, 20, 1, 1, 1, 1, 1, 1, 1, 1, 20, 20,
                    20, 20, 20, 1, 1, 1, 20, 20, 20, 1,  1, 1, 1, 1, 1, 1, 1, 1, 20, 20};
    af::array tss(20, 2, data);

    af::array result = tsa::features::longestStrikeBelowMean(tss);

    float *longestCalculated = result.host<float>();

    ASSERT_EQ(longestCalculated[0], 8);
    ASSERT_EQ(longestCalculated[1], 9);
}

void maxLangevinFixedPoint() {
    float data[] = {0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5};
    af::array tss(6, 2, data);

    af::array result = tsa::features::maxLangevinFixedPoint(tss, 7, 2);

    float *calculated = result.host<float>();

    float expected[] = {4.562970585, 4.562970585};

    ASSERT_NEAR(calculated[0], expected[0], EPSILON * 1e4);
    ASSERT_NEAR(calculated[1], expected[1], EPSILON * 1e4);
}

void maximum() {
    float data[] = {20, 20, 20, 18, 25, 19, 20, 20, 20, 20, 40, 30, 1,  50, 1, 1,  5, 1, 20, 20,
                    20, 20, 20, 2,  19, 1,  20, 20, 20, 1,  15, 1,  30, 1,  1, 18, 4, 1, 20, 20};
    af::array tss(20, 2, data);

    af::array result = tsa::features::maximum(tss);

    float *maximum = result.host<float>();

    ASSERT_EQ(maximum[0], 50);
    ASSERT_EQ(maximum[1], 30);
}

void mean() {
    float data[] = {20, 20, 20, 18, 25, 19, 20, 20, 20, 20, 40, 30, 1,  50, 1, 1,  5, 1, 20, 20,
                    20, 20, 20, 2,  19, 1,  20, 20, 20, 1,  15, 1,  30, 1,  1, 18, 4, 1, 20, 20};
    af::array tss(20, 2, data);

    af::array result = tsa::features::mean(tss);

    float *mean = result.host<float>();

    ASSERT_NEAR(mean[0], 18.55, EPSILON * 2);
    ASSERT_NEAR(mean[1], 12.7, EPSILON * 2);
}

void meanAbsoluteChange() {
    float data[] = {0, 1, 2, 3, 4, 5, 8, 10, 12, 14, 16, 18};
    af::array tss(6, 2, data);

    af::array result = tsa::features::meanAbsoluteChange(tss);

    // check distances
    float r = 5.0 / 6.0;
    float *hostResult = result.host<float>();
    ASSERT_NEAR(r, hostResult[0], EPSILON);
    ASSERT_NEAR(r * 2.0, hostResult[1], EPSILON);
}

void meanChange() {
    float data[] = {0, 1, 2, 3, 4, 5, 8, 10, 12, 14, 16, 18};
    af::array tss(6, 2, data);

    af::array result = tsa::features::meanChange(tss);

    // check distances
    float r = 5.0 / 6.0;
    float *hostResult = result.host<float>();
    ASSERT_NEAR(r, hostResult[0], EPSILON);
    ASSERT_NEAR(r * 2.0, hostResult[1], EPSILON);
}

void meanSecondDerivativeCentral() {
    float data[] = {1, 3, 7, 4, 8, 2, 5, 1, 7, 4};
    af::array tss(5, 2, data);

    af::array result = tsa::features::meanSecondDerivativeCentral(tss);

    // check distances
    float r0 = 1.0 / 5.0;
    float r1 = -3.0 / 5.0;
    float *hostResult = result.host<float>();
    ASSERT_NEAR(r0, hostResult[0], EPSILON);
    ASSERT_NEAR(r1, hostResult[1], EPSILON);
}

void median() {
    float data[] = {20, 20, 20, 18, 25, 19, 20, 20, 20, 20, 40, 30, 1,  50, 1, 1,  5, 1, 20, 20,
                    20, 20, 20, 2,  19, 1,  20, 20, 20, 1,  15, 1,  30, 1,  1, 18, 4, 1, 20, 20};
    af::array tss(20, 2, data);

    af::array result = tsa::features::median(tss);

    float *median = result.host<float>();

    ASSERT_NEAR(median[0], 20, EPSILON * 2);
    ASSERT_NEAR(median[1], 18.5, EPSILON * 2);
}

void minimum() {
    float data[] = {20, 20, 20, 18, 25, 19, 20, 20, 20, 20, 40, 30, 1,  50, 13, 15, 5, 16, 20, 20,
                    20, 20, 20, 2,  19, 4,  20, 20, 20, 4,  15, 6,  30, 7,  9,  18, 4, 10, 20, 20};
    af::array tss(20, 2, data);

    af::array result = tsa::features::minimum(tss);

    float *minimum = result.host<float>();

    ASSERT_EQ(minimum[0], 1);
    ASSERT_EQ(minimum[1], 2);
}

void numberCrossingM() {
    float data[] = {1, 2, 1, 1, -3, -4, 7, 8, 9, 10, -2, 1, -3, 5, 6, 7, -10,
                    1, 2, 1, 1, -3, -4, 7, 8, 9, 10, -2, 1, -3, 5, 6, 7, -10};
    af::array tss(17, 2, data);

    af::array result = tsa::features::numberCrossingM(tss, 0);

    float *ncm = result.host<float>();

    ASSERT_EQ(ncm[0], 7);
    ASSERT_EQ(ncm[1], 7);
}

void cwtCoefficients() {
    float data[] = {0.1, 0.2, 0.3, 0.1, 0.2, 0.3};
    int widths[] = {1, 2, 3};
    af::array data_d(3, 2, data);
    af::array widths_d(3, 1, widths);
    af::array result = tsa::features::cwtCoefficients(data_d, widths_d, 2, 2);

    float *cwt = result.host<float>();

    float r0 = 0.26517161726951599;
    float r1 = 0.26517161726951599;

    ASSERT_NEAR(r0, cwt[0], EPSILON);
    ASSERT_NEAR(r1, cwt[1], EPSILON);
}

void numberPeaks() {
    float data[] = {3, 0, 0, 4, 0, 0, 13, 3, 0, 0, 4, 0, 0, 13};
    af::array tss(7, 2, data);

    af::array result = tsa::features::numberPeaks(tss, 2);

    float *np = result.host<float>();

    ASSERT_EQ(np[0], 1);
    ASSERT_EQ(np[1], 1);
}

void percentageOfReoccurringDatapointsToAllDatapoints() {
    float data[] = {3, 0, 0, 4, 0, 0, 13, 3, 0, 0, 4, 0, 0, 13};
    af::array tss(7, 2, data);

    af::array result = tsa::features::percentageOfReoccurringDatapointsToAllDatapoints(tss, false);

    float *calculated = result.host<float>();

    float expected[] = {0.25, 0.25};

    ASSERT_EQ(calculated[0], expected[0]);
    ASSERT_EQ(calculated[1], expected[1]);
}

void quantile() {
    float data[] = {3, 0, 0, 4, 0, 0, 13, 3, 0, 0, 4, 0, 0, 13};
    af::array tss(7, 2, data);

    tss = af::sort(tss, 0);

    float q[] = {0.6};
    af::array qq = af::array(1, q);

    af::array result = tsa::features::quantile(tss, qq);

    float *calculated = result.host<float>();

    float expected[] = {1.79999999, 1.79999999};

    ASSERT_NEAR(calculated[0], expected[0], EPSILON);
    ASSERT_NEAR(calculated[1], expected[1], EPSILON);
}

void ratioBeyondRSigma() {
    float data[] = {3, 0, 0, 4, 0, 0, 13, 3, 0, 0, 4, 0, 0, 13};
    af::array tss(7, 2, data);

    af::array result = tsa::features::ratioBeyondRSigma(tss, 0.5);

    float *calculated = result.host<float>();

    float expected[] = {0.7142857142857143, 0.7142857142857143};

    ASSERT_NEAR(calculated[0], expected[0], EPSILON);
    ASSERT_NEAR(calculated[1], expected[1], EPSILON);
}

void sampleEntropy() {
    float data[] = {3, 0, 0, 4, 0, 0, 13, 3, 0, 0, 4, 0, 0, 13};
    af::array tss(7, 2, data);

    af::array result = tsa::features::sampleEntropy(tss);

    float *calculated = result.host<float>();

    float expected[] = {1.252762968495368, 1.252762968495368};

    ASSERT_NEAR(calculated[0], expected[0], EPSILON);
    ASSERT_NEAR(calculated[1], expected[1], EPSILON);
}

void skewness() {
    float data[] = {3, 0, 0, 4, 0, 0, 13, 3, 0, 0, 4, 0, 0, 13};
    af::array tss(7, 2, data);

    af::array result = tsa::features::skewness(tss);

    float *calculated = result.host<float>();

    float expected[] = {2.038404735373753, 2.038404735373753};

    ASSERT_NEAR(calculated[0], expected[0], EPSILON);
    ASSERT_NEAR(calculated[1], expected[1], EPSILON);
}

void standardDeviation() {
    float data[] = {20, 20, 20, 18, 25, 19, 20, 20, 20, 20, 40, 30, 1,  50, 1, 1,  5, 1, 20, 20,
                    20, 20, 20, 2,  19, 1,  20, 20, 20, 1,  15, 1,  30, 1,  1, 18, 4, 1, 20, 20};
    af::array tss(20, 2, data);

    af::array result = tsa::features::standardDeviation(tss);

    float *stdev = result.host<float>();

    ASSERT_NEAR(stdev[0], 12.363150892875165, EPSILON);
    ASSERT_NEAR(stdev[1], 9.51367436903324, EPSILON);
}

void sumOfReoccurringDatapoints() {
    float data[] = {3, 3, 0, 4, 0, 13, 13, 3, 3, 0, 4, 0, 13, 13};
    af::array tss(7, 2, data);

    af::array result = tsa::features::sumOfReoccurringDatapoints(tss, false);

    float *calculated = result.host<float>();

    float expected[] = {32, 32};

    ASSERT_EQ(calculated[0], expected[0]);
    ASSERT_EQ(calculated[1], expected[1]);
}

TSA_TEST(FeaturesTests, AbsEnergy, absEnergy);
TSA_TEST(FeaturesTests, AbsEnergy2, absEnergy2);
TSA_TEST(FeaturesTests, AbsoluteSumOfChanges, absoluteSumOfChanges);
TSA_TEST(FeaturesTests, AggregatedCorrelationMean, aggregatedCorrelationMean);
TSA_TEST(FeaturesTests, AggregatedCorrelationMedian, aggregatedCorrelationMedian);
TSA_TEST(FeaturesTests, AggregatedCorrelationMin, aggregatedCorrelationMin);
TSA_TEST(FeaturesTests, AggregatedCorrelationMax, aggregatedCorrelationMax);
TSA_TEST(FeaturesTests, AggregatedCorrelationStdev, aggregatedCorrelationStdev);
TSA_TEST(FeaturesTests, AggregatedCorrelationVar, aggregatedCorrelationVar);
TSA_TEST(FeaturesTests, AggregatedLinearTrendMean, aggregatedLinearTrendMean);
TSA_TEST(FeaturesTests, AggregatedLinearTrendMin, aggregatedLinearTrendMin);
TSA_TEST(FeaturesTests, AggregatedLinearTrendMultipleSeriesMean, aggregatedLinearTrendMultipleSeriesMean);
TSA_TEST(FeaturesTests, AggregatedLinearTrendMultipleSeriesMin, aggregatedLinearTrendMultipleSeriesMin);
TSA_TEST(FeaturesTests, ApproximateEntropy, approximateEntropy);
TSA_TEST(FeaturesTests, CrossCovariance, crossCovariance);
TSA_TEST(FeaturesTests, CrossCovarianceBiased, crossCovarianceBiased);
TSA_TEST(FeaturesTests, CrossCovarianceUnbiased, crossCovarianceUnbiased);
TSA_TEST(FeaturesTests, AutoCovariance, autoCovariance);
TSA_TEST(FeaturesTests, CrossCorrelation, crossCorrelation);
TSA_TEST(FeaturesTests, AutoCorrelation, autoCorrelation);
TSA_TEST(FeaturesTests, BinnedEntropy, binnedEntropy);
TSA_TEST(FeaturesTests, C3, c3);
TSA_TEST(FeaturesTests, CidCe, cidCe);
TSA_TEST(FeaturesTests, CountAboveMean, countAboveMean);
TSA_TEST(FeaturesTests, CountBelowMean, countBelowMean);
TSA_TEST(FeaturesTests, EnergyRatioByChunk, energyRatioByChunk);
TSA_TEST(FeaturesTests, FftAggregated, fftAggregated);
TSA_TEST(FeaturesTests, FftCoefficient, fftCoefficient);
TSA_TEST(FeaturesTests, FirstLocationOfMaximum, firstLocationOfMaximum);
TSA_TEST(FeaturesTests, FirstLocationOfMinimum, firstLocationOfMinimum);
TSA_TEST(FeaturesTests, HasDuplicates, hasDuplicates);
TSA_TEST(FeaturesTests, HasDuplicateMax, hasDuplicateMax);
TSA_TEST(FeaturesTests, HasDuplicateMin, hasDuplicateMin);
TSA_TEST(FeaturesTests, IndexMaxQuantile, indexMaxQuantile);
TSA_TEST(FeaturesTests, Kurtosis, kurtosis);
TSA_TEST(FeaturesTests, LargeStandardDeviation, largeStandardDeviation);
TSA_TEST(FeaturesTests, LastLocationOfMaximum, lastLocationOfMaximum);
TSA_TEST(FeaturesTests, LastLocationOfMinimum, lastLocationOfMinimum);
TSA_TEST(FeaturesTests, Length, length);
TSA_TEST(FeaturesTests, LinearTrend, linearTrend);
TSA_TEST(FeaturesTests, LongestStrikeAboveMean, longestStrikeAboveMean);
TSA_TEST(FeaturesTests, LongestStrikeBelowMean, longestStrikeBelowMean);
TSA_TEST_BACKENDS(FeaturesTests, MaxLangevinFixedPoint, maxLangevinFixedPoint, true, true, false, false, false, false);
TSA_TEST(FeaturesTests, Maximum, maximum);
TSA_TEST(FeaturesTests, Mean, mean);
TSA_TEST(FeaturesTests, MeanAbsoluteChange, meanAbsoluteChange);
TSA_TEST(FeaturesTests, MeanChange, meanChange);
TSA_TEST(FeaturesTests, MeanSecondDerivativeCentral, meanSecondDerivativeCentral);
TSA_TEST(FeaturesTests, Median, median);
TSA_TEST(FeaturesTests, Minimum, minimum);
TSA_TEST(FeaturesTests, NumberCrossingM, numberCrossingM);
TSA_TEST(FeaturesTests, CwtCoefficients, cwtCoefficients);
TSA_TEST(FeaturesTests, NumberPeaks, numberPeaks);
TSA_TEST(FeaturesTests, PercentageOfReoccurringDatapointsToAllDatapoints,
         percentageOfReoccurringDatapointsToAllDatapoints);
TSA_TEST(FeaturesTests, Quantile, quantile);
TSA_TEST(FeaturesTests, RatioBeyondRSigma, ratioBeyondRSigma);
TSA_TEST(FeaturesTests, SampleEntropy, sampleEntropy);
TSA_TEST(FeaturesTests, Skewness, skewness);
TSA_TEST(FeaturesTests, StandardDeviation, standardDeviation);
TSA_TEST(FeaturesTests, SumOfReoccurringDatapoints, sumOfReoccurringDatapoints);
