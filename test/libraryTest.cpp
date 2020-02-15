// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <khiva/library.h>

#include "khivaTest.h"

#include <khiva/internal/libraryInternal.h>

void backendInfoTest() { khiva::library::backendInfo(); }

void setBackendTest() {
    int backends = af::getAvailableBackends();
    bool cuda = backends & af::Backend::AF_BACKEND_CUDA;
    bool opencl = backends & af::Backend::AF_BACKEND_OPENCL;
    bool cpu = backends & af::Backend::AF_BACKEND_CPU;

    if (cuda) {
        khiva::library::setBackend(khiva::library::Backend::KHIVA_BACKEND_CUDA);
        ASSERT_EQ(af::getActiveBackend(), af::Backend::AF_BACKEND_CUDA);
    }

    if (opencl) {
        khiva::library::setBackend(khiva::library::Backend::KHIVA_BACKEND_OPENCL);
        ASSERT_EQ(af::getActiveBackend(), af::Backend::AF_BACKEND_OPENCL);
    }

    if (cpu) {
        khiva::library::setBackend(khiva::library::Backend::KHIVA_BACKEND_CPU);
        ASSERT_EQ(af::getActiveBackend(), af::Backend::AF_BACKEND_CPU);
    }
}

void getBackendTest() {
    int backends = khiva::library::getBackends();
    bool cuda = backends & khiva::library::Backend::KHIVA_BACKEND_CUDA;
    bool opencl = backends & khiva::library::Backend::KHIVA_BACKEND_OPENCL;
    bool cpu = backends & khiva::library::Backend::KHIVA_BACKEND_CPU;

    if (cuda) {
        khiva::library::setBackend(khiva::library::Backend::KHIVA_BACKEND_CUDA);
        ASSERT_EQ(khiva::library::getBackend(), khiva::library::Backend::KHIVA_BACKEND_CUDA);
    }

    if (opencl) {
        khiva::library::setBackend(khiva::library::Backend::KHIVA_BACKEND_OPENCL);
        ASSERT_EQ(khiva::library::getBackend(), khiva::library::Backend::KHIVA_BACKEND_OPENCL);
    }

    if (cpu) {
        khiva::library::setBackend(khiva::library::Backend::KHIVA_BACKEND_CPU);
        ASSERT_EQ(khiva::library::getBackend(), khiva::library::Backend::KHIVA_BACKEND_CPU);
    }
}

void getBackendsTest() {
    int backends = khiva::library::getBackends();
    int backendsAF = af::getAvailableBackends();

    ASSERT_EQ(backends, backendsAF);
}

void setDeviceTest() {
    int devices = af::getDeviceCount();
    for (int i = 0; i < devices; i++) {
        khiva::library::setDevice(i);
        ASSERT_EQ(af::getDevice(), i);
    }
}

void getDeviceTest() {
    int devices = af::getDeviceCount();
    for (int i = 0; i < devices; i++) {
        khiva::library::setDevice(i);
        ASSERT_EQ(khiva::library::getDevice(), i);
    }
}

void getDeviceCountTest() {
    int backends = khiva::library::getBackends();
    bool cuda = backends & khiva::library::Backend::KHIVA_BACKEND_CUDA;
    bool opencl = backends & khiva::library::Backend::KHIVA_BACKEND_OPENCL;
    bool cpu = backends & khiva::library::Backend::KHIVA_BACKEND_CPU;

    if (cuda) {
        khiva::library::setBackend(khiva::library::Backend::KHIVA_BACKEND_CUDA);
        ASSERT_EQ(af::getDeviceCount(), khiva::library::getDeviceCount());
    }

    if (opencl) {
        khiva::library::setBackend(khiva::library::Backend::KHIVA_BACKEND_OPENCL);
        ASSERT_EQ(af::getDeviceCount(), khiva::library::getDeviceCount());
    }

    if (cpu) {
        khiva::library::setBackend(khiva::library::Backend::KHIVA_BACKEND_CPU);
        ASSERT_EQ(af::getDeviceCount(), khiva::library::getDeviceCount());
    }
}

void memoryInDeviceTest() {
    using namespace khiva::library;

    setDeviceMemoryInGB(4.0);
    ASSERT_EQ(2048, internal::getValueScaledToMemoryDevice(2048, internal::Complexity::LINEAR));
    ASSERT_EQ(2048, internal::getValueScaledToMemoryDevice(2048, internal::Complexity::CUADRATIC));
    ASSERT_EQ(2048, internal::getValueScaledToMemoryDevice(2048, internal::Complexity::CUBIC));

    setDeviceMemoryInGB(2.0);
    ASSERT_EQ(1024, internal::getValueScaledToMemoryDevice(2048, internal::Complexity::LINEAR));
    ASSERT_EQ(1448, internal::getValueScaledToMemoryDevice(2048, internal::Complexity::CUADRATIC));
    ASSERT_EQ(1625, internal::getValueScaledToMemoryDevice(2048, internal::Complexity::CUBIC));

    setDeviceMemoryInGB(1.0);
    ASSERT_EQ(512, internal::getValueScaledToMemoryDevice(2048, internal::Complexity::LINEAR));
    ASSERT_EQ(1024, internal::getValueScaledToMemoryDevice(2048, internal::Complexity::CUADRATIC));
    ASSERT_EQ(1290, internal::getValueScaledToMemoryDevice(2048, internal::Complexity::CUBIC));

    setDeviceMemoryInGB(4.0);
    ASSERT_EQ(2048, internal::getValueScaledToMemoryDevice(2048, internal::Complexity::LINEAR));
    ASSERT_EQ(2048, internal::getValueScaledToMemoryDevice(2048, internal::Complexity::CUADRATIC));
    ASSERT_EQ(2048, internal::getValueScaledToMemoryDevice(2048, internal::Complexity::CUBIC));

    setDeviceMemoryInGB(8.0);
    ASSERT_EQ(4096, internal::getValueScaledToMemoryDevice(2048, internal::Complexity::LINEAR));
    ASSERT_EQ(2896, internal::getValueScaledToMemoryDevice(2048, internal::Complexity::CUADRATIC));
    ASSERT_EQ(2580, internal::getValueScaledToMemoryDevice(2048, internal::Complexity::CUBIC));

    setDeviceMemoryInGB(6.0);
    ASSERT_EQ(3072, internal::getValueScaledToMemoryDevice(2048, internal::Complexity::LINEAR));
    ASSERT_EQ(2508, internal::getValueScaledToMemoryDevice(2048, internal::Complexity::CUADRATIC));
    ASSERT_EQ(2344, internal::getValueScaledToMemoryDevice(2048, internal::Complexity::CUBIC));

    setDeviceMemoryInGB(6.0);
    ASSERT_EQ(30e6, internal::getValueScaledToMemoryDevice(20e6, internal::Complexity::LINEAR));
    ASSERT_EQ(24494897, internal::getValueScaledToMemoryDevice(20e6, internal::Complexity::CUADRATIC));
    ASSERT_EQ(22894284, internal::getValueScaledToMemoryDevice(20e6, internal::Complexity::CUBIC));
}

KHIVA_TEST(LibraryTests, BackendInfoTest, backendInfoTest)
KHIVA_TEST(LibraryTests, SetBackendTest, setBackendTest)
KHIVA_TEST(LibraryTests, GetBackendTest, getBackendTest)
KHIVA_TEST(LibraryTests, GetBackendsTest, getBackendsTest)
KHIVA_TEST(LibraryTests, SetDeviceTest, setDeviceTest)
KHIVA_TEST(LibraryTests, GetDeviceTest, getDeviceTest)
KHIVA_TEST(LibraryTests, GetDeviceCountTest, getDeviceCountTest)
KHIVA_TEST(LibraryTests, MemoryInDeviceTest, memoryInDeviceTest)
