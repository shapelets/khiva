// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <jni.h>
#include <tsa/features.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_tsa_Features_crossCorrelation(JNIEnv *env, jobject thisObj, jdoubleArray xss,
                                                          jlong xssLength, jlong xssNumberOfTss, jdoubleArray yss,
                                                          jlong yssLength, jlong yssNumberOfTss, jboolean unbiased,
                                                          jdoubleArray result) {
    af::array primitive_result;
    long xssFull_length = xssLength * xssNumberOfTss;
    jdouble input_xss[xssFull_length];
    env->GetDoubleArrayRegion(xss, 0, xssFull_length, &input_xss[0]);
    long yssFull_length = yssLength * yssNumberOfTss;
    jdouble input_yss[yssFull_length];
    env->GetDoubleArrayRegion(yss, 0, yssFull_length, &input_yss[0]);

    primitive_result = tsa::features::crossCorrelation(af::array(xssLength, xssNumberOfTss, input_xss),
                                                       af::array(yssLength, yssNumberOfTss, input_yss), unbiased);
    long output_result_length = std::max(yssLength, xssLength);
    jdouble output_result[output_result_length];
    primitive_result.host(output_result);
    env->SetDoubleArrayRegion(result, 0, output_result_length, &output_result[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_autoCovariance(JNIEnv *env, jobject thisObj, jdoubleArray xss, jlong xssLength,
                                                        jlong xssNumberOfTss, jboolean unbiased, jdoubleArray result) {
    af::array primitive_result;
    long xssFull_length = xssLength * xssNumberOfTss;
    jdouble input_xss[xssFull_length];
    env->GetDoubleArrayRegion(xss, 0, xssFull_length, &input_xss[0]);

    primitive_result = tsa::features::autoCovariance(af::array(xssLength, xssNumberOfTss, input_xss), unbiased);
    long output_result_length = xssNumberOfTss * xssLength;
    jdouble output_result[output_result_length];
    primitive_result.host(output_result);
    env->SetDoubleArrayRegion(result, 0, output_result_length, &output_result[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_crossCovariance(JNIEnv *env, jobject thisObj, jdoubleArray xss,
                                                         jlong xssLength, jlong xssNumberOfTss, jdoubleArray yss,
                                                         jlong yssLength, jlong yssNumberOfTss, jboolean unbiased,
                                                         jdoubleArray result) {
    af::array primitive_result;
    long xssFull_length = xssLength * xssNumberOfTss;
    jdouble input_xss[xssFull_length];
    env->GetDoubleArrayRegion(xss, 0, xssFull_length, &input_xss[0]);
    long yssFull_length = yssLength * yssNumberOfTss;
    jdouble input_yss[yssFull_length];
    env->GetDoubleArrayRegion(yss, 0, yssFull_length, &input_yss[0]);

    primitive_result = tsa::features::crossCovariance(af::array(xssLength, xssNumberOfTss, input_xss),
                                                      af::array(yssLength, yssNumberOfTss, input_yss), unbiased);

    long output_result_length = xssLength * yssLength;
    jdouble output_result[output_result_length];
    primitive_result.host(output_result);
    env->SetDoubleArrayRegion(result, 0, output_result_length, &output_result[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_approximateEntropy(JNIEnv *env, jobject thisObj, jdoubleArray tss,
                                                            jlong tssLength, jlong tssNumberOfTss, jint m, jfloat r,
                                                            jdoubleArray result) {
    af::array primitive_result;
    long tssFull_length = tssLength * tssNumberOfTss;
    jdouble input_tss[tssFull_length];
    env->GetDoubleArrayRegion(tss, 0, tssFull_length, &input_tss[0]);

    primitive_result = tsa::features::approximateEntropy(af::array(tssLength, tssNumberOfTss, input_tss), m, r);

    jdouble output_result[tssNumberOfTss];
    primitive_result.host(output_result);
    env->SetDoubleArrayRegion(result, 0, tssNumberOfTss, &output_result[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_c3(JNIEnv *env, jobject thisObj, jdoubleArray tss, jlong tssLength,
                                            jlong tssNumberOfTss, jlong lag, jdoubleArray result) {
    af::array primitive_result;
    long tssFull_length = tssLength * tssNumberOfTss;
    jdouble input_tss[tssFull_length];
    env->GetDoubleArrayRegion(tss, 0, tssFull_length, &input_tss[0]);

    primitive_result = tsa::features::c3(af::array(tssLength, tssNumberOfTss, input_tss), lag);

    jdouble output_result[tssNumberOfTss];
    primitive_result.host(output_result);
    env->SetDoubleArrayRegion(result, 0, tssNumberOfTss, &output_result[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_cidCe(JNIEnv *env, jobject thisObj, jdoubleArray tss, jlong tssLength,
                                               jlong tssNumberOfTss, jboolean zNormalize, jdoubleArray result) {
    af::array primitive_result;
    long tssFull_length = tssLength * tssNumberOfTss;
    jdouble input_tss[tssFull_length];
    env->GetDoubleArrayRegion(tss, 0, tssFull_length, &input_tss[0]);

    primitive_result = tsa::features::cidCe(af::array(tssLength, tssNumberOfTss, input_tss), zNormalize);

    jdouble output_result[tssNumberOfTss];
    primitive_result.host(output_result);
    env->SetDoubleArrayRegion(result, 0, tssNumberOfTss, &output_result[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_absEnergy(JNIEnv *env, jobject thisObj, jdoubleArray timeSeries,
                                                   jlong timeSeriesLength, jlong numberOfTimeSeries,
                                                   jdoubleArray jResult) {
    af::array result;
    long concatenatedTimeSeriesLength = timeSeriesLength * numberOfTimeSeries;
    jdouble inputTs[concatenatedTimeSeriesLength];
    env->GetDoubleArrayRegion(timeSeries, 0, concatenatedTimeSeriesLength, &inputTs[0]);

    result = tsa::features::absEnergy(af::array(timeSeriesLength, numberOfTimeSeries, inputTs));

    jdouble inputCResult[numberOfTimeSeries];
    result.host(inputCResult);
    env->SetDoubleArrayRegion(jResult, 0, numberOfTimeSeries, &inputCResult[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_absoluteSumOfChanges(JNIEnv *env, jobject thisObj, jdoubleArray timeSeries,
                                                              jlong timeSeriesLength, jlong numberOfTimeSeries,
                                                              jdoubleArray jResult) {
    af::array result;
    long concatenatedTimeSeriesLength = timeSeriesLength * numberOfTimeSeries;
    jdouble inputTs[concatenatedTimeSeriesLength];
    env->GetDoubleArrayRegion(timeSeries, 0, concatenatedTimeSeriesLength, &inputTs[0]);

    result = tsa::features::absoluteSumOfChanges(af::array(timeSeriesLength, numberOfTimeSeries, inputTs));

    jdouble inputCResult[numberOfTimeSeries];
    result.host(inputCResult);
    env->SetDoubleArrayRegion(jResult, 0, numberOfTimeSeries, &inputCResult[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_autoCorrelation(JNIEnv *env, jobject thisObj, jdoubleArray tss,
                                                         jlong tssLength, jlong tssNumberOfTss, jlong maxLag,
                                                         jboolean unbiased, jdoubleArray result) {
    af::array primitive_result;
    long tssFull_length = tssLength * tssNumberOfTss;
    jdouble input_tss[tssFull_length];
    env->GetDoubleArrayRegion(tss, 0, tssFull_length, &input_tss[0]);

    primitive_result =
        tsa::features::autoCorrelation(af::array(tssLength, tssNumberOfTss, input_tss), maxLag, unbiased);

    jdouble output_result[tssFull_length];
    primitive_result.host(output_result);
    env->SetDoubleArrayRegion(result, 0, tssFull_length, &output_result[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_binnedEntropy(JNIEnv *env, jobject thisObj, jdoubleArray tss, jlong tssLength,
                                                       jlong tssNumberOfTss, jint max_bins, jdoubleArray result) {
    af::array primitive_result;
    long tssFull_length = tssLength * tssNumberOfTss;
    jdouble input_tss[tssFull_length];
    env->GetDoubleArrayRegion(tss, 0, tssFull_length, &input_tss[0]);

    primitive_result = tsa::features::binnedEntropy(af::array(tssLength, tssNumberOfTss, input_tss), max_bins);

    jdouble output_result[tssNumberOfTss];
    primitive_result.host(output_result);
    env->SetDoubleArrayRegion(result, 0, tssNumberOfTss, &output_result[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_countAboveMean(JNIEnv *env, jobject thisObj, jdoubleArray tss, jlong tssLength,
                                                        jlong tssNumberOfTss, jintArray result) {
    af::array primitive_result;
    long tssFull_length = tssLength * tssNumberOfTss;
    jdouble input_tss[tssFull_length];
    env->GetDoubleArrayRegion(tss, 0, tssFull_length, &input_tss[0]);

    primitive_result = tsa::features::countAboveMean(af::array(tssLength, tssNumberOfTss, input_tss));

    jint output_result[tssNumberOfTss];
    primitive_result.host(output_result);
    env->SetIntArrayRegion(result, 0, tssNumberOfTss, &output_result[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_countBelowMean(JNIEnv *env, jobject thisObj, jdoubleArray tss, jlong tssLength,
                                                        jlong tssNumberOfTss, jintArray result) {
    af::array primitive_result;
    long tssFull_length = tssLength * tssNumberOfTss;
    jdouble input_tss[tssFull_length];
    env->GetDoubleArrayRegion(tss, 0, tssFull_length, &input_tss[0]);

    primitive_result = tsa::features::countBelowMean(af::array(tssLength, tssNumberOfTss, input_tss));

    jint output_result[tssNumberOfTss];
    primitive_result.host(output_result);
    env->SetIntArrayRegion(result, 0, tssNumberOfTss, &output_result[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_energyRatioByChunks(JNIEnv *env, jobject thisObj, jdoubleArray tss,
                                                             jlong tssLength, jlong tssNumberOfTss, jlong numSegments,
                                                             jlong segmentFocus, jdoubleArray result) {
    af::array primitive_result;
    long tssFull_length = tssLength * tssNumberOfTss;
    jdouble input_tss[tssFull_length];
    env->GetDoubleArrayRegion(tss, 0, tssFull_length, &input_tss[0]);

    primitive_result =
        tsa::features::energyRatioByChunks(af::array(tssLength, tssNumberOfTss, input_tss), numSegments, segmentFocus);

    jdouble output_result[tssNumberOfTss];
    primitive_result.host(output_result);
    env->SetDoubleArrayRegion(result, 0, tssNumberOfTss, &output_result[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_firstLocationOfMaximum(JNIEnv *env, jobject thisObj, jdoubleArray tss,
                                                                jlong tssLength, jlong tssNumberOfTss,
                                                                jdoubleArray result) {
    af::array primitive_result;
    long tssFull_length = tssLength * tssNumberOfTss;
    jdouble input_tss[tssFull_length];
    env->GetDoubleArrayRegion(tss, 0, tssFull_length, &input_tss[0]);

    primitive_result = tsa::features::firstLocationOfMaximum(af::array(tssLength, tssNumberOfTss, input_tss));

    jdouble output_result[tssNumberOfTss];
    primitive_result.host(output_result);
    env->SetDoubleArrayRegion(result, 0, tssNumberOfTss, &output_result[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_firstLocationOfMinimum(JNIEnv *env, jobject thisObj, jdoubleArray tss,
                                                                jlong tssLength, jlong tssNumberOfTss,
                                                                jdoubleArray result) {
    af::array primitive_result;
    long tssFull_length = tssLength * tssNumberOfTss;
    jdouble input_tss[tssFull_length];
    env->GetDoubleArrayRegion(tss, 0, tssFull_length, &input_tss[0]);

    primitive_result = tsa::features::firstLocationOfMinimum(af::array(tssLength, tssNumberOfTss, input_tss));

    jdouble output_result[tssNumberOfTss];
    primitive_result.host(output_result);
    env->SetDoubleArrayRegion(result, 0, tssNumberOfTss, &output_result[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_hasDuplicates(JNIEnv *env, jobject thisObj, jdoubleArray tss, jlong tssLength,
                                                       jlong tssNumberOfTss, jbooleanArray result) {
    af::array primitive_result;
    long tssFull_length = tssLength * tssNumberOfTss;
    jdouble input_tss[tssFull_length];
    env->GetDoubleArrayRegion(tss, 0, tssFull_length, &input_tss[0]);

    primitive_result = tsa::features::hasDuplicates(af::array(tssLength, tssNumberOfTss, input_tss));

    jboolean output_result[tssNumberOfTss];
    primitive_result.host(output_result);
    env->SetBooleanArrayRegion(result, 0, tssNumberOfTss, &output_result[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_hasDuplicateMax(JNIEnv *env, jobject thisObj, jdoubleArray tss,
                                                         jlong tssLength, jlong tssNumberOfTss, jbooleanArray result) {
    af::array primitive_result;
    long tssFull_length = tssLength * tssNumberOfTss;
    jdouble input_tss[tssFull_length];
    env->GetDoubleArrayRegion(tss, 0, tssFull_length, &input_tss[0]);

    primitive_result = tsa::features::hasDuplicateMax(af::array(tssLength, tssNumberOfTss, input_tss));

    jboolean output_result[tssNumberOfTss];
    primitive_result.host(output_result);
    env->SetBooleanArrayRegion(result, 0, tssNumberOfTss, &output_result[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_indexMaxQuantile(JNIEnv *env, jobject thisObj, jdoubleArray tss,
                                                          jlong tssLength, jlong tssNumberOfTss, jfloat q,
                                                          jdoubleArray result) {
    af::array primitive_result;
    long tssFull_length = tssLength * tssNumberOfTss;
    jdouble input_tss[tssFull_length];
    env->GetDoubleArrayRegion(tss, 0, tssFull_length, &input_tss[0]);

    primitive_result = tsa::features::indexMaxQuantile(af::array(tssLength, tssNumberOfTss, input_tss), q);

    jdouble output_result[tssNumberOfTss];
    primitive_result.host(output_result);
    env->SetDoubleArrayRegion(result, 0, tssNumberOfTss, &output_result[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_kurtosis(JNIEnv *env, jobject thisObj, jdoubleArray tss, jlong tssLength,
                                                  jlong tssNumberOfTss, jdoubleArray result) {
    af::array primitive_result;
    long tssFull_length = tssLength * tssNumberOfTss;
    jdouble input_tss[tssFull_length];
    env->GetDoubleArrayRegion(tss, 0, tssFull_length, &input_tss[0]);

    primitive_result = tsa::features::kurtosis(af::array(tssLength, tssNumberOfTss, input_tss));

    jdouble output_result[tssNumberOfTss];
    primitive_result.host(output_result);
    env->SetDoubleArrayRegion(result, 0, tssNumberOfTss, &output_result[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_largeStandardDeviation(JNIEnv *env, jobject thisObj, jdoubleArray tss,
                                                                jlong tssLength, jlong tssNumberOfTss, jfloat r,
                                                                jbooleanArray result) {
    af::array primitive_result;
    long tssFull_length = tssLength * tssNumberOfTss;
    jdouble input_tss[tssFull_length];
    env->GetDoubleArrayRegion(tss, 0, tssFull_length, &input_tss[0]);

    primitive_result = tsa::features::largeStandardDeviation(af::array(tssLength, tssNumberOfTss, input_tss), r);

    jboolean output_result[tssNumberOfTss];
    primitive_result.host(output_result);
    env->SetBooleanArrayRegion(result, 0, tssNumberOfTss, &output_result[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_lastLocationOfMaximum(JNIEnv *env, jobject thisObj, jdoubleArray tss,
                                                               jlong tssLength, jlong tssNumberOfTss,
                                                               jdoubleArray result) {
    af::array primitive_result;
    long tssFull_length = tssLength * tssNumberOfTss;
    jdouble input_tss[tssFull_length];
    env->GetDoubleArrayRegion(tss, 0, tssFull_length, &input_tss[0]);

    primitive_result = tsa::features::lastLocationOfMaximum(af::array(tssLength, tssNumberOfTss, input_tss));

    jdouble output_result[tssNumberOfTss];
    primitive_result.host(output_result);
    env->SetDoubleArrayRegion(result, 0, tssNumberOfTss, &output_result[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_lastLocationOfMinimum(JNIEnv *env, jobject thisObj, jdoubleArray tss,
                                                               jlong tssLength, jlong tssNumberOfTss,
                                                               jdoubleArray result) {
    af::array primitive_result;
    long tssFull_length = tssLength * tssNumberOfTss;
    jdouble input_tss[tssFull_length];
    env->GetDoubleArrayRegion(tss, 0, tssFull_length, &input_tss[0]);

    primitive_result = tsa::features::lastLocationOfMinimum(af::array(tssLength, tssNumberOfTss, input_tss));

    jdouble output_result[tssNumberOfTss];
    primitive_result.host(output_result);
    env->SetDoubleArrayRegion(result, 0, tssNumberOfTss, &output_result[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_length(JNIEnv *env, jobject thisObj, jdoubleArray tss, jlong tssLength,
                                                jlong tssNumberOfTss, jintArray result) {
    af::array primitive_result;
    long tssFull_length = tssLength * tssNumberOfTss;
    jdouble input_tss[tssFull_length];
    env->GetDoubleArrayRegion(tss, 0, tssFull_length, &input_tss[0]);

    primitive_result = tsa::features::length(af::array(tssLength, tssNumberOfTss, input_tss));

    jint output_result[tssNumberOfTss];
    primitive_result.host(output_result);
    env->SetIntArrayRegion(result, 0, tssNumberOfTss, &output_result[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_linearTrend(JNIEnv *env, jobject thisObj, jdoubleArray tss, jlong tssLength,
                                                     jlong tssNumberOfTss, jdoubleArray pvalue, jdoubleArray rvalue,
                                                     jdoubleArray intercept, jdoubleArray slope, jdoubleArray stderr) {
    af::array primitive_pvalue;
    af::array primitive_rvalue;
    af::array primitive_intercept;
    af::array primitive_slope;
    af::array primitive_stderr;

    long tssFull_length = tssLength * tssNumberOfTss;
    jdouble input_tss[tssFull_length];
    env->GetDoubleArrayRegion(tss, 0, tssFull_length, &input_tss[0]);

    tsa::features::linearTrend(af::array(tssLength, tssNumberOfTss, input_tss), primitive_pvalue, primitive_rvalue,
                               primitive_intercept, primitive_slope, primitive_stderr);

    jdouble output_pvalue[tssNumberOfTss];
    jdouble output_rvalue[tssNumberOfTss];
    jdouble output_intercept[tssNumberOfTss];
    jdouble output_slope[tssNumberOfTss];
    jdouble output_stderr[tssNumberOfTss];

    primitive_pvalue.host(output_pvalue);
    primitive_rvalue.host(output_rvalue);
    primitive_intercept.host(output_intercept);
    primitive_slope.host(output_slope);
    primitive_stderr.host(output_stderr);

    env->SetDoubleArrayRegion(pvalue, 0, tssNumberOfTss, &output_pvalue[0]);
    env->SetDoubleArrayRegion(rvalue, 0, tssNumberOfTss, &output_rvalue[0]);
    env->SetDoubleArrayRegion(intercept, 0, tssNumberOfTss, &output_intercept[0]);
    env->SetDoubleArrayRegion(slope, 0, tssNumberOfTss, &output_slope[0]);
    env->SetDoubleArrayRegion(stderr, 0, tssNumberOfTss, &output_stderr[0]);

    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_hasDuplicateMin(JNIEnv *env, jobject thisObj, jdoubleArray tss,
                                                         jlong tssLength, jlong tssNumberOfTss, jbooleanArray result) {
    af::array primitive_result;
    long tssFull_length = tssLength * tssNumberOfTss;
    jdouble input_tss[tssFull_length];
    env->GetDoubleArrayRegion(tss, 0, tssFull_length, &input_tss[0]);

    primitive_result = tsa::features::hasDuplicateMin(af::array(tssLength, tssNumberOfTss, input_tss));

    jboolean output_result[tssNumberOfTss];
    primitive_result.host(output_result);
    env->SetBooleanArrayRegion(result, 0, tssNumberOfTss, &output_result[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_longestStrikeAboveMean(JNIEnv *env, jobject thisObj, jdoubleArray tss,
                                                                jlong tssLength, jlong tssNumberOfTss,
                                                                jdoubleArray result) {
    af::array primitive_result;
    long tssFull_length = tssLength * tssNumberOfTss;
    jdouble input_tss[tssFull_length];
    env->GetDoubleArrayRegion(tss, 0, tssFull_length, &input_tss[0]);

    primitive_result = tsa::features::longestStrikeAboveMean(af::array(tssLength, tssNumberOfTss, input_tss));

    jdouble output_result[tssNumberOfTss];
    primitive_result.host(output_result);
    env->SetDoubleArrayRegion(result, 0, tssNumberOfTss, &output_result[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_longestStrikeBelowMean(JNIEnv *env, jobject thisObj, jdoubleArray tss,
                                                                jlong tssLength, jlong tssNumberOfTss,
                                                                jdoubleArray result) {
    af::array primitive_result;
    long tssFull_length = tssLength * tssNumberOfTss;
    jdouble input_tss[tssFull_length];
    env->GetDoubleArrayRegion(tss, 0, tssFull_length, &input_tss[0]);

    primitive_result = tsa::features::longestStrikeBelowMean(af::array(tssLength, tssNumberOfTss, input_tss));

    jdouble output_result[tssNumberOfTss];
    primitive_result.host(output_result);
    env->SetDoubleArrayRegion(result, 0, tssNumberOfTss, &output_result[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_maximum(JNIEnv *env, jobject thisObj, jdoubleArray tss, jlong tssLength,
                                                 jlong tssNumberOfTss, jdoubleArray result) {
    af::array primitive_result;
    long tssFull_length = tssLength * tssNumberOfTss;
    jdouble input_tss[tssFull_length];
    env->GetDoubleArrayRegion(tss, 0, tssFull_length, &input_tss[0]);

    primitive_result = tsa::features::maximum(af::array(tssLength, tssNumberOfTss, input_tss));

    jdouble output_result[tssNumberOfTss];
    primitive_result.host(output_result);
    env->SetDoubleArrayRegion(result, 0, tssNumberOfTss, &output_result[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_meanAbsoluteChange(JNIEnv *env, jobject thisObj, jdoubleArray tss,
                                                            jlong tssLength, jlong tssNumberOfTss,
                                                            jdoubleArray result) {
    af::array primitive_result;
    long tssFull_length = tssLength * tssNumberOfTss;
    jdouble input_tss[tssFull_length];
    env->GetDoubleArrayRegion(tss, 0, tssFull_length, &input_tss[0]);

    primitive_result = tsa::features::meanAbsoluteChange(af::array(tssLength, tssNumberOfTss, input_tss));

    jdouble output_result[tssNumberOfTss];
    primitive_result.host(output_result);
    env->SetDoubleArrayRegion(result, 0, tssNumberOfTss, &output_result[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Features_fftCoefficient(JNIEnv *env, jobject thisObj, jdoubleArray tss, jlong tssLength,
                                                        jlong tssNumberOfTss, jlong coefficient, jdoubleArray real,
                                                        jdoubleArray imag, jdoubleArray absolute, jdoubleArray angle) {
    af::array primitive_real;
    af::array primitive_imag;
    af::array primitive_absolute;
    af::array primitive_angle;

    long tssFull_length = tssLength * tssNumberOfTss;
    jdouble input_tss[tssFull_length];
    env->GetDoubleArrayRegion(tss, 0, tssFull_length, &input_tss[0]);

    tsa::features::fftCoefficient(af::array(tssLength, tssNumberOfTss, input_tss), coefficient, primitive_real,
                                  primitive_imag, primitive_absolute, primitive_angle);

    jdouble output_real[tssNumberOfTss];
    jdouble output_imag[tssNumberOfTss];
    jdouble output_absolute[tssNumberOfTss];
    jdouble output_angle[tssNumberOfTss];

    primitive_real.host(output_real);
    primitive_imag.host(output_imag);
    primitive_absolute.host(output_absolute);
    primitive_angle.host(output_angle);

    env->SetDoubleArrayRegion(real, 0, tssNumberOfTss, &output_real[0]);
    env->SetDoubleArrayRegion(imag, 0, tssNumberOfTss, &output_imag[0]);
    env->SetDoubleArrayRegion(absolute, 0, tssNumberOfTss, &output_absolute[0]);
    env->SetDoubleArrayRegion(angle, 0, tssNumberOfTss, &output_angle[0]);

    return;
}

#ifdef __cplusplus
}
#endif
