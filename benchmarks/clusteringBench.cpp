// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <benchmark/benchmark.h>
#include <khiva/clustering.h>
#include "khivaBenchmark.h"

template <af::Backend BE, int D>
void Kmeans(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);
    int k = state.range(2);

    auto t = af::randu(n, m, f32);

    af::sync();
    while (state.KeepRunning()) {
        af::array means;
        af::array labels;
        khiva::clustering::kMeans(t, k, means, labels);
        means.eval();
        af::sync();
    }
    addMemoryCounters(state);
}



void cudaBenchmarks() {
    BENCHMARK_TEMPLATE(Kmeans, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 256 << 10}, {16, 128}, {8, 16}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);
}

void openclBenchmarks() {
    BENCHMARK_TEMPLATE(Kmeans, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 256 << 10}, {16, 128}, {8, 16}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);
}

void cpuBenchmarks() {
    BENCHMARK_TEMPLATE(Kmeans, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 256 << 10}, {16, 128}, {8, 16}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);
}

KHIVA_BENCHMARK_MAIN(cudaBenchmarks, openclBenchmarks, cpuBenchmarks)
