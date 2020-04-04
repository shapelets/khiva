// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_BINDINGC_NORMALIZATION_H
#define KHIVA_BINDINGC_NORMALIZATION_H

#include <khiva_c/defines.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Normalizes the given time series according to its maximum value and adjusts each value within the range
 * (-1, 1).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param result An array with the same dimensions as tss, whose values (time series in dimension 0) have been
 * normalized by dividing each number by 10^j, where j is the number of integer digits of the max number in the time
 * series.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void decimal_scaling_norm(khiva_array *tss, khiva_array *result, int *error_code, char *error_message);

/**
 * @brief Same as decimal_scaling_norm, but it performs the operation in place, without allocating further memory.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void decimal_scaling_norm_in_place(khiva_array *tss, int *error_code, char *error_message);

/**
 * @brief Normalizes the given time series according to its minimum and maximum value and adjusts each value within the
 * range [low, high].
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param high Maximum final value (Defaults to 1.0).
 * @param low  Minimum final value (Defaults to 0.0).
 * @param epsilon Safeguard for constant (or near constant) time series as the operation implies a unit scale operation
 * between min and max values in the tss.
 * @param result Array with the same dimensions as tss, whose values (time series in dimension 0) have been
 * normalized by maximum and minimum values, and scaled as per high and low parameters.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void max_min_norm(khiva_array *tss, const double *high, const double *low, const double *epsilon, khiva_array *result,
                              int *error_code, char *error_message);

/**
 * @brief Same as max_min_norm, but it performs the operation in place, without allocating further memory.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param high Maximum final value (Defaults to 1.0).
 * @param low  Minimum final value (Defaults to 0.0).
 * @param epsilon Safeguard for constant (or near constant) time series as the operation implies a unit scale operation
 * between min and max values in the tss.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void max_min_norm_in_place(khiva_array *tss, const double *high, const double *low, const double *epsilon, int *error_code,
                                       char *error_message);

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
 * @param result An array with the same dimensions as tss, whose values (time series in dimension 0) have been
 * normalized by substracting the mean from each number and dividing each number by \f$ max(x) - min(x)\f$, in the
 * time series.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void mean_norm(khiva_array *tss, khiva_array *result, int *error_code, char *error_message);

/**
 * @brief Normalizes the given time series according to its maximum-minimum value and its mean. It follows the following
 * formulae:
 * \f[
 * \acute{x} = \frac{x - mean(x)}{max(x) - min(x)}.
 * \f]
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void mean_norm_in_place(khiva_array *tss, int *error_code, char *error_message);

/**
 * @brief Calculates a new set of times series with zero mean and standard deviation one.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_l Time series length (All time series need to have the same length).
 * @param tss_n Number of time series.
 * @param epsilon Minimum standard deviation to consider. It acts as a gatekeeper for
 * those time series that may be constant or near constant.
 * @param result Array with the same dimensions as tss where the time series have been
 * adjusted for zero mean and one as standard deviation.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void znorm(khiva_array *tss, const double *epsilon, khiva_array *result, int *error_code, char *error_message);

/**
 * @brief Adjusts the time series in the given input and performs z-norm
 * inplace (without allocating further memory).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @param epsilon Minimum standard deviation to consider. It acts as a gatekeeper for
 * those time series that may be constant or near constant.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void znorm_in_place(khiva_array *tss, const double *epsilon, int *error_code, char *error_message);

#ifdef __cplusplus
}
#endif

#endif
