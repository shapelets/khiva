// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_BINDINGC_MATRIX_H
#define KHIVA_BINDINGC_MATRIX_H

#include <khiva_c/defines.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Primitive of the findBestNDiscords function.
 *
 * @param profile The matrix profile containing the minimum distance of each
 * subsequence
 * @param The matrix profile index containing the index of the most similar
 * subsequence
 * @param length_profile Length of the matrix profile
 * @param m Subsequence length value used to calculate the input matrix profile.
 * @param n Number of discords to extract
 * @param discord_distances The distance of the best N discords
 * @param discord_indices The indices of the best N discords
 * @param subsequence_indices The indices of the query sequences that produced
 * the "N" bigger discords.
 * @param self_join Indicates whether the input profile comes from a self join operation or not. It determines
 * whether the mirror similar region is included in the output or not.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void find_best_n_discords(khiva_array *profile, khiva_array *index, const long *m, const long *n,
                                      khiva_array *discord_distances, khiva_array *discord_indices,
                                      khiva_array *subsequence_indices, bool *self_join, int *error_code,
                                      char *error_message);

/**
 * @brief Primitive of the findBestNMotifs function.
 *
 * @param profile The matrix profile containing the minimum distance of each
 * subsequence.
 * @param index The matrix profile index containing where each minimum occurs.
 * @param length_profile Length of the matrix profile.
 * @param m Subsequence length value used to calculate the input matrix profile.
 * @param n Number of motifs to extract.
 * @param motif_distances The distance of the best N motifs.
 * @param motif_indices The indices of the best N motifs.
 * @param subsequence_indices The indices of the query sequences that produced
 * the minimum reported in the motifs.
 * @param self_join Indicates whether the input profile comes from a self join operation or not. It determines
 * whether the mirror similar region is included in the output or not.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void find_best_n_motifs(khiva_array *profile, khiva_array *index, const long *m, const long *n,
                                    khiva_array *motif_distances, khiva_array *motif_indices,
                                    khiva_array *subsequence_indices, bool *self_join, int *error_code,
                                    char *error_message);

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
 * @param q Array whose first dimension is the length of the query time series and the second dimension is the number of
 * queries.
 * @param t Array whose first dimension is the length of the time series and the second dimension is the number of time
 * series.
 * @param n Number of matches to return.
 * @param distances Resulting distances.
 * @param indexes Resulting indexes.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void find_best_n_occurrences(khiva_array *q, khiva_array *t, const long *n, khiva_array *distances,
                                         khiva_array *indexes, int *error_code, char *error_message);

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
 * @param q Array whose first dimension is the length of the query time series and the second dimension is the number of
 * queries.
 * @param t Array whose first dimension is the length of the time series and the second dimension is the number of time
 * series.
 * @param distances Resulting distances.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void mass(khiva_array *q, khiva_array *t, khiva_array *distances, int *error_code, char *error_message);

/**
 * @brief  Primitive of the STOMP algorithm.
 *
 * [1] Yan Zhu, Zachary Zimmerman, Nader Shakibay Senobari, Chin-Chia Michael Yeh, Gareth Funning, Abdullah Mueen,
 * Philip Brisk and Eamonn Keogh (2016). Matrix Profile II: Exploiting a Novel Algorithm and GPUs to break the one
 * Hundred Million Barrier for Time Series Motifs and Joins. IEEE ICDM 2016.
 *
 * @param tssa Query time series
 * @param tssb Reference time series
 * @param m Pointer to a long with the length of the subsequence.
 * @param p The matrix profile, which reflects the distance to the closer element of the subsequence
 * from 'tssa' in 'tssb'.
 * @param i The matrix profile index, which points to where the aforementioned minimum is located.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void stomp(khiva_array *tssa, khiva_array *tssb, const long *m, khiva_array *p, khiva_array *i, int *error_code,
                       char *error_message);

/**
 * @brief Primitive of the STOMP self join algorithm.
 *
 * [1] Yan Zhu, Zachary Zimmerman, Nader Shakibay Senobari, Chin-Chia Michael Yeh, Gareth Funning, Abdullah Mueen,
 * Philip Brisk and Eamonn Keogh (2016). Matrix Profile II: Exploiting a Novel Algorithm and GPUs to break the one
 * Hundred Million Barrier for Time Series Motifs and Joins. IEEE ICDM 2016.
 *
 * @param tss Query and reference time series
 * @param m Pointer to a long with the length of the subsequence.
 * @param p The matrix profile, which reflects the distance to the closer element of the subsequence
 * from 'tss' in a different location of itself
 * @param i The matrix profile index, which points to where the aforementioned minimum is located
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void stomp_self_join(khiva_array *tss, const long *m, khiva_array *p, khiva_array *i, int *error_code,
                                 char *error_message);

/**
 * @brief Matrix Profile algorithm
 *
 * [1] Yan Zhu, Zachary Zimmerman, Nader Shakibay Senobari, Chin-Chia Michael Yeh, Gareth Funning, Abdullah Mueen,
 * Philip Brisk and Eamonn Keogh (2016). Matrix Profile II: Exploiting a Novel Algorithm and GPUs to break the one
 * Hundred Million Barrier for Time Series Motifs and Joins. IEEE ICDM 2016.
 *
 * @param tssa Query time series
 * @param tssb Reference time series
 * @param m Pointer to a long with the length of the subsequence.
 * @param p The matrix profile, which reflects the distance to the closer element of the subsequence
 * from 'tssa' in 'tssb'.
 * @param i The matrix profile index, which points to where the aforementioned minimum is located.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void matrix_profile(khiva_array *tssa, khiva_array *tssb, const long *m, khiva_array *p, khiva_array *i,
                                int *error_code, char *error_message);

/**
 * @brief Matrix Profile self join algorithm.
 *
 * [1] Yan Zhu, Zachary Zimmerman, Nader Shakibay Senobari, Chin-Chia Michael Yeh, Gareth Funning, Abdullah Mueen,
 * Philip Brisk and Eamonn Keogh (2016). Matrix Profile II: Exploiting a Novel Algorithm and GPUs to break the one
 * Hundred Million Barrier for Time Series Motifs and Joins. IEEE ICDM 2016.
 *
 * @param tss Query and reference time series
 * @param m Pointer to a long with the length of the subsequence.
 * @param p The matrix profile, which reflects the distance to the closer element of the subsequence
 * from 'tss' in a different location of itself
 * @param i The matrix profile index, which points to where the aforementioned minimum is located
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void matrix_profile_self_join(khiva_array *tss, const long *m, khiva_array *p, khiva_array *i, int *error_code,
                                          char *error_message);

/**
 * @brief Calculates the matrix profile to the left and to the right between 't' and using a subsequence length of 'm'.
 *
 * [1] Yan Zhu, Makoto Imamura, Daniel Nikovski, and Eamonn Keogh. Matrix Profile VII: Time Series Chains: A New
 * Primitive for Time Series Data Mining. IEEE ICDM 2017.
 *
 * @param tss Time series to compute the matrix profile.
 * @param m Subsequence length.
 * @param pleft The matrix profile distance to the left.
 * @param ileft The subsequence index of the matrix profile to the left.
 * @param pright The matrix profile distance to the right.
 * @param iright The subsequence index of the matrix profile to the right.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 *
 *  Notice that when there is no match the subsequence index is the length of tss.
 */
KHIVA_C_API void matrix_profile_lr(khiva_array *tss, const long *m, khiva_array *pleft, khiva_array *ileft,
                                   khiva_array *pright, khiva_array *iright, int *error_code, char *error_message);

/**
 * @brief Calculates all the chains within 'tss' using a subsequence length of 'm'.
 *
 * [1] Yan Zhu, Makoto Imamura, Daniel Nikovski, and Eamonn Keogh. Matrix Profile VII: Time Series Chains: A New
*  Primitive for Time Series Data Mining. IEEE ICDM 2017
 *
 * @param tss Time series to compute the chains within them.
 * @param m Subsequence length.
 * @param chains The calculated chains with the following topology:
 *  - 1st dimension corresponds to the chains indexes flattened.
 *  - 2nd dimension:
                - [0] corresponds to all the indexes in the chains flattened
                - [1] corresponds to the index of the chain that the value in [0] belongs to.
 *  - 3rd dimension corresponds to the number of time series.
 *
 *  Notice that the size of the first dimension is the maximum possible size which is n - m + 1. If the number of
 *  values belonging to a chain is lower than the maximum, the remaining values and indexes are 0. It implies
 *  that 0 is an invalid chain index.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void get_chains(khiva_array *tss, const long *m, khiva_array *chains, int *error_code, char *error_message);

#ifdef __cplusplus
}
#endif

#endif
