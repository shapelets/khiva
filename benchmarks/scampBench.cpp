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
#include <iterator>

#include "khivaBenchmark.h"

template <af::Backend BE, int D>
void MatrixProfile(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto tss = af::randu(n, f64);

    af::array profile;
    af::array index;

    af::sync();
    while (state.KeepRunning()) {
        khiva::matrix::matrixProfile(tss, m, profile, index);
        profile.eval();
        index.eval();
        af::sync();
    }

    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void MatrixProfile2(benchmark::State &state) {
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
        khiva::matrix::matrixProfile(ta, tb, m, profile, index);
        profile.eval();
        index.eval();
        af::sync();
    }

    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void MatrixProfileThresh(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);
    double threshold = 0.5;

    auto tss = af::randu(n, f64);

    af::array sumCorrelation;

    af::sync();
    while (state.KeepRunning()) {
        khiva::matrix::matrixProfileThresh(tss, m, threshold, sumCorrelation);
        sumCorrelation.eval();
        af::sync();
    }

    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void MatrixProfileThresh2(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);
    double threshold = 0.5;

    auto ta = af::randu(n, f64);
    auto tb = af::randu(n, f64);

    af::array sumCorrelation;

    af::sync();
    while (state.KeepRunning()) {
        khiva::matrix::matrixProfileThresh(ta, tb, m, threshold, sumCorrelation);
        sumCorrelation.eval();
        af::sync();
    }

    addMemoryCounters(state);
}

template <af::Backend BE, int D>
void MatrixProfileLR(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);

    auto n = state.range(0);
    auto m = state.range(1);

    auto tss = af::randu(n, f64);

    af::array profileLeft;
    af::array profileRight;
    af::array indexLeft;
    af::array indexRight;

    af::sync();
    while (state.KeepRunning()) {
        khiva::matrix::matrixProfileLR(tss, m, profileLeft, indexLeft, profileRight, indexRight);
        profileLeft.eval();
        profileRight.eval();
        indexLeft.eval();
        indexRight.eval();
        af::sync();
    }

    addMemoryCounters(state);
}

void cudaBenchmarks() {
    // Empty cuda benchmarks because we want to benchmark only on cpu
}

void openclBenchmarks() {
    // Empty opencl benchmarks because we want to benchmark only on cpu
}

void cpuBenchmarks() {
    BENCHMARK_TEMPLATE(MatrixProfile, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{16 << 10, 128 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(MatrixProfile2, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{16 << 10, 128 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(MatrixProfileLR, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{16 << 10, 128 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(MatrixProfileThresh, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{16 << 10, 128 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);

    BENCHMARK_TEMPLATE(MatrixProfileThresh2, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(2)
        ->Ranges({{16 << 10, 128 << 10}, {16, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);
}

KHIVA_BENCHMARK_MAIN(cudaBenchmarks, openclBenchmarks, cpuBenchmarks)
