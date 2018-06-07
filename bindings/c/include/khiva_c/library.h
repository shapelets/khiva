// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva_c/defines.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get the devices info.
 */
KHIVAAPI void info();

/**
 * @brief Set the backend.
 *
 * @param backend The desired backend.
 */
KHIVAAPI void set_backend(int *backend);

/**
 * @brief Get the active backend.
 *
 * @param backend The active backend.
 */
KHIVAAPI void get_backend(int *backend);

/**
 * @brief Get the available backends.
 *
 * @param backends The available backends.
 */
KHIVAAPI void get_backends(int *backends);

/**
 * @brief Set the device.
 *
 * @param device The desired device.
 */
KHIVAAPI void set_device(int *device);

/**
 * @brief Get the active device.
 *
 * @param device The active device.
 */
KHIVAAPI void get_device_id(int *device_id);

/**
 * @brief Get the devices count.
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
