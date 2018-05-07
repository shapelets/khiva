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
 * @brief Calculates the covariance matrix of the time series contained in tss.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param unbiased unbiased Determines whether it divides by n - 1 (if false) or n (if true).
 *
 * @return The updated ref and a ref to the covariance matrix of the time series.
 */
JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Statistics_covariance(JNIEnv *env, jobject thisObj, jlong ref, jboolean unbiased);

/**
 * @brief Calculates the kth moment of the given time series.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param k The specific moment to be calculated.
 *
 * @return The updated ref and a ref to the kth moment of the given time series.
 */
JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Statistics_moment(JNIEnv *env, jobject thisObj, jlong ref, jint k);

/**
 * @brief Estimates standard deviation based on a sample. The standard deviation is calculated using the "n-1" method.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @return The updated ref and a ref to the sample standard deviation.
 */
JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Statistics_sampleStdev(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Calculates the kurtosis of tss (calculated with the adjusted Fisher-Pearson standardized moment coefficient
 * G2).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return The updated ref and a ref to the kurtosis of tss.
 */
JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Statistics_kurtosis(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Calculates the sample skewness of tss (calculated with the adjusted Fisher-Pearson standardized moment
 * coefficient G1).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 *
 * @return The updated ref and a ref to an array containing the skewness of each time series in tss.
 */
JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Statistics_skewness(JNIEnv *env, jobject thisObj, jlong ref);

/**
 * @brief Calculates the values at the given quantile.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series. NOTE: the time series should be sorted.
 * @param q Percentile(s) at which to extract score(s). One or many.
 * @param precision Number of decimals expected.
 *
 * @return Updated refs and a ref to the values at the given quantile.
 */
JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Statistics_quantile(JNIEnv *env, jobject thisObj, jlong ref, jlong ref_q,
                                                                       jfloat precision);

/**
 * @brief Discretizes the time series into equal-sized buckets based on sample quantiles.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series. NOTE: the time series should be sorted.
 * @param quantiles Number of quantiles to extract. From 0 to 1, step 1/quantiles.
 * @param precision Number of decimals expected.
 *
 * @return The updated ref and a ref to a matrix with the categories, one category per row, the start of the
 * category in the first column and the end in the second category.
 */
JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Statistics_quantilesCut(JNIEnv *env, jobject thisObj, jlong ref, jfloat quantiles,
                                                                           jfloat precision);

#ifdef __cplusplus
}
#endif
