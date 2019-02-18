// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <benchmark/benchmark.h>
#include <set>
#include <vector>
#include "khivaBenchmark.h"

template <af::Backend BE, int D>
void MovingSumConvolve(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);
    auto tsLen = state.range(0);
    auto m = state.range(1);

    af::array ts = af::randu(tsLen);
    af::array filter = af::constant(1, m);

    af::sync();
    while (state.KeepRunning()) {
        af::array movSum = af::convolve(ts, filter, AF_CONV_EXPAND);
        movSum(af::seq(m - 1, tsLen - 1)).eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void MovingSumScan(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);
    auto tsLen = state.range(0);
    auto m = state.range(1);
    af::array ts = af::randu(tsLen);

    af::sync();
    while (state.KeepRunning()) {
        af::array cumsum = af::accum(ts);
        af::array exCumsum = af::scan(ts, 0, AF_BINARY_ADD, false);
        (cumsum(af::seq(m - 1, tsLen - 1)) - exCumsum(af::seq(0, tsLen - m))).eval();
        af::sync();
    }
    addMemoryCounters(state);
}

void cudaBenchmarks() {
    BENCHMARK_TEMPLATE(MovingSumConvolve, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
        ->RangeMultiplier(8)
        ->Ranges({{1 << 10, 32 << 10}, {64, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(MovingSumScan, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
        ->RangeMultiplier(8)
        ->Ranges({{1 << 10, 32 << 10}, {64, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);
}

void openclBenchmarks() {
    BENCHMARK_TEMPLATE(MovingSumConvolve, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
        ->RangeMultiplier(8)
        ->Ranges({{1 << 10, 32 << 10}, {64, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(MovingSumScan, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
        ->RangeMultiplier(8)
        ->Ranges({{1 << 10, 32 << 10}, {64, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);
}

void cpuBenchmarks() {
    BENCHMARK_TEMPLATE(MovingSumConvolve, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(8)
        ->Ranges({{1 << 10, 32 << 10}, {64, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(MovingSumScan, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(8)
        ->Ranges({{1 << 10, 32 << 10}, {64, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);
}

KHIVA_BENCHMARK_MAIN(cudaBenchmarks, openclBenchmarks, cpuBenchmarks)
