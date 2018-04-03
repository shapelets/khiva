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
        auto longest = tsa::features::maximum(t);
        longest.eval();
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
        auto longest = tsa::features::meanAbsoluteChange(t);
        longest.eval();
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

    BENCHMARK_TEMPLATE(MeanAbsoluteChange, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(MeanSecondDerivativeCentral, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 512 << 10}, {32, 128}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(Minimum, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(NumberCrossingM, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
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

    BENCHMARK_TEMPLATE(MeanAbsoluteChange, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(MeanSecondDerivativeCentral, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 512 << 10}, {32, 128}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(Minimum, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(NumberCrossingM, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
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

    BENCHMARK_TEMPLATE(FftCoefficient, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 512 << 10}, {16, 128}, {32, 256}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(FirstLocationOfMaximum, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(FirstLocationOfMinimum, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

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

    BENCHMARK_TEMPLATE(MeanAbsoluteChange, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(MeanSecondDerivativeCentral, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 512 << 10}, {32, 128}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(Minimum, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(NumberCrossingM, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);
}

TSA_BENCHMARK_MAIN(cudaBenchmarks, openclBenchmarks, cpuBenchmarks);
