// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/polynomial.h>
#include <khiva_jni/polynomial.h>
#include <khiva_jni/util.h>

jlongArray JNICALL Java_io_shapelets_khiva_Polynomial_polyfit(JNIEnv *env, jobject, jlong refX, jlong refY, jint deg) {
    const jint l = 3;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array xx = (af_array)refX;
    af::array x;
    af_array yy = (af_array)refY;
    af::array y;
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    check_and_retain_arrays(xx, yy, x, y);

    af_retain_array(&af_p, khiva::polynomial::polyfit(x, y, deg).get());
    tmp[0] = (jlong)xx;
    tmp[1] = (jlong)yy;
    tmp[2] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

jlongArray JNICALL Java_io_shapelets_khiva_Polynomial_roots(JNIEnv *env, jobject, jlong ref) {
    const jint l = 2;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr = (af_array)ref;
    af::array var = af::array(arr);

    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr, var.get());
    af_retain_array(&af_p, khiva::polynomial::roots(var).get());

    tmp[0] = (jlong)arr;
    tmp[1] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}
