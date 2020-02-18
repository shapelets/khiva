// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <benchmark/benchmark.h>
#include <khiva/internal/matrixInternal.h>
#include <khiva/matrix.h>

#include <algorithm>
#include <cmath>

#include "khivaBenchmark.h"

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
        auto sdp = khiva::matrix::internal::slidingDotProduct(q, t);
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
            auto sdp = khiva::matrix::internal::slidingDotProduct(input(af::span, idx, af::span, af::span), t);
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
        khiva::matrix::internal::meanStdev(t, a, m, mean, stdev);
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
        khiva::matrix::internal::meanStdev(t, a, m, mean, stdev);
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
        af::array mask = khiva::matrix::internal::generateMask(m, 2048, batchStart, n - m + 1, 0);
        mask.eval();
        af::sync();
    }

    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void CalculateDistances(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, f64);
    af::array a;
    auto q = t(af::seq(0, m - 1));
    af::array mean;
    af::array stdev;

    khiva::matrix::internal::meanStdev(t, a, m, mean, stdev);

    auto qt = khiva::matrix::internal::slidingDotProduct(q, t);
    af::array mask = khiva::matrix::internal::generateMask(m, 1, 0, n - m + 1, 0);

    auto sumQ = sum(q);
    auto sumQ2 = sum(pow(q, 2));

    af::array distances;

    af::sync();
    while (state.KeepRunning()) {
        khiva::matrix::internal::calculateDistances(qt, a, sumQ, sumQ2, mean, stdev, mask, distances);
        distances.eval();
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

    khiva::matrix::internal::meanStdev(t, a, m, mean, stdev);

    auto input = af::array(m, n - m + 1, t.type());

    for (int i = 0; i < m; i++) {
        input(i, af::span, af::span, af::span) = t(af::seq(i, n - m + i));
    }

    af::array distances;

    af::array mask = khiva::matrix::internal::generateMask(m, n - m + 1, 0, n - m + 1, 0);

    af::sync();
    while (state.KeepRunning()) {
        gfor(af::seq idx, n - m + 1) {
            auto q = input(af::span, idx, af::span, af::span);
            auto sumQ = sum(q);
            auto sumQ2 = sum(pow(q, 2));
            auto qt = khiva::matrix::internal::slidingDotProduct(q, t);
            khiva::matrix::internal::calculateDistances(qt, a, sumQ, sumQ2, mean, stdev, mask, distances);
            distances.eval();
        }
        af::sync();
    }
    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void MassComplete(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto t = af::randu(n, f64);
    auto q = t(af::seq(0, m - 1));

    af::array distances;

    af::sync();
    while (state.KeepRunning()) {
        khiva::matrix::mass(q, t, distances);
        distances.eval();
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

    af::array distances;
    af::array aux;
    af::array mean;
    af::array stdev;

    khiva::matrix::internal::meanStdev(t, aux, m, mean, stdev);
    af::array mask = khiva::matrix::internal::generateMask(m, 1, 0, n - m + 1, 0);

    af::sync();
    while (state.KeepRunning()) {
        khiva::matrix::internal::massWithMask(q, t, aux, mean, stdev, mask, distances);
        distances.eval();
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
        khiva::matrix::stomp(ta, tb, m, profile, index);
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
    std::vector<double> t_host;
    t_host.reserve(n);
    std::generate_n(std::back_inserter(t_host), n, std::rand);

    af::array profile;
    af::array index;

    af::sync();
    while (state.KeepRunning()) {
        khiva::matrix::stomp(af::array(n, t_host.data()), af::array(n, t_host.data()), m, profile, index);
        profile.eval();
        index.eval();
        af::sync();
    }

    addMemoryCounters(state);
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
        khiva::matrix::stomp(t, m, profile, index);
        profile.eval();
        index.eval();
        af::sync();
    }

    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void FindBestNMotifs(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = 8192L;
    auto m = state.range(0);

    auto t = af::randu(n, f64);

    af::array profile;
    af::array index;
    af::array motifs;
    af::array motifsIndices;
    af::array subsequenceIndices;

    khiva::matrix::stomp(t, m, profile, index);
    profile.eval();
    index.eval();

    float percent = (log2(state.range(1)) + 1) * 0.125f;
    long maxMotifs = std::max(static_cast<int>(std::ceil(profile.dims(0) / std::ceil(m / 2.0f))), 1);
    long nMotifs = static_cast<long>(std::ceil(percent * maxMotifs));

    af::sync();
    while (state.KeepRunning()) {
        khiva::matrix::findBestNMotifs(profile, index, m, nMotifs, motifs, motifsIndices, subsequenceIndices, true);

        motifs.eval();
        motifsIndices.eval();
        subsequenceIndices.eval();
        af::sync();
    }

    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void FindBestNDiscords(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = 8192L;
    auto m = state.range(0);

    auto t = af::randu(n, f64);

    af::array profile;
    af::array index;
    af::array discords;
    af::array discordsIndices;
    af::array subsequenceIndices;

    khiva::matrix::stomp(t, m, profile, index);
    profile.eval();
    index.eval();

    float percent = (log2(state.range(1)) + 1) * 0.125f;
    long maxDiscords = std::max(static_cast<int>(std::ceil(profile.dims(0) / std::ceil(m / 2.0f))), 1);
    long nDiscords = static_cast<long>(std::ceil(percent * maxDiscords));

    af::sync();
    while (state.KeepRunning()) {
        khiva::matrix::findBestNDiscords(profile, index, m, nDiscords, discords, discordsIndices, subsequenceIndices,
                                         true);

        discords.eval();
        discordsIndices.eval();
        subsequenceIndices.eval();
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
        ->Ranges({{2 << 10, 128 << 10}, {128, 1024}, {16 << 9, 32 << 9}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(CalculateDistances, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
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

    BENCHMARK_TEMPLATE(MassComplete, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 20, 4 << 20}, {16, 512}})
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

    BENCHMARK_TEMPLATE(FindBestNMotifs, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{16, 1024}, {1, 128}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(FindBestNDiscords, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{16, 1024}, {1, 128}})
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
        ->Ranges({{2 << 10, 128 << 10}, {128, 1024}, {16 << 9, 32 << 9}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(CalculateDistances, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
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

    BENCHMARK_TEMPLATE(MassComplete, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 20, 4 << 20}, {16, 512}})
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

    BENCHMARK_TEMPLATE(FindBestNMotifs, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{16, 1024}, {1, 128}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(FindBestNDiscords, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{16, 1024}, {1, 128}})
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
        ->Ranges({{2 << 10, 128 << 10}, {128, 1024}, {16 << 9, 32 << 9}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(CalculateDistances, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
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

    BENCHMARK_TEMPLATE(MassComplete, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{1 << 20, 4 << 20}, {16, 512}})
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

    BENCHMARK_TEMPLATE(FindBestNMotifs, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{16, 1024}, {1, 128}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(FindBestNDiscords, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{16, 1024}, {1, 128}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);
}

KHIVA_BENCHMARK_MAIN(cudaBenchmarks, openclBenchmarks, cpuBenchmarks)
