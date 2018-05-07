// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa/linalg.h>
#include <tsa_jni/linalg.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlongArray JNICALL Java_com_gcatsoft_tsa_Linalg_lls(JNIEnv *env, jobject thisObj, jlong ref_a, jlong ref_b) {
    jint l = 3;
    jlong tmp[l];
    jlongArray pointers = env->NewLongArray(l);

    af_array arr_a = (af_array)ref_a;
    af::array var_a = af::array(arr_a);
    af_array arr_b = (af_array)ref_b;
    af::array var_b = af::array(arr_b);
    jlong raw_pointer = 0;
    af_array af_p = (af_array)raw_pointer;

    af_retain_array(&arr_a, var_a.get());
    af_retain_array(&arr_b, var_b.get());

    af_retain_array(&af_p, tsa::linalg::lls(var_a, var_b).get());

    tmp[0] = (jlong)arr_a;
    tmp[1] = (jlong)arr_b;
    tmp[2] = (jlong)af_p;

    env->SetLongArrayRegion(pointers, 0, l, &tmp[0]);

    return pointers;
}

#ifdef __cplusplus
}
#endif
