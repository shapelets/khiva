// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <jni.h>
#include <khiva_jni/defines.h>

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
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_absEnergy(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Calculates the sum over the absolute value of consecutive changes in the time series.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same)
 * and dimension one indicates the number of time series.
 * @return Updated ref and the reference to an array with the same dimensions as the ref array, whose values (time
 * series in dimension 0) contains absolute value of consecutive changes in the time series.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_absoluteSumOfChanges(JNIEnv *env, jobject, jlong ref);

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
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_aggregatedAutocorrelation(JNIEnv *env, jobject, jlong ref,
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
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_aggregatedLinearTrend(JNIEnv *env, jobject, jlong ref,
                                                                                    jlong chunkSize,
                                                                                    jint aggregationFunction);

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
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_approximateEntropy(JNIEnv *env, jobject, jlong ref,
                                                                                 jint m, jfloat r);

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
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_crossCovariance(JNIEnv *env, jobject, jlong ref_xss,
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
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_autoCovariance(JNIEnv *env, jobject, jlong ref,
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
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_crossCorrelation(JNIEnv *env, jobject, jlong ref_xss,
                                                                               jlong ref_yss, jboolean unbiased);

/**
 * @brief Calculates the autocorrelation of the specified lag for the given time series.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param maxLag The maximum lag to compute.
 * @param unbiased Determines whether it divides by n - lag (if true) or n (if false).
 * @return The updated ref and the autocorrelation value for the given time series.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_autoCorrelation(JNIEnv *env, jobject, jlong ref,
                                                                              jlong maxLag, jboolean unbiased);
/**
 * @brief Calculates the binned entropy for the given time series and number of bins.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param max_bins The number of bins.
 * @return The updated ref and the binned entropy value for the given time series.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_binnedEntropy(JNIEnv *env, jobject, jlong ref,
                                                                            jint max_bins);

/**
 * @brief Calculates the Schreiber, T. and Schmitz, A. (1997) measure of non-linearity
 * for the given time series.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param lag The lag.
 * @return The updated ref and the non-linearity value for the given time series.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_c3(JNIEnv *env, jobject, jlong ref, jlong lag);

/**
 * @brief Calculates an estimate for the time series complexity defined by Batista, Gustavo EAPA, et al (2014). (A more
 * complex time series has more peaks, valleys, etc.).
 *
 * @param ref Expects an input array whose dimension zero is the length of the timeseries (all the same) and dimension
 * one indicates the number of time series.
 * @param zNormalize Controls whether the time series should be z-normalized or not.
 * @return The updated ref and the complexity value for the given time series.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_cidCe(JNIEnv *env, jobject, jlong ref,
                                                                    jboolean zNormalize);

/**
 * @brief Calculates the number of values in the time series that are higher than the mean.
 *
 * @param ref Expects an input array whose dimension zero is the length of the timeseries (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the number of values in the time series that are higher
 * than the mean.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_countAboveMean(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Calculates the number of values in the time series that are lower than the mean.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the number of values in the time series that are lower than the mean.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_countBelowMean(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Calculates a Continuous wavelet transform for the Ricker wavelet, also known as
 * the "Mexican hat wavelet" which is defined by:
 *
 *  \f[
 *      \frac{2}{\sqrt{3a} \pi^{
 *  \frac{1} { 4 }}} (1 - \frac{x^2}{a^2}) exp(-\frac{x^2}{2a^2})
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
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_cwtCoefficients(JNIEnv *env, jobject, jlong ref,
                                                                              jlong ref_w, jint coeff, jint w);

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
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_energyRatioByChunks(JNIEnv *env, jobject, jlong ref,
                                                                                  jlong numSegments,
                                                                                  jlong segmentFocus);

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
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_fftAggregated(JNIEnv *env, jobject, jlong ref);

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
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_fftCoefficient(JNIEnv *env, jobject, jlong ref,
                                                                             jlong coefficient);

/**
 * @brief Calculates the first relative location of the maximal value for each time series.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the first relative location of the maximum value to the length of the time series,
 *  for each time series.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_firstLocationOfMaximum(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Calculates the first location of the minimal value of each time series. The position
 * is calculated relatively to the length of the series.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the first relative location of the minimal value of each series.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_firstLocationOfMinimum(JNIEnv *env, jobject, jlong ref);

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
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same)
 * and dimension one indicates the number of time series.
 * @param m Order of polynom to fit for estimating fixed points of dynamics.
 * @param r Number of quantils to use for averaging.
 * @return The updated ref and the coefficients for each time series.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_friedrichCoefficients(JNIEnv *env, jobject, jlong ref,
                                                                                    jint m, jfloat r);

/**
 * @brief Calculates if the input time series contain duplicated elements.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the array containing True if the time series contains duplicated elements
 * and false otherwise.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_hasDuplicates(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Calculates if the maximum within input time series is duplicated.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and an array containing True if the maximum value of the time series is duplicated
 * and false otherwise.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_hasDuplicateMax(JNIEnv *env, jobject, jlong ref);
/**
 * @brief Calculates if the minimum of the input time series is duplicated
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the array containing True if the minimum of the time series is duplicated
 * and false otherwise.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_hasDuplicateMin(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Calculates the index of the max quantile.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param q The quantile.
 * @return The updated ref and the index of the max quantile q.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_indexMassQuantile(JNIEnv *env, jobject, jlong ref,
                                                                                jfloat q);

/**
 * @brief Returns the kurtosis of ref (calculated with the adjusted Fisher-Pearson
 * standardized moment coefficient G2).
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the kurtosis of each time series.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_kurtosis(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Checks if the time series within ref have a large standard deviation.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param r The threshold.
 * @return  The updated ref and an array containing True for those time series in ref that have a large standard
 * deviation.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_largeStandardDeviation(JNIEnv *env, jobject, jlong ref,
                                                                                     jfloat r);

/**
 * @brief Calculates the last location of the maximum value of each time series. The position
 * is calculated relatively to the length of the series.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the last relative location of the maximum value of each series.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_lastLocationOfMaximum(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Calculates the last location of the minimum value of each time series. The position
 * is calculated relatively to the length of the series.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the last relative location of the minimum value of each time series.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_lastLocationOfMinimum(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Returns the length of the input time series.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the length of ref.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_length(JNIEnv *env, jobject, jlong ref);

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
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_linearTrend(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Calculates all Local Maximals fot the time series in ref.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same)
 * and dimension one indicates the number of time series.
 * @return The updated ref and the calculated local maximals for each time series in array.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_localMaximals(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Calculates the length of the longest consecutive subsequence in ref that is bigger than the mean of ref.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @return The updated ref and the length of the longest consecutive subsequence in the input time series that is
 * bigger than the mean.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_longestStrikeAboveMean(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Calculates the length of the longest consecutive subsequence in ref that is below the mean of ref.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the length of the longest consecutive subsequence in the input time series that is below
 * the mean.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_longestStrikeBelowMean(JNIEnv *env, jobject, jlong ref);

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
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_maxLangevinFixedPoint(JNIEnv *env, jobject, jlong ref,
                                                                                    jint m, jfloat r);

/**
 * @brief Calculates the maximum value for each time series within ref.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the maximum value of each time series within ref.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_maximum(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Calculates the mean value for each time series within ref.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the mean value of each time series within ref.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_mean(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Calculates the mean over the absolute differences between subsequent time series values in ref.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the maximum value of each time series within ref.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_meanAbsoluteChange(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Calculates the mean over the differences between subsequent time series values in ref.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the mean over the differences between subsequent time series values.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_meanChange(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Calculates mean value of a central approximation of the second derivative for each time series in ref.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the mean value of a central approximation of the second derivative for each time series.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_meanSecondDerivativeCentral(JNIEnv *env, jobject,
                                                                                          jlong ref);

/**
 * @brief Calculates the median value for each time series within ref.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the median value of each time series within ref.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_median(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Calculates the minimum value for each time series within ref.
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the minimum value of each time series within ref.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_minimum(JNIEnv *env, jobject, jlong ref);

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
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_numberCrossingM(JNIEnv *env, jobject, jlong ref, jint m);

/**
 * @brief This feature calculator searches for different peaks. To do so, the time series is smoothed by a ricker
 * wavelet and for widths ranging from 1 to maxW. This feature calculator returns the number of peaks that occur at
 * enough width scales and with sufficiently high Signal-to-Noise-Ratio (SNR).
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same)
 * and dimension one indicates the number of time series.
 * @param maxW The maximum width to consider.
 * @return The updated ref and the number of peaks for each time series.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_numberCwtPeaks(JNIEnv *env, jobject, jlong ref,
                                                                             jint maxW);

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
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_numberPeaks(JNIEnv *env, jobject, jlong ref, jint n);

/**
* @brief Calculates the value of the partial autocorrelation function at the given lag. The lag \f$k\f$ partial
* autocorrelation of a time series \f$\lbrace x_t, t = 1 \ldots T \rbrace\f$ equals the partial correlation of
\f$x_t\f$ and \f$x_{t-k}\f$, adjusted for the intermediate variables \f$\lbrace x_{t-1}, \ldots, x_{t-k+1}
\rbrace\f$ ([1]). Following [2], it can be defined as:
*
* \f[
\alpha_k = \frac{ Cov(x_t, x_{t-k} | x_{t-1}, \ldots, x_{t-k+1})}
{\sqrt{ Var(x_t | x_{t-1}, \ldots, x_{t-k+1}) Var(x_{t-k} | x_{t-1}, \ldots, x_{t-k+1} )}}
* \f]
* with (a) \f$x_t = f(x_{t-1}, \ldots, x_{t-k+1})\f$ and (b) \f$ x_{t-k} = f(x_{t-1}, \ldots, x_{t-k+1})\f$
being AR(k-1) models that can be fitted by OLS. Be aware that in (a), the regression is done on past values to
predict \f$ x_t \f$ whereas in (b), future values are used to calculate the past value \f$x_{t-k}\f$.
It is said in [1] that "for an AR(p), the partial autocorrelations \f$ \alpha_k \f$ will be nonzero for \f$ k<=p \f$
and zero for \f$ k>p \f$."
* With this property, it is used to determine the lag of an AR-Process.
*
* [1] Box, G. E., Jenkins, G. M., Reinsel, G. C., & Ljung, G. M. (2015).
* Time series analysis: forecasting and control. John Wiley & Sons.
* [2] https://onlinecourses.science.psu.edu/stat510/node/62
*
* @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
* one indicates the number of time series.
* @param lags Indicates the lags to be calculated.
* @return The updated refs and the partial autocorrelation for each time series for the given lag.
*/
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_partialAutocorrelation(JNIEnv *env, jobject, jlong ref,
                                                                                     jlong lags);

/**
 * @brief Calculates the percentage of unique values, that are present in the time series more than once.
 * \f[
 *      len(different values occurring more than once) / len(different values)
 * \f]
 * This means the percentage is normalized to the number of unique values, in contrast to the
 * Java_io_shapelets_khiva_Features_percentageOfReoccurringValuesToAllValues.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param isSorted Indicates if the input time series is sorted or not. Defaults to false.
 * @return The updated ref and the percentage of unique values, that are present in the time series more than
 * once.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_percentageOfReoccurringDatapointsToAllDatapoints(
    JNIEnv *env, jobject, jlong ref, jboolean isSorted);

/**
 * @brief Calculates the percentage of unique values, that are present in the time series more than once.
 * \f[
 *      \frac{\textit{number of data points occurring more than once}}{\textit{number of all data points})}
 * \f]
 * This means the percentage is normalized to the number of unique values, in contrast to the
 * Java_io_shapelets_khiva_Features_percentageOfReoccurringDatapointsToAllDatapoints.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same)
 * and dimension one indicates the number of time series.
 * @param isSorted Indicates if the input time series is sorted or not. Defaults to false.
 * @return The updated ref and the percentage of unique values, that are present in the time series more than once.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_percentageOfReoccurringValuesToAllValues(
    JNIEnv *env, jobject, jlong ref, jboolean isSorted);

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
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_quantile(JNIEnv *env, jobject, jlong ref, jlong ref_q,
                                                                       jfloat precision);

/**
 * @brief Counts observed values within the interval [min, max).
 *
 * @param ref Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @param min Value that sets the lower limit.
 * @param max Value that sets the upper limit.
 * @return The updated ref and the values at the given range.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_rangeCount(JNIEnv *env, jobject, jlong ref, jfloat min,
                                                                         jfloat max);

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
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_ratioBeyondRSigma(JNIEnv *env, jobject, jlong ref,
                                                                                jfloat r);

/**
 * @brief Calculates a factor which is 1 if all values in the time series occur only once, and below one if this is
 * not the case. In principle, it just returns:
 *
 * \f[
 *      \frac{\textit{number\_unique\_values}}{\textit{number\_values}}
 * \f]
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @return The updated ref and the ratio of unique values with respect to the total number of values.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_ratioValueNumberToTimeSeriesLength(JNIEnv *env, jobject,
                                                                                                 jlong ref);

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
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_sampleEntropy(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Calculates the sample skewness of ref (calculated with the adjusted Fisher-Pearson standardized
 * moment coefficient G1).
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and an array containing the skewness of each time series in ref.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_skewness(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Estimates the cross power spectral density of the time series ref at different frequencies. To do so, the
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
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @param coeff The coefficient to be returned.
 * @return The updated ref and the power spectrum of the different
 * frequencies for each time series in ref.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_spktWelchDensity(JNIEnv *env, jobject, jlong ref,
                                                                               jint coeff);

/**
 * @brief Calculates the standard deviation of each time series within ref.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and the standard deviation of each time series within ref.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_standardDeviation(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Calculates the sum of all data points, that are present in the time series more than once.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param isSorted Indicates if the input time series is sorted or not. Defaults to false.
 * @return The updated ref and the sum of all data points, that are present in the time series more than once.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_sumOfReoccurringDatapoints(JNIEnv *env, jobject,
                                                                                         jlong ref, jboolean isSorted);

/**
 * @brief Calculates the sum of all values, that are present in the time series more than once.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same)
 * and dimension one indicates the number of time series.
 * @param isSorted Indicates if the input time series is sorted or not. Defaults to false.
 * @return The updated ref and the sum of all values, that are present in the time series more than once.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_sumOfReoccurringValues(JNIEnv *env, jobject, jlong ref,
                                                                                     jboolean isSorted);

/**
 * @brief Calculates the sum over the time series ref.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @return The updated ref and an array containing the sum of values in each time series.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_sumValues(JNIEnv *env, jobject, jlong ref);

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
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_symmetryLooking(JNIEnv *env, jobject, jlong ref,
                                                                              jfloat r);

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
 *  feature to extract from time series.
 *
 * [1] Fulcher, B.D., Jones, N.S. (2014). Highly comparative feature-based time-series classification.
 * Knowledge and Data Engineering, IEEE Transactions on 26, 3026–3037.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @param lag The lag to be computed.
 * @return The updated ref and an array containing the time reversal asymetry statistic value in each time series.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_timeReversalAsymmetryStatistic(JNIEnv *env, jobject,
                                                                                             jlong ref, jint lag);

/**
 * @brief Counts occurrences of value in the time series ref.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param v The value to be counted.
 * @return The updated ref and an array containing the count of the given value in each time series.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_valueCount(JNIEnv *env, jobject, jlong ref, jfloat v);

/**
 * @brief Computes the variance for the time series ref.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @return The updated ref and an array containing the variance in each time series.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_variance(JNIEnv *env, jobject, jlong ref);

/**
 * @brief Calculates if the variance of ref is greater than the standard deviation. In other words, if the variance of
 * ref is larger than 1.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @return The updated ref and an array denoting if the variance of ref is greater than the standard deviation.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Features_varianceLargerThanStandardDeviation(JNIEnv *env, jobject,
                                                                                                  jlong ref);
#ifdef __cplusplus
}
#endif
