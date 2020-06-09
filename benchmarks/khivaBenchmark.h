// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_BENCHMARK_H
#define KHIVA_BENCHMARK_H

#include <arrayfire.h>
#include <benchmark/benchmark.h>
#include <iostream>

// Removing Google benchmark MAIN macro to force using ours
#undef BENCHMARK_MAIN

#ifndef CUDA_BENCHMARKING_DEVICE
#define CUDA_BENCHMARKING_DEVICE 0
#endif

#ifndef OPENCL_BENCHMARKING_DEVICE
#define OPENCL_BENCHMARKING_DEVICE 0
#endif

#ifndef CPU_BENCHMARKING_DEVICE
#define CPU_BENCHMARKING_DEVICE 0
#endif

#define KHIVA_BENCHMARK_MAIN(CUDA_BENCH, OPENCL_BENCH, CPU_BENCH) \
    KHIVA_BENCHMARK_BACKENDS_MAIN(CUDA_BENCH, OPENCL_BENCH, CPU_BENCH, true, true, true)

#define KHIVA_BENCHMARK_BACKENDS_MAIN(CUDA_BENCH, OPENCL_BENCH, CPU_BENCH, CUDA, OPENCL, CPU) \
    int main(int argc, char **argv) {                                                         \
        ::benchmark::Initialize(&argc, argv);                                                 \
        if (::benchmark::ReportUnrecognizedArguments(argc, argv)) return 1;                   \
        int backends = af::getAvailableBackends();                                            \
        bool cuda = backends & af::Backend::AF_BACKEND_CUDA;                                  \
        bool opencl = backends & af::Backend::AF_BACKEND_OPENCL;                              \
        bool cpu = backends & af::Backend::AF_BACKEND_CPU;                                    \
        if (cuda && (CUDA)) {                                                                   \
            af::setBackend(af::Backend::AF_BACKEND_CUDA);                                     \
            for (int i = 0; i < af::getDeviceCount(); i++) {                                  \
                if (i == CUDA_BENCHMARKING_DEVICE) {                                          \
                    std::cout << "Run on CUDA backend, device[" << i << "]: ";                \
                    char name[100], platform[100], toolkit[100], compute[100];                \
                    af::deviceInfo(name, platform, toolkit, compute);                         \
                    std::cout << name << std::endl;                                           \
                    CUDA_BENCH();                                                             \
                }                                                                             \
            }                                                                                 \
        }                                                                                     \
        if (opencl && (OPENCL)) {                                                               \
            af::setBackend(af::Backend::AF_BACKEND_OPENCL);                                   \
            for (int i = 0; i < af::getDeviceCount(); i++) {                                  \
                if (i == OPENCL_BENCHMARKING_DEVICE) {                                        \
                    std::cout << "Run on OPENCL backend, device[" << i << "]: ";              \
                    char name[100], platform[100], toolkit[100], compute[100];                \
                    af::deviceInfo(name, platform, toolkit, compute);                         \
                    std::cout << name << std::endl;                                           \
                    OPENCL_BENCH();                                                           \
                }                                                                             \
            }                                                                                 \
        }                                                                                     \
        if (cpu && (CPU)) {                                                                     \
            af::setBackend(af::Backend::AF_BACKEND_CPU);                                      \
            for (int i = 0; i < af::getDeviceCount(); i++) {                                  \
                if (i == CPU_BENCHMARKING_DEVICE) {                                           \
                    std::cout << "Run on CPU backend, device[" << i << "]: ";                 \
                    char name[100], platform[100], toolkit[100], compute[100];                \
                    af::deviceInfo(name, platform, toolkit, compute);                         \
                    std::cout << name << " " << platform << std::endl;                        \
                    CPU_BENCH();                                                              \
                }                                                                             \
            }                                                                                 \
        }                                                                                     \
        ::benchmark::RunSpecifiedBenchmarks();                                                \
    }

void addMemoryCounters(benchmark::State &state) {
    size_t bytes, buffers, lockedBytes, lockedBuffers;
    // This is already doing an af::sync();
    af::deviceMemInfo(&bytes, &buffers, &lockedBytes, &lockedBuffers);

    state.counters["Memory"] = static_cast<double>(bytes);
    state.counters["Buffers"] = static_cast<double>(buffers);
    state.counters["LockedMemory"] = static_cast<double>(lockedBytes);
    state.counters["LockedBuffers"] = static_cast<double>(lockedBuffers);

    af::deviceGC();
}

#endif  // KHIVA_BENCHMARK_H
