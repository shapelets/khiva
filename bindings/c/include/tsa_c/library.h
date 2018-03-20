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
 * @brief Set the back-end.
 *
 * @param backend The desired back-end.
 */
void set_backend(int *backend);

/**
 * @brief Set the device.
 *
 * @param device The desired device.
 */
void set_device(int *device);

#ifdef __cplusplus
}
#endif
};  // namespace library
};  // namespace tsa