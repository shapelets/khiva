// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <benchmark/benchmark.h>
#include "khivaBenchmark.h"

template <af::Backend BE, int D>
void ManualFFT(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto ts = af::randu(n);
    auto q = af::randu(m);
    auto ta = af::constant(0, 2 * n, ts.type());
    auto qra = af::constant(0, 2 * n, q.type());

    af::sync();
    while (state.KeepRunning()) {
        ta(af::seq(0, n - 1)) = ts;
        qra(af::seq(0, m - 1)) = af::flip(q, 0);
        auto qraf = af::fft(qra);
        auto raf = af::fft(ta);
        auto prod = qraf * raf;
        af::ifft(prod).eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void ExpansionFFT(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto ts = af::randu(n);
    auto q = af::randu(m);
    auto qr = af::flip(q, 0);

    af::sync();
    while (state.KeepRunning()) {
        auto qraf = af::fft(qr, 2 * n);
        auto raf = af::fft(ts, 2 * n);
        auto prod = qraf * raf;
        af::ifft(prod).eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void ConvolveOp(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);
    auto n = state.range(0);
    auto m = state.range(1);

    auto ts = af::randu(n);
    auto q = af::randu(m);

    af::sync();
    while (state.KeepRunning()) {
        convolve(ts, flip(q, 0), AF_CONV_EXPAND).eval();
        af::sync();
    }
    addMemoryCounters(state);
}

void cudaBenchmarks() {
    BENCHMARK_TEMPLATE(ConvolveOp, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 512 << 10}, {64, 1 << 10}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(ExpansionFFT, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
        ->RangeMultiplier(8)
        ->Ranges({{1 << 10, 512 << 10}, {64, 1 << 10}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(ManualFFT, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 512 << 10}, {64, 1 << 10}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);
}

void openclBenchmarks() {
    BENCHMARK_TEMPLATE(ConvolveOp, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 512 << 10}, {64, 1 << 10}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(ExpansionFFT, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
        ->RangeMultiplier(8)
        ->Ranges({{1 << 10, 512 << 10}, {64, 1 << 10}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(ManualFFT, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 512 << 10}, {64, 1 << 10}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);
}

void cpuBenchmarks() {
    BENCHMARK_TEMPLATE(ConvolveOp, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 512 << 10}, {64, 1 << 10}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(ExpansionFFT, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(8)
        ->Ranges({{1 << 10, 512 << 10}, {64, 1 << 10}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(ManualFFT, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 512 << 10}, {64, 1 << 10}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);
}

KHIVA_BENCHMARK_MAIN(cudaBenchmarks, openclBenchmarks, cpuBenchmarks)
