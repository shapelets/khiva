// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_BINDINGJAVA_INTERNAL_UTILS_H
#define KHIVA_BINDINGJAVA_INTERNAL_UTILS_H

#include <jni.h>

namespace khiva {
namespace jni {

template <typename Func, typename... Args>
jlong KhivaCall(JNIEnv *env, Func f, jlong ref, Args &&... args) {
    try {
        auto arr = *reinterpret_cast<af::array *>(ref);
        auto result = f(arr, std::forward<Args>(args)...);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        auto exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        auto exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Unknown error executing native function");
    }
    return 0;
}

template <typename Func, typename... Args>
jlong KhivaCallTwoArrays(JNIEnv *env, Func f, jlong ref_a, jlong ref_b, Args &&... args) {
    try {
        auto arr_a = *reinterpret_cast<af::array *>(ref_a);
        auto arr_b = *reinterpret_cast<af::array *>(ref_b);
        auto result = f(arr_a, arr_b, std::forward<Args>(args)...);
        return reinterpret_cast<jlong>(new af::array(result));
    } catch (const std::exception &e) {
        auto exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, e.what());
    } catch (...) {
        auto exceptionClass = env->FindClass("io/shapelets/khiva/KhivaException");
        env->ThrowNew(exceptionClass, "Unknown error executing native function");
    }
    return 0;
}
}  // namespace jni
}  // namespace khiva
#endif