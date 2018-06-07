# KHIVA Benchmarks

In order to execute the benchmarks in all the available backends we have defined the `KHIVA_BENCHMARK_MAIN` macro, which redefines the `BENCHMARK_MAIN` macro of Google benchmarks.

The `KHIVA_BENCHMARK_MAIN` needs 3 functions in the following order:
1. A function containing the benchmarks to be executed in the **CUDA** backend.
2. A function containing the benchmarks to be executed in the **OPENCL** backend.
3. A function containing the benchmarks to be executed in the **CPU** backend.

The device on which the benchmarks are executed are defined in the following constants:
* **CUDA_BENCHMARKING_DEVICE**: Device to use for the CUDA backend. Defaults to 0.
* **OPENCL_BENCHMARKING_DEVICE**: Device to use for the OPENCL backend. Defaults to 0.
* **CPU_BENCHMARKING_DEVICE**: Device to use for the CPU backend. Defaults to 0.

Example benchmarking file:
```C++
// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <benchmark/benchmark.h>
#include "khivabenchmark.h"

template <af::Backend BE, int D>
void test(benchmark::State &state) {
    af::setBackend(BE);
    af::setDevice(D);
    
    // DATA INITIALIZATION

    af::sync();
    while (state.KeepRunning()) {
        // CODE TO MEASURE
        af::sync();
    }
}

void cudaBenchmarks() {
    BENCHMARK_TEMPLATE(test, af::Backend::AF_BACKEND_CUDA, CUDA_BENCHMARKING_DEVICE)
        ->RangeMultiplier(8)
        ->Ranges({{1 << 10, 32 << 10}, {64, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);
}

void openclBenchmarks() {
    BENCHMARK_TEMPLATE(test, af::Backend::AF_BACKEND_OPENCL, OPENCL_BENCHMARKING_DEVICE)
        ->RangeMultiplier(8)
        ->Ranges({{1 << 10, 32 << 10}, {64, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);
}

void cpuBenchmarks() {
    BENCHMARK_TEMPLATE(test, af::Backend::AF_BACKEND_CPU, CPU_BENCHMARKING_DEVICE)
        ->RangeMultiplier(8)
        ->Ranges({{1 << 10, 32 << 10}, {64, 512}})
        ->Unit(benchmark::TimeUnit::kMicrosecond);
}

KHIVA_BENCHMARK_MAIN(cudaBenchmarks, openclBenchmarks, cpuBenchmarks);
```
