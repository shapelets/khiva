// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <tsa/library.h>
#include "tsaTest.h"

// Simple test, does not use gmock
void setBackendTest() {
    int backends = af::getAvailableBackends();
    bool cuda = backends & af::Backend::AF_BACKEND_CUDA;
    bool opencl = backends & af::Backend::AF_BACKEND_OPENCL;
    bool cpu = backends & af::Backend::AF_BACKEND_CPU;

    if (cuda) {
        tsa::library::setBackend(tsa::library::Backend::TSA_BACKEND_CUDA);
        ASSERT_EQ(af::getActiveBackend(), af::Backend::AF_BACKEND_CUDA);
    }

    if (opencl) {
        tsa::library::setBackend(tsa::library::Backend::TSA_BACKEND_OPENCL);
        ASSERT_EQ(af::getActiveBackend(), af::Backend::AF_BACKEND_OPENCL);
    }

    if (cpu) {
        tsa::library::setBackend(tsa::library::Backend::TSA_BACKEND_CPU);
        ASSERT_EQ(af::getActiveBackend(), af::Backend::AF_BACKEND_CPU);
    }
}

void getBackendTest() {
    int backends = tsa::library::getBackends();
    bool cuda = backends & tsa::library::Backend::TSA_BACKEND_CUDA;
    bool opencl = backends & tsa::library::Backend::TSA_BACKEND_OPENCL;
    bool cpu = backends & tsa::library::Backend::TSA_BACKEND_CPU;

    if (cuda) {
        tsa::library::setBackend(tsa::library::Backend::TSA_BACKEND_CUDA);
        ASSERT_EQ(tsa::library::getBackend(), tsa::library::Backend::TSA_BACKEND_CUDA);
    }

    if (opencl) {
        tsa::library::setBackend(tsa::library::Backend::TSA_BACKEND_OPENCL);
        ASSERT_EQ(tsa::library::getBackend(), tsa::library::Backend::TSA_BACKEND_OPENCL);
    }

    if (cpu) {
        tsa::library::setBackend(tsa::library::Backend::TSA_BACKEND_CPU);
        ASSERT_EQ(tsa::library::getBackend(), tsa::library::Backend::TSA_BACKEND_CPU);
    }
}

void getBackendsTest() {
    int backends = tsa::library::getBackends();
    int backendsAF = af::getAvailableBackends();

    ASSERT_EQ(backends, backendsAF);
}

void setDeviceTest() {
    int devices = af::getDeviceCount();
    for (int i = 0; i < devices; i++) {
        tsa::library::setDevice(i);
        ASSERT_EQ(af::getDevice(), i);
    }
}

void getDeviceTest() {
    int devices = af::getDeviceCount();
    for (int i = 0; i < devices; i++) {
        tsa::library::setDevice(i);
        ASSERT_EQ(tsa::library::getDevice(), i);
    }
}

TSA_TEST(LibraryTests, SetBackendTest, setBackendTest);
TSA_TEST(LibraryTests, GetBackendTest, getBackendTest);
TSA_TEST(LibraryTests, GetBackendsTest, getBackendsTest);
TSA_TEST(LibraryTests, SetDeviceTest, setDeviceTest);
TSA_TEST(LibraryTests, GetDeviceTest, getDeviceTest);
