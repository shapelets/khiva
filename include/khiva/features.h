// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_CORE_FEATURES_H
#define KHIVA_CORE_FEATURES_H

#include <khiva/defines.h>

#include <arrayfire.h>

namespace khiva {

namespace features {
/**
 * @brief Calculates the absolute energy of the time series which is the sum over the squared values.
 * \f[
 *      E = \sum_{i=1,\ldots, n} x_i^2
 * \f]
 *
 * @param base Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 *
 * @return af::array An array with the same dimensions as tss, whose values (time series in dimension 0)
 * contains the sum of the squares values in the time series.
 */
KHIVAAPI af::array absEnergy(af::array base);

/**
 * @brief Calculates the sum over the absolute value of consecutive changes in the time series.
 * \f[
 *       \sum_{i=1, \ldots, n-1} \mid x_{i+1}- x_i \mid
 * \f]
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 *
 * @return af::array An array with the same dimensions as tss, whose values (time series in dimension 0) contains
 * absolute value of consecutive changes in the time series.
 */
KHIVAAPI af::array absoluteSumOfChanges(af::array tss);

/**
 * @brief Calculates the value of an aggregation function f_agg (e.g. var or mean) of the autocorrelation
 * (Compare to http://en.wikipedia.org/wiki/Autocorrelation#Estimation), taken over different all possible
 * lags (1 to length of x).
 * \f[
 * \frac{1}{n-1} \sum_{l=1,\ldots, n} \frac{1}{(n-l)\sigma^{2}} \sum_{t=1}^{n-l}(X_{t}-\mu )(X_{t+l}-\mu),
 * \f]
 *  where \f$n\f$ is the length of the time series \f$X_i\f$, \f$\sigma^2\f$ its variance and \f$\mu\f$ its mean.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @param aggregationFunction The function to summarise all autocorrelation with different lags.
 *
 * @return af::array An array with the same dimensions as tss, whose values (time series in dimension 0)
 * contains the aggregated correlation for each time series.
 */
KHIVAAPI af::array aggregatedAutocorrelation(af::array tss,
                                    af::array (*aggregationFunction)(const af::array &, const bool, const dim_t));

/**
 * @brief Calculates the value of an aggregation function f_agg (e.g. var or mean) of the autocorrelation
 * (Compare to http://en.wikipedia.org/wiki/Autocorrelation#Estimation), taken over different all possible
 * lags (1 to length of x).
 * \f[
 * \frac{1}{n-1} \sum_{l=1,\ldots, n} \frac{1}{(n-l)\sigma^{2}} \sum_{t=1}^{n-l}(X_{t}-\mu )(X_{t+l}-\mu),
 * \f]
 *  where \f$n\f$ is the length of the time series \f$X_i\f$, \f$\sigma^2\f$ its variance and \f$\mu\f$ its mean.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @param aggregationFunction The function to summarise all autocorrelation with different lags.
 *
 * @return af::array An array with the same dimensions as tss, whose values (time series in dimension 0)
 * contains the aggregated correlation for each time series.
 */
KHIVAAPI af::array aggregatedAutocorrelation(af::array tss, af::array (*aggregationFunction)(const af::array &, const int));

/**
 * @brief Calculates the value of an aggregation function f_agg (e.g. var or mean) of the autocorrelation
 * (Compare to http://en.wikipedia.org/wiki/Autocorrelation#Estimation), taken over different all possible
 * lags (1 to length of x).
 * \f[
 * \frac{1}{n-1} \sum_{l=1,\ldots, n} \frac{1}{(n-l)\sigma^{2}} \sum_{t=1}^{n-l}(X_{t}-\mu )(X_{t+l}-\mu),
 * \f]
 *  where \f$n\f$ is the length of the time series \f$X_i\f$, \f$\sigma^2\f$ its variance and \f$\mu\f$ its mean.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @param aggregationFunction The function to summarise all autocorrelation with different lags.
 *
 * @return af::array An array with the same dimensions as tss, whose values (time series in dimension 0)
 * contains the aggregated correlation for each time series.
 */
KHIVAAPI af::array aggregatedAutocorrelation(af::array tss, af::array (*aggregationFunction)(const af::array &, const dim_t));

/**
 * @brief Calculates a linear least-squares regression for values of the time series that were aggregated over chunks
 * versus the sequence from 0 up to the number of chunks minus one.
 *
 * @param t The time series to calculate the features of.
 * @param chunkSize The chunkSize used to aggregate the data.
 * @param aggregationFunction Function to be used in the aggregation.
 * @param slope Slope of the regression line.
 * @param intercept Intercept of the regression line.
 * @param rvalue Correlation coefficient.
 * @param pvalue Two-sided p-value for a hypothesis test whose null hypothesis is that the slope is zero, using
 * Wald Test with t-distribution of the test statistic.
 * @param stderrest Standard error of the estimated gradient.
 */
KHIVAAPI void aggregatedLinearTrend(af::array t, long chunkSize, af::array (*aggregationFunction)(const af::array &, const int),
                           af::array &slope, af::array &intercept, af::array &rvalue, af::array &pvalue,
                           af::array &stderrest);

/**
 * @brief Calculates a linear least-squares regression for values of the time series that were aggregated over chunks
 * versus the sequence from 0 up to the number of chunks minus one.
 *
 * @param t The time series to calculate the features of.
 * @param chunkSize The chunkSize used to aggregate the data.
 * @param aggregationFunction Function to be used in the aggregation.
 * @param slope Slope of the regression line.
 * @param intercept Intercept of the regression line.
 * @param rvalue Correlation coefficient.
 * @param pvalue Two-sided p-value for a hypothesis test whose null hypothesis is that the slope is zero, using
 * Wald Test with t-distribution of the test statistic.
 * @param stderrest Standard error of the estimated gradient.
 */
KHIVAAPI void aggregatedLinearTrend(af::array t, long chunkSize,
                           af::array (*aggregationFunction)(const af::array &, const dim_t), af::array &slope,
                           af::array &intercept, af::array &rvalue, af::array &pvalue, af::array &stderrest);

/**
 * @brief Calculates a vectorized Approximate entropy algorithm (https://en.wikipedia.org/wiki/Approximate_entropy).
 * For short time series, this method is highly dependent on the parameters, but should be stable for N > 2000,
 * see:
 *
 * [1] Yentes et al., The Appropriate Use of Approximate Entropy and Sample Entropy with Short Data Sets, (2012).
 * Other shortcomings and alternatives discussed in:
 * Richman & Moorman, Physiological time-series analysis using approximate entropy and sample entropy, (2000).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @param m Length of compared run of data.
 * @param r Filtering level, must be positive.
 *
 * @return af::array An array with the same dimensions as tss, whose values (time series in dimension 0) contains
 * the vectorized Approximate entropy for all the input time series in tss.
 */
KHIVAAPI af::array approximateEntropy(af::array tss, int m, float r);

/**
 * @brief Calculates the autocorrelation of the specified lag for the given time series, according to the formula [1].
 * \f[
 * \frac{1}{(n-l)\sigma^{2}} \sum_{t=1}^{n-l}(X_{t}-\mu )(X_{t+l}-\mu),
 * \f]
 * where \f$n\f$ is the length of the time series \f$X_i\f$, \f$\sigma^2\f$ its variance and \f$\mu\f$ its mean, \f$l\f$
 * denotes the lag.
 *
 * [1] https://en.wikipedia.org/wiki/Autocorrelation#Estimation
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param maxLag The maximum lag to compute.
 * @param unbiased Determines whether it divides by (n - lag) (if true), or n (if false).
 *
 * @return af::array The autocorrelation value for the given time series.
 */
KHIVAAPI af::array autoCorrelation(af::array tss, long maxLag, bool unbiased = false);

/**
 * @brief Calculates the auto-covariance the given time series.
 *
 * @param xss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param unbiased Determines whether it divides by n - lag (if true) or n (if false).
 *
 * @return af::array The auto-covariance value for the given time series.
 */
KHIVAAPI af::array autoCovariance(af::array xss, bool unbiased = false);

/**
 * @brief Calculates the binned entropy for the given time series and number of bins. It calculates the value of:
 * \f[
 * \sum_{k=0}^{min(max\_bins, len(x))} p_k log(p_k) \cdot \mathbf{1}_{(p_k > 0)},
 * \f]
 * where \f$p_k\f$ is the percentage of samples in bin \f$k\f$.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param max_bins The number of bins.
 *
 * @return af::array The binned entropy value for the given time series.
 */
KHIVAAPI af::array binnedEntropy(af::array tss, int max_bins);

/**
 * @brief This function calculates the value of:
 * \f[
 *  \frac{1}{n-2lag} \sum_{i=0}^{n-2lag} x_{i + 2 \cdot lag}^2 \cdot x_{i + lag} \cdot x_{i},
 * \f]
 * which is:
 * \f[
 * \mathbb{E}[L^2(X)^2 \cdot L(X) \cdot X],
 * \f]
 * where \f$\mathbb{E}\f$ is the mean and \f$L\f$ is the lag operator. It was proposed in [1] as a measure of
 * non linearity in the time series.
 *
 * [1] Schreiber, T. and Schmitz, A., Discrimination power of measures for nonlinearity in a time series,
 * PHYSICAL REVIEW E, VOLUME 55, NUMBER 5, (1997).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param lag The lag.
 *
 * @return af::array The non-linearity value for the given time series.
 */
KHIVAAPI af::array c3(af::array tss, long lag);

/**
 * @brief This function calculator is an estimate for a time series complexity [1] (A more complex time series has more
 * peaks, valleys etc.). It calculates the value of:
 * \f[
 *  \sqrt{ \sum_{i=0}^{n-2lag} ( x_{i} - x_{i+1})^2 }.
 * \f]
 *
 * [1] Batista, Gustavo EAPA, et al (2014). CID: an efficient complexity-invariant distance for time series.
 * Data Mining and Knowledge Difscovery 28.3 (2014): 634-669.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param zNormalize Controls whether the time series should be z-normalized or not.
 *
 * @return af::array The complexity value for the given time series.
 */
KHIVAAPI af::array cidCe(af::array tss, bool zNormalize = false);

/**
 * @brief Calculates the number of values in the time series that are higher than the mean.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array The number of values in the time series that are higher than the mean.
 */
KHIVAAPI af::array countAboveMean(af::array tss);

/**
 * @brief Calculates the number of values in the time series that are lower than the mean.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array The number of values in the time series that are lower than the mean.
 */
KHIVAAPI af::array countBelowMean(af::array tss);

/**
 * @brief Calculates the cross-covariance of the given time series.
 *
 * @param xss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param yss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param unbiased Determines whether it divides by n - lag (if true) or n (if false).
 *
 * @return af::array The cross-covariance value for the given time series.
 */
KHIVAAPI af::array crossCovariance(af::array xss, af::array yss, bool unbiased = true);

/**
 * @brief Calculates the cross-correlation of the given time series.
 *
 * @param xss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param yss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param unbiased Determines whether it divides by n - lag (if true) or n (if false).
 *
 * @return af::array The cross-correlation value for the given time series.
 */
KHIVAAPI af::array crossCorrelation(af::array xss, af::array yss, bool unbiased = true);

/** @brief Calculates a Continuous wavelet transform for the Ricker wavelet, also known as the "Mexican hat wavelet"
 * which is defined by:
 *  \f[
 *  \frac{2}{\sqrt{3a} \pi^{
 *      \frac{1} { 4 }}} (1 - \frac{x^2}{a^2}) exp(-\frac{x^2}{2a^2}),
 *  \f]
 *  where \f$a\f$ is the width parameter of the wavelet function.
 * This feature calculator takes three different parameter: widths, coeff and w. The feature calculator takes all
 * the different widths arrays and then calculates the cwt one time for each different width array. Then the values
 * for the different coefficient for coeff and width w are returned.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same)
 * and dimension one indicates the number of time series.
 * @param widths Array that contains all different widths.
 * @param coeff Coefficient of interest.
 * @param w Width of interest.
 *
 * @return af::array Result of calculated coefficients.
 */
KHIVAAPI af::array cwtCoefficients(af::array tss, af::array widths, int coeff, int w);

/**
 * @brief Calculates the sum of squares of chunk i out of N chunks expressed as a ratio with the sum of squares over
 * the whole series. segmentFocus should be lower than the number of segments.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param numSegments The number of segments to divide the series into.
 * @param segmentFocus The segment number (starting at zero) to return a feature on.
 *
 * @return af::array The energy ratio by chunk of the time series.
 */
KHIVAAPI af::array energyRatioByChunks(af::array tss, long numSegments, long segmentFocus);

/**
 * @brief Calculates the spectral centroid (mean), variance, skew, and kurtosis of the absolute fourier transform
 * spectrum.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array The spectral centroid (mean), variance, skew, and kurtosis of the absolute fourier transform
 * spectrum.
 */
KHIVAAPI af::array fftAggregated(af::array tss);

/**
 * @brief Calculates the fourier coefficients of the one-dimensional discrete Fourier Transform for real input by using
 * fast fourier transformation algorithm,
 * \f[
 * A_k = \sum_{m=0}^{n-1} a_m \exp \left \{ -2 \pi i \frac{m k}{n} \right \},
 * \qquad k = 0, \ldots , n-1.
 * \f]
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param coefficient The coefficient to extract from the FFT.
 * @param real The real part of the coefficient.
 * @param imag The imaginary part of the coefficient.
 * @param abs The absolute value of the coefficient.
 * @param angle The angle of the coefficient.
 */
KHIVAAPI void fftCoefficient(af::array tss, long coefficient, af::array &real, af::array &imag, af::array &abs,
                    af::array &angle);

/**
 * @brief Calculates the first relative location of the maximal value for each time series.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array The first relative location of the maximum value to the length of the time series, for each
 * time series.
 */
KHIVAAPI af::array firstLocationOfMaximum(af::array tss);

/**
 * @brief Calculates the first location of the minimal value of each time series. The position is calculated relatively
 * to the length of the series.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array the first relative location of the minimal value of each time series.
 */
KHIVAAPI af::array firstLocationOfMinimum(af::array tss);

/**
 * @brief Coefficients of polynomial \f$h(x)\f$, which has been fitted to the deterministic dynamics of Langevin model:
 * \f[
 *    \dot(x)(t) = h(x(t)) + R \mathcal(N)(0,1)
 * \f]
 * as described by [1]. For short time series this method is highly dependent on the parameters.
 *
 * [1] Friedrich et al., Physics Letters A 271, p. 217-222, Extracting model equations from experimental data, (2000).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param m Order of polynom to fit for estimating fixed points of dynamics.
 * @param r Number of quantiles to use for averaging.
 *
 * @return af::array The coefficients for each time series.
 */
KHIVAAPI af::array friedrichCoefficients(af::array tss, int m, float r);

/**
 * @brief Computes if the input time series contain duplicated elements.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array Array containing True if the time series contains duplicated elements and false otherwise.
 */
KHIVAAPI af::array hasDuplicates(af::array tss);

/**
 * @brief Computes if the maximum within time series is duplicated.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array Array containing True if the maximum value of the time series is duplicated and false otherwise.
 */
KHIVAAPI af::array hasDuplicateMax(af::array tss);

/**
 * @brief Computes if the minimum of input time series is duplicated.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array Array containing True if the minimum of the time series is duplicated and false otherwise.
 */
KHIVAAPI af::array hasDuplicateMin(af::array tss);

/**
 * @brief Calculates the relative index \f$i\f$ where \f$q\%\f$ of the mass of the time series within tss lie at the
 * left of \f$i\f$. For example for \f$q = 50\%\f$ this feature calculator will return the mass center of the time
 * series.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @param q The quantile limit.
 *
 * @return af::array The relative indices i where q% of the mass of the time series lie at the left of i.
 */
KHIVAAPI af::array indexMassQuantile(af::array tss, float q);

/**
 * @brief Returns the kurtosis of tss (calculated with the adjusted Fisher-Pearson standardized moment coefficient G2).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array The kurtosis of tss.
 */
KHIVAAPI af::array kurtosis(af::array tss);

/**
 * @brief Checks if the time series within tss have a large standard deviation.
 * \f[
 *  std(x) > r * (max(X)-min(X)).
 * \f]
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param r The threshold value.
 *
 * @return af::array Array containing True for those time series in tss that have a large standard deviation.
 */
KHIVAAPI af::array largeStandardDeviation(af::array tss, float r);

/**
 * @brief Calculates the last location of the maximum value of each time series. The position is calculated relatively
 * to the length of the series.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array The last relative location of the maximum value of each time series.
 */
KHIVAAPI af::array lastLocationOfMaximum(af::array tss);

/**
 * @brief Calculates the last location of the minimum value of each time series. The position is calculated relatively
 * to the length of the series.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return af::array The last relative location of the minimum value of each series.
 */
KHIVAAPI af::array lastLocationOfMinimum(af::array tss);

/**
 * @brief Returns the length of the input time series.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array The length of tss.
 */
KHIVAAPI af::array length(af::array tss);

/**
 * @brief Calculate a linear least-squares regression for the values of the time series versus the sequence from 0
 * to length of the time series minus one.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param pvalue The p-values for all time series.
 * @param rvalue The r-values for all time series.
 * @param intercept The intercept values for all time series.
 * @param slope The slope for all time series.
 * @param stder The stderr values for all time series.
 */
KHIVAAPI void linearTrend(af::array tss, af::array &pvalue, af::array &rvalue, af::array &intercept, af::array &slope,
                 af::array &stder);

/**
 * @brief Calculates all Local Maximals for the time series in tss.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array The calculated local maximals for each time series in tss.
 */
KHIVAAPI af::array localMaximals(af::array tss);

/**
 * @brief Calculates the length of the longest consecutive subsequence in tss that is bigger than the mean of tss.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 *
 * @return af::array the length of the longest consecutive subsequence in the input time series that is bigger than
 * the mean.
 */
KHIVAAPI af::array longestStrikeAboveMean(af::array tss);

/**
 * @brief Calculates the length of the longest consecutive subsequence in tss that is below the mean of tss.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array The length of the longest consecutive subsequence in the input time series that is below the mean.
 */
KHIVAAPI af::array longestStrikeBelowMean(af::array tss);

/**
 * @brief Largest fixed point of dynamics \f$\max_x {h(x)=0}\f$ estimated from polynomial
 * \f$h(x)\f$, which has been fitted to the deterministic dynamics of Langevin model:
 * \f[
 *    \dot{x}(t) = h(x(t)) + R \mathcal(N)(0,1)
 * \f]
 *
 * [1] Friedrich et al., Extracting model equations from experimental data, Physics Letters A 271, p. 217-222, (2000).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series. NOTE: the time series should be sorted.
 * @param m Order of polynom to fit for estimating fixed points of dynamics.
 * @param r Number of quantiles to use for averaging.
 *
 * @return af::array Largest fixed point of deterministic dynamics.
 */
KHIVAAPI af::array maxLangevinFixedPoint(af::array tss, int m, float r);

/**
 * @brief Calculates the maximum value for each time series within tss.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 *
 * @return af::array The maximum value of each time series within tss.
 */
KHIVAAPI af::array maximum(af::array tss);

/**
 * @brief Calculates the mean value for each time series within tss.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 *
 * @return af::array The mean value of each time series within tss.
 */
KHIVAAPI af::array mean(af::array tss);

/**
 * @brief Calculates the mean over the absolute differences between subsequent time series values in tss.
 * \f[
 * \frac{1}{n} \sum_{i=1,\ldots, n-1} | x_{i+1} - x_{i}|.
 * \f]
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array The mean over the absolute differences between subsequent time series values.
 */
KHIVAAPI af::array meanAbsoluteChange(af::array tss);

/**
 * @brief Calculates the mean over the differences between subsequent time series values in tss.
 * \f[
 * \frac{1}{n} \sum_{i=1,\ldots, n-1}  x_{i+1} - x_{i}.
 * \f]
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array The mean over the differences between subsequent time series values.
 */
KHIVAAPI af::array meanChange(af::array tss);

/**
 * @brief Calculates mean value of a central approximation of the second derivative for each time series in tss.
 * \f[
 * \frac{1}{n} \sum_{i=1,\ldots, n-1}  \frac{1}{2} (x_{i+2} - 2 \cdot x_{i+1} + x_i).
 * \f]
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array The mean value of a central approximation of the second derivative for each time series.
 */
KHIVAAPI af::array meanSecondDerivativeCentral(af::array tss);

/**
 * @brief Calculates the median value for each time series within tss.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array The median value of each time series within tss.
 */
KHIVAAPI af::array median(af::array tss);

/**
 * @brief Calculates the minimum value for each time series within tss.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array The minimum value of each time series within tss.
 */
KHIVAAPI af::array minimum(af::array tss);

/**
 * @brief Calculates the number of m-crossings. A m-crossing is defined as two sequential values where the first value
 * is lower than m and the next is greater, or viceversa. If you set m to zero, you will get the number of zero
 * crossings.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param m The m value.
 *
 * @return af::array The number of m-crossings of each time series within tss.
 */
KHIVAAPI af::array numberCrossingM(af::array tss, int m);

/**
 * @brief This feature calculator searches for different peaks. To do so, the time series is smoothed by a ricker
 * wavelet and for widths ranging from 1 to maxW. This feature calculator returns the number of peaks that occur at
 * enough width scales and with sufficiently high Signal-to-Noise-Ratio (SNR).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param maxW The maximum width to consider.
 *
 * @return af::array The number of peaks for each time series.
 */
KHIVAAPI af::array numberCwtPeaks(af::array tss, int maxW);

/**
 * @brief Calculates the number of peaks of at least support \f$n\f$ in the time series \f$tss\f$. A peak of support
 * \f$n\f$ is defined as a subsequence of \f$tss\f$ where a value occurs, which is bigger than its \f$n\f$ neighbourgs
 * to the left and to the right.
 *
 * [1] Bioinformatics (2006) 22 (17): 2059-2065. doi: 10.1093/bioinformatics/btl355,
 * http://bioinformatics.oxfordjournals.org/content/22/17/2059.long
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param n The support of the peak.
 *
 * @return af::array The number of peaks of at least support \f$n\f$.
 */
KHIVAAPI af::array numberPeaks(af::array tss, int n);

/**
 * @brief Calculates the value of the partial autocorrelation function at the given lag. The lag \f$k\f$ partial
 * autocorrelation of a time series \f$\lbrace x_t, t = 1 \ldots T \rbrace\f$ equals the partial correlation of
 * \f$x_t\f$ and \f$x_{t-k}\f$, adjusted for the intermediate variables \f$\lbrace x_{t-1}, \ldots, x_{t-k+1}
 * \rbrace\f$ ([1]). Following [2], it can be defined as:
 * \f[
 *      \alpha_k = \frac{ Cov(x_t, x_{t-k} | x_{t-1}, \ldots, x_{t-k+1})}
 *      {\sqrt{ Var(x_t | x_{t-1}, \ldots, x_{t-k+1}) Var(x_{t-k} | x_{t-1}, \ldots, x_{t-k+1} )}}
 * \f]
 * with (a) \f$x_t = f(x_{t-1}, \ldots, x_{t-k+1})\f$ and (b) \f$ x_{t-k} = f(x_{t-1}, \ldots, x_{t-k+1})\f$
 * being AR(k-1) models that can be fitted by OLS. Be aware that in (a), the regression is done on past values to
 * predict \f$ x_t \f$ whereas in (b), future values are used to calculate the past value \f$x_{t-k}\f$.
 * It is said in [1] that, for an AR(p), the partial autocorrelations \f$ \alpha_k \f$ will be nonzero for
 * \f$ k<=p \f$ and zero for \f$ k>p \f$. With this property, it is used to determine the lag of an AR-Process.
 *
 * [1] Box, G. E., Jenkins, G. M., Reinsel, G. C., & Ljung, G. M. (2015). Time series analysis: forecasting and control.
 * John Wiley & Sons.
 *
 * [2] https://onlinecourses.science.psu.edu/stat510/node/62
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param lags Indicates the lags to be calculated.
 *
 * @return af::array The partial autocorrelation for each time series for the given lag.
 */
KHIVAAPI af::array partialAutocorrelation(af::array tss, af::array lags);

/**
 * @brief Calculates the percentage of unique values, that are present in the time series more than once.
 * \f[
 *      \frac{len(\textit{different values occurring more than once})}{len(\textit{different values})}
 * \f]
 * This means the percentage is normalized to the number of unique values, in contrast to the
 * percentageOfReoccurringValuesToAllValues.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param isSorted Indicates if the input time series is sorted or not. Defaults to false.
 *
 * @return af::array The percentage of unique data points, that are present in the time series more than once.
 */
KHIVAAPI af::array percentageOfReoccurringDatapointsToAllDatapoints(af::array tss, bool isSorted = false);

/**
 * @brief Calculates the percentage of unique values, that are present in the time series more than once.
 * \f[
 *      \frac{\textit{number of data points occurring more than once}}{\textit{number of all data points})}
 * \f]
 * This means the percentage is normalized to the number of unique values, in contrast to the
 * percentageOfReoccurringDatapointsToAllDatapoints.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param isSorted Indicates if the input time series is sorted or not. Defaults to false.
 *
 * @return af::array The percentage of unique values, that are present in the time series more than once.
 */
KHIVAAPI af::array percentageOfReoccurringValuesToAllValues(af::array tss, bool isSorted = false);

/**
 * @brief Returns values at the given quantile.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param q Percentile(s) at which to extract score(s). One or many.
 * @param precision Number of decimals expected.
 *
 * @return af::array Values at the given quantile.
 */
KHIVAAPI af::array quantile(af::array tss, af::array q, float precision = 100000000);

/**
 * @brief Counts observed values within the interval [min, max).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param min Value that sets the lower limit.
 * @param max Value that sets the upper limit.
 *
 * @return af::array Values at the given range.
 */
KHIVAAPI af::array rangeCount(af::array tss, float min, float max);

/**
 * @brief Calculates the ratio of values that are more than \f$r*std(x)\f$ (so \f$r\f$ sigma) away from the mean of
 * \f$x\f$.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param r Number of times that the values should be away from.
 *
 * @return af::array The ratio of values that are more than \f$r*std(x)\f$ (so \f$r\f$ sigma) away from the mean of
 * \f$x\f$.
 */
KHIVAAPI af::array ratioBeyondRSigma(af::array tss, float r);

/**
 * @brief Calculates a factor which is 1 if all values in the time series occur only once, and below one if this is
 * not the case. In principle, it just returns:
 * \f[
 *      \frac{\textit{number\_unique\_values}}{\textit{number\_values}}
 * \f]
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array The ratio of unique values with respect to the total number of values.
 */
KHIVAAPI af::array ratioValueNumberToTimeSeriesLength(af::array tss);

/**
 * @brief Calculates a vectorized sample entropy algorithm. For short time-series this method is highly dependent on the
 * parameters, but should be stable for N > 2000, see:
 *
 * [1] Yentes et al., The Appropriate Use of Approximate Entropy and Sample Entropy with Short Data Sets, (2012).
 *
 * [2] Richman & Moorman,Physiological time-series analysis using approximate entropy and sample entropy, (2000).
 *
 * [3] https://en.wikipedia.org/wiki/Sample_entropy
 *
 * [4] https://www.ncbi.nlm.nih.gov/pubmed/10843903?dopt=Abstract
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array With the same dimensions as tss, whose values (time series in dimension 0) contains the
 * vectorized sample entropy for all the input time series in tss.
 */
KHIVAAPI af::array sampleEntropy(af::array tss);

/**
 * @brief Calculates the sample skewness of tss (calculated with the adjusted Fisher-Pearson standardized moment
 * coefficient G1).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array Containing the skewness of each time series in tss.
 */
KHIVAAPI af::array skewness(af::array tss);

/**
 * @brief Estimates the cross power spectral density of the time series tss at different frequencies. To do so, the
 * time series is first shifted from the time domain to the frequency domain. Welch's method computes an estimate of the
 * power spectral density by dividing the data into overlapping segments, computing a modified periodogram for each
 * segment and averaging the periodograms.
 *
 * [1] P. Welch, "The use of the fast Fourier transform for the estimation of power spectra: A method based on time
 * averaging over short, modified periodograms", IEEE Trans. Audio Electroacoust. vol. 15, pp. 70-73, 1967.
 *
 * [2] M.S. Bartlett, "Periodogram Analysis and Continuous Spectra", Biometrika, vol. 37, pp. 1-16, 1950.
 *
 * [3] Rabiner, Lawrence R., and B. Gold. "Theory and Application of Digital Signal Processing" Prentice-Hall, pp.
 * 414-419, 1975.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param coeff The coefficient to be returned.
 *
 * @return af::array Containing the power spectrum of the different frequencies for each time series in tss.
 */
KHIVAAPI af::array spktWelchDensity(af::array tss, int coeff);

/**
 * @brief Calculates the standard deviation of each time series within tss.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array The standard deviation of each time series within tss.
 */
KHIVAAPI af::array standardDeviation(af::array tss);

/**
 * @brief Calculates the sum of all data points, that are present in the time series more than once.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param isSorted Indicates if the input time series is sorted or not. Defaults to false.
 *
 * @return af::array The sum of all data points, that are present in the time series more than once.
 */
KHIVAAPI af::array sumOfReoccurringDatapoints(af::array tss, bool isSorted = false);

/**
 * @brief Calculates the sum of all values, that are present in the time series more than once.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param isSorted Indicates if the input time series is sorted or not. Defaults to false.
 *
 * @return af::array Returns the sum of all values, that are present in the time series more than once.
 */
KHIVAAPI af::array sumOfReoccurringValues(af::array tss, bool isSorted = false);

/**
 * @brief Calculates the sum over the time series tss.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array An array containing the sum of values in each time series.
 */
KHIVAAPI af::array sumValues(af::array tss);

/**
 * @brief Calculates if the distribution of tss *looks symmetric*. This is the case if
 * \f[
 *      | mean(tss)-median(tss)| < r * (max(tss)-min(tss)).
 * \f]
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param r The percentage of the range to compare with.
 *
 * @return af::array Denoting if the input time series look symmetric.
 */
KHIVAAPI af::array symmetryLooking(af::array tss, float r);

/**
 * @brief This function calculates the value of:
 * \f[
 *      \frac{1}{n-2lag} \sum_{i=0}^{n-2lag} x_{i + 2 \cdot lag}^2 \cdot x_{i + lag} - x_{i + lag} \cdot  x_{i}^2,
 * \f]
 * which is:
 * \f[
 *       \mathbb{E}[L^2(X)^2 \cdot L(X) - L(X) \cdot X^2],
 * \f]
 * where \f$ \mathbb{E} \f$ is the mean and \f$ L \f$ is the lag operator. It was proposed in [1] as a promising feature
 * to extract from time series.
 *
 * [1] Fulcher, B.D., Jones, N.S. (2014). Highly comparative feature-based time-series classification.
 * Knowledge and Data Engineering, IEEE Transactions on 26, 3026–3037.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param lag The lag to be computed.
 *
 * @return af::array Containing the time reversal asymmetry statistic value in each time series.
 */
KHIVAAPI af::array timeReversalAsymmetryStatistic(af::array tss, int lag);

/**
 * @brief Counts occurrences of value in the time series tss.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param v The value to be counted.
 *
 * @return af::array Containing the count of the given value in each time series.
 */
KHIVAAPI af::array valueCount(af::array tss, float v);

/**
 * @brief Computes the variance for the time series tss.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array An array containing the variance in each time series.
 */
KHIVAAPI af::array variance(af::array tss);

/**
 * @brief Calculates if the variance of tss is greater than the standard deviation. In other words, if the variance of
 * tss is larger than 1.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return af::array Denoting if the variance of tss is greater than the standard deviation.
 */
KHIVAAPI af::array varianceLargerThanStandardDeviation(af::array tss);

}  // namespace features
}  // namespace khiva

#endif
