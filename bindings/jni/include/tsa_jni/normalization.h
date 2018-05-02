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
 * @return The updated ref and an array with the same dimensions as ref where the time series have been
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

/**
 * @brief Normalizes the given time series according to its minimum and maximum value and adjusts each value within the
 * range [low, high].
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param high Maximum final value (Defaults to 1.0).
 * @param low  Minimum final value (Defaults to 0.0).
 * @param epsilon Safeguard for constant (or near constant) time series as the operation implies a unit scale operation
 * between min and max values in the ref.
 * @return The updated ref and an array with the same dimensions as ref, whose values (time series in dimension 0) have
 * been normalized by maximum and minimum values, and scaled as per high and low parameters.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Normalization_maxMinNorm(JNIEnv *env, jobject thisObj, jlong ref, jdouble high,
                                                               jdouble low, jdouble epsilon);

/**
 * @brief Same as Java_tsa_Normalization_maxMinNorm, but it performs the operation in place, without allocating further
 * memory.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param high Maximum final value (Defaults to 1.0).
 * @param low  Minimum final value (Defaults to 0.0).
 * @param epsilon Safeguard for constant (or near constant) time series as the operation implies a unit scale operation
 * between min and max values in the ref.
 * @return The updated ref.
 */
JNIEXPORT jlong JNICALL Java_tsa_Normalization_maxMinNormInPlace(JNIEnv *env, jobject thisObj, jlong ref, jdouble high,
                                                                 jdouble low, jdouble epsilon);

/**
 * @brief Normalizes the given time series according to its maximum value and adjusts each value within the range
 * (-1, 1).
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and an array with the same dimensions as ref, whose values (time series in dimension 0) have
 * been normalized by dividing each number by 10^j, where j is the number of integer digits of the max number in the
 * time series.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Normalization_decimalScalingNorm(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Same as Java_tsa_Normalization_decimalScalingNorm, but it performs the operation in place, without allocating
 * further memory.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref.
 */
JNIEXPORT jlong JNICALL Java_tsa_Normalization_decimalScalingNormInPlace(JNIEnv *env, jobject thisObj, jlong ref);

#ifdef __cplusplus
}
#endif
