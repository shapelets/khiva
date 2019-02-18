// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_BINDINGC_LIBRARY_H
#define KHIVA_BINDINGC_LIBRARY_H

#include <khiva_c/defines.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Gets information from the active backend.
 */
KHIVAAPI void backend_info(char **info);

/**
 * @brief Sets the backend.
 *
 * @param backend The desired backend.
 */
KHIVAAPI void set_backend(int *backend);

/**
 * @brief Gets the active backend.
 *
 * @param backend The active backend.
 */
KHIVAAPI void get_backend(int *backend);

/**
 * @brief Gets the available backends.
 *
 * @param backends The available backends.
 */
KHIVAAPI void get_backends(int *backends);

/**
 * @brief Sets the device.
 *
 * @param device The desired device.
 */
KHIVAAPI void set_device(int *device);

/**
 * @brief Gets the active device.
 *
 * @param device The active device.
 */
KHIVAAPI void get_device_id(int *device_id);

/**
 * @brief Gets the devices count.
 *
 * @param device_count The devices count.
 */
KHIVAAPI void get_device_count(int *device_count);

/**
 * @brief Returns a string with the current version of the library.
 *
 * @param v A previously malloced character array where to copy the version.
 */
KHIVAAPI void version(char **v);

#ifdef __cplusplus
}
#endif

#endif
