// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa_c/defines.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Returns the covariance matrix of the time series contained in tss.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param unbiased Determines whether it divides by n - 1 (if false) or n (if true).
 * @param result The covariance matrix of the time series.
 */
TSAAPI void covariance_statistics(tsa_array *tss, bool *unbiased, tsa_array *result);

/**
 * @brief Returns the kth moment of the given time series.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param k The specific moment to be calculated.
 * @param result The kth moment of the given time series.
 */
TSAAPI void moment_statistics(tsa_array *tss, int *k, tsa_array *result);

/**
 * @brief Estimates standard deviation based on a sample. The standard deviation is calculated using the "n-1" method.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param result The sample standard deviation.
 */
TSAAPI void sample_stdev_statistics(tsa_array *tss, tsa_array *result);

/**
 * @brief Returns the kurtosis of tss (calculated with the adjusted Fisher-Pearson standardized moment coefficient G2).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param result The kurtosis of tss.
 */
TSAAPI void kurtosis_statistics(tsa_array *tss, tsa_array *result);

/**
 * @brief Calculates the sample skewness of tss (calculated with the adjusted Fisher-Pearson standardized moment
 * coefficient G1).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param result Array containing the skewness of each time series in tss.
 */
TSAAPI void skewness_statistics(tsa_array *tss, tsa_array *result);

/**
 * @brief Returns values at the given quantile.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series. NOTE: the time series should be sorted.
 * @param q Percentile(s) at which to extract score(s). One or many.
 * @param precision Number of decimals expected.
 * @param result Values at the given quantile.
 */
TSAAPI void quantile_statistics(tsa_array *tss, tsa_array *q, float *precision, tsa_array *result);

/**
 * @brief Discretizes the time series into equal-sized buckets based on sample quantiles.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series. NOTE: the time series should be sorted.
 * @param quantiles Number of quantiles to extract. From 0 to 1, step 1/quantiles.
 * @param precision Number of decimals expected.
 * @param result Matrix with the categories, one category per row, the start of the category in the first column and
 * the end in the second category.
 */
TSAAPI void quantiles_cut_statistics(tsa_array *tss, float *quantiles, float *precision, tsa_array *result);

#ifdef __cplusplus
}
#endif