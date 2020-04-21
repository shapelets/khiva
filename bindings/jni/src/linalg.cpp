// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/linalg.h>
#include <khiva_jni/linalg.h>
#include <khiva_jni/internal/utils.h>

jlong JNICALL Java_io_shapelets_khiva_Linalg_lls(JNIEnv *env, jobject, jlong ref_a, jlong ref_b) {
    return khiva::jni::KhivaCallTwoArrays(env, khiva::linalg::lls, ref_a, ref_b);
}
