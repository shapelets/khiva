// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

namespace tsa {

namespace features {

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Primitive of the absEnergy function.
 *
 * @param time_series Time series concatenated in a single row.
 * @param time_series_length time_series length (All time series need to have the same length).
 * @param number_of_time_series Number of time series in time_series.
 * @param primitive_result Absolute Energy.
 */
void abs_energy(double *time_series, long *time_series_length, long *number_of_time_series, double *primitive_result);

/**
 * @brief Primitive of the absoluteSumOfChanges function.
 *
 * @param time_series  Time series concatenated in a single row.
 * @param time_series_length time_series length (All time series need to have the same length).
 * @param number_of_time_series  Number of time series.
 * @param primitive_result Absolute sum of changes.
 */
void absolute_sum_of_changes(double *time_series, long *time_series_length, long *number_of_time_series,
                             double *primitive_result);

/**
 * @brief Calculates the value of an aggregation function f_agg (e.g. var or mean) of the autocorrelation
 * (Compare to http://en.wikipedia.org/wiki/Autocorrelation#Estimation), taken over different all possible
 * lags (1 to length of x).
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_l Time series length (All time series need to have the same length).
 * @param tss_n Number of time series.
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
void aggregated_autocorrelation(double *tss, long *tss_l, long *tss_n, int *aggregation_function, double *result);

/**
 * @brief Calculates a linear least-squares regression for values of the time series that were aggregated
 * over chunks versus the sequence from 0 up to the number of chunks minus one.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_l Time series length (All time series need to have the same length).
 * @param tss_n Number of time series.
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
void aggregated_linear_trend(double *t, long *t_l, long *t_n, long *chunkSize, int *aggregation_function, double *slope,
                             double *intercept, double *rvalue, double *pvalue, double *stderrest);

/**
 * @brief Primitive of the aproximateEntropy function.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series.
 * @param m Length of compared run of data.
 * @param r Filtering level, must be positive.
 * @param result The vectorized approximate entropy for all the input time series in tss.
 */
void approximate_entropy(double *tss, long *tss_length, long *tss_number_of_tss, int *m, double *r, double *result);

/**
 * @brief Primitive of the crossCovariance function.
 *
 * @param xss Time series concatenated in a single row.
 * @param xss_length xss Time series length (All time series need to have the same length).
 * @param xss_number_of_tss Number of time series in xss.
 * @param yss Time series concatenated in a single row.
 * @param yss_length yss Time series length.
 * @param yss_number_of_tss Number of time series in yss.
 * @param unbiased Determines whether it divides by n - lag (if true) or
 * n (if false).
 * @result The cross-covariance value for the given time series.
 */
void cross_covariance(double *xss, long *xss_length, long *xss_number_of_tss, double *yss, long *yss_length,
                      long *yss_number_of_tss, bool *unbiased, double *result);

/**
 * @brief Primitive of the autoCovariance function.
 *
 * @param xss Time series concatenated in a single row.
 * @param xss_length Time series length (All time series need to have the same length).
 * @param xss_number_of_tss Number of time series.
 * @param unbiased Determines whether it divides by n - lag (if true) or
 * n (if false).
 * @param result The auto-covariance value for the given time series.
 */
void auto_covariance(double *xss, long *xss_length, long *xss_number_of_tss, bool *unbiased, double *result);

/**
 * @brief Primitive of the cross_correlation function.
 *
 * @param xss Time series concatenated in a single row.
 * @param xss_length Time series length (All time series need to have the same length).
 * @param xss_number_of_tss Number of time series.
 * @param yss Time series concatenated in a single row.
 * @param yss_length  yss time series length.
 * @param yss_number_of_tss yss Number of time series.
 * @param unbiased Determines whether it divides by n - lag (if true) or
 * n (if false).
 * @param result The cross-correlation value for the given time series.
 */
void cross_correlation(double *xss, long *xss_length, long *xss_number_of_tss, double *yss, long *yss_length,
                       long *yss_number_of_tss, bool *unbiased, double *result);

/**
 * @brief Primitive of autoCorrelation function.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series.
 * @param max_lag The maximum lag to compute.
 * @param unbiased Determines whether it divides by n - lag (if true) or n ( if false)
 * @param result The autocorrelation value for the given time series.
 */
void auto_correlation(double *tss, long *tss_length, long *tss_number_of_tss, long *max_lag, bool *unbiased,
                      double *result);

/**
 * @brief Primitive of binnedEntropy function.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss NUmber of time series.
 * @param max_bins The number of bins.
 * @param result The binned entropy value for the given time series.
 */
void binned_entropy(double *tss, long *tss_length, long *tss_number_of_tss, int *max_bins, double *result);

/**
 * @brief Primitive of the c3 function.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series.
 * @param lag The lag
 * @param result The non-linearity value for the given time series.
 */
void c3(double *tss, long *tss_length, long *tss_number_of_tss, long *lag, double *result);

/**
 * @brief Primitive of the cidCe function.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length tss length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series in tss.
 * @param zNormalize Controls whether the time series should be z-normalized or not.
 * @param result The complexity value for the given time series.
 */
void cidCe(double *tss_time_series, long *tss_length, long *tss_number_of_tss, bool *zNormalize, double *result);

/**
 * @brief Primitive of countAboveMean function.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss NUmber of time series.
 * @param result The number of values in the time series that are higher
 * than the mean.
 */
void count_above_mean(double *tss, long *tss_length, long *tss_number_of_tss, unsigned int *result);

/**
 * @brief Primitive of countBelowMean function.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series.
 * @param result The number of values in the time series that are lower
 * than the mean.
 */
void count_below_mean(double *tss, long *tss_length, long *tss_number_of_tss, unsigned int *result);

/**
 * @brief Calculates a Continuous wavelet transform for the Ricker wavelet, also known as
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
 * @param tss Time series concatenated in a single row.
 * @param tss_l Time series length (All time series need to have the same length).
 * @param tss_n Number of time series.
 * @param widths Array that contains all different widths.
 * @param widths_l widths length (All of those ones need to have the same length)
 * @param widths_n Number of widths.
 * @param coeff Coefficient of interest.
 * @param w Width of interest.
 * @param result Result of calculated coefficients.
 */
void cwt_coefficients(double *tss, long *tss_l, long *tss_n, int *widths, long *widths_l, long *widths_n, int *coeff,
                      int *w, double *result);

/**
 * @brief Primitive of energyRatioByChunks function.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series.
 * @param num_segments The number of segments to divide the series into.
 * @param segment_focus The segment number (starting at zero) to return a feature on.
 * @param result The energy ratio by chunk of the time series.
 */
void energy_ratio_by_chunks(double *tss, long *tss_length, long *tss_number_of_tss, long *num_segments,
                            long *segment_focus, double *result);

/**
 * @brief Calculates the spectral centroid(mean), variance, skew, and kurtosis of the absolute fourier transform
 * spectrum.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_l Time series length (All time series need to have the same length).
 * @param tss_n Number of time series.
 * @param result The spectral centroid (mean), variance, skew, and kurtosis of the absolute fourier transform
 * spectrum.
 */
void fft_aggregated(double *tss, long *tss_l, long *tss_n, double *result);

/**
 * @brief Calculates the fourier coefficients of the one-dimensional discrete
 * Fourier Transform for real input by fast fourier transformation algorithm.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series.
 * @param coefficient The coefficient to extract from the FFT.
 * @param real The real part of the coefficient.
 * @param imag The imaginary part of the cofficient.
 * @param absolute The absolute value of the coefficient.
 * @param angle The angle of the coefficient.
 */
void fftCoefficient(double *tss, long *tss_length, long *tss_number_of_tss, long *coefficient, double *real,
                    double *imag, double *absolute, double *angle);

/**
 * @brief Calculates the first relative location of the maximal value for each time series.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series.
 * @param result The first relative location of the maximum value to the length of the time series,
 *  for each time series.
 */
void first_location_of_maximum(double *tss, long *tss_length, long *tss_number_of_tss, double *result);

/**
 * @brief Calculates the first location of the minimal value of each time series. The position
 * is calculated relatively to the length of the series.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series.
 * @param result The first relative location of the minimal value of each series.
 */
void first_location_of_minimum(double *tss, long *tss_length, long *tss_number_of_tss, double *result);

/**
 * @brief Calculates if the input time series contain duplicated elements.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series.
 * @param result Array containing True if the time series contains duplicated elements
 * and false otherwise.
 */
void has_duplicates(double *tss, long *tss_length, long *tss_number_of_tss, bool *result);

/**
 * @brief Calculates if the maximum within input time series is duplicated.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series.
 * @param result Array containing True if the maximum value of the time series is duplicated
 * and false otherwise.
 */
void has_duplicate_max(double *tss, long *tss_length, long *tss_number_of_tss, bool *result);

/**
 * @brief Calculates if the minimum of the input time series is duplicated
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series.
 * @param result Array containing True if the minimum of the time series is duplicated
 * and false otherwise.
 */
void has_duplicate_min(double *tss, long *tss_length, long *tss_number_of_tss, bool *result);

/**
 * @brief Calculates the index of the max quantile.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series.
 * @param q The quantile.
 * @param result The index of the max quantile q.
 */
void index_max_quantile(double *tss, long *tss_length, long *tss_number_of_tss, double *q, double *result);

/**
 * @brief Returns the kurtosis of tss (calculated with the adjusted Fisher-Pearson
 * standardized moment coefficient G2).
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series.
 * @param result The kurtosis of each tss.
 */
void kurtosis(double *tss, long *tss_length, long *tss_number_of_tss, double *result);

/**
 * @brief Checks if the time series within tss have a large standard deviation.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series.
 * @param r The threshold.
 * @param result  Array containing True for those time series in tss that have a large standard deviation.
 */
void large_standard_deviation(double *tss, long *tss_length, long *tss_number_of_tss, double *r, bool *result);

/**
 * @brief Calculates the last location of the maximum value of each time series. The position
 * is calculated relatively to the length of the series.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series.
 * @param result The last relative location of the maximum value of each series.
 */
void last_location_of_maximum(double *tss, long *tss_length, long *tss_number_of_tss, double *result);

/**
 * @brief Calculates the last location of the minimum value of each time series. The position
 * is calculated relatively to the length of the series.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series.
 * @param result The last relative location of the minimum value of each series.
 */
void last_location_of_minimum(double *tss, long *tss_length, long *tss_number_of_tss, double *result);

/**
 * @brief Returns the length of the input time series.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series.
 * @param result The length of tss.
 */
void length(double *tss, long *tss_length, long *tss_number_of_tss, int *result);

/**
 * @brief Calculate a linear least-squares regression for the values of the time series versus the sequence from 0 to
 * length of the time series minus one.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series.
 * @param pvalue The pvalues for all time series.
 * @param rvalue The rvalues for all time series.
 * @param intercept The intercept values for all time series.
 * @param slope The slope for all time series.
 * @param stdrr The stderr values for all time series.
 */
void linear_trend(double *tss, long *tss_length, long *tss_number_of_tss, double *pvalue, double *rvalue,
                  double *intercept, double *slope, double *stdrr);

/**
 * @brief Calculates the length of the longest consecutive subsequence in tss that is bigger than the mean of tss.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series.
 * @param result The length of the longest consecutive subsequence in the input time series that is bigger than the
 * mean.
 */
void longest_strike_above_mean(double *tss, long *tss_length, long *tss_number_of_tss, double *result);

/**
 * @brief Calculates the length of the longest consecutive subsequence in tss that is below the mean of tss.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series.
 * @param result The length of the longest consecutive subsequence in the input time series that is below the mean.
 */
void longest_strike_below_mean(double *tss, long *tss_length, long *tss_number_of_tss, double *result);

/**
 * @brief Largest fixed point of dynamics \f$\max_x {h(x)=0}\f$ estimated from polynomial
 * \f$h(x)\f$, which has been fitted to the deterministic dynamics of Langevin model
 * \f[
 *    \dot(x)(t) = h(x(t)) + R \mathcal(N)(0,1)
 * \f]
 * as described by
 * Friedrich et al. (2000): Physics Letters A 271, p. 217-222 *Extracting model equations from experimental data.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_l Time series length (All time series need to have the same length).
 * @param tss_n Number of time series.
 * @param m Order of polynom to fit for estimating fixed points of dynamics.
 * @param r Number of quantiles to use for averaging.
 * @param result Largest fixed point of deterministic dynamics.
 */
void max_langevin_fixed_point(double *tss, long *tss_l, long *tss_n, int *m, double *r, double *result);

/**
 * @brief Calculates the maximum value for each time series within tss.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series.
 * @param result The maximum value of each time series within tss.
 */
void maximum(double *tss, long *tss_length, long *tss_number_of_tss, double *result);

/**
 * @brief Calculates the mean value for each time series within tss.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_l Time series length (All time series need to have the same length).
 * @param tss_n Number of time series.
 * @param result The mean value of each time series within tss.
 */
void mean(double *tss, long *tss_l, long *tss_n, double *result);

/**
 * @brief Calculates the mean over the absolute differences between subsequent time series values in tss.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_length Time series length (All time series need to have the same length).
 * @param tss_number_of_tss Number of time series.
 * @param result The maximum value of each time series within tss.
 */
void mean_absolute_change(double *tss, long *tss_length, long *tss_number_of_tss, double *result);

/**
 * @brief Calculates the mean over the differences between subsequent time series values in tss.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_l Time series length (All time series need to have the same length).
 * @param tss_n Number of time series.
 * @param result The mean over the differences between subsequent time series values.
 */
void mean_change(double *tss, long *tss_l, long *tss_n, double *result);

/**
 * @brief Calculates mean value of a central approximation of the second derivative for each time series in tss.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_l Time series length (All time series need to have the same length).
 * @param tss_n Number of time series.
 * @param result The mean value of a central approximation of the second derivative for each time series.
 */
void mean_second_derivative_central(double *tss, long *tss_l, long *tss_n, double *result);

/**
 * @brief Calculates the median value for each time series within tss.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_l Time series length (All time series need to have the same length).
 * @param tss_n Number of time series.
 * @param result The median value of each time series within tss.
 */
void median(double *tss, long *tss_l, long *tss_n, double *result);

/**
 * @brief Calculates the minimum value for each time series within tss.
 * @param tss Time series concatenated in a single row.
 * @param tss_l Time series length (All time series need to have the same length).
 * @param tss_n Number of time series.
 * @param result The minimum value of each time series within tss.
 */
void minimum(double *tss, long *tss_l, long *tss_n, double *result);

/**
 * @brief Calculates the number of m-crossings. A m-crossing is defined as two sequential values where the first
 * value is lower than m and the next is greater, or viceversa. If you set m to zero, you will get the number of
 * zero crossings.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_l Time series length (All time series need to have the same length).
 * @param tss_n Number of time series.
 * @param m The m value.
 * @param result The number of m-crossings of each time series within tss.
 */
void number_crossing_m(double *tss, long *tss_l, long *tss_n, int *m, double *result);

/**
 * @brief Calculates the number of peaks of at least support \f$n\f$ in the time series \f$tss\f$. A peak of support
 * \f$n\f$ is defined as a subsequence of \f$tss\f$ where a value occurs, which is bigger than its \f$n\f$ neighbours to
 * the left and to the right.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_l Time series length (All time series need to have the same length).
 * @param tss_n Number of time series.
 * @param n The support of the peak.
 * @param result The number of peaks of at least support \f$n\f$.
 */
void number_peaks(double *tss, long *tss_l, long *tss_n, int *n, double *result);

/**
 * @brief Calculates the percentage of unique values, that are present in the time series more than once.
 * \f[
 *      len(different values occurring more than once) / len(different values)
 * \f]
 * This means the percentage is normalized to the number of unique values, in contrast to the
 * percentageOfReoccurringValuesToAllValues.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_l Time series length (All time series need to have the same length).
 * @param tss_n Number of time series.
 * @param is_sorted Indicates if the input time series is sorted or not. Defaults to false.
 * @return Returns the percentage of unique values, that are present in the time series more than once.
 */
void percentage_of_reoccurring_datapoints_to_all_datapoints(double *tss, long *tss_l, long *tss_n, bool *is_sorted,
                                                            double *result);

/**
 * @brief Returns values at the given quantile.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_l Time series length (All time series need to have the same length).
 * @param tss_n Number of time series.
 * @param q Percentile(s) at which to extract score(s). One or many.
 * @param q_n Number of percentiles.
 * @param precision Number of decimals expected.
 * @return Values at the given quantile.
 */
void quantile(double *tss, long *tss_l, long *tss_n, double *q, long *q_n, double *precision, double *result);

/**
 * @brief Calculates the ratio of values that are more than \f$r*std(x)\f$ (so \f$r\f$ sigma) away from the mean of
 * \f$x\f$.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_l Time series length (All time series need to have the same length).
 * @param tss_n Number of time series.
 * @param r Number of times that the values should be away from.
 * @return The ratio of values that are more than \f$r*std(x)\f$ (so \f$r\f$ sigma) away from the mean of
 * \f$x\f$.
 */
void ratio_beyond_r_sigma(double *tss, long *tss_l, long *tss_n, double *r, double *result);

/**
 * @brief Calculates a vectorized sample entropy algorithm.
 * https://en.wikipedia.org/wiki/Sample_entropy
 * https://www.ncbi.nlm.nih.gov/pubmed/10843903?dopt=Abstract
 * For short time-series this method is highly dependent on the parameters, but should be stable for N > 2000,
 * see: Yentes et al. (2012) - The Appropriate Use of Approximate Entropy and Sample Entropy with Short Data Sets
 * Other shortcomings and alternatives discussed in:
 * Richman & Moorman (2000) - Physiological time-series analysis using approximate entropy and sample entropy.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_l Time series length (All time series need to have the same length).
 * @param tss_n Number of time series.
 * @param result An array with the same dimensions as tss, whose values (time series in dimension 0)
 * contains the vectorized sample entropy for all the input time series in tss.
 */
void sample_entropy(double *tss, long *tss_l, long *tss_n, double *result);

/**
 * @brief Calculates the sample skewness of tss (calculated with the adjusted Fisher-Pearson standardized
 * moment coefficient G1).
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_l Time series length (All time series need to have the same length).
 * @param tss_n Number of time series.
 * @param result Array containing the skewness of each time series in tss.
 */
void skewness(double *tss, long *tss_l, long *tss_n, double *result);

/**
 * @brief Calculates the standard deviation of each time series within tss.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_l Time series length (All time series need to have the same length).
 * @param tss_n Number of time series.
 * @param result The standard deviation of each time series within tss.
 */
void standard_deviation(double *tss, long *tss_l, long *tss_n, double *result);

/**
 * @brief Calculates the sum of all data points, that are present in the time series more than once.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_l Time series length (All time series need to have the same length).
 * @param tss_n Number of time series.
 * @param is_sorted Indicates if the input time series is sorted or not. Defaults to false.
 * @param result Returns the sum of all data points, that are present in the time series more than once.
 */
void sum_of_reoccurring_datapoints(double *tss, long *tss_l, long *tss_n, bool *is_sorted, double *result);

/**
 * @brief Calculates if the distribution of tss *looks symmetric*. This is the case if
 * \f[
 *      | mean(tss)-median(tss)| < r * (max(tss)-min(tss))
 * \f]
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_l Time series length (All time series need to have the same length).
 * @param tss_n Number of time series.
 * @param r The percentage of the range to compare with.
 * @param result An array denoting if the input time series look symmetric.
 */
void symmetry_looking(double *tss, long *tss_l, long *tss_n, double *r, bool *result);

/**
 * @brief Counts occurrences of value in the time series tss.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_l Time series length (All time series need to have the same length).
 * @param tss_n Number of time series.
 * @param v The value to be counted.
 * @param result An array containing the count of the given value in each time series.
 */
void value_count(int *tss, long *tss_l, long *tss_n, double *v, int *result);

#ifdef __cplusplus
}
#endif
};  // namespace features
};  // namespace tsa