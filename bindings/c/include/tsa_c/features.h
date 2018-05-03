// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Calculates the sum over the square values of the timeseries
 *
 * @param array Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @param result An array with the same dimensions as array, whose values (time series in dimension 0)
 * contains the sum of the squares values in the timeseries
 */
void abs_energy(af_array *array, af_array *result);

/**
 * @brief Calculates the sum over the absolute value of consecutive changes in the time series
 *
 * @param array Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @param result An array with the same dimensions as array, whose values (time series in dimension 0)
 * contains absolute value of consecutive changes in the time series
 */
void absolute_sum_of_changes(af_array *array, af_array *result);

/**
 * @brief Calculates the value of an aggregation function f_agg (e.g. var or mean) of the autocorrelation
 * (Compare to http://en.wikipedia.org/wiki/Autocorrelation#Estimation), taken over different all possible
 * lags (1 to length of x).
 *
 * @param array Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of time series.
 * @param aggregation_function Function to be used in the aggregation. It receives an integer which indicates the
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
 * @param result An array whose values contains the aggregated correaltion for each time series.
 */
void aggregated_autocorrelation(af_array *array, int *aggregation_function, af_array *result);

/**
 * @brief Calculates a linear least-squares regression for values of the time series that were aggregated
 * over chunks versus the sequence from 0 up to the number of chunks minus one.
 *
 * @param array The time series to calculate the features of
 * @param chunkSize The chunk size used to aggregate the data.
 * @param aggregation_function Function to be used in the aggregation. It receives an integer which indicates the
 * function to be applied:
 *          {
 *              0 : mean,
 *              1 : median
 *              2 : min,
 *              3 : max,
 *              4 : stdev,
 *              default : mean
 *          }
 * @param slope Slope of the regression line.
 * @param intercept Intercept of the regression line.
 * @param rvalue Correlation coefficient.
 * @param pvalue Two-sided p-value for a hypothesis test whose null hypothesis is that the slope is zero,
 * using Wald Test with t-distribution of the test statistic.
 * @param stderrest Standard error of the estimated gradient.
 */
void aggregated_linear_trend(af_array *array, long *chunkSize, int *aggregation_function, af_array *slope,
                             af_array *intercept, af_array *rvalue, af_array *pvalue, af_array *stderrest);

/**
 * @brief Calculates a vectorized Approximate entropy algorithm.
 * https://en.wikipedia.org/wiki/Approximate_entropy
 * For short time-series this method is highly dependent on the parameters, but should be stable for N > 2000,
 * see: Yentes et al. (2012) - The Appropriate Use of Approximate Entropy and Sample Entropy with Short Data Sets
 * Other shortcomings and alternatives discussed in:
 * Richman & Moorman (2000) - Physiological time-series analysis using approximate entropy and sample entropy.
 *
 * @param array Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @param m Length of compared run of data.
 * @param r Filtering level, must be positive.
 * @param result The vectorized approximate entropy for all the input time series in array.
 */
void approximate_entropy(af_array *array, int *m, float *r, af_array *result);

/**
 * @brief Calculates the cross-covariance of the given time series.
 *
 * @param xss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param yss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param unbiased Determines whether it divides by n - lag (if true) or
 * n (if false).
 * @param result The cross-covariance value for the given time series.
 */
void cross_covariance(af_array *xss, af_array *yss, bool *unbiased, af_array *result);

/**
 * @brief Calculates the auto-covariance the given time series.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param unbiased Determines whether it divides by n - lag (if true) or
 * n (if false).
 * @param result The auto-covariance value for the given time series.
 */
void auto_covariance(af_array *array, bool *unbiased, af_array *result);

/**
 * @brief Calculates the cross-correlation of the given time series.
 *
 * @param xss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param yss Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param unbiased Determines whether it divides by n - lag (if true) or
 * n (if false).
 * @param result The cross-correlation value for the given time series.
 */
void cross_correlation(af_array *xss, af_array *yss, bool *unbiased, af_array *result);

/**
 * @brief Calculates the autocorrelation of the specified lag for the given time
 * series.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param max_lag The maximum lag to compute.
 * @param unbiased Determines whether it divides by n - lag (if true) or n ( if false)
 * @param result The autocorrelation value for the given time series.
 */
void auto_correlation(af_array *array, long *max_lag, bool *unbiased, af_array *result);

/**
 * @brief Calculates the binned entropy for the given time series and number of bins.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param max_bins The number of bins.
 * @param result The binned entropy value for the given time series.
 */
void binned_entropy(af_array *array, int *max_bins, af_array *result);

/**
 * @brief Calculates the Schreiber, T. and Schmitz, A. (1997) measure of non-linearity
 * for the given time series.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param lag The lag
 * @param result The non-linearity value for the given time series.
 */
void c3(af_array *array, long *lag, af_array *result);

/**
 * @brief Calculates an estimate for the time series complexity defined by
 * Batista, Gustavo EAPA, et al (2014). (A more complex time series has more peaks,
 * valleys, etc.).
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param zNormalize Controls whether the time series should be z-normalized or not.
 * @param result The complexity value for the given time series.
 */
void cid_ce(af_array *array, bool *zNormalize, af_array *result);

/**
 * @brief Calculates the number of values in the time series that are higher than
 * the mean.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param result The number of values in the time series that are higher
 * than the mean.
 */
void count_above_mean(af_array *array, af_array *result);

/**
 * @brief Calculates the number of values in the time series that are lower than
 * the mean.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param result The number of values in the time series that are lower
 * than the mean.
 */
void count_below_mean(af_array *array, af_array *result);

/**
 * @brief Calculates a Continuous wavelet transform for the Ricker wavelet, also known as
 * the "Mexican hat wavelet" which is defined by:
 *
 *  .. math::
 *      \frac{2}{\sqrt{3a} \pi^{
 *  \frac{1} { 4 }}} (1 - \frac{x^2}{a^2}) exp(-\frac{x^2}{2a^2})
 *
 *  where :math:`a` is the width parameter of the wavelet function.
 *
 * This feature calculator takes three different parameter: widths, coeff and w. The feature calculator takes all
 * the different widths arrays and then calculates the cwt one time for each different width array. Then the values
 * for the different coefficient for coeff and width w are returned. (For each dic in param one feature is
 * returned).
 *
 * @param array Expects an input array whose dimension zero is the length of the time series (all the same)
 * and dimension one indicates the number of time series.
 * @param width Array that contains all different widths.
 * @param coeff Coefficient of interest.
 * @param w Width of interest.
 * @param result Result of calculated coefficients.
 */
void cwt_coefficients(af_array *array, af_array *width, int *coeff, int *w, af_array *result);

/**
 * @brief Calculates the sum of squares of chunk i out of N chunks expressed as a ratio
 * with the sum of squares over the whole series. segmentFocus should be lower
 * than the number of segments
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param num_segments The number of segments to divide the series into.
 * @param segment_focus The segment number (starting at zero) to return a feature on.
 * @param result The energy ratio by chunk of the time series.
 */
void energy_ratio_by_chunks(af_array *array, long *num_segments, long *segment_focus, af_array *result);

/**
 * @brief Calculates the spectral centroid(mean), variance, skew, and kurtosis of the absolute fourier transform
 * spectrum.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param result The spectral centroid (mean), variance, skew, and kurtosis of the absolute fourier transform
 * spectrum.
 */
void fft_aggregated(af_array *array, af_array *result);

/**
 * @brief Calculates the fourier coefficients of the one-dimensional discrete
 * Fourier Transform for real input by fast fourier transformation algorithm.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param coefficient The coefficient to extract from the FFT.
 * @param real The real part of the coefficient.
 * @param imag The imaginary part of the cofficient.
 * @param absolute The absolute value of the coefficient.
 * @param angle The angle of the coefficient.
 */
void fft_coefficient(af_array *array, long *coefficient, af_array *real, af_array *imag, af_array *absolute,
                     af_array *angle);

/**
 * @brief Calculates the first relative location of the maximal value for each time series.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param result The first relative location of the maximum value to the length of the time series,
 *  for each time series.
 */
void first_location_of_maximum(af_array *array, af_array *result);

/**
 * @brief Calculates the first location of the minimal value of each time series. The position
 * is calculated relatively to the length of the series.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param result The first relative location of the minimal value of each series.
 */
void first_location_of_minimum(af_array *array, af_array *result);

/**
 * @brief Coefficients of polynomial \f$h(x)\f$, which has been fitted to the deterministic
 * dynamics of Langevin model:
 * \f[
 *    \dot(x)(t) = h(x(t)) + R \mathcal(N)(0,1)
 * \f]
 * as described by [1]. For short time series this method is highly dependent on the parameters.
 *
 * [1] Friedrich et al. (2000): Physics Letters A 271, p. 217-222
 * Extracting model equations from experimental data.
 *
 * @param array Expects an input array whose dimension zero is the length of the time series (all the same)
 * and dimension one indicates the number of time series.
 * @param m Order of polynom to fit for estimating fixed points of dynamics.
 * @param r Number of quantils to use for averaging.
 * @param result The coefficients for each time series.
 */
void friedrich_coefficients(af_array *array, int *m, float *r, af_array *result);

/**
 * @brief Calculates if the input time series contain duplicated elements.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param result Array containing True if the time series contains duplicated elements
 * and false otherwise.
 */
void has_duplicates(af_array *array, af_array *result);

/**
 * @brief Calculates if the maximum within input time series is duplicated.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param result Array containing True if the maximum value of the time series is duplicated
 * and false otherwise.
 */
void has_duplicate_max(af_array *array, af_array *result);

/**
 * @brief Calculates if the minimum of the input time series is duplicated
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param result Array containing True if the minimum of the time series is duplicated
 * and false otherwise.
 */
void has_duplicate_min(af_array *array, af_array *result);

/**
 * @brief Calculates the index of the max quantile.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param q The quantile.
 * @param result The index of the max quantile q.
 */
void index_mass_quantile(af_array *array, float *q, af_array *result);

/**
 * @brief Returns the kurtosis of array (calculated with the adjusted Fisher-Pearson
 * standardized moment coefficient G2).
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param result The kurtosis of each array.
 */
void kurtosis(af_array *array, af_array *result);

/**
 * @brief Checks if the time series within array have a large standard deviation.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param r The threshold.
 * @param result  Array containing True for those time series in array that have a large standard deviation.
 */
void large_standard_deviation(af_array *array, float *r, af_array *result);

/**
 * @brief Calculates the last location of the maximum value of each time series. The position
 * is calculated relatively to the length of the series.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param result The last relative location of the maximum value of each series.
 */
void last_location_of_maximum(af_array *array, af_array *result);

/**
 * @brief Calculates the last location of the minimum value of each time series. The position
 * is calculated relatively to the length of the series.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param result The last relative location of the minimum value of each series.
 */
void last_location_of_minimum(af_array *array, af_array *result);

/**
 * @brief Returns the length of the input time series.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param result The length of the time series.
 */
void length(af_array *array, af_array *result);

/**
 * @brief Calculate a linear least-squares regression for the values of the time series versus the sequence from 0 to
 * length of the time series minus one.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param pvalue The pvalues for all time series.
 * @param rvalue The rvalues for all time series.
 * @param intercept The intercept values for all time series.
 * @param slope The slope for all time series.
 * @param stdrr The stderr values for all time series.
 */
void linear_trend(af_array *array, af_array *pvalue, af_array *rvalue, af_array *intercept, af_array *slope,
                  af_array *stdrr);

/**
 * @brief Calculates all Local Maximals fot the time series in array.
 *
 * @param array Expects an input array whose dimension zero is the length of the time series (all the same)
 * and dimension one indicates the number of time series.
 * @param result The calculated local maximals for each time series in array.
 */
void local_maximals(af_array *array, af_array *result);

/**
 * @brief Calculates the length of the longest consecutive subsequence in array that is bigger than the mean of array.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param result The length of the longest consecutive subsequence in the input time series that is bigger than the
 * mean.
 */
void longest_strike_above_mean(af_array *array, af_array *result);

/**
 * @brief Calculates the length of the longest consecutive subsequence in array that is below the mean of array.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param result The length of the longest consecutive subsequence in the input time series that is below the mean.
 */
void longest_strike_below_mean(af_array *array, af_array *result);

/**
 * @brief Largest fixed point of dynamics \f$\max_x {h(x)=0}\f$ estimated from polynomial
 * \f$h(x)\f$, which has been fitted to the deterministic dynamics of Langevin model
 * \f[
 *    \dot(x)(t) = h(x(t)) + R \mathcal(N)(0,1)
 * \f]
 * as described by
 * Friedrich et al. (2000): Physics Letters A 271, p. 217-222 *Extracting model equations from experimental data.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param m Order of polynom to fit for estimating fixed points of dynamics.
 * @param r Number of quantiles to use for averaging.
 * @param result Largest fixed point of deterministic dynamics.
 */
void max_langevin_fixed_point(af_array *array, int *m, float *r, af_array *result);

/**
 * @brief Calculates the maximum value for each time series within array.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param result The maximum value of each time series within array.
 */
void maximum(af_array *array, af_array *result);

/**
 * @brief Calculates the mean value for each time series within array.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param result The mean value of each time series within array.
 */
void mean(af_array *array, af_array *result);

/**
 * @brief Calculates the mean over the absolute differences between subsequent time series values in array.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param result The maximum value of each time series within array.
 */
void mean_absolute_change(af_array *array, af_array *result);

/**
 * @brief Calculates the mean over the differences between subsequent time series values in array.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param result The mean over the differences between subsequent time series values.
 */
void mean_change(af_array *array, af_array *result);

/**
 * @brief Calculates mean value of a central approximation of the second derivative for each time series in array.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param result The mean value of a central approximation of the second derivative for each time series.
 */
void mean_second_derivative_central(af_array *array, af_array *result);

/**
 * @brief Calculates the median value for each time series within array.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param result The median value of each time series within array.
 */
void median(af_array *array, af_array *result);

/**
 * @brief Calculates the minimum value for each time series within array.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param result The minimum value of each time series within array.
 */
void minimum(af_array *array, af_array *result);

/**
 * @brief Calculates the number of m-crossings. A m-crossing is defined as two sequential values where the first
 * value is lower than m and the next is greater, or viceversa. If you set m to zero, you will get the number of
 * zero crossings.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param m The m value.
 * @param result The number of m-crossings of each time series within array.
 */
void number_crossing_m(af_array *array, int *m, af_array *result);

/**
 * @brief This feature calculator searches for different peaks. To do so, the time series is smoothed by a ricker
 * wavelet and for widths ranging from 1 to max_w. This feature calculator returns the number of peaks that occur at
 * enough width scales and with sufficiently high Signal-to-Noise-Ratio (SNR).
 *
 * @param array Expects an input array whose dimension zero is the length of the time series (all the same)
 * and dimension one indicates the number of time series.
 * @param max_w The maximum width to consider.
 * @param result The number of peaks for each time series.
 */
void number_cwt_peaks(af_array *array, int *max_w, af_array *result);

/**
 * @brief Calculates the number of peaks of at least support \f$n\f$ in the time series \f$array\f$. A peak of support
 * \f$n\f$ is defined as a subsequence of \f$array\f$ where a value occurs, which is bigger than its \f$n\f$ neighbours
 * to the left and to the right.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param n The support of the peak.
 * @param result The number of peaks of at least support \f$n\f$.
 */
void number_peaks(af_array *array, int *n, af_array *result);

/**
 * @brief Calculates the value of the partial autocorrelation function at the given lag. The lag \f$k\f$ partial
 * autocorrelation of a time series \f$\lbrace x_t, t = 1 \ldots T \rbrace\f$ equals the partial correlation of
 * \f$x_t\f$ and \f$x_{t-k}\f$, adjusted for the intermediate variables \f$\lbrace x_{t-1}, \ldots, x_{t-k+1}
 * \rbrace\f$ ([1]). Following [2], it can be defined as:
 *
 * \f[
 *      \alpha_k = \frac{ Cov(x_t, x_{t-k} | x_{t-1}, \ldots, x_{t-k+1})}
 *      {\sqrt{ Var(x_t | x_{t-1}, \ldots, x_{t-k+1}) Var(x_{t-k} | x_{t-1}, \ldots, x_{t-k+1} )}}
 * \f]
 * with (a) \f$x_t = f(x_{t-1}, \ldots, x_{t-k+1})\f$ and (b) \f$ x_{t-k} = f(x_{t-1}, \ldots, x_{t-k+1})\f$
 * being AR(k-1) models that can be fitted by OLS. Be aware that in (a), the regression is done on past values to
 * predict \f$ x_t \f$ whereas in (b), future values are used to calculate the past value \f$x_{t-k}\f$.
 * It is said in [1] that "for an AR(p), the partial autocorrelations \f$ \alpha_k \f$ will be nonzero for \f$ k<=p \f$
 * and zero for \f$ k>p \f$."
 * With this property, it is used to determine the lag of an AR-Process.
 *
 * [1] Box, G. E., Jenkins, G. M., Reinsel, G. C., & Ljung, G. M. (2015).
 * Time series analysis: forecasting and control. John Wiley & Sons.
 * [2] https://onlinecourses.science.psu.edu/stat510/node/62
 *
 * @param array Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @param lags Indicates the lags to be calculated.
 * @param result Returns partial autocorrelation for each time series for the given lag.
 */
void partial_autocorrelation(af_array *array, af_array *lags, af_array *result);

/**
 * @brief Calculates the percentage of unique values, that are present in the time series more than once.
 * \f[
 *      len(different values occurring more than once) / len(different values)
 * \f]
 * This means the percentage is normalized to the number of unique values, in contrast to the
 * percentageOfReoccurringValuesToAllValues.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param is_sorted Indicates if the input time series is sorted or not. Defaults to false.
 * @param result Returns the percentage of unique values, that are present in the time series more than once.
 */
void percentage_of_reoccurring_datapoints_to_all_datapoints(af_array *array, bool *is_sorted, af_array *result);

/**
 * @brief Calculates the percentage of unique values, that are present in the time series more than once.
 * \f[
 *      \frac{\textit{number of data points occurring more than once}}{\textit{number of all data points})}
 * \f]
 * This means the percentage is normalized to the number of unique values, in contrast to the
 * percentageOfReoccurringDatapointsToAllDatapoints.
 *
 * @param array Expects an input array whose dimension zero is the length of the time series (all the same)
 * and dimension one indicates the number of time series.
 * @param is_sorted Indicates if the input time series is sorted or not. Defaults to false.
 * @param result Returns the percentage of unique values, that are present in the time series more than once.
 */
void percentage_of_reoccurring_values_to_all_values(af_array *array, bool *is_sorted, af_array *result);

/**
 * @brief Returns values at the given quantile.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param q Percentile(s) at which to extract score(s). One or many.
 * @param precision Number of decimals expected.
 * @param result Values at the given quantile.
 */
void quantile(af_array *array, af_array *q, float *precision, af_array *result);

/**
 * @brief Counts observed values within the interval [min, max).
 *
 * @param array Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @param min Value that sets the lower limit.
 * @param max Value that sets the upper limit.
 * @param result Values at the given range.
 */
void range_count(af_array *array, float *min, float *max, af_array *result);

/**
 * @brief Calculates the ratio of values that are more than \f$r*std(x)\f$ (so \f$r\f$ sigma) away from the mean of
 * \f$x\f$.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param r Number of times that the values should be away from.
 * @param result The ratio of values that are more than \f$r*std(x)\f$ (so \f$r\f$ sigma) away from the mean of
 * \f$x\f$.
 */
void ratio_beyond_r_sigma(af_array *array, float *r, af_array *result);

/**
 * @brief Calculates a factor which is 1 if all values in the time series occur only once, and below one if this is
 * not the case. In principle, it just returns:
 *
 * \f[
 *      \frac{\textit{number_unique_values}}{\textit{number_values}}
 * \f]
 *
 * @param array Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @param result The ratio of unique values with respect to the total number of values.
 */
void ratio_value_number_to_time_series_length(af_array *array, af_array *result);

/**
 * @brief Calculates a vectorized sample entropy algorithm.
 * https://en.wikipedia.org/wiki/Sample_entropy
 * https://www.ncbi.nlm.nih.gov/pubmed/10843903?dopt=Abstract
 * For short time-series this method is highly dependent on the parameters, but should be stable for N > 2000,
 * see: Yentes et al. (2012) - The Appropriate Use of Approximate Entropy and Sample Entropy with Short Data Sets
 * Other shortcomings and alternatives discussed in:
 * Richman & Moorman (2000) - Physiological time-series analysis using approximate entropy and sample entropy.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param result An array with the same dimensions as array, whose values (time series in dimension 0)
 * contains the vectorized sample entropy for all the input time series in array.
 */
void sample_entropy(af_array *array, af_array *result);

/**
 * @brief Calculates the sample skewness of array (calculated with the adjusted Fisher-Pearson standardized
 * moment coefficient G1).
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param result Array containing the skewness of each time series in array.
 */
void skewness(af_array *array, af_array *result);

/**
 * @brief Estimates the cross power spectral density of the time series array at different frequencies. To do so, the
 * time series is first shifted from the time domain to the frequency domain.
 *
 * Welch's method computes an estimate of the power spectral density by dividing the data into overlapping
 * segments, computing a modified periodogram for each segment and averaging the periodograms.
 * [1] P. Welch, "The use of the fast Fourier transform for the estimation of power spectra: A method based on time
 *  averaging over short, modified periodograms", IEEE Trans. Audio Electroacoust. vol. 15, pp. 70-73, 1967.
 * [2] M.S. Bartlett, "Periodogram Analysis and Continuous Spectra", Biometrika, vol. 37, pp. 1-16, 1950.
 * [3] Rabiner, Lawrence R., and B. Gold. "Theory and Application of Digital Signal Processing" Prentice-Hall, pp.
 * 414-419, 1975.
 *
 * @param array Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @param coeff The coefficient to be returned.
 * @param result Array containing the power spectrum of the different frequencies for each time series in
 * array.
 */
void spkt_welch_density(af_array *array, int *coeff, af_array *result);

/**
 * @brief Calculates the standard deviation of each time series within array.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param result The standard deviation of each time series within array.
 */
void standard_deviation(af_array *array, af_array *result);

/**
 * @brief Calculates the sum of all data points, that are present in the time series more than once.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param is_sorted Indicates if the input time series is sorted or not. Defaults to false.
 * @param result Returns the sum of all data points, that are present in the time series more than once.
 */
void sum_of_reoccurring_datapoints(af_array *array, bool *is_sorted, af_array *result);

/**
 * @brief Calculates the sum of all values, that are present in the time series more than once.
 *
 * @param array Expects an input array whose dimension zero is the length of the time series (all the same)
 * and dimension one indicates the number of time series.
 * @param is_sorted Indicates if the input time series is sorted or not. Defaults to false.
 * @param result Returns the sum of all values, that are present in the time series more than once.
 */
void sum_of_reoccurring_values(af_array *array, bool *is_sorted, af_array *result);

/**
 * @brief Calculates the sum over the time series array.
 *
 * @param array Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @param result An array containing the sum of values in each time series.
 */
void sum_values(af_array *array, af_array *result);

/**
 * @brief Calculates if the distribution of array *looks symmetric*. This is the case if
 * \f[
 *      | mean(array)-median(array)| < r * (max(array)-min(array))
 * \f]
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param r The percentage of the range to compare with.
 * @param result An array denoting if the input time series look symmetric.
 */
void symmetry_looking(af_array *array, float *r, af_array *result);

/**
 * @brief This function calculates the value of:
 * \f[
 *      \frac{1}{n-2lag} \sum_{i=0}^{n-2lag} x_{i + 2 \cdot lag}^2 \cdot x_{i + lag} - x_{i + lag} \cdot  x_{i}^2
 * \f]
 * which is
 * \f[
 *       \mathbb{E}[L^2(X)^2 \cdot L(X) - L(X) \cdot X^2]
 * \f]
 * where \f$ \mathbb{E} \f$ is the mean and \f$ L \f$ is the lag operator. It was proposed in [1] as a promising
 * feature to extract from time series.
 *
 * [1] Fulcher, B.D., Jones, N.S. (2014). Highly comparative feature-based time-series classification.
 * Knowledge and Data Engineering, IEEE Transactions on 26, 3026–3037.
 *
 * @param array Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @param lag The lag to be computed.
 * @param result An array containing the time reversal asymetry statistic value in each time series.
 */
void time_reversal_asymmetry_statistic(af_array *array, int *lag, af_array *result);

/**
 * @brief Counts occurrences of value in the time series array.
 *
 * @param array Expects an input array whose dimension zero is the length of the
 * time series (all the same) and dimension one indicates the number of time
 * series.
 * @param v The value to be counted.
 * @param result An array containing the count of the given value in each time series.
 */
void value_count(af_array *array, float *v, af_array *result);

/**
 * @brief Computes the variance for the time series array.
 *
 * @param array Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @param result An array containing the variance in each time series.
 */
void variance(af_array *array, af_array *result);

/**
 * @brief Calculates if the variance of array is greater than the standard deviation. In other words, if the variance of
 * array is larger than 1.
 *
 * @param array Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @param result An array denoting if the variance of array is greater than the standard deviation.
 */
void variance_larger_than_standard_deviation(af_array *array, af_array *result);

#ifdef __cplusplus
}
#endif