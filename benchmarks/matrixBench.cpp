// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <benchmark/benchmark.h>
#include <tsa/matrix.h>
#include "tsaBenchmark.h"

template <af::Backend BE, int D>
void SlidingDotProduct(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, f64);
    auto q = t(af::seq(0, m));

    af::sync();
    while (state.KeepRunning()) {
        auto sdp = tsa::matrix::slidingDotProduct(q, t);
        sdp.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void SlidingDotProductParallel(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, f64);

    auto indices = af::range(n - m);
    auto input = af::array(m, n - m, t.type());

    for (int i = 0; i < m; i++) {
        input(i, af::span, af::span, af::span) = t(af::seq(i, n - m - 1 + i));
    }

    af::sync();
    while (state.KeepRunning()) {
        gfor(af::seq idx, n - m) {
            auto sdp = tsa::matrix::slidingDotProduct(input(af::span, idx, af::span, af::span), t);
            sdp.eval();
        }
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void MeanStdevAuxiliary(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, f64);
    af::array a;
    auto q = t(af::seq(0, m));
    af::array mean;
    af::array stdev;

    af::sync();
    while (state.KeepRunning()) {
        tsa::matrix::meanStdev(t, a, m, mean, stdev);
        mean.eval();
        stdev.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void MeanStdev(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, f64);
    af::array a;
    auto q = t(af::seq(0, m));
    af::array mean;
    af::array stdev;

    af::sync();
    while (state.KeepRunning()) {
        tsa::matrix::meanStdev(t, a, m, mean, stdev);
        mean.eval();
        stdev.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void GenerateMask(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);
    auto batchStart = state.range(2);

    auto t = af::randu(n, f64);

    af::array profile;
    af::array index;

    af::sync();
    while (state.KeepRunning()) {
        af::array mask = tsa::matrix::generateMask(m, 2048, batchStart, n - m + 1);
        mask.eval();
        af::sync();
    }

    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void CalculateDistanceProfile(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, f64);
    af::array a;
    auto q = t(af::seq(0, m - 1));
    af::array mean;
    af::array stdev;

    tsa::matrix::meanStdev(t, a, m, mean, stdev);

    auto qt = tsa::matrix::slidingDotProduct(q, t);
    af::array mask = tsa::matrix::generateMask(m, 1, 0, n - m + 1);

    auto sumQ = sum(q);
    auto sumQ2 = sum(pow(q, 2));

    af::array distance;
    af::array index;

    af::sync();
    while (state.KeepRunning()) {
        tsa::matrix::calculateDistanceProfile(m, qt, a, sumQ, sumQ2, mean, stdev, mask, distance, index);
        distance.eval();
        index.eval();
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void CalculateDistanceProfileParallel(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, f64);
    af::array a;
    af::array mean;
    af::array stdev;

    tsa::matrix::meanStdev(t, a, m, mean, stdev);

    auto input = af::array(m, n - m + 1, t.type());

    for (int i = 0; i < m; i++) {
        input(i, af::span, af::span, af::span) = t(af::seq(i, n - m + i));
    }

    af::array distance;
    af::array index;

    af::array mask = tsa::matrix::generateMask(m, n - m + 1, 0, n - m + 1);

    af::sync();
    while (state.KeepRunning()) {
        gfor(af::seq idx, n - m + 1) {
            auto q = input(af::span, idx, af::span, af::span);
            auto sumQ = sum(q);
            auto sumQ2 = sum(pow(q, 2));
            auto qt = tsa::matrix::slidingDotProduct(q, t);
            tsa::matrix::calculateDistanceProfile(m, qt, a, sumQ, sumQ2, mean, stdev, mask, distance, index);
            distance.eval();
            index.eval();
        }
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void Mass(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, f64);
    auto q = t(af::seq(0, m - 1));

    af::array distance;
    af::array index;
    af::array aux;
    af::array mean;
    af::array stdev;

    tsa::matrix::meanStdev(t, aux, m, mean, stdev);
    af::array mask = tsa::matrix::generateMask(m, 1, 0, n - m + 1);

    af::sync();
    while (state.KeepRunning()) {
        tsa::matrix::mass(q, t, m, aux, mean, stdev, mask, distance, index);
        distance.eval();
        index.eval();
        af::sync();
    }

    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void Stomp(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto ta = af::randu(n, f64);
    auto tb = af::randu(n, f64);

    af::array profile;
    af::array index;

    af::sync();
    while (state.KeepRunning()) {
        tsa::matrix::stomp(ta, tb, m, profile, index);
        profile.eval();
        index.eval();
        af::sync();
    }

    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void StompDataCPU(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    std::srand(0);
    double *t_host = (double *)malloc(n * sizeof(double));
    for (long i = 0; i < n; i++) {
        t_host[i] = std::rand();
    }

    af::array profile;
    af::array index;

    af::sync();
    while (state.KeepRunning()) {
        tsa::matrix::stomp(af::array(n, t_host), af::array(n, t_host), m, profile, index);
        profile.eval();
        index.eval();
        af::sync();
    }

    addMemoryCounters(state);

    delete[] t_host;
}

template <af::Backend BE, int D>
void StompWithItself(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, f64);

    af::array profile;
    af::array index;

    af::sync();
    while (state.KeepRunning()) {
        tsa::matrix::stomp(t, m, profile, index);
        profile.eval();
        index.eval();
        af::sync();
    }

    addMemoryCounters(state);
}

void cudaBenchmarks() {
    BENCHMARK_TEMPLATE(SlidingDotProduct, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
        ->RangeMultiplier(8)
        ->Ranges({{1 << 10, 128 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(SlidingDotProductParallel, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 8 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(MeanStdevAuxiliary, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
        ->RangeMultiplier(8)
        ->Ranges({{1 << 10, 32 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(MeanStdev, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
        ->RangeMultiplier(8)
        ->Ranges({{1 << 10, 32 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(GenerateMask, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{2 << 10, 8 << 10}, {128, 512}, {16 << 9, 32 << 9}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(CalculateDistanceProfile, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
        ->RangeMultiplier(8)
        ->Ranges({{1 << 10, 32 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(CalculateDistanceProfileParallel, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 4 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(Mass, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 4 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(StompDataCPU, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 16 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(Stomp, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{16 << 10, 128 << 10}, {256, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(StompWithItself, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{16 << 10, 32 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);
}

void openclBenchmarks() {
    BENCHMARK_TEMPLATE(SlidingDotProduct, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
        ->RangeMultiplier(8)
        ->Ranges({{1 << 10, 128 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(SlidingDotProductParallel, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 8 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(MeanStdevAuxiliary, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
        ->RangeMultiplier(8)
        ->Ranges({{1 << 10, 32 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(MeanStdev, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
        ->RangeMultiplier(8)
        ->Ranges({{1 << 10, 32 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(GenerateMask, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{2 << 10, 8 << 10}, {128, 512}, {16 << 9, 32 << 9}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(CalculateDistanceProfile, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
        ->RangeMultiplier(8)
        ->Ranges({{1 << 10, 32 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(CalculateDistanceProfileParallel, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 4 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(Mass, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 4 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(StompDataCPU, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 16 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(Stomp, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{16 << 10, 128 << 10}, {256, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(StompWithItself, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{16 << 10, 32 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);
}

void cpuBenchmarks() {
    BENCHMARK_TEMPLATE(SlidingDotProduct, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(8)
        ->Ranges({{1 << 10, 128 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(SlidingDotProductParallel, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 8 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(MeanStdevAuxiliary, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(8)
        ->Ranges({{1 << 10, 32 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(MeanStdev, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(8)
        ->Ranges({{1 << 10, 32 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(GenerateMask, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{2 << 10, 8 << 10}, {128, 512}, {16 << 9, 32 << 9}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(CalculateDistanceProfile, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(8)
        ->Ranges({{1 << 10, 32 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(CalculateDistanceProfileParallel, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 4 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(Mass, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 4 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(Stomp, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{16 << 10, 128 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(StompDataCPU, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 10, 16 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(StompWithItself, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{16 << 10, 32 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);
}

TSA_BENCHMARK_MAIN(cudaBenchmarks, openclBenchmarks, cpuBenchmarks);