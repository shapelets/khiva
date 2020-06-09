// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_BINDINGJAVA_NORMALIZATION_H
#define KHIVA_BINDINGJAVA_NORMALIZATION_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Normalizes the given time series according to its maximum value and adjusts each value within the range
 * (-1, 1).
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return A reference to an array with the same dimensions as ref, whose values (time series in dimension 0) have
 * been normalized by dividing each number by 10^j, where j is the number of integer digits of the max number in the
 * time series.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Normalization_decimalScalingNorm(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Same as Java_io_shapelets_khiva_Normalization_decimalScalingNorm, but it performs the operation in place,
 * without allocating further memory.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 */
JNIEXPORT void JNICALL Java_io_shapelets_khiva_Normalization_decimalScalingNormInPlace(JNIEnv *, jobject, jlong ref);

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
 *
 * @return A reference to an array with the same dimensions as ref, whose values (time series in dimension 0) have
 * been normalized by maximum and minimum values, and scaled as per high and low parameters.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Normalization_maxMinNorm(JNIEnv *env, jobject, jlong ref, jdouble high,
                                                                         jdouble low, jdouble epsilon);

/**
 * @brief Same as Java_io_shapelets_khiva_Normalization_maxMinNorm, but it performs the operation in place, without
 * allocating further memory.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param high Maximum final value (Defaults to 1.0).
 * @param low  Minimum final value (Defaults to 0.0).
 * @param epsilon Safeguard for constant (or near constant) time series as the operation implies a unit scale operation
 * between min and max values in the ref.
 */
JNIEXPORT void JNICALL Java_io_shapelets_khiva_Normalization_maxMinNormInPlace(JNIEnv *, jobject, jlong ref,
                                                                               jdouble high, jdouble low,
                                                                               jdouble epsilon);

/**
 * @brief Normalizes the given time series according to its maximum-minimum value and its mean. It follows the following
 * formulae:
 * \f[
 * \acute{x} = \frac{x - mean(x)}{max(x) - min(x)}.
 * \f]
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return A reference to an array with the same dimensions as tss, whose values (time series in dimension 0) have
 * been normalized by substracting the mean from each number and dividing each number by \f$ max(x) - min(x)\f$, in the
 * time series.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Normalization_meanNorm(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Normalizes the given time series according to its maximum-minimum value and its mean. It follows the following
 * formulae:
 * \f[
 * \acute{x} = \frac{x - mean(x)}{max(x) - min(x)}.
 * \f]
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 */
JNIEXPORT void JNICALL Java_io_shapelets_khiva_Normalization_meanNormInPlace(JNIEnv *, jobject, jlong ref);

/**
 * @brief Calculates a new set of time series with zero mean and standard deviation one.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param epsilon Minimum standard deviation to consider. It acts a a gatekeeper for those time series that may be
 * constant or near constant.
 *
 * @return A reference to an array with the same dimensions as ref where the time series have been
 * adjusted for zero mean and one as standard deviation.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Normalization_znorm(JNIEnv *env, jobject, jlong ref, jdouble epsilon);

/**
 * @brief Adjusts the time series in the given input and performs z-norm
 * inplace (without allocating further memory).
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param epsilon Minimum standard deviation to consider. It acts as a gatekeeper for those time series that may be
 * constant or near constant.
 */
JNIEXPORT void JNICALL Java_io_shapelets_khiva_Normalization_znormInPlace(JNIEnv *, jobject, jlong ref,
                                                                          jdouble epsilon);

#ifdef __cplusplus
}
#endif

#endif
