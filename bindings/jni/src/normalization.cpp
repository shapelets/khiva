// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa/normalization.h>
#include <tsa_jni/normalization.h>

#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT void JNICALL Java_tsa_Normalization_znorm(JNIEnv *env, jobject thisObj, jdoubleArray tss, jlong tss_l,
                                                    jlong tss_n, jdouble epsilon, jdoubleArray result) {
    long tss_fl = tss_l * tss_n;
    jdouble input_tss[tss_fl];
    env->GetDoubleArrayRegion(tss, 0, tss_fl, &input_tss[0]);
    af::array primitive_result;
    primitive_result = tsa::normalization::znorm(af::array(tss_l, tss_n, input_tss), epsilon);
    jdouble output_result[tss_n * tss_l];
    primitive_result.host(output_result);
    env->SetDoubleArrayRegion(result, 0, tss_n * tss_l, &output_result[0]);
    return;
}

JNIEXPORT void JNICALL Java_tsa_Normalization_znormInPlace(JNIEnv *env, jobject thisObj, jdoubleArray tss, jlong tssL,
                                                           jlong tssN, jdouble epsilon) {
    long tss_fl = tssL * tssN;
    jdouble input_tss[tss_fl];
    env->GetDoubleArrayRegion(tss, 0, tss_fl, &input_tss[0]);
    af::array primitive_result = af::array(tssL, tssN, input_tss);
    tsa::normalization::znormInPlace(primitive_result, epsilon);
    jdouble output_result[tssN * tssL];
    primitive_result.host(output_result);
    env->SetDoubleArrayRegion(tss, 0, tssN * tssL, &output_result[0]);
    return;
}

#ifdef __cplusplus
}
#endif