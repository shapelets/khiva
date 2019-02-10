// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_BINDINGC_STATISTICS_H
#define KHIVA_BINDINGC_STATISTICS_H

#include <khiva_c/defines.h>

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
KHIVAAPI void covariance_statistics(khiva_array *tss, bool *unbiased, khiva_array *result);

/**
 * @brief Returns the kurtosis of tss (calculated with the adjusted Fisher-Pearson standardized moment coefficient G2).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param result The kurtosis of tss.
 */
KHIVAAPI void kurtosis_statistics(khiva_array *tss, khiva_array *result);

/**
 * @brief The Ljung–Box test checks that data whithin the time series are independently distributed (i.e. the
 * correlations in the population from which the sample is taken are 0, so that any observed correlations in the data
 * result from randomness of the sampling process). Data are no independently distributed, if they exhibit serial
 * correlation.
 *
 * The test statistic is:
 *
 * \f[
 * Q = n\left(n+2\right)\sum_{k=1}^h\frac{\hat{\rho}^2_k}{n-k}
 * \f]
 *
 * where ''n'' is the sample size, \f$\hat{\rho}k \f$ is the sample autocorrelation at lag ''k'', and ''h'' is the
 * number of lags being tested. Under \f$ H_0 \f$ the statistic Q follows a \f$\chi^2{(h)} \f$. For significance level
 * \f$\alpha\f$, the \f$critical region\f$ for rejection of the hypothesis of randomness is:
 *
 * \f[
 * Q > \chi_{1-\alpha,h}^2
 * \f]
 *
 * where \f$ \chi_{1-\alpha,h}^2 \f$ is the \f$\alpha\f$-quantile of the chi-squared distribution with ''h'' degrees of
 * freedom.
 *
 * [1] G. M. Ljung  G. E. P. Box (1978). On a measure of lack of fit in time series models.
 * Biometrika, Volume 65, Issue 2, 1 August 1978, Pages 297–303.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param lags Number of lags being tested.
 * @param The Ljung-Box statistic test.
 */
KHIVAAPI void ljung_box(khiva_array *tss, long *lags, khiva_array *result);

/**
 * @brief Returns the kth moment of the given time series.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param k The specific moment to be calculated.
 * @param result The kth moment of the given time series.
 */
KHIVAAPI void moment_statistics(khiva_array *tss, int *k, khiva_array *result);

/**
 * @brief Returns values at the given quantile.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series. NOTE: the time series should be sorted.
 * @param q Percentile(s) at which to extract score(s). One or many.
 * @param precision Number of decimals expected.
 * @param result Values at the given quantile.
 */
KHIVAAPI void quantile_statistics(khiva_array *tss, khiva_array *q, float *precision, khiva_array *result);

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
KHIVAAPI void quantiles_cut_statistics(khiva_array *tss, float *quantiles, float *precision, khiva_array *result);

/**
 * @brief Estimates standard deviation based on a sample. The standard deviation is calculated using the "n-1" method.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param result The sample standard deviation.
 */
KHIVAAPI void sample_stdev_statistics(khiva_array *tss, khiva_array *result);

/**
 * @brief Calculates the sample skewness of tss (calculated with the adjusted Fisher-Pearson standardized moment
 * coefficient G1).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param result Array containing the skewness of each time series in tss.
 */
KHIVAAPI void skewness_statistics(khiva_array *tss, khiva_array *result);

#ifdef __cplusplus
}
#endif

#endif
