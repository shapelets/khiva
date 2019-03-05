// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <jni.h>
#include <khiva/clustering.h>
#include <khiva_jni/clustering.h>

JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Clustering_kMeans(JNIEnv *env, jobject, jlong ref_tss, jint k,
                                                                       jlong ref_initial_centroids, jlong ref_centroids,
                                                                       jlong ref_initial_labels, jlong ref_labels,
                                                                       jfloat tolerance, jint maxIterations) {
    const jint l = 3;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref_tss;
    af::array var = af::array(arr);

    jlong raw_pointer_labels = 0;
    af_array af_p_labels = (af_array)raw_pointer_labels;

    jlong raw_pointer_centroids = 0;
    af_array af_p_centroids = (af_array)raw_pointer_centroids;

    af_retain_array(&arr, var.get());

    af::array primitive_labels;
    af::array primitive_centroids;

    khiva::clustering::kMeans(var, static_cast<int>(k), primitive_centroids, primitive_labels,
                              static_cast<float>(tolerance), static_cast<int>(maxIterations));

    af_retain_array(&af_p_labels, primitive_labels.get());
    af_retain_array(&af_p_centroids, primitive_centroids.get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p_centroids;
    tmp[2] = (jlong)af_p_labels;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
    return pointers;
}

JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Clustering_kShape(JNIEnv *env, jobject, jlong ref_tss, jint k,
                                                                       jlong ref_initial_centroids, jlong ref_centroids,
                                                                       jlong ref_initial_labels, jlong ref_labels,
                                                                       jfloat tolerance, jint maxIterations) {
    const jint l = 3;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref_tss;
    af::array var = af::array(arr);

    jlong raw_pointer_labels = 0;
    af_array af_p_labels = (af_array)raw_pointer_labels;

    jlong raw_pointer_centroids = 0;
    af_array af_p_centroids = (af_array)raw_pointer_centroids;

    af_retain_array(&arr, var.get());

    af::array primitive_labels;
    af::array primitive_centroids;

    khiva::clustering::kShape(var, static_cast<int>(k), primitive_centroids, primitive_labels,
                              static_cast<float>(tolerance), static_cast<int>(maxIterations));

    af_retain_array(&af_p_labels, primitive_labels.get());
    af_retain_array(&af_p_centroids, primitive_centroids.get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p_centroids;
    tmp[2] = (jlong)af_p_labels;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
    return pointers;
}
