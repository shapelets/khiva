// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/distances.h>
#include <khiva_jni/distances.h>
#include <khiva_jni/internal/utils.h>

jlong JNICALL Java_io_shapelets_khiva_Distances_euclidean(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::distances::euclidean, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Distances_dtw(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(
        env, [](const af::array &a) { return khiva::distances::dtw(a); }, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Distances_hamming(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::distances::hamming, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Distances_manhattan(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::distances::manhattan, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Distances_sbd(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::distances::sbd, ref);
}

jlong JNICALL Java_io_shapelets_khiva_Distances_squaredEuclidean(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::distances::squaredEuclidean, ref);
}
