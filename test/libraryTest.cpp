// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <khiva/library.h>
#include "khivaTest.h"

// Simple test, does not use gmock
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

KHIVA_TEST(LibraryTests, SetBackendTest, setBackendTest)
KHIVA_TEST(LibraryTests, GetBackendTest, getBackendTest)
KHIVA_TEST(LibraryTests, GetBackendsTest, getBackendsTest)
KHIVA_TEST(LibraryTests, SetDeviceTest, setDeviceTest)
KHIVA_TEST(LibraryTests, GetDeviceTest, getDeviceTest)
KHIVA_TEST(LibraryTests, GetDeviceCountTest, getDeviceCountTest)
