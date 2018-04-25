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
 * @brief Calculates a new set of timeseries with zero mean and standard deviation one.
 *
 * @param ref Expects an input array whose dimension zero is the length of the timeseries (all the same) and dimension
 * one indicates the number of time series.
 * @param epsilon Minimum standard deviation to consider. It acts a a gatekeeper for those time series that may be
 * constant or near constant.
 * @return The updated ref and the with the same dimensions as ref where the time series have been
 * adjusted for zero mean and one as standard deviation.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Normalization_znorm(JNIEnv *env, jobject thisObj, jlong ref, jdouble epsilon);

/**
 * @brief Adjusts the time series in the given input and performs z-norm
 * inplace (without allocating further memory).
 *
 * @param ref Expects an input array whose dimension zero is the length of the timeseries (all the same) and dimension
 * one indicates the number of time series.
 * @param epsilon Minimum standard deviation to consider. It acts as a gatekeeper for those time series that may be
 * constant or near constant.
 * @return The updated ref.
 */
JNIEXPORT jlong JNICALL Java_tsa_Normalization_znormInPlace(JNIEnv *env, jobject thisObj, jlong ref, jdouble epsilon);

#ifdef __cplusplus
}
#endif
