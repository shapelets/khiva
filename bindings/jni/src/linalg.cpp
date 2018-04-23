//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa/linalg.h>
#include <tsa_jni/linalg.h>

#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT void JNICALL Java_tsa_Linalg_lls(JNIEnv *env, jobject thisObj, jdoubleArray a, jlong aL, jlong aN,
                                           jdoubleArray b, jlong bL, jdoubleArray result) {
    long a_fl = aL * aN;
    jdouble input_a[a_fl];
    env->GetDoubleArrayRegion(a, 0, a_fl, &input_a[0]);
    jdouble input_b[bL];
    env->GetDoubleArrayRegion(b, 0, bL, &input_b[0]);
    af::array primitive_result;
    primitive_result = tsa::linalg::lls(af::array(aL, aN, input_a), af::array(bL, input_b));
    jdouble output_result[aN];
    primitive_result.host(output_result);
    env->SetDoubleArrayRegion(result, 0, aN, &output_result[0]);
    return;
}
#ifdef __cplusplus
}
#endif
