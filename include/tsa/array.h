// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#include <arrayfire.h>

using namespace af;

namespace tsa {

typedef af::dtype dtype;

namespace array {

/**
 * @brief Create an Array object.
 *
 * @param data Data used in order to create the array.
 * @param ndims Number of dimensions of the data.
 * @param dims Cardinality of dimesions of the data.
 * @param result Array created.
 * @param type Data type.
 */
af::array createArray(void *data, unsigned ndims, dim_t *dims, const int type);

/**
 * @brief Retrieves the data from the device to the host.
 *
 * @param array The Array that contains the data to be retrieved.
 * @param data Pointer to previously allocated memory in the host.
 */
void getData(af::array array, void *data);

/**
 * @brief Get the Array dimensions.
 *
 * @param array Array from which to get the dimensions
 * @param dims The dimensions.
 */
af::dim4 getDims(af::array array);

/**
 * @brief Displays an Array.
 *
 * @param array The array to display.
 */
void displayArray(af::array array);

/**
 * @brief Decrease the references count of the given array.
 *
 * @param array The Array to release.
 */
void deleteArray(af_array array);
};  // namespace array
};  // namespace tsa