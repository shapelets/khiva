// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_BINDINGJAVA_MATRIX_H
#define KHIVA_BINDINGJAVA_MATRIX_H

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
 * @return References to:
 *           - The distance of the best N motifs.
 *           - The indexes of the best N motifs.
 *           - The indexes of the query sequences that produced
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
 * @return References to:
 *          - The distance of the best N discords.
 *          - The indexes of the best N discords.
 *          - The indexes of the query sequences that produced
 *            the "N" bigger discords.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Matrix_findBestNDiscords(JNIEnv *env, jobject, jlong ref_profile,
                                                                              jlong ref_index, jlong m, jlong n,
                                                                              jboolean self_join);

/**
 * @brief Calculates the N best matches of several queries in several time series.
 *
 * The result has the following structure:
 *  - 1st dimension corresponds to the nth best match.
 *  - 2nd dimension corresponds to the number of queries.
 *  - 3rd dimension corresponds to the number of time series.
 *
 * For example, the distance in the position (1, 2, 3) corresponds to the second best distance of the third query in the
 * fourth time series. The index in the position (1, 2, 3) is the is the index of the subsequence which leads to the
 * second best distance of the third query in the fourth time series.
 *
 * @param ref_query Array whose first dimension is the length of the query time series and the second dimension is the
 * number of queries.
 * @param ref_ts Array whose first dimension is the length of the time series and the second dimension is the number of
 * time series.
 * @param n Number of matches to return.
 * @return References to:
 *          - The resulting distances.
 *          - The resulting indexes.
 */
JNIEXPORT jlongArray Java_io_shapelets_khiva_Matrix_findBestNOccurrences(JNIEnv *env, jobject, jlong ref_query,
                                                                         jlong ref_ts, jlong n);

/**
 * @brief Mueen's Algorithm for Similarity Search.
 *
 * The result has the following structure:
 *  - 1st dimension corresponds to the index of the subsequence in the time series.
 *  - 2nd dimension corresponds to the number of queries.
 *  - 3rd dimension corresponds to the number of time series.
 *
 * For example, the distance in the position (1, 2, 3) correspond to the distance of the third query to the fourth time
 * series for the second subsequence in the time series.
 *
 * [1] Chin-Chia Michael Yeh, Yan Zhu, Liudmila Ulanova, Nurjahan Begum, Yifei Ding, Hoang Anh Dau, Diego Furtado Silva,
 * Abdullah Mueen, Eamonn Keogh (2016). Matrix Profile I: All Pairs Similarity Joins for Time Series: A Unifying View
 * that Includes Motifs, Discords and Shapelets. IEEE ICDM 2016.
 *
 * @param ref_query Array whose first dimension is the length of the query time series and the second dimension is the
 * number of queries.
 * @param ref_ts Array whose first dimension is the length of the time series and the second dimension is the number of
 * time series.
 * @return A reference to the resulting distances.
 *
 */
JNIEXPORT jlong Java_io_shapelets_khiva_Matrix_mass(JNIEnv *env, jobject, jlong ref_query, jlong ref_ts);

/**
 * @brief STOMP algorithm to calculate the matrix profile between 'ta' and 'tb' using a subsequence length
 * of 'm'.
 *
 * [1] Yan Zhu, Zachary Zimmerman, Nader Shakibay Senobari, Chin-Chia Michael Yeh, Gareth Funning, Abdullah Mueen,
 * Philip Brisk and Eamonn Keogh (2016). Matrix Profile II: Exploiting a Novel Algorithm and GPUs to break the one
 * Hundred Million Barrier for Time Series Motifs and Joins. IEEE ICDM 2016.
 *
 * @param ref_a Query time series.
 * @param ref_b Reference time series.
 * @param m The length of the subsequence.
 * @return References to:
 *          - The distance profile.
 *          - The index profile.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Matrix_stomp(JNIEnv *env, jobject, jlong ref_a, jlong ref_b,
                                                                  jlong m);

/**
 * @brief STOMP algorithm to calculate the matrix profile between 't' and itself using a subsequence length
 * of 'm'. This method filters the trivial matches.
 *
 * [1] Yan Zhu, Zachary Zimmerman, Nader Shakibay Senobari, Chin-Chia Michael Yeh, Gareth Funning, Abdullah Mueen,
 * Philip Brisk and Eamonn Keogh (2016). Matrix Profile II: Exploiting a Novel Algorithm and GPUs to break the one
 * Hundred Million Barrier for Time Series Motifs and Joins. IEEE ICDM 2016.
 *
 * @param ref_a Query and reference time series.
 * @param m Subsequence length.Subsequence length.
 * @return References to:
 *          - The matrix profile, which reflects the distance to the closer element of the subsequence
 *            from 't' in a different location of itself.
 *          - The matrix profile index, which points to where the aforementioned minimum is located.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Matrix_stompSelfJoin(JNIEnv *env, jobject, jlong ref_a, jlong m);

/**
 * @brief Calculates the matrix profile between 'ta' and 'tb' using a subsequence length
 * of 'm'.
 *
 * [1] Yan Zhu, Zachary Zimmerman, Nader Shakibay Senobari, Chin-Chia Michael Yeh, Gareth Funning, Abdullah Mueen,
 * Philip Brisk and Eamonn Keogh (2016). Matrix Profile II: Exploiting a Novel Algorithm and GPUs to break the one
 * Hundred Million Barrier for Time Series Motifs and Joins. IEEE ICDM 2016.
 *
 * @param ref_a Query time series.
 * @param ref_b Reference time series.
 * @param m The length of the subsequence.
 * @return References to:
 *          - The distance profile.
 *          - The index profile.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Matrix_matrixProfile(JNIEnv *env, jobject, jlong ref_a,
                                                                          jlong ref_b, jlong m);

/**
 * @brief Calculates the matrix profile between 't' and itself using a subsequence length
 * of 'm'. This method filters the trivial matches.
 *
 * [1] Yan Zhu, Zachary Zimmerman, Nader Shakibay Senobari, Chin-Chia Michael Yeh, Gareth Funning, Abdullah Mueen,
 * Philip Brisk and Eamonn Keogh (2016). Matrix Profile II: Exploiting a Novel Algorithm and GPUs to break the one
 * Hundred Million Barrier for Time Series Motifs and Joins. IEEE ICDM 2016.
 *
 * @param ref_a Query and reference time series.
 * @param m Subsequence length.Subsequence length.
 * @return References to:
 *          - The matrix profile, which reflects the distance to the closer element of the subsequence
 *            from 't' in a different location of itself.
 *          - The matrix profile index, which points to where the aforementioned minimum is located.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Matrix_matrixProfileSelfJoin(JNIEnv *env, jobject, jlong ref_a,
                                                                                  jlong m);

/**
 * @brief Calculates the matrix profile to the left and to the right between 't' and using a subsequence length of 'm'.
 *
 * [1] Yan Zhu, Makoto Imamura, Daniel Nikovski, and Eamonn Keogh. Matrix Profile VII: Time Series Chains: A New
 * Primitive for Time Series Data Mining. IEEE ICDM 2017.
 *
 * @param ref_a Time series to compute the matrix profile.
 * @param m Subsequence length.
 * @return References to:
 *          - The matrix profile to the left distances
 *          - The subsequence indexes to the left
 *          - The matrix profile to the right distances
 *          - The subsequence indexes to the right
 *
 *  Notice that when there is no match the subsequence index is the length of tss.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Matrix_matrixProfileLR(JNIEnv *env, jobject, jlong ref_a, jlong m);

/**
 * @brief Calculates all the chains within 'tss' using a subsequence length of 'm'.
 *
 * [1] Yan Zhu, Makoto Imamura, Daniel Nikovski, and Eamonn Keogh. Matrix Profile VII: Time Series Chains: A New
*  Primitive for Time Series Data Mining. IEEE ICDM 2017.
 *
 * @param ref_a Time series to compute the chains within them.
 * @param m Subsequence length.
 * @return A reference to the calculated chains with the following topology:
 *  - 1st dimension corresponds to the chains indexes flattened.
 *  - 2nd dimension:
                - [0] corresponds to all the indexes in the chains flattened
                - [1] corresponds to the index of the chain that the value in [0] belongs to.
 *  - 3rd dimension corresponds to the number of time series.
 *
 *  Notice that the size of the first dimension is the maximum possible size which is n - m + 1. If the number of
 *  values belonging to a chain is lower than the maximum, the remaining values and indexes are 0. It implies
 *  that 0 is an invalid chain index.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Matrix_getChains(JNIEnv *env, jobject, jlong ref_a, jlong m);

#ifdef __cplusplus
}
#endif

#endif
