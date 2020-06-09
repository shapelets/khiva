// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/statistics.h>
#include <khiva_jni/internal/utils.h>
#include <khiva_jni/statistics.h>

jlong JNICALL Java_io_shapelets_khiva_Statistics_covariance(JNIEnv *env, jobject, jlong ref, jboolean unbiased) {
    return khiva::jni::KhivaCall(env, khiva::statistics::covariance, ref, unbiased);
}

jlong JNICALL Java_io_shapelets_khiva_Statistics_moment(JNIEnv *env, jobject, jlong ref, jint k) {
    return khiva::jni::KhivaCall(env, khiva::statistics::moment, ref, k);
}

jlong JNICALL Java_io_shapelets_khiva_Statistics_sampleStdev(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::statistics::sampleStdev, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Statistics_kurtosis(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::statistics::kurtosis, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Statistics_skewness(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::statistics::skewness, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Statistics_quantile(JNIEnv *env, jobject, jlong ref, jlong ref_q,
                                                          jfloat precision) {
    return khiva::jni::KhivaCallTwoArrays(env, khiva::statistics::quantile, ref, ref_q, precision);
}

jlong JNICALL Java_io_shapelets_khiva_Statistics_quantilesCut(JNIEnv *env, jobject, jlong ref, jfloat quantiles,
                                                              jfloat precision) {
    return khiva::jni::KhivaCall(env, khiva::statistics::quantilesCut, ref, quantiles, precision);
}

jlong JNICALL Java_io_shapelets_khiva_Statistics_ljungBox(JNIEnv *env, jobject, jlong ref, jlong lags) {
    return khiva::jni::KhivaCall(env, khiva::statistics::ljungBox, ref, lags);
}
