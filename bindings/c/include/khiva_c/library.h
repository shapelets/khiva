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
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void backend_info(char **info, int *error_code, char *error_message);

/**
 * @brief Sets the backend.
 *
 * @param backend The desired backend.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void set_backend(int *backend, int *error_code, char *error_message);

/**
 * @brief Gets the active backend.
 *
 * @param backend The active backend.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void get_backend(int *backend, int *error_code, char *error_message);

/**
 * @brief Gets the available backends.
 *
 * @param backends The available backends.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void get_backends(int *backends, int *error_code, char *error_message);

/**
 * @brief Sets the device.
 *
 * @param device The desired device.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void set_device(int *device, int *error_code, char *error_message);

/**
 * @brief Gets the active device.
 *
 * @param device The active device.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void get_device_id(int *device_id, int *error_code, char *error_message);

/**
 * @brief Gets the devices count.
 *
 * @param device_count The devices count.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void get_device_count(int *device_count, int *error_code, char *error_message);

/**
 * @brief Set the memory of the device in use. This information is used for splitting some algorithms and execute them
 * in batch mode. The default value used if it is not set is 4GB.
 *
 * @param memory The device memory.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void set_device_memory_in_gb(double *memory, int *error_code, char *error_message);

/**
 * @brief Returns a string with the current version of the library.
 *
 * @param v A previously malloced character array where to copy the version.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void version(char **v, int *error_code, char *error_message);

#ifdef __cplusplus
}
#endif

#endif
