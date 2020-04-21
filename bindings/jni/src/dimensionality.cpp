// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/dimensionality.h>
#include <khiva_jni/dimensionality.h>
#include <khiva_jni/internal/utils.h>

jlong JNICALL Java_io_shapelets_khiva_Dimensionality_paa(JNIEnv *env, jobject, jlong ref, jint bins) {
    return khiva::jni::KhivaCall(
        env, [](const af::array &a, int bins) { return khiva::dimensionality::PAA(a, bins); }, ref, bins);
}

jlong JNICALL Java_io_shapelets_khiva_Dimensionality_pip(JNIEnv *env, jobject, jlong ref, jint numberIPs) {
    return khiva::jni::KhivaCall(env, khiva::dimensionality::PIP, ref, numberIPs);
}

jlong JNICALL Java_io_shapelets_khiva_Dimensionality_PLABottomUp(JNIEnv *env, jobject, jlong ref, jfloat maxError) {
    return khiva::jni::KhivaCall(
        env, [](const af::array &a, float f) { return khiva::dimensionality::PLABottomUp(a, f); }, ref, maxError);
}

jlong JNICALL Java_io_shapelets_khiva_Dimensionality_PLASlidingWindow(JNIEnv *env, jobject, jlong ref,
                                                                      jfloat maxError) {
    return khiva::jni::KhivaCall(
        env, [](const af::array &a, float f) { return khiva::dimensionality::PLASlidingWindow(a, f); }, ref, maxError);
}

jlong JNICALL Java_io_shapelets_khiva_Dimensionality_ramerDouglasPeucker(JNIEnv *env, jobject, jlong ref,
                                                                         jdouble epsilon) {
    return khiva::jni::KhivaCall(
        env, [](const af::array &a, float f) { return khiva::dimensionality::ramerDouglasPeucker(a, f); }, ref,
        epsilon);
}

jlong JNICALL Java_io_shapelets_khiva_Dimensionality_sax(JNIEnv *env, jobject, jlong ref, jint alphabetSize) {
    return khiva::jni::KhivaCall(env, khiva::dimensionality::SAX, ref, alphabetSize);
}

jlong JNICALL Java_io_shapelets_khiva_Dimensionality_visvalingam(JNIEnv *env, jobject, jlong ref, jint numPoints) {
    return khiva::jni::KhivaCall(
        env, [](const af::array &a, int n) { return khiva::dimensionality::visvalingam(a, n); }, ref, numPoints);
}
