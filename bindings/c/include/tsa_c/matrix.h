// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <tsa_c/defines.h>

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
 * @param n Number of discords to extract
 * @param discord_distances The distance of the best N discords
 * @param discord_indices The indices of the best N discords
 * @param subsequence_indices The indices of the query sequences that produced
 * the "N" bigger discords.
 */
TSAAPI void find_best_n_discords(af_array *profile, af_array *index, long *n, af_array *discord_distances,
                                 af_array *discord_indices, af_array *subsequence_indices);

/**
 * @brief Primitive of the findBestNMotifs function.
 *
 * @param profile The matrix profile containing the minimum distance of each
 * subsequence.
 * @param index The matrix profile index containing where each minimum occurs.
 * @param length_profile Length of the matrix profile.
 * @param n Number of motifs to extract.
 * @param motif_distances The distance of the best N motifs.
 * @param motif_indices The indices of the best N motifs.
 * @param subsequence_indices The indices of the query sequences that produced
 * the minimum reported in the motifs.
 */
TSAAPI void find_best_n_motifs(af_array *profile, af_array *index, long *n, af_array *motif_distances,
                               af_array *motif_indices, af_array *subsequence_indices);

/**
 * @brief  Primitive of the STOMP algorithm.
 *
 * @param tssa Query time series
 * @param tssb Reference time series
 * @param m Pointer to a long with the length of the subsequence.
 * @param p The matrix profile, which reflects the distance to the closer element of the subsequence
 * from 'tssa' in 'tssb'.
 * @param i The matrix profile index, which points to where the aforementioned minimum is located.
 */
TSAAPI void stomp(af_array *tssa, af_array *tssb, long *m, af_array *p, af_array *i);

/**
 * @brief Primitive of the STOMP self join algorithm.
 *
 * @param tss Query and reference time series
 * @param m Pointer to a long with the length of the subsequence.
 * @param p The matrix profile, which reflects the distance to the closer element of the subsequence
 * from 'tss' in a different location of itself
 * @param i The matrix profile index, which points to where the aforementioned minimum is located
 */
TSAAPI void stomp_self_join(af_array *tss, long *m, af_array *p, af_array *i);

#ifdef __cplusplus
}
#endif