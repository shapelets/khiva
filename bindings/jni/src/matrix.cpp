// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <tsa/matrix.h>
#include <tsa_jni/matrix.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL Java_tsa_Matrix_findBestNDiscords(JNIEnv *env, jobject thisObj, jdoubleArray profile,
                                                         jintArray index, jlong lengthProfile, jlong n,
                                                         jdoubleArray jDiscordDistances, jintArray jDiscordIndices,
                                                         jintArray jSubsequenceIndices) {
    af::array discords;
    af::array discordIndices;
    af::array subsequenceIndices;

    jdouble inputP[lengthProfile];
    jint inputI[lengthProfile];

    env->GetDoubleArrayRegion(profile, 0, lengthProfile, &inputP[0]);
    env->GetIntArrayRegion(index, 0, lengthProfile, &inputI[0]);

    tsa::matrix::findBestNDiscords(af::array(lengthProfile, inputP), af::array(lengthProfile, inputI), n, discords,
                                   discordIndices, subsequenceIndices);

    jdouble inputDiscords[n];
    jint inputDiscordIndices[n];
    jint inputSubsequenceIndices[n];

    discords.host(inputDiscords);
    discordIndices.host(inputDiscordIndices);
    subsequenceIndices.host(inputSubsequenceIndices);

    env->SetDoubleArrayRegion(jDiscordDistances, 0, n, &inputDiscords[0]);
    env->SetIntArrayRegion(jDiscordIndices, 0, n, &inputDiscordIndices[0]);
    env->SetIntArrayRegion(jSubsequenceIndices, 0, n, &inputSubsequenceIndices[0]);

    return;
}

JNIEXPORT void JNICALL Java_tsa_Matrix_findBestNMotifs(JNIEnv *env, jobject thisObj, jdoubleArray profile,
                                                       jintArray index, jlong lengthProfile, jlong n,
                                                       jdoubleArray jMotifDistances, jintArray jMotifIndices,
                                                       jintArray jSubsequenceIndices) {
    af::array motifs;
    af::array motifIndices;
    af::array subsequenceIndices;

    jdouble inputP[lengthProfile];
    jint inputI[lengthProfile];

    env->GetDoubleArrayRegion(profile, 0, lengthProfile, &inputP[0]);
    env->GetIntArrayRegion(index, 0, lengthProfile, &inputI[0]);

    tsa::matrix::findBestNMotifs(af::array(lengthProfile, inputP), af::array(lengthProfile, inputI), n, motifs,
                                 motifIndices, subsequenceIndices);

    jdouble inputMotifs[n];
    jint inputMotifIndices[n];
    jint inputSubsequenceIndices[n];

    motifs.host(inputMotifs);
    motifIndices.host(inputMotifIndices);
    subsequenceIndices.host(inputSubsequenceIndices);

    env->SetDoubleArrayRegion(jMotifDistances, 0, n, &inputMotifs[0]);
    env->SetIntArrayRegion(jMotifIndices, 0, n, &inputMotifIndices[0]);
    env->SetIntArrayRegion(jSubsequenceIndices, 0, n, &inputSubsequenceIndices[0]);

    return;
}

JNIEXPORT void JNICALL Java_tsa_Matrix_stomp(JNIEnv *env, jobject thisObj, jdoubleArray ta, jdoubleArray tb, jlong lta,
                                             jlong ltb, jlong m, jdoubleArray p, jintArray i) {
    af::array distance;
    af::array index;

    jdouble input_ta[lta];
    jdouble input_tb[ltb];

    env->GetDoubleArrayRegion(ta, 0, lta, &input_ta[0]);
    env->GetDoubleArrayRegion(tb, 0, ltb, &input_tb[0]);

    af::array ata = af::array(lta, input_ta);
    af::array atb = af::array(ltb, input_tb);

    long subsequence = m;

    tsa::matrix::stomp(ata, atb, subsequence, distance, index);

    jdouble input_p[ltb - m + 1];
    jint input_i[ltb - m + 1];

    distance.host(input_p);
    index.host(input_i);

    env->SetDoubleArrayRegion(p, 0, ltb - m + 1, &input_p[0]);
    env->SetIntArrayRegion(i, 0, ltb - m + 1, &input_i[0]);

    return;
}

JNIEXPORT void JNICALL Java_tsa_Matrix_stompSelfJoin(JNIEnv *env, jobject thisObj, jdoubleArray ta, jlong lta, jlong m,
                                                     jdoubleArray p, jintArray i) {
    af::array distance;
    af::array index;

    jdouble input_ta[lta];

    env->GetDoubleArrayRegion(ta, 0, lta, &input_ta[0]);

    af::array ata = af::array(lta, input_ta);

    long subsequence = m;

    tsa::matrix::stomp(ata, subsequence, distance, index);

    jdouble input_p[lta - m + 1];
    jint input_i[lta - m + 1];

    distance.host(input_p);
    index.host(input_i);

    env->SetDoubleArrayRegion(p, 0, lta - m + 1, &input_p[0]);
    env->SetIntArrayRegion(i, 0, lta - m + 1, &input_i[0]);

    return;
}

#ifdef __cplusplus
}
#endif
