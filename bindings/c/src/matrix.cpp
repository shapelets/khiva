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

void find_best_n_discords(af_array *profile, af_array *index, long *n, af_array *discord_distances,
                          af_array *discord_indices, af_array *subsequence_indices) {
    af::array var_profile = af::array(*profile);
    af::array var_index = af::array(*index);
    af_retain_array(profile, var_profile.get());
    af_retain_array(index, var_index.get());

    af::array discords;
    af::array discordIndices;
    af::array subsequenceIndices;
    tsa::matrix::findBestNDiscords(var_profile, var_index, *n, discords, discordIndices, subsequenceIndices);
    af_retain_array(discord_distances, discords.get());
    af_retain_array(discord_indices, discordIndices.get());
    af_retain_array(subsequence_indices, subsequenceIndices.get());
}

void find_best_n_motifs(af_array *profile, af_array *index, long *n, af_array *motif_distances, af_array *motif_indices,
                        af_array *subsequence_indices) {
    af::array var_profile = af::array(*profile);
    af::array var_index = af::array(*index);
    af_retain_array(profile, var_profile.get());
    af_retain_array(index, var_index.get());

    af::array motifs;
    af::array motifIndices;
    af::array subsequenceIndices;
    tsa::matrix::findBestNMotifs(var_profile, var_index, *n, motifs, motifIndices, subsequenceIndices);
    af_retain_array(motif_distances, motifs.get());
    af_retain_array(motif_indices, motifIndices.get());
    af_retain_array(subsequence_indices, subsequenceIndices.get());
}

void stomp(af_array *tssa, af_array *tssb, long *m, af_array *p, af_array *i) {
    af::array var_tssa = af::array(*tssa);
    af::array var_tssb = af::array(*tssb);
    af_retain_array(tssa, var_tssa.get());
    af_retain_array(tssb, var_tssb.get());

    af::array distance;
    af::array index;
    tsa::matrix::stomp(var_tssa, var_tssb, *m, distance, index);
    af_retain_array(p, distance.get());
    af_retain_array(i, index.get());
}

void stomp_self_join(af_array *tss, long *m, af_array *p, af_array *i) {
    af::array var_tss = af::array(*tss);
    af_retain_array(tss, var_tss.get());

    af::array profile;
    af::array index;

    tsa::matrix::stomp(var_tss, *m, profile, index);
    af_retain_array(p, profile.get());
    af_retain_array(i, index.get());
}

#ifdef __cplusplus
}
#endif
