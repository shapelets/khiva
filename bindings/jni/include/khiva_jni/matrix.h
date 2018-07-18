// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief This function extracts the best N motifs from a previously calculated matrix profile.
 *
 * @param ref_profile The matrix profile containing the minimum distance of each
 * subsequence.
 * @param ref_index The matrix profile index containing where each minimum occurs.
 * @param m Subsequence length value used to calculate the input matrix profile.
 * @param n Number of motifs to extract.
 * @param self_join Indicates whether the input profile comes from a self join operation or not. It determines
 * whether the mirror similar region is included in the output or not.
 * @return The updated ref_profile and ref_index and references to:
 *           - The distance of the best N motifs.
 *           - The indices of the best N motifs.
 *           - The indices of the query sequences that produced
 *             the minimum reported in the motifs.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Matrix_findBestNMotifs(JNIEnv *env, jobject, jlong ref_profile,
                                                                            jlong ref_index, jlong m, jlong n,
                                                                            jboolean self_join);

/**
 * @brief This function extracts the best N motifs from a previously calculated matrix profile.
 *
 * @param ref_profile The matrix profile containing the minimum distance of each
 * subsequence.
 * @param ref_index The matrix profile index containing where each maximum occurs.
 * @param m Subsequence length value used to calculate the input matrix profile.
 * @param n Number of discords to extract.
 * @param self_join Indicates whether the input profile comes from a self join operation or not. It determines
 * whether the mirror similar region is included in the output or not.
 * @return The updated ref_profile and ref_index and references to:
 *          - The distance of the best N discords.
 *          - The indices of the best N discords.
 *          - The indices of the query sequences that produced
 *            the "N" bigger discords.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Matrix_findBestNDiscords(JNIEnv *env, jobject, jlong ref_profile,
                                                                              jlong ref_index, jlong m, jlong n,
                                                                              jboolean self_join);

/**
 * @brief STOMP algorithm to calculate the matrix profile between 'ta' and 'tb' using a subsequence length
 * of 'm'.
 *
 * @param ref_a Query time series.
 * @param ref_b Reference time series.
 * @param m The length of the subsequence.
 * @return The updated ref_a and ref_b and references to:
 *          - The distance profile.
 *          - The index profile.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Matrix_stomp(JNIEnv *env, jobject, jlong ref_a, jlong ref_b,
                                                                  jlong m);

/**
 * @brief STOMP algorithm to calculate the matrix profile between 't' and itself using a subsequence length
 * of 'm'. This method filters the trivial matches.
 *
 * @param ref_a Query and reference time series.
 * @param m Subsequence length.Subsequence length.
 * @return The updated ref_a and references to:
 *          - The matrix profile, which reflects the distance to the closer element of the subsequence
 *            from 't' in a different location of itself.
 *          - The matrix profile index, which points to where the aforementioned minimum is located.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Matrix_stompSelfJoin(JNIEnv *env, jobject, jlong ref_a, jlong m);

#ifdef __cplusplus
}
#endif
