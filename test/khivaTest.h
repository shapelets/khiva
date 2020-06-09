// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_TEST_H
#define KHIVA_TEST_H

constexpr auto EPSILON = 1e-6;

#define KHIVA_TEST(SUITE_NAME, TEST_NAME, FUNCTION_NAME) \
    KHIVA_TEST_BACKENDS(SUITE_NAME, TEST_NAME, FUNCTION_NAME, true, true, true, true, true, true)

#define KHIVA_TEST_BACKENDS(SUITE_NAME, TEST_NAME, FUNCTION_NAME, CUDA, OPENCL, CPU, CUDADEVICES, OPENCLDEVICES, \
                            CPUDEVICES)                                                                          \
    TEST(SUITE_NAME, TEST_NAME) {                                                                                \
        int backends = af::getAvailableBackends();                                                               \
        bool cuda = backends & af::Backend::AF_BACKEND_CUDA;                                                     \
        bool opencl = backends & af::Backend::AF_BACKEND_OPENCL;                                                 \
        bool cpu = backends & af::Backend::AF_BACKEND_CPU;                                                       \
                                                                                                                 \
        if (cpu && (CPU)) {                                                                                        \
            af::setBackend(af::Backend::AF_BACKEND_CPU);                                                         \
            int devices = (CPUDEVICES) ? af::getDeviceCount() : 1;                                               \
            for (int i = 0; i < devices; i++) {                                                                  \
                af::setDevice(i);                                                                                \
                std::cout << "\033[32m[----------]\033[0m CPU backend, device: ";                                \
                char name[100], platform[100], toolkit[100], compute[100];                                       \
                af::deviceInfo(name, platform, toolkit, compute);                                                \
                std::cout << name << " " << platform << std::endl;                                               \
                FUNCTION_NAME();                                                                                 \
            }                                                                                                    \
        }                                                                                                        \
        if (cuda && (CUDA)) {                                                                                      \
            af::setBackend(af::Backend::AF_BACKEND_CUDA);                                                        \
            int devices = (CUDADEVICES) ? af::getDeviceCount() : 1;                                              \
            for (int i = 0; i < devices; i++) {                                                                  \
                af::setDevice(i);                                                                                \
                std::cout << "[----------] CUDA backend, device: ";                                              \
                char name[100], platform[100], toolkit[100], compute[100];                                       \
                af::deviceInfo(name, platform, toolkit, compute);                                                \
                std::cout << name << std::endl;                                                                  \
                FUNCTION_NAME();                                                                                 \
            }                                                                                                    \
        }                                                                                                        \
        if (opencl && (OPENCL)) {                                                                                  \
            af::setBackend(af::Backend::AF_BACKEND_OPENCL);                                                      \
            int devices = (OPENCLDEVICES) ? af::getDeviceCount() : 1;                                            \
            for (int i = 0; i < devices; i++) {                                                                  \
                af::setDevice(i);                                                                                \
                std::cout << "\033[32m[----------]\033[0m OPENCL backend, device: ";                             \
                char name[100], platform[100], toolkit[100], compute[100];                                       \
                af::deviceInfo(name, platform, toolkit, compute);                                                \
                std::cout << name << std::endl;                                                                  \
                FUNCTION_NAME();                                                                                 \
            }                                                                                                    \
        }                                                                                                        \
    }

#endif  // KHIVA_TEST_H
