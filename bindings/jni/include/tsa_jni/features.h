// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <jni.h>

namespace tsa {

namespace features {

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief JNI interfsce of the crossCorrelation function.
 *
 * @param xss Time series concatenated in a single row.
 * @param xss_length Time series length (All time series need to have the same length).
 * @param xssNumberOfTss Number of time series.
 * @param yss Time series concatenated in a single row.
 * @param yssLength  yss time series length.
 * @param yssNumberOfTss yss Number of time series.
 * @param unbiased Determines whether it divides by n - lag (if true) or
 * n (if false).
 * @param result The cross-correlation value for the given time series.
 */
JNIEXPORT void JNICALL Java_tsa_Features_crossCorrelation(JNIEnv *env, jobject thisObj, jdoubleArray xss,
                                                          jlong xssLength, jlong xssNumberOfTss, jdoubleArray yss,
                                                          jlong yssLength, jlong yssNumberOfTss, jboolean unbiased,
                                                          jdoubleArray result);

/**
 * @brief JNI interface of the autoCovariance function.
 *
 * @param xss Time series concatenated in a single row.
 * @param xssLength Time series length (All time series need to have the same length).
 * @param xssNumberOfTss Number of time series.
 * @param unbiased Determines whether it divides by n - lag (if true) or
 * n (if false).
 * @param result The auto-covariance value for the given time series.
 */
JNIEXPORT void JNICALL Java_tsa_Features_autoCovariance(JNIEnv *env, jobject thisObj, jdoubleArray xss, jlong xssLength,
                                                        jlong xssNumberOfTss, jboolean unbiased, jdoubleArray result);

/**
 * @brief JNI interface of the crossCovariance function.
 *
 * @param xss Time series concatenated in a single row.
 * @param xssLength xss Time series length (All time series need to have the same length).
 * @param xssNumberOfTss Number of time series in xss.
 * @param yss Time series concatenated in a single row.
 * @param yssLength yss Time series length.
 * @param yssNumberOfTss Number of time series in yss.
 * @param unbiased Determines whether it divides by n - lag (if true) or
 * n (if false).
 * @result The cross-covariance value for the given time series.
 */
JNIEXPORT void JNICALL Java_tsa_Features_crossCovariance(JNIEnv *env, jobject thisObj, jdoubleArray xss,
                                                         jlong xssLength, jlong xssNumberOfTss, jdoubleArray yss,
                                                         jlong yssLength, jlong yssNumberOfTss, jboolean unbiased,
                                                         jdoubleArray result);
/**
 * @brief JNI interface of the aproximateEntropy function.
 *
 * @param tss Time series concatenated in a single row.
 * @param tssLength Time series length (All time series need to have the same length).
 * @param tssNumberOfTss Number of time series.
 * @param m Length of compared run of data.
 * @param r Filtering level, must be positive.
 * @param result The vectorized approximate entropy for all the input time series in tss.
 */
JNIEXPORT void JNICALL Java_tsa_Features_approximateEntropy(JNIEnv *env, jobject thisObj, jdoubleArray tss,
                                                            jlong tssLength, jlong tssNumberOfTss, jint m, jdouble r,
                                                            jdoubleArray result);

/**
 * @brief JNI interface of the c3 function.
 *
 * @param tss Time series concatenated in a single row.
 * @param tssLength Time series length (All time series need to have the same length).
 * @param tssNumberOfTss Number of time series.
 * @param lag The lag
 * @param result The non-linearity value for the given time series.
 */
JNIEXPORT void JNICALL Java_tsa_Features_c3(JNIEnv *env, jobject thisObj, jdoubleArray tss, jlong tssLength,
                                            jlong tssNumberOfTss, jlong lag, jdoubleArray result);

/**
 * @brief JNI interface of the cidCe function.
 *
 * @param tss Time series concatenated in a single row.
 * @param tssLength tss length (All time series need to have the same length).
 * @param tssNumberOfTss Number of time series in tss.
 * @param zNormalize Controls whether the time series should be z-normalized or not.
 * @param result The complexity value for the given time series.
 */
JNIEXPORT void JNICALL Java_tsa_Features_cidCe(JNIEnv *env, jobject thisObj, jdoubleArray tss, jlong tssLength,
                                               jlong tssNumberOfTss, jboolean zNormalize, jdoubleArray result);

/**
 * @brief JNI interface of the absoluteSumOfChanges function.
 *
 * @param timeSeries  Time series concatenated in a single row.
 * @param timeSeriesLength Length of each time series.
 * @param numberOfTimeSeries Number of time series into timeSeries.
 * @param jResult Absolute sum of changes.
 */
JNIEXPORT void JNICALL Java_tsa_Features_absoluteSumOfChanges(JNIEnv *env, jobject thisObj, jdoubleArray timeSeries,
                                                              jlong timeSeriesLength, jlong numberOfTimeSeries,
                                                              jdoubleArray jResult);

/**
 * @brief JNI interface of the absEnergy function.
 *
 * @param timeSeries Time series concatenated in a single row.
 * @param timeSeriesLength Length of each time series.
 * @param numberOfTimeSeries Number of time series into timeSeries.
 * @param jResult Absolute Energy.
 */
JNIEXPORT void JNICALL Java_tsa_Features_absEnergy(JNIEnv *env, jobject thisObj, jdoubleArray timeSeries,
                                                   jlong timeSeriesLength, jlong numberOfTimeSeries,
                                                   jdoubleArray jResult);

/**
 * @brief JNI interface of the autoCorrelation function.
 *
 * @param tss Time series concatenated in a single row.
 * @param tssLength Time series length (All time series need to have the same length).
 * @param tssNumberOfTss Number of time series.
 * @param maxLag The maximum lag to compute.
 * @param unbiased Determines whether it divides by n - lag (if true) or n ( if false)
 * @param result The autocorrelation value for the given time series.
 */
JNIEXPORT void JNICALL Java_tsa_Features_autoCorrelation(JNIEnv *env, jobject thisObj, jdoubleArray tss,
                                                         jlong tssLength, jlong tssNumberOfTss, jlong maxLag,
                                                         jboolean unbiased, jdoubleArray result);

/**
 * @brief JNI interface of the binnedEntropy function.
 *
 * @param tss Time series concatenated in a single row.
 * @param tssLength Time series length (All time series need to have the same length).
 * @param tssNumberOfTss NUmber of time series.
 * @param max_bins The number of bins.
 * @param result The binned entropy value for the given time series.
 */
JNIEXPORT void JNICALL Java_tsa_Features_binnedEntropy(JNIEnv *env, jobject thisObj, jdoubleArray tss, jlong tssLength,
                                                       jlong tssNumberOfTss, jint max_bins, jdoubleArray result);

/**
 * @brief JNI interface of the countAboveMean function.
 *
 * @param tss Time series concatenated in a single row.
 * @param tssLength Time series length (All time series need to have the same length).
 * @param tssNumberOfTss NUmber of time series.
 * @param result The number of values in the time series that are higher
 * than the mean.
 */
JNIEXPORT void JNICALL Java_tsa_Features_countAboveMean(JNIEnv *env, jobject thisObj, jdoubleArray tss, jlong tssLength,
                                                        jlong tssNumberOfTss, jintArray result);

/**
 * @brief JNI interface of the countBelowMean function.
 *
 * @param tss Time series concatenated in a single row.
 * @param tssLength Time series length (All time series need to have the same length).
 * @param tssNumberOfTss Number of time series.
 * @param result The number of values in the time series that are lower
 * than the mean.
 */
JNIEXPORT void JNICALL Java_tsa_Features_countBelowMean(JNIEnv *env, jobject thisObj, jdoubleArray tss, jlong tssLength,
                                                        jlong tssNumberOfTss, jintArray result);

/**
 * @brief JNI interface of the energyRatioByChunks.
 *
 * @param tss Time series concatenated in a single row.
 * @param tssLength Time series length (All time series need to have the same length).
 * @param tssNumberOfTss Number of time series.
 * @param numSegments The number of segments to divide the series into.
 * @param segmentFocus The segment number (starting at zero) to return a feature on.
 * @param result The energy ratio by chunk of the time series.
 */
JNIEXPORT void JNICALL Java_tsa_Features_energyRatioByChunks(JNIEnv *env, jobject thisObj, jdoubleArray tss,
                                                             jlong tssLength, jlong tssNumberOfTss, jlong numSegments,
                                                             jlong segmentFocus, jdoubleArray result);

/**
 * @brief Calculates the first relative location of the maximal value for each time series.
 *
 * @param tss Time series concatenated in a single row.
 * @param tssLength Time series length (All time series need to have the same length).
 * @param tssNumberOfTss Number of time series.
 * @param result The first relative location of the maximum value to the length of the time series,
 *  for each time series.
 */
JNIEXPORT void JNICALL Java_tsa_Features_firstLocationOfMaximum(JNIEnv *env, jobject thisObj, jdoubleArray tss,
                                                                jlong tssLength, jlong tssNumberOfTss,
                                                                jdoubleArray result);
/**
 * @brief Calculates the first location of the minimal value of each time series. The position
 * is calculated relatively to the length of the series.
 *
 * @param tss Time series concatenated in a single row.
 * @param tssLength Time series length (All time series need to have the same length).
 * @param tssNumberOfTss Number of time series.
 * @param result The first relative location of the minimal value of each series.
 */
JNIEXPORT void JNICALL Java_tsa_Features_firstLocationOfMinimum(JNIEnv *env, jobject thisObj, jdoubleArray tss,
                                                                jlong tssLength, jlong tssNumberOfTss,
                                                                jdoubleArray result);

/**
 * @brief Calculates if the input time series contain duplicated elements.
 *
 * @param tss Time series concatenated in a single row.
 * @param tssLength Time series length (All time series need to have the same length).
 * @param tssNumberOfTss Number of time series.
 * @param result Array containing True if the time series contains duplicated elements
 * and false otherwise.
 */
JNIEXPORT void JNICALL Java_tsa_Features_hasDuplicates(JNIEnv *env, jobject thisObj, jdoubleArray tss, jlong tssLength,
                                                       jlong tssNumberOfTss, jdoubleArray result);

/**
 * @brief Calculates if the maximum within input time series is duplicated.
 *
 * @param tss Time series concatenated in a single row.
 * @param tssLength Time series length (All time series need to have the same length).
 * @param tssNumberOfTss Number of time series.
 * @param result Array containing True if the maximum value of the time series is duplicated
 * and false otherwise.
 */
JNIEXPORT void JNICALL Java_tsa_Features_hasDuplicateMax(JNIEnv *env, jobject thisObj, jbooleanArray tss,
                                                         jlong tssLength, jlong tssNumberOfTss, jbooleanArray result);

/**
 * @brief Calculates the index of the max quantile.
 *
 * @param tss Time series concatenated in a single row.
 * @param tssLength Time series length (All time series need to have the same length).
 * @param tssNumberOfTss Number of time series.
 * @param q The quantile.
 * @param result The index of the max quantile q.
 */
JNIEXPORT void JNICALL Java_tsa_Features_indexMaxQuantile(JNIEnv *env, jobject thisObj, jdoubleArray tss,
                                                          jlong tssLength, jlong tssNumberOfTss, jfloat q,
                                                          jdoubleArray result);

/**
 * @brief Returns the kurtosis of tss (calculated with the adjusted Fisher-Pearson
 * standardized moment coefficient G2).
 *
 * @param tss Time series concatenated in a single row.
 * @param tssLength Time series length (All time series need to have the same length).
 * @param tssNumberOfTss Number of time series.
 * @param result The kurtosis of each tss.
 */
JNIEXPORT void JNICALL Java_tsa_Features_kurtosis(JNIEnv *env, jobject thisObj, jdoubleArray tss, jlong tssLength,
                                                  jlong tssNumberOfTss, jdoubleArray result);

/**
 * @brief Checks if the time series within tss have a large standard deviation.
 *
 * @param tss Time series concatenated in a single row.
 * @param tssLength Time series length (All time series need to have the same length).
 * @param tssNumberOfTss Number of time series.
 * @param r The threshold.
 * @param result  Array containing True for those time series in tss that have a large standard deviation.
 */
JNIEXPORT void JNICALL Java_tsa_Features_largeStandardDeviation(JNIEnv *env, jobject thisObj, jdoubleArray tss,
                                                                jlong tssLength, jlong tssNumberOfTss, jfloat r,
                                                                jbooleanArray result);

/**
 * @brief Calculates the last location of the maximum value of each time series. The position
 * is calculated relatively to the length of the series.
 *
 * @param tss Time series concatenated in a single row.
 * @param tssLength Time series length (All time series need to have the same length).
 * @param tssNumberOfTss Number of time series.
 * @param result The last relative location of the maximum value of each series.
 */
JNIEXPORT void JNICALL Java_tsa_Features_lastLocationOfMaximum(JNIEnv *env, jobject thisObj, jdoubleArray tss,
                                                               jlong tssLength, jlong tssNumberOfTss,
                                                               jdoubleArray result);

/**
 * @brief Calculates the last location of the minimum value of each time series. The position
 * is calculated relatively to the length of the series.
 *
 * @param tss Time series concatenated in a single row.
 * @param tssLength Time series length (All time series need to have the same length).
 * @param tssNumberOfTss Number of time series.
 * @param result The last relative location of the minimum value of each series.
 */
JNIEXPORT void JNICALL Java_tsa_Features_lastLocationOfMinimum(JNIEnv *env, jobject thisObj, jdoubleArray tss,
                                                               jlong tssLength, jlong tssNumberOfTss,
                                                               jdoubleArray result);

/**
 * @brief Returns the length of the input time series.
 *
 * @param tss Time series concatenated in a single row.
 * @param tssLength Time series length (All time series need to have the same length).
 * @param tssNumberOfTss Number of time series.
 * @param result The length of tss.
 */
JNIEXPORT void JNICALL Java_tsa_Features_length(JNIEnv *env, jobject thisObj, jdoubleArray tss, jlong tssLength,
                                                jlong tssNumberOfTss, jintArray result);

/**
 * @brief Calculate a linear least-squares regression for the values of the time series versus the sequence from 0 to
 * length of the time series minus one.
 *
 * @param tss Time series concatenated in a single row.
 * @param tssLength Time series length (All time series need to have the same length).
 * @param tssNumberOfTss Number of time series.
 * @param pvalue The pvalues for all time series.
 * @param rvalue The rvalues for all time series.
 * @param intercept The intercept values for all time series.
 * @param slope The slope for all time series.
 * @param stdrr The stderr values for all time series.
 */
JNIEXPORT void JNICALL Java_tsa_Features_linearTrend(JNIEnv *env, jobject thisObj, jdoubleArray tss, jlong tssLength,
                                                     jlong tssNumberOfTss, jdoubleArray pvalue, jdoubleArray rvalue,
                                                     jdoubleArray intercept, jdoubleArray slope, jdoubleArray stderr);
#ifdef __cplusplus
}
#endif
};  // namespace features
};  // namespace tsa