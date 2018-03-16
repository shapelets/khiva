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
void Linear(benchmark::State &state) {
    af::setBackend(BE);

    auto n = state.range(0);
    auto m = state.range(1);

    auto x = af::randu(n, m, f64);
    auto y = af::randu(n, m, f64);

    af::sync();
    while (state.KeepRunning()) {
        af::array slope, intercept, rvalue, pvalue, stderrest;
        tsa::regression::linear(x, y, slope, intercept, rvalue, pvalue, stderrest);
        slope.eval();
        intercept.eval();
        rvalue.eval();
        pvalue.eval();
        stderrest.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

BENCHMARK_TEMPLATE(Linear, af::Backend::AF_BACKEND_OPENCL)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 32 << 10}, {4, 64}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_TEMPLATE(Linear, af::Backend::AF_BACKEND_CPU)
    ->RangeMultiplier(2)
    ->Ranges({{1 << 10, 32 << 10}, {4, 64}})
    ->Unit(benchmark::TimeUnit::kMicrosecond);

BENCHMARK_MAIN();