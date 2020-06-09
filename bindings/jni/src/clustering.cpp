// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/clustering.h>
#include <khiva_jni/clustering.h>
#include <array>

JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Clustering_kMeans(JNIEnv *env, jobject, jlong ref_tss, jint k,
                                                                       jfloat tolerance, jint maxIterations) {
    try {
        auto arr = *reinterpret_cast<af::array*>(ref_tss);
        
        af::array primitive_labels;
        af::array primitive_centroids;
        khiva::clustering::kMeans(arr, k, primitive_centroids, primitive_labels, tolerance, static_cast<int>(maxIterations));

        auto centroids_result = new af::array(primitive_centroids);
        auto labels_result = new af::array(primitive_labels);

        constexpr auto output_size = 2;
        std::array<jlong, output_size> output;
        output[0] = reinterpret_cast<jlong>(centroids_result);
        output[1] = reinterpret_cast<jlong>(labels_result);

        auto pointers = env->NewLongArray(output_size);
        env->SetLongArrayRegion(pointers, 0, output_size, output.data());
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Clustering_kMeans. Unknown reason");
    }
    return nullptr;
}

JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Clustering_kShape(JNIEnv *env, jobject, jlong ref_tss, jint k,
                                                                       jfloat tolerance, jint maxIterations) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref_tss);

        af::array primitive_labels;
        af::array primitive_centroids;
        khiva::clustering::kShape(arr, k, primitive_centroids, primitive_labels, tolerance, static_cast<int>(maxIterations));

        auto centroids_result = new af::array(primitive_centroids);
        auto labels_result = new af::array(primitive_labels);

        constexpr auto output_size = 2;
        std::array<jlong, output_size> output;
        output[0] = reinterpret_cast<jlong>(centroids_result);
        output[1] = reinterpret_cast<jlong>(labels_result);

        auto pointers = env->NewLongArray(output_size);
        env->SetLongArrayRegion(pointers, 0, output_size, output.data());
        return pointers;
    } catch (const std::exception &e) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        jclass exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Error in Clustering_kShape. Unknown reason");
    }
    return nullptr;
}
