// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>

using namespace af;

namespace tsa {

namespace features {

/**
 * @brief Calculates the sum over the square values of the timeseries
 *
 * @param base Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @return af::array An array with the same dimensions as tss, whose values (time series in dimension 0)
 * contains the sum of the suares values in the timeseries
 */
af::array absEnergy(af::array base);

/**
 * @brief Calculates the sum over the absolute value of consecutive changes in the time series
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @return af::array An array with the same dimensions as tss, whose values (time series in dimension 0)
 * contains absolute value of consecutive changes in the time series
 */
af::array absoluteSumOfChanges(af::array tss);

/**
 * @brief Calculates the value of an aggregation function f_agg (e.g. var or mean) of the autocorrelation
 * (Compare to http://en.wikipedia.org/wiki/Autocorrelation#Estimation), taken over different all possible
 * lags (1 to length of x).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of time series.
 *
 * @param aggregationFunction The function to summarise all autocorrelation with deffierent lags.
 *
 * @return af::array An array with the same dimensions as tss, whose values (time series in dimension 0)
 * contains the aggregated correaltion for each time series.
 */
af::array aggregatedAutocorrelation(af::array tss,
                                    af::array (*aggregationFunction)(const af::array &, const bool, const dim_t));

/**
 * @brief Calculates the value of an aggregation function f_agg (e.g. var or mean) of the autocorrelation
 * (Compare to http://en.wikipedia.org/wiki/Autocorrelation#Estimation), taken over different all possible
 * lags (1 to length of x).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same)
 * and dimension one indicates the number of time series.
 *
 * @param aggregationFunction The function to summarise all autocorrelation with deffierent lags.
 *
 * @return af::array An array with the same dimensions as tss, whose values (time series in dimension 0)
 * contains the aggregated correaltion for each time series.
 */
af::array aggregatedAutocorrelation(af::array tss, af::array (*aggregationFunction)(const af::array &, const int));

/**
 * @brief Calculates the value of an aggregation function f_agg (e.g. var or mean) of the autocorrelation
 * (Compare to http://en.wikipedia.org/wiki/Autocorrelation#Estimation), taken over different all possible
 * lags (1 to length of x).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of time series.
 *
 * @param aggregationFunction The function to summarise all autocorrelation with deffierent lags.
 *
 * @return af::array An array with the same dimensions as tss, whose values (time series in dimension 0)
 * contains the aggregated correaltion for each time series.
 */
af::array aggregatedAutocorrelation(af::array tss, af::array (*aggregationFunction)(const af::array &, const dim_t));

/**
 * @brief Calculates a linear least-squares regression for values of the time series that were aggregated
 * over chunks versus the sequence from 0 up to the number of chunks minus one.
 *
 * @param t The time series to calculate the features of
 * @param chunkSize The chunkSize used to aggregate the data
 * @param aggregationFunction Function to be used in the aggregation
 * @param slope Slope of the regression line
 * @param intercept Intercept of the regression line
 * @param rvalue Correlation coefficient
 * @param pvalue Two-sided p-value for a hypothesis test whose null hypothesis is
 * that the slope is zero, using Wald Test with t-distribution of
 * the test statistic
 * @param stderrest Standard error of the estimated gradient
 */
void aggregatedLinearTrend(af::array t, long chunkSize, af::array (*aggregationFunction)(const af::array &, const int),
                           af::array &slope, af::array &intercept, af::array &rvalue, af::array &pvalue,
                           af::array &stderrest);

/**
 * @brief Calculates a linear least-squares regression for values of the time series that were aggregated
 * over chunks versus the sequence from 0 up to the number of chunks minus one
 *
 * @param t The time series to calculate the features of
 * @param chunkSize The chunkSize used to aggregate the data
 * @param aggregationFunction Function to be used in the aggregation
 * @param slope Slope of the regression line
 * @param intercept Intercept of the regression line
 * @param rvalue Correlation coefficient
 * @param pvalue Two-sided p-value for a hypothesis test whose null hypothesis is
 * that the slope is zero, using Wald Test with t-distribution of
 * the test statistic
 * @param stderrest Standard error of the estimated gradient
 */
void aggregatedLinearTrend(af::array t, long chunkSize,
                           af::array (*aggregationFunction)(const af::array &, const dim_t), af::array &slope,
                           af::array &intercept, af::array &rvalue, af::array &pvalue, af::array &stderrest);

/**
 * @brief Calculates a vectorized Approximate entropy algorithm.
 * https://en.wikipedia.org/wiki/Approximate_entropy
 * For short time-series this method is highly dependent on the parameters, but should be stable for N > 2000,
 * see: Yentes et al. (2012) - The Appropriate Use of Approximate Entropy and Sample Entropy with Short Data Sets
 * Other shortcomings and alternatives discussed in:
 * Richman & Moorman (2000) - Physiological time-series analysis using approximate entropy and sample entropy
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @param m Length of compared run of data
 * @param r Filtering level, must be positive
 * @return af::array An array with the same dimensions as tss, whose values (time series in dimension 0)
 * contains the vectorized Approximate entropy for all the input time series in tss
 */
af::array approximateEntropy(af::array tss, int m, float r);

/**
 * @brief Calculates the cross-covariance of the given time series
 *
 * @param xss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param yss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param unbiased Determines whether it divides by n - lag (if true) or
 * n (if false)
 * @return af::array The cross-covariance value for the given time series
 */
af::array crossCovariance(af::array xss, af::array yss, bool unbiased = true);

/**
 * @brief Calculates the auto-covariance the given time series
 *
 * @param xss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param unbiased Determines whether it divides by n - lag (if true) or
 * n (if false)
 * @return af::array The auto-covariance value for the given time series
 */
af::array autoCovariance(af::array xss, bool unbiased = false);

/**
 * @brief Calculates the cross-correlation of the given time series
 *
 * @param xss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param yss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param unbiased Determines whether it divides by n - lag (if true) or
 * n (if false)
 * @return af::array The cross-correlation value for the given time series
 */
af::array crossCorrelation(af::array xss, af::array yss, bool unbiased = true);

/**
 * @brief Calculates the autocorrelation of the specified lag for the given time
 * series
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param maxLag The maximum lag to compute
 * @param unbiased Determines whether it divides by n - lag (if true) or
 * n (if false)
 * @return af::array The autocorrelation value for the given time series
 */
af::array autoCorrelation(af::array tss, long maxLag, bool unbiased = false);

/**
 * @brief Calculates the binned entropy for the given time series and number of bins
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param max_bins The number of bins
 * @return af::array The binned entropy value for the given time series
 */
af::array binnedEntropy(af::array tss, int max_bins);

/**
 * @brief Calculates the Schreiber, T. and Schmitz, A. (1997) measure of non-linearity
 * for the given time series
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param lag The lag
 * @return af::array The non-linearity value for the given time series
 */
af::array c3(af::array tss, long lag);

/**
 * @brief Calculates an estimate for the time series complexity defined by
 * Batista, Gustavo EAPA, et al (2014). (A more complex time series has more peaks,
 * valleys, etc.)
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param zNormalize Controls whether the time series should be z-normalized or not
 * @return af::array The complexity value for the given time series
 */
af::array cidCe(af::array tss, bool zNormalize = false);

/**
 * @brief Calculates the number of values in the time series that are higher than
 * the mean
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @return af::array The number of values in the time series that are higher
 * than the mean
 */
af::array countAboveMean(af::array tss);

/**
 * @brief Calculates the number of values in the time series that are lower than
 * the mean
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @return af::array The number of values in the time series that are lower
 * than the mean
 */
af::array countBelowMean(af::array tss);

/** @brief Calculates a Continuous wavelet transform for the Ricker wavelet, also known as
 * the "Mexican hat wavelet" which is defined by:
 *
 *  .. math::
 *      \\frac{2}{\\sqrt{3a} \\pi^{
 *  \\frac{1} { 4 }}} (1 - \\frac{x^2}{a^2}) exp(-\\frac{x^2}{2a^2})
 *
 *  where :math:`a` is the width parameter of the wavelet function.
 *
 * This feature calculator takes three different parameter: widths, coeff and w. The feature calculator takes all
 * the different widths arrays and then calculates the cwt one time for each different width array. Then the values
 * for the different coefficient for coeff and width w are returned. (For each dic in param one feature is
 * returned).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same)
 * and dimension one indicates the number of time series.
 * @param widths Array that contains all different widths.
 * @param coeff Coefficient of interest.
 * @param w Width of interest.
 * @return af::array Result of calculated coefficients.
 */
af::array cwtCoefficients(af::array tss, af::array widths, int coeff, int w);

/**
 * @brief Calculates the sum of squares of chunk i out of N chunks expressed as a ratio
 * with the sum of squares over the whole series. segmentFocus should be lower
 * than the number of segments
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param numSegments The number of segments to divide the series into
 * @param segmentFocus The segment number (starting at zero) to return a feature on
 * @return af::array The energy ratio by chunk of the time series
 */
af::array energyRatioByChunks(af::array tss, long numSegments, long segmentFocus);

/**
 * @brief Calculates the fourier coefficients of the one-dimensional discrete
 * Fourier Transform for real input by fast fourier transformation algorithm
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param coefficient The coefficient to extract from the FFT
 * @param real The real part of the coefficient
 * @param imag The imaginary part of the cofficient
 * @param abs The absolute value of the coefficient
 * @param angle The angle of the coefficient
 */
void fftCoefficient(af::array tss, long coefficient, af::array &real, af::array &imag, af::array &abs,
                    af::array &angle);

/**
 * @brief Calculates the first relative location of the maximal value for each timeseries.
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @return af::array The first relative location of the maximum value to the length of the timeseries,
 *  for each timeseries.
 */
af::array firstLocationOfMaximum(af::array tss);

/**
 * @brief Calculates the first location of the minimal value of each time series. The position
 * is calculated relatively to the length of the series
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @return af::array the first relative location of the minimal value of each series
 */
af::array firstLocationOfMinimum(af::array tss);

/**
 * @brief Calculates if the input time series contain duplicated elements
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @return af::array Array containing True if the time series contains duplicated elements
 * and false otherwise
 */
af::array hasDuplicates(af::array tss);

/**
 * @brief Calculates if the maximum within input time series is duplicated
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @return af::array Array containing True if the maximum value of the time series is duplicated
 * and false otherwise
 */
af::array hasDuplicateMax(af::array tss);

/**
 * @brief Calculates if the minimum of input time series is duplicated
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @return af::array Array containing True if the minimum of the time series is duplicated
 * and false otherwise
 */
af::array hasDuplicateMin(af::array tss);

/**
 * @brief Calculates the relative index i where q% of the mass of the time series within tss lie at the left of i.
 * For example for q = 50% this feature calculator will return the mass center of the time series.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same)
 * and dimension one indicates the number of time series.
 *
 * @param q The quantile limit
 *
 * @return af::array The relative indices i where q% of the mass of the time series lie at the left of i.
 */
af::array indexMaxQuantile(af::array tss, float q);

/**
 * @brief Returns the kurtosis of tss (calculated with the adjusted Fisher-Pearson
 * standardized moment coefficient G2).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @return af::array The kurtosis of tss
 */
af::array kurtosis(af::array tss);

/**
 * @brief Checks if the time series within tss have a large standard deviation.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of time series.
 *
 * @param r The threshold value.
 *
 * @return af::array Array containing True for those time series in tss that have a large standard deviation.
 */
af::array largeStandardDeviation(af::array tss, float r);

/**
 * @brief Calculates the last location of the maximum value of each time series. The position
 * is calculated relatively to the length of the series
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @return af::array The last relative location of the maximum value of each series
 */
af::array lastLocationOfMaximum(af::array tss);

/**
 * @brief Calculates the last location of the minimum value of each time series. The position
 * is calculated relatively to the length of the series
 *
 * @param tss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @return af::array The last relative location of the minimum value of each series
 */
af::array lastLocationOfMinimum(af::array tss);

/**
 * @brief Returns the length of the input time series.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @return af::array The length of tss
 */
af::array length(af::array tss);

/**
 * @brief Calculate a linear least-squares regression for the values of the time series versus the sequence from 0
 * to length of the time series minus one.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @param pvalue The pvalues for all timeseries
 * @param rvalue The rvalues for all timeseries
 * @param intercept The intercept values for all timeseries
 * @param slope The slope for all timeseries
 * @param stderr The stderr values for all timeseries
 */
void linearTrend(af::array tss, af::array &pvalue, af::array &rvalue, af::array &intercept, af::array &slope,
                 af::array &stderr);

/**
 * @brief Calculates the length of the longest consecutive subsequence in tss that is bigger than the mean of tss.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @return af::array the length of the longest consecutive subsequence in the input time series that is bigger than
 * the mean.
 */
af::array longestStrikeAboveMean(af::array tss);

/**
 * @brief Calculates the length of the longest consecutive subsequence in tss that is below the mean of tss.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @ return af::array The length of the longest consecutive subsequence in the input time series that is below the
 * mean.
 */
af::array longestStrikeBelowMean(af::array tss);

/**
 * @brief Largest fixed point of dynamics \f$\max_x {h(x)=0}\f$ estimated from polynomial
 * \f$h(x)\f$, which has been fitted to the deterministic dynamics of Langevin model
 * \f[
 *    \dot(x)(t) = h(x(t)) + R \mathcal(N)(0,1)
 * \f]
 * as described by
 * Friedrich et al. (2000): Physics Letters A 271, p. 217-222 *Extracting model equations from experimental data*
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @param m Order of polynom to fit for estimating fixed points of dynamics.
 * @param r Number of quantiles to use for averaging.
 * @return af::array Largest fixed point of deterministic dynamics
 */
af::array maxLangevinFixedPoint(af::array tss, int m, float r);

/**
 * @brief Calculates the maximum value for each time series within tss.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @return af::array The maximum value of each time series within tss.
 */
af::array maximum(af::array tss);

/**
 * @brief Calculates the mean value for each time series within tss.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @return af::array The mean value of each time series within tss.
 */
af::array mean(af::array tss);

/**
 * @brief Calculates the mean over the absolute differences between subsequent time series values in tss.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of time series.
 * @return af::array The mean over the absolute differences between subsequent time series values.
 */
af::array meanAbsoluteChange(af::array tss);

/**
 * @brief Calculates the mean over the differences between subsequent time series values in tss.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of time series.
 * @return af::array The mean over the differences between subsequent time series values.
 */
af::array meanChange(af::array tss);

/**
 * @brief Calculates mean value of a central approximation of the second derivative for each time series in tss.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 *
 * @return af::array The mean value of a central approximation of the second derivative for each time series.
 */
af::array meanSecondDerivativeCentral(af::array tss);

/**
 * @brief Calculates the minimum value for each time series within tss.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @return af::array The minimum value of each time series within tss.
 */
af::array minimum(af::array tss);

/**
 * @brief Calculates the number of m-crossings. A m-crossing is defined as two sequential values where the first
 * value is lower than m and the next is greater, or viceversa. If you set m to zero, you will get the number of
 * zero crossings.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 *
 * @param m The m value.
 *
 * @return af::array The number of m-crossings of each time series within tss.
 */
af::array numberCrossingM(af::array tss, int m);

};  // namespace features
};  // namespace tsa