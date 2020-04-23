// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_BINDINGJAVA_INTERNAL_JNI_TRAITS_H
#define KHIVA_BINDINGJAVA_INTERNAL_JNI_TRAITS_H

#include <jni.h>
#include <khiva/array.h>

namespace khiva {
namespace jni {

    template <typename T>
struct ArrayTraits {};

template <>
struct ArrayTraits<float> {
    using JavaType = jfloat;
    using JavaTypePtr = jfloat *;
    using JavaArrayType = jfloatArray;

    static constexpr auto type = khiva::dtype::f32;
    static constexpr auto newArray = &JNIEnv::NewFloatArray;
    static constexpr auto getArrayElements = &JNIEnv::GetFloatArrayElements;
    static constexpr auto releaseArrayElements = &JNIEnv::ReleaseFloatArrayElements;
};

template <>
struct ArrayTraits<double> {
    using JavaType = jdouble;
    using JavaTypePtr = jdouble *;
    using JavaArrayType = jdoubleArray;

    static constexpr auto type = khiva::dtype::f64;
    static constexpr auto newArray = &JNIEnv::NewDoubleArray;
    static constexpr auto getArrayElements = &JNIEnv::GetDoubleArrayElements;
    static constexpr auto releaseArrayElements = &JNIEnv::ReleaseDoubleArrayElements;
};

template <>
struct ArrayTraits<int> {
    using JavaType = jint;
    using JavaTypePtr = jint *;
    using JavaArrayType = jintArray;

    static constexpr auto type = khiva::dtype::s32;
    static constexpr auto newArray = &JNIEnv::NewIntArray;
    static constexpr auto getArrayElements = &JNIEnv::GetIntArrayElements;
    static constexpr auto releaseArrayElements = &JNIEnv::ReleaseIntArrayElements;
};

template <>
struct ArrayTraits<bool> {
    using JavaType = jboolean;
    using JavaTypePtr = jboolean *;
    using JavaArrayType = jbooleanArray;

    static constexpr auto type = khiva::dtype::b8;
    static constexpr auto newArray = &JNIEnv::NewBooleanArray;
    static constexpr auto getArrayElements = &JNIEnv::GetBooleanArrayElements;
    static constexpr auto releaseArrayElements = &JNIEnv::ReleaseBooleanArrayElements;
};

template <>
struct ArrayTraits<long> {
    using JavaType = jlong;
    using JavaTypePtr = jlong *;
    using JavaArrayType = jlongArray;

    static constexpr auto type = khiva::dtype::s64;
    static constexpr auto newArray = &JNIEnv::NewLongArray;
    static constexpr auto getArrayElements = &JNIEnv::GetLongArrayElements;
    static constexpr auto releaseArrayElements = &JNIEnv::ReleaseLongArrayElements;
};

template <>
struct ArrayTraits<short> {
    using JavaType = jshort;
    using JavaTypePtr = jshort *;
    using JavaArrayType = jshortArray;

    static constexpr auto type = khiva::dtype::s16;
    static constexpr auto newArray = &JNIEnv::NewShortArray;
    static constexpr auto getArrayElements = &JNIEnv::GetShortArrayElements;
    static constexpr auto releaseArrayElements = &JNIEnv::ReleaseShortArrayElements;
};

template <>
struct ArrayTraits<byte> {
    using JavaType = jbyte;
    using JavaTypePtr = jbyte *;
    using JavaArrayType = jbyteArray;

    static constexpr auto type = khiva::dtype::u8;
    static constexpr auto newArray = &JNIEnv::NewByteArray;
    static constexpr auto getArrayElements = &JNIEnv::GetByteArrayElements;
    static constexpr auto releaseArrayElements = &JNIEnv::ReleaseByteArrayElements;
};
}  // namespace jni
}  // namespace khiva
#endif