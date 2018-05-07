// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Group by operation in the input array using nColumnsKey columns as group keys and nColumnsValue columns as
 * values. The data is expected to be sorted. The aggregation function determines the operation to aggregate the values.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of time series.
 * @param aggregationFunction Function to be used in the aggregation. It receives an integer which indicates the
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
 * @param nColumnsKey Number of columns conforming the key.
 * @param nColumnsValue Number of columns conforming the value (they are expected to be consecutive to the column
 * keys).
 *
 * @return The updated ref and an array with the values of the group keys aggregated using the aggregationFunction.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Regularization_groupBy(JNIEnv *env, jobject thisObj, jlong ref,
                                                             jint aggregationFunction, jint nColumnsKey,
                                                             jint nColumnsValue);

#ifdef __cplusplus
}
#endif