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
 * @brief Calculates the sum over the square values of the time series.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of time series.
 * @return Updated ref and the Absolute Energy Array reference.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_absEnergy(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Calculates the sum over the absolute value of consecutive changes in the time series.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same)
 * and dimension one indicates the number of time series.
 * @return Updated ref and the reference to an array with the same dimensions as the ref array, whose values (time
 * series in dimension 0) contains absolute value of consecutive changes in the time series.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_absoluteSumOfChanges(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Calculates the value of an aggregation function f_agg (e.g. var or mean) of the autocorrelation
 * (Compare to http://en.wikipedia.org/wiki/Autocorrelation#Estimation), taken over different all possible
 * lags (1 to length of x).
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param aggregationFunction Function to be used in the aggregation. It receives an integer which indicates the
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
 * @return Updated reference and an array whose values contains the aggregated correaltion for each time series.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_aggregatedAutocorrelation(JNIEnv *env, jobject thisObj, jlong ref,
                                                                         jint aggregationFunction);

/**
 * @brief Calculates a linear least-squares regression for values of the time series that were aggregated
 * over chunks versus the sequence from 0 up to the number of chunks minus one.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param chunkSize The chunkSize used to aggregate the data
 * @param aggregationFunction Function to be used in the aggregation. It receives an integer which indicates the
 * function to be applied:
 *          {
 *              0 : mean,
 *              1 : median
 *              2 : min,
 *              3 : max,
 *              4 : stdev,
 *              default : mean
 *          }
 * @return The updated ref and references to:
 *         {
 *             slope Slope of the regression line
 *             intercept Intercept of the regression line
 *             rvalue Correlation coefficient
 *             pvalue Two-sided p-value for a hypothesis test whose null hypothesis is
 *                   that the slope is zero, using Wald Test with t-distribution of
 *                   the test statistic
 *             stderrest Standard error of the estimated gradient
 *         }
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_aggregatedLinearTrend(JNIEnv *env, jobject thisObj, jlong ref,
                                                                     jlong chunkSize, jint aggregationFunction);

/**
 * @brief Calculates a vectorized Approximate entropy algorithm.
 * https://en.wikipedia.org/wiki/Approximate_entropy
 * For short time series this method is highly dependent on the parameters, but should be stable for N > 2000,
 * see: Yentes et al. (2012) - The Appropriate Use of Approximate Entropy and Sample Entropy with Short Data Sets
 * Other shortcomings and alternatives discussed in:
 * Richman & Moorman (2000) - Physiological time-series analysis using approximate entropy and sample entropy.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param m Length of compared run of data.
 * @param r Filtering level, must be positive.
 * @return The updated ref and the vectorized approximate entropy for all the input time series in ref Array.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_approximateEntropy(JNIEnv *env, jobject thisObj, jlong ref, jint m,
                                                                  jdouble r);

/**
 * @brief Calculates the cross-covariance of the given time series.
 *
 * @param ref_xss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of time series.
 * @param ref_yss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @param unbiased Determines whether it divides by n - lag (if true) or
 * n (if false).
 * @return The updated refs and the cross-covariance value for the given time series.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_crossCovariance(JNIEnv *env, jobject thisObj, jlong ref_xss,
                                                               jlong ref_yss, jboolean unbiased);

/**
 * @brief Calculates the auto-covariance the given time series.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of time series.
 * @param unbiased Determines whether it divides by n - lag (if true) or
 * n (if false).
 * @return The updated ref and the auto-covariance value for the given time series.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_autoCovariance(JNIEnv *env, jobject thisObj, jlong ref,
                                                              jboolean unbiased);

/**
 * @brief Calculates the cross-correlation of the given time series.
 *
 * @param ref_xss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @param ref_yss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @param unbiased Determines whether it divides by n - lag (if true) or n (if false).
 * @return The updated refs and the cross-correlation value for the given time series.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_crossCorrelation(JNIEnv *env, jobject thisObj, jlong ref_xss,
                                                                jlong ref_yss, jboolean unbiased);

/**
 * @brief Calculates the autocorrelation of the specified lag for the given time series.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param maxLag The maximum lag to compute.
 * @param unbiased Determines whether it divides by n - lag (if true) or n ( if false)
 * @return The updated ref and the autocorrelation value for the given time series.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_autoCorrelation(JNIEnv *env, jobject thisObj, jlong ref, jlong maxLag,
                                                               jboolean unbiased);
/**
 * @brief Calculates the binned entropy for the given time series and number of bins.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param max_bins The number of bins.
 * @return The updated ref and the binned entropy value for the given time series.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_binnedEntropy(JNIEnv *env, jobject thisObj, jlong ref, jint max_bins);

/**
 * @brief Calculates the Schreiber, T. and Schmitz, A. (1997) measure of non-linearity
 * for the given time series.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param lag The lag
 * @return The updated ref and the non-linearity value for the given time series.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_c3(JNIEnv *env, jobject thisObj, jlong ref, jlong lag);

/**
 * @brief Calculates an estimate for the time series complexity defined by Batista, Gustavo EAPA, et al (2014). (A more
 * complex time series has more peaks, valleys, etc.).
 *
 * @param ref Expects an input array whose dimension zero is the length of the timeseries (all the same) and dimension
 * one indicates the number of time series.
 * @param zNormalize Controls whether the time series should be z-normalized or not.
 * @return The updated ref and the complexity value for the given time series.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_cidCe(JNIEnv *env, jobject thisObj, jlong ref, jboolean zNormalize);

/**
 * @brief Calculates the number of values in the time series that are higher than the mean.
 *
 * @param ref Expects an input array whose dimension zero is the length of the timeseries (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the number of values in the time series that are higher
 * than the mean.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_countAboveMean(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Calculates the number of values in the time series that are lower than the mean.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the number of values in the time series that are lower than the mean.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_countBelowMean(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Calculates a Continuous wavelet transform for the Ricker wavelet, also known as
 * the "Mexican hat wavelet" which is defined by:
 *
 *  \f[
 *      \\frac{2}{\\sqrt{3a} \\pi^{
 *  \\frac{1} { 4 }}} (1 - \\frac{x^2}{a^2}) exp(-\\frac{x^2}{2a^2})
 *  \f]
 *
 *  where :math:`a` is the width parameter of the wavelet function.
 *
 * This feature calculator takes three different parameter: widths, coeff and w. The feature calculator takes all
 * the different widths arrays and then calculates the cwt one time for each different width array. Then the values
 * for the different coefficient for coeff and width w are returned. (For each dic in param one feature is
 * returned).
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param ref_w Array that contains all different widths.
 * @param coeff Coefficient of interest.
 * @param w Width of interest.
 * @return Updated refs and the result of calculated coefficients.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_cwtCoefficients(JNIEnv *env, jobject thisObj, jlong ref, jlong ref_w,
                                                               jint coeff, jint w);

/**
 * @brief Calculates the sum of squares of chunk i out of N chunks expressed as a ratio
 * with the sum of squares over the whole series. segmentFocus should be lower
 * than the number of segments.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param numSegments The number of segments to divide the series into.
 * @param segmentFocus The segment number (starting at zero) to return a feature on.
 * @return The updated ref and the energy ratio by chunk of the time series.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_energyRatioByChunks(JNIEnv *env, jobject thisObj, jlong ref,
                                                                   jlong numSegments, jlong segmentFocus);

/**
 * @brief Calculates the spectral centroid(mean), variance, skew, and kurtosis of the absolute fourier transform
 * spectrum.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return  The updated ref and references to:
 *              {
 *                  mean the spectral centroid (mean).
 *                  variance The ref variance.
 *                  skew The ref skew.
 *                  kurtosis kurtosis of the absolute fourier transform spectrum.
 *              }
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_fftAggregated(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Calculates the fourier coefficients of the one-dimensional discrete
 * Fourier Transform for real input by fast fourier transformation algorithm.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and refs to:
 *          {
 *              coefficient The coefficient to extract from the FFT.
 *              real The real part of the coefficient.
 *              imag The imaginary part of the cofficient.
 *              absolute The absolute value of the coefficient.
 *              angle The angle of the coefficient.
 *          }
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_fftCoefficient(JNIEnv *env, jobject thisObj, jlong ref,
                                                              jlong coefficient);

/**
 * @brief Calculates the first relative location of the maximal value for each time series.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the first relative location of the maximum value to the length of the time series,
 *  for each time series.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_firstLocationOfMaximum(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Calculates the first location of the minimal value of each time series. The position
 * is calculated relatively to the length of the series.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the first relative location of the minimal value of each series.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_firstLocationOfMinimum(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Calculates if the input time series contain duplicated elements.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the array containing True if the time series contains duplicated elements
 * and false otherwise.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_hasDuplicates(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Calculates if the maximum within input time series is duplicated.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and an array containing True if the maximum value of the time series is duplicated
 * and false otherwise.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_hasDuplicateMax(JNIEnv *env, jobject thisObj, jlong ref);
/**
 * @brief Calculates if the minimum of the input time series is duplicated
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the array containing True if the minimum of the time series is duplicated
 * and false otherwise.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_hasDuplicateMin(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Calculates the index of the max quantile.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param q The quantile.
 * @return The updated ref and the index of the max quantile q.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_indexMaxQuantile(JNIEnv *env, jobject thisObj, jlong ref, jfloat q);

/**
 * @brief Returns the kurtosis of ref (calculated with the adjusted Fisher-Pearson
 * standardized moment coefficient G2).
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the kurtosis of each time series.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_kurtosis(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Checks if the time series within ref have a large standard deviation.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param r The threshold.
 * @return  The updated ref and an array containing True for those time series in ref that have a large standard
 * deviation.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_largeStandardDeviation(JNIEnv *env, jobject thisObj, jlong ref,
                                                                      jfloat r);

/**
 * @brief Calculates the last location of the maximum value of each time series. The position
 * is calculated relatively to the length of the series.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the last relative location of the maximum value of each series.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_lastLocationOfMaximum(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Calculates the last location of the minimum value of each time series. The position
 * is calculated relatively to the length of the series.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the last relative location of the minimum value of each series.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_lastLocationOfMinimum(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Returns the length of the input time series.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return THe updated ref and the length of ref.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_length(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Calculates a linear least-squares regression for the values of the time series versus the sequence from 0 to
 * length of the time series minus one.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the referentces to:
 *
 *              {
 *                  pvalue The pvalues for all time series.
 *                  rvalue The rvalues for all time series.
 *                  intercept The intercept values for all time series.
 *                  slope The slope for all time series.
 *                  stdrr The stderr values for all time series.
 *              }
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_linearTrend(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Calculates the length of the longest consecutive subsequence in ref that is bigger than the mean of ref.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the length of the longest consecutive subsequence in the input time series that is bigger
 * than the mean.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_longestStrikeAboveMean(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Calculates the length of the longest consecutive subsequence in ref that is below the mean of ref.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the length of the longest consecutive subsequence in the input time series that is below
 * the mean.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_longestStrikeBelowMean(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Computes the Largest fixed point of dynamics \f$\max_x {h(x)=0}\f$ estimated from polynomial
 * \f$h(x)\f$, which has been fitted to the deterministic dynamics of Langevin model
 * \f[
 *    \dot(x)(t) = h(x(t)) + R \mathcal(N)(0,1)
 * \f]
 * as described by
 * Friedrich et al. (2000): Physics Letters A 271, p. 217-222 *Extracting model equations from experimental data*
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param m Order of polynom to fit for estimating fixed points of dynamics.
 * @param r Number of quantiles to use for averaging.
 * @return The updated ref and the largest fixed point of deterministic dynamics.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_maxLangevinFixedPoint(JNIEnv *env, jobject thisObj, jlong ref, jint m,
                                                                     jfloat r);

/**
 * @brief Calculates the maximum value for each time series within ref.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the maximum value of each time series within ref.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_maximum(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Calculates the mean value for each time series within ref.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the mean value of each time series within ref.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_mean(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Calculates the mean over the absolute differences between subsequent time series values in ref.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the maximum value of each time series within ref.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_meanAbsoluteChange(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Calculates the mean over the differences between subsequent time series values in ref.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the mean over the differences between subsequent time series values.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_meanChange(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Calculates mean value of a central approximation of the second derivative for each time series in ref.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the mean value of a central approximation of the second derivative for each time series.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_meanSecondDerivativeCentral(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Calculates the median value for each time series within ref.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the median value of each time series within ref.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_median(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Calculates the minimum value for each time series within ref.
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the minimum value of each time series within ref.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_minimum(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Calculates the number of m-crossings. A m-crossing is defined as two sequential values where the first
 * value is lower than m and the next is greater, or viceversa. If you set m to zero, you will get the number of
 * zero crossings.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param m The m value.
 * @return The updated ref and the number of m-crossings of each time series within ref.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_numberCrossingM(JNIEnv *env, jobject thisObj, jlong ref, jint m);

/**
 * @brief Calculates the number of peaks of at least support \f$n\f$ in the time series \f$ref\f$. A peak of support
 * \f$n\f$ is defined as a subsequence of \f$ref\f$ where a value occurs, which is bigger than its \f$n\f$ neighbours to
 * the left and to the right.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param n The support of the peak.
 * @return The updated ref and the number of peaks of at least support \f$n\f$.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_numberPeaks(JNIEnv *env, jobject thisObj, jlong ref, jint n);

/**
 * @brief Calculates the percentage of unique values, that are present in the time series more than once.
 * \f[
 *      len(different values occurring more than once) / len(different values)
 * \f]
 * This means the percentage is normalized to the number of unique values, in contrast to the
 * percentageOfReoccurringValuesToAllValues.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param isSorted Indicates if the input time series is sorted or not. Defaults to false.
 * @return The updated ref and the percentage of unique values, that are present in the time series more than
 * once.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_percentageOfReoccurringDatapointsToAllDatapoints(JNIEnv *env,
                                                                                                jobject thisObj,
                                                                                                jlong ref,
                                                                                                jboolean isSorted);

/**
 * @brief Returns values at the given quantile.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param q Percentile(s) at which to extract score(s). One or many.
 * @param qL Number of percentiles.
 * @param precision Number of decimals expected.
 * @return The updated ref and the values at the given quantile.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_quantile(JNIEnv *env, jobject thisObj, jlong ref, jlong ref_q,
                                                        jfloat precision);

/**
 * @brief Calculates the ratio of values that are more than \f$r*std(x)\f$ (so \f$r\f$ sigma) away from the mean of
 * \f$x\f$.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param r Number of times that the values should be away from.
 * @return The updated ref and the ratio of values that are more than \f$r*std(x)\f$ (so \f$r\f$ sigma) away from
 * the mean of \f$x\f$.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_ratioBeyondRSigma(JNIEnv *env, jobject thisObj, jlong ref, jfloat r);
/**
 * @brief Calculates a vectorized sample entropy algorithm.
 * https://en.wikipedia.org/wiki/Sample_entropy
 * https://www.ncbi.nlm.nih.gov/pubmed/10843903?dopt=Abstract
 * For short time-series this method is highly dependent on the parameters, but should be stable for N > 2000,
 * see: Yentes et al. (2012) - The Appropriate Use of Approximate Entropy and Sample Entropy with Short Data Sets
 * Other shortcomings and alternatives discussed in:
 * Richman & Moorman (2000) - Physiological time-series analysis using approximate entropy and sample entropy.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and an array with the same dimensions as ref, whose values (time series in dimension
 * 0) contains the vectorized sample entropy for all the input time series in ref.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_sampleEntropy(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Calculates the sample skewness of ref (calculated with the adjusted Fisher-Pearson standardized
 * moment coefficient G1).
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and an array containing the skewness of each time series in ref.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_skewness(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Calculates the standard deviation of each time series within ref.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the standard deviation of each time series within ref.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_standardDeviation(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Calculates the sum of all data points, that are present in the time series more than once.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param isSorted Indicates if the input time series is sorted or not. Defaults to false.
 * @return The updated ref and the sum of all data points, that are present in the time series more than once.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_sumOfReoccurringDatapoints(JNIEnv *env, jobject thisObj, jlong ref,
                                                                          jboolean isSorted);

/**
 * @brief Calculates if the distribution of ref *looks symmetric*. This is the case if
 * \f[
 *      | mean(ref)-median(ref)| < r * (max(ref)-min(ref))
 * \f]
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param r The percentage of the range to compare with.
 * @return The updated ref and an array denoting if the input time series look symmetric.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_symmetryLooking(JNIEnv *env, jobject thisObj, jlong ref, jfloat r);

/**
 * @brief Counts occurrences of value in the time series ref.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param v The value to be counted.
 * @return The updated ref and an array containing the count of the given value in each time series.
 */
JNIEXPORT jlongArray JNICALL Java_tsa_Features_valueCount(JNIEnv *env, jobject thisObj, jlong ref, jfloat v);
#ifdef __cplusplus
}
#endif
