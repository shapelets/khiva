// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_CORE_REGULARIZATION_H
#define KHIVA_CORE_REGULARIZATION_H

#include <arrayfire.h>

namespace khiva {

namespace regularization {

/**
 * @brief Group by operation in the input array using nColumnsKey columns as group keys and nColumnsValue columns as
 * values. The data is expected to be sorted. The aggregation function determines the operation to aggregate the values.
 *
 * @param in Input array containing the keys and values to operate with.
 * @param aggregationFunction This param determines the operation aggregating the values.
 * @param nColumnsKey Number of columns conforming the key.
 * @param nColumnsValue Number of columns conforming the value (they are expected to be consecutive to the column keys).
 *
 * @return af::array Array with the values of the group keys aggregated using the aggregationFunction.
 */
af::array groupBy(af::array in, af::array (*aggregationFunction)(const af::array &, bool, const dim_t),
                  int nColumnsKey = 1, int nColumnsValue = 1);

/**
 * @brief Group by operation in the input array using nColumnsKey columns as group keys and nColumnsValue columns as
 * values. The data is expected to be sorted. The aggregation function determines the operation to aggregate the values.
 *
 * @param in Input array containing the keys and values to operate with.
 * @param aggregationFunction This param determines the operation aggregating the values.
 * @param nColumnsKey Number of columns conforming the key.
 * @param nColumnsValue Number of columns conforming the value (they are expected to be consecutive to the column keys).
 *
 * @return af::array Array with the values of the group keys aggregated using the aggregationFunction.
 */
af::array groupBy(af::array in, af::array (*aggregationFunction)(const af::array &, const int), int nColumnsKey = 1,
                  int nColumnsValue = 1);

/**
 * @brief Group by operation in the input array using nColumnsKey columns as group keys and nColumnsValue columns as
 * values. The data is expected to be sorted. The aggregation function determines the operation to aggregate the values.
 *
 * @param in Input array containing the keys and values to operate with.
 * @param aggregationFunction This param determines the operation aggregating the values.
 * @param nColumnsKey Number of columns conforming the key.
 * @param nColumnsValue Number of columns conforming the value (they are expected to be consecutive to the column keys).
 *
 * @return af::array Array with the values of the group keys aggregated using the aggregationFunction.
 */
af::array groupBy(af::array in, af::array (*aggregationFunction)(const af::array &, const dim_t), int nColumnsKey = 1,
                  int nColumnsValue = 1);

}  // namespace regularization
}  // namespace khiva

#endif