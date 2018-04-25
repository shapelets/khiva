// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Creates an Array object.
 *
 * @param data Data used in order to create the array.
 * @param ndims Number of dimensions of the data.
 * @param dims Cardinality of dimensions of the data.
 * @param result Array created.
 * @param type Data type.
 */
void create_array(void *data, unsigned ndims, dim_t *dims, af_array *result, const int type);

/**
 * @brief Retrieves the data from the device to the host.
 *
 * @param array The Array that contains the data to be retrieved.
 * @param data Pointer to previously allocated memory in the host.
 */
void get_data(af_array *array, void *data);

/**
 * @brief Gets the Array dimensions.
 *
 * @param array Array from which to get the dimensions.
 * @param dims The dimensions.
 */
void get_dims(af_array *array, dim_t *dims);

/**
 * @brief Displays an Array.
 *
 * @param array The array to display.
 */
void display_array(af_array *array);

/**
 * @brief Decreases the references count of the given array.
 *
 * @param array The Array to release.
 */
void delete_array(af_array *array);

/**
 * @brief Gets the type of the array.
 *
 * @param array The array to obtain the type information from.
 * @param type Value of the Dtype enumeration.
 */
void get_type(af_array *array, int *t);

#ifdef __cplusplus
}
#endif