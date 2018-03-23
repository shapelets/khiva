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
#ifdef __cplusplus
}
#endif
