// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <jni.h>
#include <khiva/clustering.h>
#include <khiva_jni/clustering.h>

jlongArray JNICALL Java_io_shapelets_khiva_Clustering_kShape(JNIEnv *env, jobject, jlong ref, jint k, jfloat tolerance){
    const jint l = 3;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer_idx = 0;
    af_array af_p_idx = (af_array)raw_pointer_idx;

    jlong raw_pointer_centroids = 0;
    af_array af_p_centroids = (af_array)raw_pointer_centroids;

    af_retain_array(&arr, var.get());

    af::array primitive_idx;
    af::array primitive_centroids;

    khiva::clustering::kShape(var, static_cast<int>(k), static_cast<float>(tolerance), primitive_idx,
            primitive_centroids);

    af_retain_array(&af_p_idx, primitive_idx.get());
    af_retain_array(&af_p_centroids, primitive_centroids.get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p_idx;
    tmp[2] = (jlong)af_p_centroids;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
    return pointers;
}