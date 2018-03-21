// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

namespace tsa {

namespace library {

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Get the devices info.
 */
void info();

/**
 * @brief Set the backend.
 *
 * @param backend The desired backend.
 */
void set_backend(int *backend);

/**
 * @brief Get the active backend.
 *
 * @param backend The active backend.
 */
void get_backend(int *backend);

/**
 * @brief Get the available backends.
 *
 * @param backends The available backends.
 */
void get_backends(int *backends);

/**
 * @brief Set the device.
 *
 * @param device The desired device.
 */
void set_device(int *device);

/**
 * @brief Get the active device.
 *
 * @param device The active device.
 */
void get_device_id(int *device_id);

/**
 * @brief Get the devices count.
 *
 * @param device_count The devices count.
 */
void get_device_count(int *device_count);

#ifdef __cplusplus
}
#endif
};  // namespace library
};  // namespace tsa