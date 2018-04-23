// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <benchmark/benchmark.h>
#include <tsa/features.h>
#include "tsaBenchmark.h"

template <af::Backend BE, int D>
void AbsoluteSumOfChanges(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto asoc = tsa::features::absoluteSumOfChanges(t);
        asoc.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void AbsEnergy(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto ae = tsa::features::absEnergy(t);
        ae.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void AggregatedLinearTrend(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);
    auto chunkSize = state.range(2);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        af::array slope, intercept, rvalue, pvalue, stderrest;
        tsa::features::aggregatedLinearTrend(t, chunkSize, af::mean, slope, intercept, rvalue, pvalue, stderrest);
        slope.eval();
        intercept.eval();
        rvalue.eval();
        pvalue.eval();
        stderrest.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void AggregatedAutocorrelation(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();

    while (state.KeepRunning()) {
        af::array output = tsa::features::aggregatedAutocorrelation(t, af::mean);
        output.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void ApproximateEntropy(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto entropy = tsa::features::approximateEntropy(t, 128, 0.5);
        entropy.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void CrossCovariance(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto cc = tsa::features::crossCovariance(t, t);
        cc.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void AutoCovariance(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto ac = tsa::features::autoCovariance(t);
        ac.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void CrossCorrelation(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto cc = tsa::features::crossCorrelation(t, t);
        cc.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void AutoCorrelation(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);
    auto lag = state.range(2);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto ac = tsa::features::autoCorrelation(t, lag);
        ac.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void BinnedEntropy(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);
    auto bins = state.range(2);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto ac = tsa::features::binnedEntropy(t, bins);
        ac.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void C3(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);
    auto lag = state.range(2);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto c3 = tsa::features::c3(t, lag);
        c3.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void CidCe(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);
    auto zNormalize = state.range(2);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto cidCe = tsa::features::cidCe(t, zNormalize);
        cidCe.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void CountBelowMean(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto cbm = tsa::features::countBelowMean(t);
        cbm.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void CwtCoefficients(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);
    int data[] = {1, 2, 3, 4, 5};
    af::array ws(5, 1, data);

    af::sync();
    while (state.KeepRunning()) {
        auto cwt = tsa::features::cwtCoefficients(t, ws, 8, 3);
        cwt.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void EnergyRatioByChunks(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);
    std::srand(0);

    auto n = state.range(0);
    auto m = state.range(1);
    auto numSegments = state.range(2);
    auto segmentFocus = std::rand() % numSegments;

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto cbm = tsa::features::energyRatioByChunks(t, numSegments, segmentFocus);
        cbm.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void FftAggregated(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);
    std::srand(0);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto fftA = tsa::features::fftAggregated(t);
        fftA.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void FftCoefficient(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);
    auto coefficient = state.range(2);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        af::array real, imag, _abs, angle;
        tsa::features::fftCoefficient(t, coefficient, real, imag, _abs, angle);
        real.eval();
        imag.eval();
        _abs.eval();
        angle.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void FirstLocationOfMaximum(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto first = tsa::features::firstLocationOfMaximum(t);
        first.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void FirstLocationOfMinimum(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto first = tsa::features::firstLocationOfMinimum(t);
        first.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void FriedrichCoefficients(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    int m2 = 7;
    float r = 2;

    af::sync();
    while (state.KeepRunning()) {
        auto fc = tsa::features::friedrichCoefficients(t, m2, r);
        fc.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void HasDuplicates(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto duplicates = tsa::features::hasDuplicates(t);
        duplicates.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void HasDuplicateMax(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto duplicateMax = tsa::features::hasDuplicateMax(t);
        duplicateMax.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void HasDuplicateMin(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto duplicateMin = tsa::features::hasDuplicateMin(t);
        duplicateMin.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void IndexMaxQuantile(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);
    float q = 0.8;

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto index = tsa::features::indexMaxQuantile(t, q);
        index.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void Kurtosis(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto kurtosis = tsa::features::kurtosis(t);
        kurtosis.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void LargeStandardDeviation(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);
    float r = 1.5;

    af::sync();
    while (state.KeepRunning()) {
        auto large = tsa::features::largeStandardDeviation(t, r);
        large.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void LastLocationOfMaximum(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto llom = tsa::features::lastLocationOfMaximum(t);
        llom.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void LastLocationOfMinimum(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto llom = tsa::features::lastLocationOfMaximum(t);
        llom.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void Length(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto length = tsa::features::length(t);
        length.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void LinearTrend(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto tss = af::randu(n, m, f64);
    af::array pvalue, rvalue, intercept, slope, stderr;

    af::sync();
    while (state.KeepRunning()) {
        tsa::features::linearTrend(tss, pvalue, rvalue, intercept, slope, stderr);
        pvalue.eval();
        rvalue.eval();
        intercept.eval();
        slope.eval();
        stderr.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void LongestStrikeAboveMean(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto longest = tsa::features::longestStrikeAboveMean(t);
        longest.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void LongestStrikeBelowMean(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto longest = tsa::features::longestStrikeBelowMean(t);
        longest.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void MaxLangevinFixedPoint(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);
    auto mm = state.range(2);
    auto r = state.range(3);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto langevin = tsa::features::maxLangevinFixedPoint(t, mm, r);
        langevin.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void Maximum(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto maximum = tsa::features::maximum(t);
        maximum.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void Mean(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto mean = tsa::features::mean(t);
        mean.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void MeanAbsoluteChange(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto mac = tsa::features::meanAbsoluteChange(t);
        mac.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void MeanChange(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto mc = tsa::features::meanChange(t);
        mc.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void MeanSecondDerivativeCentral(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto meanSDC = tsa::features::meanSecondDerivativeCentral(t);
        meanSDC.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void Median(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto median = tsa::features::median(t);
        median.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void Minimum(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto minimum = tsa::features::minimum(t);
        minimum.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void NumberCrossingM(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto ncm = tsa::features::numberCrossingM(t, 0);
        ncm.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void NumberPeaks(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);
    auto nn = state.range(2);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto np = tsa::features::numberPeaks(t, nn);
        np.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void PartialAutocorrelation(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    int lags[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    af::array lags_d(10, 1, lags);

    af::sync();
    while (state.KeepRunning()) {
        auto ncm = tsa::features::partialAutocorrelation(t, lags_d);
        ncm.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void PercentageOfReoccurringDatapointsToAllDatapoints(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);
    auto s = state.range(2);

    auto t = af::randu(n, m, f64);

    if (s) {
        t = af::sort(t);
    }

    af::sync();
    while (state.KeepRunning()) {
        auto p = tsa::features::percentageOfReoccurringDatapointsToAllDatapoints(t, s);
        p.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void PercentageOfReoccurringValuesToAllValues(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto p = tsa::features::percentageOfReoccurringValuesToAllValues(t, false);
        p.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void Quantile(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);
    float qq[] = {0.5};
    auto q = af::array(1, qq);

    t = af::sort(t, 0);

    af::sync();
    while (state.KeepRunning()) {
        auto quantile = tsa::features::quantile(t, q);
        quantile.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void RangeCount(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);
    auto t = af::randu(n, m, f64);
    float minimum = 0.2;
    float maximum = 0.8;

    af::sync();
    while (state.KeepRunning()) {
        auto range = tsa::features::rangeCount(t, minimum, maximum);
        range.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void RatioBeyondRSigma(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto rbrs = tsa::features::ratioBeyondRSigma(t, 0.5);
        rbrs.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void RatioValueNumberToTimeSeriesLength(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto ratio = tsa::features::ratioValueNumberToTimeSeriesLength(t);
        ratio.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void SampleEntropy(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto se = tsa::features::sampleEntropy(t);
        se.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void Skewness(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto kurtosis = tsa::features::kurtosis(t);
        kurtosis.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void StandardDeviation(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto stdev = tsa::features::standardDeviation(t);
        stdev.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void SumOfReoccurringDatapoints(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);
    auto s = state.range(2);

    auto t = af::randu(n, m, f64);

    if (s) {
        t = af::sort(t);
    }

    af::sync();
    while (state.KeepRunning()) {
        auto sord = tsa::features::sumOfReoccurringDatapoints(t, s);
        sord.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void SumOfReoccurringValues(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto sorv = tsa::features::sumOfReoccurringValues(t);
        sorv.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void SumValues(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto sv = tsa::features::sumOfReoccurringValues(t);
        sv.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void SymmetryLooking(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto sl = tsa::features::symmetryLooking(t, 0.1);
        sl.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void TimeReversalAsymmetryStatistic(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto tr = tsa::features::timeReversalAsymmetryStatistic(t, 2);
        tr.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void ValueCount(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto vc = tsa::features::valueCount(t, 0.5);
        vc.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void Variance(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto vc = tsa::features::variance(t);
        vc.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void NumberCwtPeaks(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto nCWTp = tsa::features::numberCwtPeaks(t, 2);
        nCWTp.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void NumberPeaks(benchmark::State &state) {
    void VarianceLargerThanStandardDeviation(benchmark::State & state) {
        af::setBackend(BE);
        af::setDevice(D);

        auto n = state.range(0);
        auto m = state.range(1);

        auto t = af::randu(n, m, f64);

        af::sync();
        while (state.KeepRunning()) {
            auto vlts = tsa::features::varianceLargerThanStandardDeviation(t);
            vlts.eval();
            af::sync();
        }
        addMemoryCounters(state);
    }

    void cudaBenchmarks() {
        BENCHMARK_TEMPLATE(AbsoluteSumOfChanges, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(AbsEnergy, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(AggregatedAutocorrelation, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 32 << 10}, {1, 32}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(AggregatedLinearTrend, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(ApproximateEntropy, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {1, 16}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(CrossCovariance, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(AutoCovariance, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(CrossCorrelation, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(AutoCorrelation, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(BinnedEntropy, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(CountBelowMean, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(CwtCoefficients, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(C3, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {16, 128}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(CidCe, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}, {true, false}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(EnergyRatioByChunks, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(FftAggregated, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 128}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(FftCoefficient, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {16, 128}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(FirstLocationOfMaximum, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(FirstLocationOfMinimum, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(FriedrichCoefficients, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(HasDuplicates, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(HasDuplicateMax, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(HasDuplicateMin, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(IndexMaxQuantile, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(Kurtosis, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(LargeStandardDeviation, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(LastLocationOfMaximum, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(LastLocationOfMinimum, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(Length, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(LinearTrend, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 32 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(LongestStrikeAboveMean, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(LongestStrikeBelowMean, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(MaxLangevinFixedPoint, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 32 << 10}, {1, 2}, {2, 8}, {2, 4}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(Maximum, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(Mean, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(MeanAbsoluteChange, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(MeanChange, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(MeanSecondDerivativeCentral, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 128}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(Median, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(Minimum, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(NumberCrossingM, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(NumberCwtPeaks, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 128}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(NumberPeaks, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 128}, {2, 32}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(PartialAutocorrelation, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(PercentageOfReoccurringDatapointsToAllDatapoints, af::Backend::AF_BACKEND_CUDA,
                           CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {2, 32}, {0, 1}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(PercentageOfReoccurringValuesToAllValues, af::Backend::AF_BACKEND_CUDA,
                           CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 256 << 10}, {2, 8}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(Quantile, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(RangeCount, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(RatioBeyondRSigma, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(RatioValueNumberToTimeSeriesLength, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(SampleEntropy, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {1, 16}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(Skewness, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {1, 16}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(StandardDeviation, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(SumOfReoccurringDatapoints, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {2, 32}, {0, 1}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(SumOfReoccurringValues, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {2, 32}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(SumValues, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(SymmetryLooking, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(TimeReversalAsymmetryStatistic, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 128}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(ValueCount, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(Variance, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(VarianceLargerThanStandardDeviation, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);
    }

    void openclBenchmarks() {
        BENCHMARK_TEMPLATE(AbsoluteSumOfChanges, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(AbsEnergy, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(AggregatedAutocorrelation, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 32 << 10}, {1, 32}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(AggregatedLinearTrend, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(ApproximateEntropy, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {1, 16}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(CrossCovariance, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(AutoCovariance, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(CrossCorrelation, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(AutoCorrelation, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(BinnedEntropy, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(CountBelowMean, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(CwtCoefficients, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(C3, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {16, 128}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(CidCe, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}, {true, false}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(EnergyRatioByChunks, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(FftAggregated, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 128}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(FftCoefficient, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {16, 128}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(FirstLocationOfMaximum, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(FirstLocationOfMinimum, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(FriedrichCoefficients, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(HasDuplicates, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(HasDuplicateMax, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(HasDuplicateMin, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(IndexMaxQuantile, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(Kurtosis, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(LargeStandardDeviation, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(LastLocationOfMaximum, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(LastLocationOfMinimum, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(Length, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(LinearTrend, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 32 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(LongestStrikeAboveMean, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(LongestStrikeBelowMean, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(MaxLangevinFixedPoint, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 32 << 10}, {1, 2}, {2, 8}, {2, 4}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(Maximum, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(Mean, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(MeanAbsoluteChange, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(MeanChange, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(MeanSecondDerivativeCentral, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 128}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(Median, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(Minimum, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(NumberCrossingM, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(NumberCwtPeaks, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(NumberPeaks, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 128}, {2, 32}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(PartialAutocorrelation, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(PercentageOfReoccurringDatapointsToAllDatapoints, af::Backend::AF_BACKEND_OPENCL,
                           OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {2, 32}, {0, 1}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(PercentageOfReoccurringValuesToAllValues, af::Backend::AF_BACKEND_OPENCL,
                           OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 256 << 10}, {2, 8}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(Quantile, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(RangeCount, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(RatioBeyondRSigma, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(RatioValueNumberToTimeSeriesLength, af::Backend::AF_BACKEND_OPENCL,
                           OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(SampleEntropy, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {1, 16}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(Skewness, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {1, 16}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(StandardDeviation, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(SumOfReoccurringDatapoints, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {2, 32}, {0, 1}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(SumOfReoccurringValues, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {2, 32}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(SumValues, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(SymmetryLooking, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(TimeReversalAsymmetryStatistic, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 128}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(ValueCount, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(Variance, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(VarianceLargerThanStandardDeviation, af::Backend::AF_BACKEND_OPENCL,
                           OPENCL_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);
    }

    void cpuBenchmarks() {
        BENCHMARK_TEMPLATE(AbsoluteSumOfChanges, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(AbsEnergy, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(AggregatedAutocorrelation, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 32 << 10}, {1, 16}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(AggregatedLinearTrend, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(ApproximateEntropy, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {1, 16}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(CrossCovariance, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(AutoCovariance, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(CrossCorrelation, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(AutoCorrelation, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(BinnedEntropy, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(C3, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {16, 128}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(CidCe, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}, {true, false}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(CountBelowMean, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(CwtCoefficients, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(EnergyRatioByChunks, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(FftAggregated, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(FftCoefficient, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(FirstLocationOfMaximum, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(FirstLocationOfMinimum, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        // Commented because the MaxLangevinFixedPoint uses the svd function of Arrayfire, which produces
        // problems with the static linking of OpenMP that AF does.
        /*BENCHMARK_TEMPLATE(FriedrichCoefficients, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);*/

        BENCHMARK_TEMPLATE(HasDuplicates, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(HasDuplicateMax, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(HasDuplicateMin, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(IndexMaxQuantile, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(Kurtosis, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(LargeStandardDeviation, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(LastLocationOfMaximum, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(LastLocationOfMinimum, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(Length, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(LinearTrend, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 32 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(LongestStrikeAboveMean, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(LongestStrikeBelowMean, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        // Commented because the MaxLangevinFixedPoint uses the svd function of Arrayfire, which produces
        // problems with the static linking of OpenMP that AF does.
        /*BENCHMARK_TEMPLATE(MaxLangevinFixedPoint, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 32 << 10}, {1, 2}, {2, 8}, {2, 4}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);*/

        BENCHMARK_TEMPLATE(Maximum, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(Mean, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(MeanAbsoluteChange, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(MeanChange, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(MeanSecondDerivativeCentral, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 128}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(Median, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(Minimum, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(NumberCrossingM, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(NumberCwtPeaks, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(NumberPeaks, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 128}, {2, 32}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(PartialAutocorrelation, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(PercentageOfReoccurringDatapointsToAllDatapoints, af::Backend::AF_BACKEND_CPU,
                           CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {2, 32}, {0, 1}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(PercentageOfReoccurringValuesToAllValues, af::Backend::AF_BACKEND_CPU,
                           CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 256 << 10}, {2, 8}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(Quantile, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(RangeCount, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(RatioBeyondRSigma, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(RatioValueNumberToTimeSeriesLength, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(SampleEntropy, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {1, 16}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(Skewness, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {1, 16}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(StandardDeviation, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(SumOfReoccurringDatapoints, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {2, 32}, {0, 1}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(SumOfReoccurringValues, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {2, 32}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(SumValues, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(SymmetryLooking, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(TimeReversalAsymmetryStatistic, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 128}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(ValueCount, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(Variance, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);

        BENCHMARK_TEMPLATE(VarianceLargerThanStandardDeviation, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
            ->RangeMultiplier(2)
            ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
            ->Unit(benchmark::TimeUnit::kMicrosecond);
    }

    TSA_BENCHMARK_MAIN(cudaBenchmarks, openclBenchmarks, cpuBenchmarks);
