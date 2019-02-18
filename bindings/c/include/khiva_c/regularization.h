// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_BINDINGC_REGULARIZATION_H
#define KHIVA_BINDINGC_REGULARIZATION_H

#include <khiva_c/defines.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Group by operation in the input array using n_columns_key columns as group keys and n_columns_value columns as
 * values. The data is expected to be sorted. The aggregation function determines the operation to aggregate the values.
 *
 * @param array Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of time series.
 * @param aggregation_function Function to be used in the aggregation. It receives an integer which indicates the
 * function to be applied:
 *          {
 *              0 : mean,
 *              1 : median
 *              2 : min,
 *              3 : max,
 *              4 : stdev,
 *              5 : var,
 *              default : mean
 *          }
 * @param n_columns_key Number of columns conforming the key.
 * @param n_columns_value Number of columns conforming the value (they are expected to be consecutive to the column
 * keys).
 *
 * @param result An array with the values of the group keys aggregated using the aggregation_function.
 */
KHIVAAPI void group_by(khiva_array *array, int *aggregation_function, int *n_columns_key, int *n_columns_value,
                       khiva_array *result);

#ifdef __cplusplus
}
#endif

#endif
