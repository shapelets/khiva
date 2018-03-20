// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <tsa/matrix.h>
#include <tsa_c/matrix.h>

#ifdef __cplusplus
extern "C" {
#endif

void find_best_n_discords(double *profile, unsigned int *index, long *length_profile, long *n,
                          double *discord_distances, int *discord_indices, int *subsequence_indices) {
    af::array discords;
    af::array discordIndices;
    af::array subsequenceIndices;
    tsa::matrix::findBestNDiscords(af::array(*length_profile, profile), af::array(*length_profile, index), *n, discords,
                                   discordIndices, subsequenceIndices);
    discords.host(discord_distances);
    discordIndices.host(discord_indices);
    subsequenceIndices.host(subsequence_indices);
}

void find_best_n_motifs(double *profile, unsigned int *index, long *length_profile, long *n, double *motif_distances,
                        int *motif_indices, int *subsequence_indices) {
    af::array motifs;
    af::array motifIndices;
    af::array subsequenceIndices;
    tsa::matrix::findBestNMotifs(af::array(*length_profile, profile), af::array(*length_profile, index), *n, motifs,
                                 motifIndices, subsequenceIndices);
    motifs.host(motif_distances);
    motifIndices.host(motif_indices);
    subsequenceIndices.host(subsequence_indices);
}

void stomp(double *ta, double *tb, long *lta, long *ltb, long *m, double *p, unsigned int *i) {
    af::array distance;
    af::array index;
    tsa::matrix::stomp(af::array(*lta, ta), af::array(*ltb, tb), *m, distance, index);
    distance.host(p);
    index.host(i);
}

void stomp_self_join(double *ta, long *lta, long *m, double *p, unsigned int *i) {
    af::array distance;
    af::array index;
    tsa::matrix::stomp(af::array(*lta, ta), *m, distance, index);
    distance.host(p);
    index.host(i);
}

#ifdef __cplusplus
}
#endif
