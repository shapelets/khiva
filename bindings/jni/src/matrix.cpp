// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/matrix.h>
#include <khiva_jni/matrix.h>

#include <array>

jlongArray JNICALL Java_io_shapelets_khiva_Matrix_findBestNDiscords(JNIEnv *env, jobject, jlong ref_profile,
                                                                    jlong ref_index, jlong m, jlong n,
                                                                    jboolean self_join) {
    try {
        auto arr_profile = *reinterpret_cast<af::array *>(ref_profile);
        auto arr_index = *reinterpret_cast<af::array *>(ref_index);
        af::array discords_distances;
        af::array discords_indices;
        af::array subsequence_indices;
        khiva::matrix::findBestNDiscords(arr_profile, arr_index, static_cast<long>(m), static_cast<long>(n),
                                         discords_distances, discords_indices, subsequence_indices,
                                         static_cast<bool>(self_join));

        constexpr auto output_size = 3;
        std::array<jlong, output_size> output;
        output[0] = reinterpret_cast<jlong>(new af::array(discords_distances));
        output[1] = reinterpret_cast<jlong>(new af::array(discords_indices));
        output[2] = reinterpret_cast<jlong>(new af::array(subsequence_indices));

        auto pointers = env->NewLongArray(output_size);
        env->SetLongArrayRegion(pointers, 0, output_size, output.data());
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_findBestNDiscords. Unknown reason");
    }
    return 0;
}

jlongArray JNICALL Java_io_shapelets_khiva_Matrix_findBestNMotifs(JNIEnv *env, jobject, jlong ref_profile,
                                                                  jlong ref_index, jlong m, jlong n,
                                                                  jboolean self_join) {
    try {
        auto arr_profile = *reinterpret_cast<af::array *>(ref_profile);
        auto arr_index = *reinterpret_cast<af::array *>(ref_index);
        af::array motifs;
        af::array motifs_indices;
        af::array subsequence_indices;
        khiva::matrix::findBestNMotifs(arr_profile, arr_index, static_cast<long>(m), static_cast<long>(n), motifs,
                                       motifs_indices, subsequence_indices, static_cast<bool>(self_join));

        constexpr auto output_size = 3;
        std::array<jlong, output_size> output;
        output[0] = reinterpret_cast<jlong>(new af::array(motifs));
        output[1] = reinterpret_cast<jlong>(new af::array(motifs_indices));
        output[2] = reinterpret_cast<jlong>(new af::array(subsequence_indices));

        auto pointers = env->NewLongArray(output_size);
        env->SetLongArrayRegion(pointers, 0, output_size, output.data());
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_findBestNMotifs. Unknown reason");
    }
    return 0;
}

jlongArray JNICALL Java_io_shapelets_khiva_Matrix_findBestNOccurrences(JNIEnv *env, jobject, jlong ref_query,
                                                                       jlong ref_ts, jlong n) {
    try {
        auto arr_query = *reinterpret_cast<af::array *>(ref_query);
        auto arr_ts = *reinterpret_cast<af::array *>(ref_ts);
        af::array distance;
        af::array index;        
        khiva::matrix::findBestNOccurrences(arr_query, arr_ts, static_cast<long>(n), distance, index);

        constexpr auto output_size = 2;
        std::array<jlong, output_size> output;
        output[0] = reinterpret_cast<jlong>(new af::array(distance));
        output[1] = reinterpret_cast<jlong>(new af::array(index));

        auto pointers = env->NewLongArray(output_size);
        env->SetLongArrayRegion(pointers, 0, output_size, output.data());
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_findBestNOccurrences. Unknown reason");
    }
    return 0;
}

jlong JNICALL Java_io_shapelets_khiva_Matrix_mass(JNIEnv *env, jobject, jlong ref_query, jlong ref_ts) {
    try {
        auto arr_query = *reinterpret_cast<af::array *>(ref_query);
        auto arr_ts = *reinterpret_cast<af::array *>(ref_ts);
        af::array distance;
        khiva::matrix::mass(arr_query, arr_ts, distance);
        return reinterpret_cast<jlong>(new af::array(distance));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_mass. Unknown reason");
    }
    return 0;
}

jlongArray JNICALL Java_io_shapelets_khiva_Matrix_stomp(JNIEnv *env, jobject, jlong ref_a, jlong ref_b, jlong m) {
    try {
        auto arr_a = *reinterpret_cast<af::array *>(ref_a);
        auto arr_b = *reinterpret_cast<af::array *>(ref_b);
        af::array distance;
        af::array index;
        khiva::matrix::stomp(arr_a, arr_b, static_cast<long>(m), distance, index);

        constexpr auto output_size = 2;
        std::array<jlong, output_size> output;
        output[0] = reinterpret_cast<jlong>(new af::array(distance));
        output[1] = reinterpret_cast<jlong>(new af::array(index));

        auto pointers = env->NewLongArray(output_size);
        env->SetLongArrayRegion(pointers, 0, output_size, output.data());
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_stomp. Unknown reason");
    }
    return 0;
}

jlongArray JNICALL Java_io_shapelets_khiva_Matrix_stompSelfJoin(JNIEnv *env, jobject, jlong ref_a, jlong m) {
    try {
        auto arr_a = *reinterpret_cast<af::array *>(ref_a);
        af::array distance;
        af::array index;
        khiva::matrix::stomp(arr_a, static_cast<long>(m), distance, index);

        constexpr auto output_size = 2;
        std::array<jlong, output_size> output;
        output[0] = reinterpret_cast<jlong>(new af::array(distance));
        output[1] = reinterpret_cast<jlong>(new af::array(index));

        auto pointers = env->NewLongArray(output_size);
        env->SetLongArrayRegion(pointers, 0, output_size, output.data());
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_stompSelfJoin. Unknown reason");
    }
    return 0;
}

jlongArray JNICALL Java_io_shapelets_khiva_Matrix_matrixProfile(JNIEnv *env, jobject, jlong ref_a, jlong ref_b,
                                                                jlong m) {
    try {
        auto arr_a = *reinterpret_cast<af::array *>(ref_a);
        auto arr_b = *reinterpret_cast<af::array *>(ref_b);
        af::array distance;
        af::array index;
        khiva::matrix::matrixProfile(arr_a, arr_b, static_cast<long>(m), distance, index);

        constexpr auto output_size = 2;
        std::array<jlong, output_size> output;
        output[0] = reinterpret_cast<jlong>(new af::array(distance));
        output[1] = reinterpret_cast<jlong>(new af::array(index));

        auto pointers = env->NewLongArray(output_size);
        env->SetLongArrayRegion(pointers, 0, output_size, output.data());
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_Matrixprofile. Unknown reason");
    }
    return 0;
}

jlongArray JNICALL Java_io_shapelets_khiva_Matrix_matrixProfileSelfJoin(JNIEnv *env, jobject, jlong ref_a, jlong m) {
    try {
        auto arr_a = *reinterpret_cast<af::array *>(ref_a);
        af::array distance;
        af::array index;
        khiva::matrix::matrixProfile(arr_a, static_cast<long>(m), distance, index);

        constexpr auto output_size = 2;
        std::array<jlong, output_size> output;
        output[0] = reinterpret_cast<jlong>(new af::array(distance));
        output[1] = reinterpret_cast<jlong>(new af::array(index));

        auto pointers = env->NewLongArray(output_size);
        env->SetLongArrayRegion(pointers, 0, output_size, output.data());
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_MatrixProfileSelfJoin. Unknown reason");
    }
    return 0;
}

JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Matrix_matrixProfileLR(JNIEnv *env, jobject, jlong ref_a,
                                                                            jlong m) {
    try {
        auto arr_a = *reinterpret_cast<af::array *>(ref_a);
        af::array pleft, ileft, pright, iright;
        khiva::matrix::matrixProfileLR(arr_a, static_cast<long>(m), pleft, ileft, pright, iright);

        constexpr auto output_size = 4;
        std::array<jlong, output_size> output;
        output[0] = reinterpret_cast<jlong>(new af::array(pleft));
        output[1] = reinterpret_cast<jlong>(new af::array(ileft));
        output[2] = reinterpret_cast<jlong>(new af::array(pright));
        output[3] = reinterpret_cast<jlong>(new af::array(iright));

        auto pointers = env->NewLongArray(output_size);
        env->SetLongArrayRegion(pointers, 0, output_size, output.data());
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_MatrixProfileLR. Unknown reason");
    }
    return 0;
}

JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Matrix_getChains(JNIEnv *env, jobject, jlong ref_a, jlong m) {
    try {
        auto arr_a = *reinterpret_cast<af::array *>(ref_a);
        af::array chains;
        khiva::matrix::getChains(arr_a, static_cast<long>(m), chains);
        return reinterpret_cast<jlong>(new af::array(chains));
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("java/lang/Exception");
        env->ThrowNew(exceptionClass, "Error in Matrix_mass. Unknown reason");
    }
    return 0;
}
