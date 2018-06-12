// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/matrix.h>
#include <khiva_jni/matrix.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Matrix_findBestNDiscords(JNIEnv *env, jobject, jlong ref_profile,
                                                                               jlong ref_index, jlong n) {
    const jint l = 5;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr_profile = (af_array)ref_profile;
    af::array var_profile = af::array(arr_profile);

    af_array arr_index = (af_array)ref_index;
    af::array var_index = af::array(arr_index);

    jlong raw_pointer_discord_distances = 0;
    af_array af_p_discord_distances = (af_array)raw_pointer_discord_distances;

    jlong raw_pointer_discord_indices = 0;
    af_array af_p_discord_indices = (af_array)raw_pointer_discord_indices;

    jlong raw_pointer_subsequence_indices = 0;
    af_array af_p_subsequence_indices = (af_array)raw_pointer_subsequence_indices;

    af_retain_array(&arr_profile, var_profile.get());
    af_retain_array(&arr_index, var_index.get());

    af::array discords;
    af::array discords_indices;
    af::array subsequence_indices;

    khiva::matrix::findBestNDiscords(var_profile, var_index, static_cast<long>(n), discords, discords_indices,
                                     subsequence_indices);

    af_retain_array(&af_p_discord_distances, discords.get());
    af_retain_array(&af_p_discord_indices, discords_indices.get());
    af_retain_array(&af_p_subsequence_indices, subsequence_indices.get());

    tmp[0] = (jlong)arr_profile;
    tmp[1] = (jlong)arr_index;
    tmp[2] = (jlong)af_p_discord_distances;
    tmp[3] = (jlong)af_p_discord_indices;
    tmp[4] = (jlong)af_p_subsequence_indices;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
    return pointers;
}

JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Matrix_findBestNMotifs(JNIEnv *env, jobject, jlong ref_profile,
                                                                             jlong ref_index, jlong n) {
    const jint l = 5;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr_profile = (af_array)ref_profile;
    af::array var_profile = af::array(arr_profile);

    af_array arr_index = (af_array)ref_index;
    af::array var_index = af::array(arr_index);

    jlong raw_pointer_motif_distances = 0;
    af_array af_p_motif_distances = (af_array)raw_pointer_motif_distances;

    jlong raw_pointer_motif_indices = 0;
    af_array af_p_motif_indices = (af_array)raw_pointer_motif_indices;

    jlong raw_pointer_subsequence_indices = 0;
    af_array af_p_subsequence_indices = (af_array)raw_pointer_subsequence_indices;

    af_retain_array(&arr_profile, var_profile.get());
    af_retain_array(&arr_index, var_index.get());

    af::array motifs;
    af::array motif_indices;
    af::array subsequence_indices;

    khiva::matrix::findBestNMotifs(var_profile, var_index, static_cast<long>(n), motifs, motif_indices,
                                   subsequence_indices);

    af_retain_array(&af_p_motif_distances, motifs.get());
    af_retain_array(&af_p_motif_indices, motif_indices.get());
    af_retain_array(&af_p_subsequence_indices, subsequence_indices.get());

    tmp[0] = (jlong)arr_profile;
    tmp[1] = (jlong)arr_index;
    tmp[2] = (jlong)af_p_motif_distances;
    tmp[3] = (jlong)af_p_motif_indices;
    tmp[4] = (jlong)af_p_subsequence_indices;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
    return pointers;
}

JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Matrix_stomp(JNIEnv *env, jobject, jlong ref_a, jlong ref_b,
                                                                   jlong m) {
    const jint l = 4;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr_a = (af_array)ref_a;
    af::array var_a = af::array(arr_a);

    af_array arr_b = (af_array)ref_b;
    af::array var_b = af::array(arr_b);

    jlong raw_pointer_distance = 0;
    af_array af_p_distance = (af_array)raw_pointer_distance;

    jlong raw_pointer_index = 0;
    af_array af_p_index = (af_array)raw_pointer_index;

    af_retain_array(&arr_a, var_a.get());
    af_retain_array(&arr_b, var_b.get());

    af::array distance;
    af::array index;
    long subsequence = static_cast<long>(m);

    khiva::matrix::stomp(var_a, var_b, subsequence, distance, index);

    af_retain_array(&af_p_distance, distance.get());
    af_retain_array(&af_p_index, index.get());

    tmp[0] = (jlong)arr_a;
    tmp[1] = (jlong)arr_b;
    tmp[2] = (jlong)af_p_distance;
    tmp[3] = (jlong)af_p_index;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
    return pointers;
}

JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Matrix_stompSelfJoin(JNIEnv *env, jobject, jlong ref_a, jlong m) {
    const jint l = 3;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr_a = (af_array)ref_a;
    af::array var_a = af::array(arr_a);

    jlong raw_pointer_distance = 0;
    af_array af_p_distance = (af_array)raw_pointer_distance;

    jlong raw_pointer_index = 0;
    af_array af_p_index = (af_array)raw_pointer_index;

    af_retain_array(&arr_a, var_a.get());

    af::array distance;
    af::array index;
    long subsequence = static_cast<long>(m);

    khiva::matrix::stomp(var_a, subsequence, distance, index);

    af_retain_array(&af_p_distance, distance.get());
    af_retain_array(&af_p_index, index.get());

    tmp[0] = (jlong)arr_a;
    tmp[1] = (jlong)af_p_distance;
    tmp[2] = (jlong)af_p_index;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);
    return pointers;
}

#ifdef __cplusplus
}
#endif
