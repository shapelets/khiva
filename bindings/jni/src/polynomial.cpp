// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/polynomial.h>
#include <khiva_jni/polynomial.h>
#include <khiva_jni/internal/utils.h>

jlong JNICALL Java_io_shapelets_khiva_Polynomial_polyfit(JNIEnv *env, jobject, jlong refX, jlong refY, jint deg) {
    return khiva::jni::KhivaCallTwoArrays(env, khiva::polynomial::polyfit, refX, refY, deg);
}

jlong JNICALL Java_io_shapelets_khiva_Polynomial_roots(JNIEnv *env, jobject, jlong ref) {
    return khiva::jni::KhivaCall(env, khiva::polynomial::roots, ref);
}
