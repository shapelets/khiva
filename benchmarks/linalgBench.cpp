// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <benchmark/benchmark.h>
#include <tsa/linalg.h>
#include "tsaBenchmark.h"

template <af::Backend BE, int D>
void Lls(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);

    auto A = af::randu(n, n, f64);
    auto b = af::randu(n, f64);

    af::sync();
    while (state.KeepRunning()) {
        auto x = tsa::linalg::lls(A, b);
        x.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

void cudaBenchmarks() {
    BENCHMARK_TEMPLATE(Lls, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{2, 8192}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);
}

void openclBenchmarks() {
    BENCHMARK_TEMPLATE(Lls, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{2, 8192}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);
}

void cpuBenchmarks() {
    // Empty cpu benchmarks because of the OpenMP static linking problem caused by Arrayfire
}

TSA_BENCHMARK_MAIN(cudaBenchmarks, openclBenchmarks, cpuBenchmarks);