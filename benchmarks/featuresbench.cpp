// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <benchmark/benchmark.h>
#include <tsa.h>

void addMemoryCounters(benchmark::State &state) {
    size_t bytes, buffers, lockedBytes, lockedBuffers;
    // This is already doing an af::sync();
    af::deviceMemInfo(&bytes, &buffers, &lockedBytes, &lockedBuffers);

    state.counters["Memory"] = bytes;
    state.counters["Buffers"] = buffers;
    state.counters["LockedMemory"] = lockedBytes;
    state.counters["LockedBuffers"] = lockedBuffers;

    af::deviceGC();
}

template <af::Backend BE>
void AbsoluteSumOfChanges(benchmark::State &state) {
    af::setBackend(BE);

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

template <af::Backend BE>
void AbsEnergy(benchmark::State &state) {
    af::setBackend(BE);

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

template <af::Backend BE>
void AggregatedLinearTrend(benchmark::State &state) {
    af::setBackend(BE);

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

template <af::Backend BE>
void AggregatedAutocorrelation(benchmark::State &state) {
    af::setBackend(BE);

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

template <af::Backend BE>
void ApproximateEntropy(benchmark::State &state) {
    af::setBackend(BE);

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

template <af::Backend BE>
void CrossCovariance(benchmark::State &state) {
    af::setBackend(BE);

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

template <af::Backend BE>
void AutoCovariance(benchmark::State &state) {
    af::setBackend(BE);

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

template <af::Backend BE>
void CrossCorrelation(benchmark::State &state) {
    af::setBackend(BE);

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

template <af::Backend BE>
void AutoCorrelation(benchmark::State &state) {
    af::setBackend(BE);

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

template <af::Backend BE>
void BinnedEntropy(benchmark::State &state) {
    af::setBackend(BE);

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

template <af::Backend BE>
void C3(benchmark::State &state) {
    af::setBackend(BE);

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

template <af::Backend BE>
void CidCe(benchmark::State &state) {
    af::setBackend(BE);

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

template <af::Backend BE>
void CountBelowMean(benchmark::State &state) {
    af::setBackend(BE);

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

template <af::Backend BE>
void EnergyRatioByChunks(benchmark::State &state) {
    af::setBackend(BE);
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

template <af::Backend BE>
void FftCoefficient(benchmark::State &state) {
    af::setBackend(BE);

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

template <af::Backend BE>
void FirstLocationOfMaximum(benchmark::State &state) {
    af::setBackend(BE);

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

template <af::Backend BE>
void FirstLocationOfMinimum(benchmark::State &state) {
    af::setBackend(BE);

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

template <af::Backend BE>
void HasDuplicates(benchmark::State &state) {
    af::setBackend(BE);

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

template <af::Backend BE>
void HasDuplicateMax(benchmark::State &state) {
    af::setBackend(BE);

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

template <af::Backend BE>
void HasDuplicateMin(benchmark::State &state) {
    af::setBackend(BE);

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

template <af::Backend BE>
void IndexMaxQuantile(benchmark::State &state) {
    af::setBackend(BE);

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

template <af::Backend BE>
void Kurtosis(benchmark::State &state) {
    af::setBackend(BE);

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

template <af::Backend BE>
void LargeStandardDeviation(benchmark::State &state) {
    af::setBackend(BE);

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

template <af::Backend BE>
void LastLocationOfMaximum(benchmark::State &state) {
    af::setBackend(BE);

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

template <af::Backend BE>
void LastLocationOfMinimum(benchmark::State &state) {
    af::setBackend(BE);

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

template <af::Backend BE>
void Length(benchmark::State &state) {
    af::setBackend(BE);

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

template <af::Backend BE>
void LinearTrend(benchmark::State &state) {
    af::setBackend(BE);

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

BENCHMARK_TEMPLATE(AbsoluteSumOfChanges, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(AbsoluteSumOfChanges, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(AbsEnergy, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(AbsEnergy, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(AggregatedAutocorrelation, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 32 << 10}, {1, 32}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(AggregatedAutocorrelation, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 32 << 10}, {1, 16}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(AggregatedLinearTrend, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(AggregatedLinearTrend, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(ApproximateEntropy, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {1, 16}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(ApproximateEntropy, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {1, 16}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(CrossCovariance, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(CrossCovariance, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(AutoCovariance, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(AutoCovariance, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(CrossCorrelation, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(CrossCorrelation, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(AutoCorrelation, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(AutoCorrelation, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(BinnedEntropy, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(BinnedEntropy, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(C3, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {16, 128}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(C3, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {16, 128}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(CidCe, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}, {true, false}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(CidCe, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}, {true, false}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(CountBelowMean, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(CountBelowMean, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(EnergyRatioByChunks, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(EnergyRatioByChunks, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(FftCoefficient, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {16, 128}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(FftCoefficient, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {16, 128}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(FirstLocationOfMaximum, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(FirstLocationOfMaximum, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(FirstLocationOfMinimum, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(FirstLocationOfMinimum, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(HasDuplicates, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(HasDuplicates, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(HasDuplicateMax, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(HasDuplicateMax, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(HasDuplicateMin, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(HasDuplicateMin, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(IndexMaxQuantile, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(IndexMaxQuantile, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(Kurtosis, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(Kurtosis, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(LargeStandardDeviation, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(LargeStandardDeviation, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(LastLocationOfMaximum, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(LastLocationOfMaximum, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(LastLocationOfMinimum, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(LastLocationOfMinimum, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(Length, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(Length, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(LinearTrend, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 32 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(LinearTrend, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 128 << 10}, {32, 256}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_MAIN();