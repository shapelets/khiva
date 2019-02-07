// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_CORE_LIBRARY_H
#define KHIVA_CORE_LIBRARY_H

#include <arrayfire.h>

namespace khiva
{

namespace library
{

typedef enum
{
    KHIVA_BACKEND_DEFAULT = af::Backend::AF_BACKEND_DEFAULT, ///< Default backend order: OpenCL -> CUDA -> CPU
    KHIVA_BACKEND_CPU = af::Backend::AF_BACKEND_CPU,         ///< CPU a.k.a sequential algorithms
    KHIVA_BACKEND_CUDA = af::Backend::AF_BACKEND_CUDA,       ///< CUDA Compute Backend
    KHIVA_BACKEND_OPENCL = af::Backend::AF_BACKEND_OPENCL,   ///< OpenCL Compute Backend
} khiva_backend;

typedef khiva_backend Backend;

/**
 * @brief Get information from the active backend.
 *
 * @return std::string The information of the backend.
 */
std::string backendInfo();

/**
 * @brief Set the backend.
 *
 * @param be The desired backend.
 */
void setBackend(khiva::library::Backend be);

/**
 * @brief Get the active backend.
 *
 * @return khiva::library::Backend The active backend.
 */
khiva::library::Backend getBackend();

/**
 * @brief Get the available backends.
 *
 * @return int The available backends.
 */
int getBackends();

/**
 * @brief Set the device.
 *
 * @param device The desired device.
 */
void setDevice(int device);

/**
 * @brief Get the active device.
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

} // namespace library
} // namespace khiva

#endif