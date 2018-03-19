// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <benchmark/benchmark.h>
#include <tsa.h>
#include "tsabenchmark.h"

template <af::Backend BE, int D>
void Linear(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

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

void cudaBenchmarks() {
    BENCHMARK_TEMPLATE(Linear, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 32 << 10}, {4, 64}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);
}

void openclBenchmarks() {
    BENCHMARK_TEMPLATE(Linear, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 32 << 10}, {4, 64}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);
}

void cpuBenchmarks() {
    BENCHMARK_TEMPLATE(Linear, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 32 << 10}, {4, 64}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);
}

TSA_BENCHMARK_MAIN(cudaBenchmarks, openclBenchmarks, cpuBenchmarks);