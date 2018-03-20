// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

namespace tsa {

namespace matrix {

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
void find_best_n_discords(double *profile, unsigned int *index, long *length_profile, long *n,
                          double *discord_distances, int *discord_indices, int *subsequence_indices);

/**
 * @brief Primitive of the findBestNMotifs function.
 *
 * @param profile The matrix profile containing the minimum distance of each
 * subsequence
 * @param index The matrix profile index containing where each minimum occurs
 * @param length_profile Length of the matrix profile
 * @param n Number of motifs to extract
 * @param motif_distances The distance of the best N motifs
 * @param motif_indices The indices of the best N motifs
 * @param subsequence_indices The indices of the query sequences that produced
 * the minimum reported in the motifs
 */
void find_best_n_motifs(double *profile, unsigned int *index, long *length_profile, long *n, double *motif_distances,
                        int *motif_indices, int *subsequence_indices);

/**
 * @brief  Primitive of the STOMP algorithm.
 *
 * @param ta Pointer of an array of doubles with the first time series values.
 * @param tb Pointer of an array of doubles with the second time series values.
 * @param lta Pointer to an integer with the length of the first time series.
 * @param ltb Pointer to an integer with the length of the second time series.
 * @param m Pointer to a long with the length of the subsequence.
 * @param p Pointer to an initialized array of doubles for storing the distance
 * profile.
 * @param i Pointer to an initialized array of doubles for storing the index
 * profile.
 */
void stomp(double *ta, double *tb, long *lta, long *ltb, long *m, double *p, unsigned int *i);

/**
 * @brief Primitive of the STOMP self join algorithm.
 *
 * @param ta Pointer of an array of doubles with the first time series values.
 * @param lta Pointer to an integer with the length of the first time series.
 * @param m Pointer to a long with the length of the subsequence.
 * @param p Pointer to an initialized  array of doubles for storing the distance
 * profile.
 * @param i Pointer to an initialized  array of doubles for storing the index
 * profile.
 */
void stomp_self_join(double *ta, long *lta, long *m, double *p, unsigned int *i);

#ifdef __cplusplus
}
#endif
};  // namespace matrix
};  // namespace tsa