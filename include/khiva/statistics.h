// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>

namespace khiva
{

namespace statistics
{
/**
 * @brief Returns the covariance matrix of the time series contained in tss.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param unbiased Determines whether it divides by n - 1 (if false) or n (if true).
 *
 * @return af::array The covariance matrix of the time series.
 */
af::array covariance(af::array tss, bool unbiased = true);

/**
 * @brief Returns the kurtosis of tss (calculated with the adjusted Fisher-Pearson standardized moment coefficient G2).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array The kurtosis of tss.
 */
af::array kurtosis(af::array tss);

/**
 * @brief Returns the kth moment of the given time series.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param k The specific moment to be calculated.
 *
 * @return af::array The kth moment of the given time series.
 */
af::array moment(af::array tss, int k);

/**
 * @brief The Ljung–Box test checks that data within the time series are independently distributed (i.e. the
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
 *
 * @return af::array Ljung-Box statistic test.
 */
af::array ljungBox(af::array tss, long lags);

/**
 * @brief Returns values at the given quantile.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series. NOTE: the time series should be sorted.
 * @param q Percentile(s) at which to extract score(s). One or many.
 * @param precision Number of decimals expected.
 *
 * @return af::array Values at the given quantile.
 */
af::array quantile(af::array tss, af::array q, float precision = 100000000);

/**
 * @brief Discretizes the time series into equal-sized buckets based on sample quantiles.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series. NOTE: the time series should be sorted.
 * @param quantiles Number of quantiles to extract. From 0 to 1, step 1/quantiles.
 * @param precision Number of decimals expected.
 *
 * @return af::array Matrix with the categories, one category per row, the start of the category in the first column and
 * the end in the second category.
 */
af::array quantilesCut(af::array tss, float quantiles, float precision = 0.00000001);

/**
 * @brief Estimates standard deviation based on a sample. The standard deviation is calculated using the "n-1" method.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array The sample standard deviation.
 */
af::array sampleStdev(af::array tss);

/**
 * @brief Calculates the sample skewness of tss (calculated with the adjusted Fisher-Pearson standardized moment
 * coefficient G1).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array Array containing the skewness of each time series in tss.
 */
af::array skewness(af::array tss);

} // namespace statistics
} // namespace khiva
