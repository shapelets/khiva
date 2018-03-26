// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>

namespace tsa {

namespace library {

typedef enum {
    TSA_BACKEND_DEFAULT = af::Backend::AF_BACKEND_DEFAULT,  ///< Default backend order: OpenCL -> CUDA -> CPU
    TSA_BACKEND_CPU = af::Backend::AF_BACKEND_CPU,          ///< CPU a.k.a sequential algorithms
    TSA_BACKEND_CUDA = af::Backend::AF_BACKEND_CUDA,        ///< CUDA Compute Backend
    TSA_BACKEND_OPENCL = af::Backend::AF_BACKEND_OPENCL,    ///< OpenCL Compute Backend
} tsa_backend;

typedef tsa_backend Backend;

/**
 * @brief Get the backend info.
 */
void backendInfo();

/**
 * @brief Set the backend.
 *
 * @param be The desired backend.
 */
void setBackend(tsa::library::Backend be);

/**
 * @brief Get the active backend
 *
 * @return tsa::library::Backend The active backend
 */
tsa::library::Backend getBackend();

/**
 * @brief Get the available backends
 *
 * @return int The available backends
 */
int getBackends();

/**
 * @brief Set the device.
 *
 * @param device The desired device.
 */
void setDevice(int device);

/**
 * @brief Get the active device
 *
 * @return int The active device.
 */
int getDevice();

/**
 * @brief Get the device count.
 *
 * @return int The device count.
 */
int getDeviceCount();

};  // namespace library
};  // namespace tsa