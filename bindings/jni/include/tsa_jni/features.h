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
                                                            jlong tssLength, jlong tssNumberOfTss, jint m, jfloat r,
                                                            jfloatArray result);

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

#ifdef __cplusplus
}
#endif
};  // namespace features
};  // namespace tsa