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
 */
KHIVAAPI void find_best_n_discords(khiva_array *profile, khiva_array *index, long *m, long *n,
                                   khiva_array *discord_distances, khiva_array *discord_indices,
                                   khiva_array *subsequence_indices, bool *self_join);

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
 */
KHIVAAPI void find_best_n_motifs(khiva_array *profile, khiva_array *index, long *m, long *n,
                                 khiva_array *motif_distances, khiva_array *motif_indices,
                                 khiva_array *subsequence_indices, bool *self_join);

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
 */
KHIVAAPI void stomp(khiva_array *tssa, khiva_array *tssb, long *m, khiva_array *p, khiva_array *i);

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
 */
KHIVAAPI void stomp_self_join(khiva_array *tss, long *m, khiva_array *p, khiva_array *i);

#ifdef __cplusplus
}
#endif

#endif
