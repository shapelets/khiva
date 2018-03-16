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
void Covariance(benchmark::State &state) {
    af::setBackend(BE);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto cov = tsa::statistics::covariance(t);
        cov.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE>
void Moment(benchmark::State &state) {
    af::setBackend(BE);

    auto n = state.range(0);
    auto m = state.range(1);
    auto k = state.range(2);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto moment = tsa::statistics::moment(t, k);
        moment.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE>
void SampleStdev(benchmark::State &state) {
    af::setBackend(BE);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto sampleStdev = tsa::statistics::sampleStdev(t);
        sampleStdev.eval();
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
        auto kurtosis = tsa::statistics::kurtosis(t);
        kurtosis.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

BENCHMARK_TEMPLATE(Covariance, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 32 << 10}, {1, 16}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(Covariance, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 32 << 10}, {1, 16}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(Moment, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {16, 32}, {1, 4}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(Moment, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {16, 32}, {1, 4}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(SampleStdev, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {16, 32}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(SampleStdev, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {16, 32}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(Kurtosis, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {16, 32}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(Kurtosis, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 512 << 10}, {16, 32}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_MAIN();