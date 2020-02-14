// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/matrix.h>
#include <khiva_c/matrix.h>
#include <khiva_c/internal/util.h>
#include <iostream>

void find_best_n_discords(khiva_array *profile, khiva_array *index, long *m, long *n, khiva_array *discord_distances,
                          khiva_array *discord_indices, khiva_array *subsequence_indices, bool *self_join,
                          int *error_code, char *error_message) {
    try {
        af::array var_profile;
        af::array var_index;
        check_and_retain_arrays(profile, index, var_profile, var_index);

        af::array discords;
        af::array discordIndices;
        af::array subsequenceIndices;

        khiva::matrix::findBestNDiscords(var_profile, var_index, *m, *n, discords, discordIndices, subsequenceIndices,
                                         self_join);
        af_retain_array(discord_distances, discords.get());
        af_retain_array(discord_indices, discordIndices.get());
        af_retain_array(subsequence_indices, subsequenceIndices.get());

    } catch (const std::exception &e) {
        fill_error("find_best_n_discords", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("find_best_n_discords", error_message, error_code, -1);
    }
}

void find_best_n_motifs(khiva_array *profile, khiva_array *index, long *m, long *n, khiva_array *motif_distances,
                        khiva_array *motif_indices, khiva_array *subsequence_indices, bool *self_join, int *error_code,
                        char *error_message) {
    try {
        af::array var_profile;
        af::array var_index;
        check_and_retain_arrays(profile, index, var_profile, var_index);

        af::array motifs;
        af::array motifIndices;
        af::array subsequenceIndices;

        khiva::matrix::findBestNMotifs(var_profile, var_index, *m, *n, motifs, motifIndices, subsequenceIndices,
                                       self_join);

        af_retain_array(motif_distances, motifs.get());
        af_retain_array(motif_indices, motifIndices.get());
        af_retain_array(subsequence_indices, subsequenceIndices.get());
    } catch (const std::exception &e) {
        fill_error("find_best_n_motifs", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("find_best_n_motifs", error_message, error_code, -1);
    }
}

void find_best_n_occurrences(khiva_array *q, khiva_array *t, long *n, khiva_array *distances, khiva_array *indexes,
                             int *error_code, char *error_message) {
    try {
        af::array var_q;
        af::array var_t;
        check_and_retain_arrays(q, t, var_q, var_t);
        af::array distancesAux, indexesAux;

        khiva::matrix::findBestNOccurrences(var_q, var_t, *n, distancesAux, indexesAux);

        af_retain_array(distances, distancesAux.get());
        af_retain_array(indexes, indexesAux.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("find_best_n_occurrences", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("find_best_n_occurrences", error_message, error_code, -1);
    }
}

void mass(khiva_array *q, khiva_array *t, khiva_array *distances, int *error_code, char *error_message) {
    try {
        af::array var_q;
        af::array var_t;
        check_and_retain_arrays(q, t, var_q, var_t);
        af::array distancesAux;

        khiva::matrix::mass(var_q, var_t, distancesAux);

        af_retain_array(distances, distancesAux.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("mass", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("mass", error_message, error_code, -1);
    }
}

void stomp(khiva_array *tssa, khiva_array *tssb, long *m, khiva_array *p, khiva_array *i, int *error_code,
           char *error_message) {
    try {
        af::array var_tssa;
        af::array var_tssb;
        check_and_retain_arrays(tssa, tssb, var_tssa, var_tssb);
        af::array distance;
        af::array index;

        khiva::matrix::stomp(var_tssa, var_tssb, *m, distance, index);

        af_retain_array(p, distance.get());
        af_retain_array(i, index.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("stomp", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("stomp", error_message, error_code, -1);
    }
}

void stomp_self_join(khiva_array *tss, long *m, khiva_array *p, khiva_array *i, int *error_code, char *error_message) {
    try {
        af::array var_tss = af::array(*tss);
        af_retain_array(tss, var_tss.get());
        af::array profile;
        af::array index;

        khiva::matrix::stomp(var_tss, *m, profile, index);

        af_retain_array(p, profile.get());
        af_retain_array(i, index.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("stomp_self_join", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("stomp_self_join", error_message, error_code, -1);
    }
}

void matrix_profile(khiva_array *tssa, khiva_array *tssb, long *m, khiva_array *p, khiva_array *i, int *error_code,
                    char *error_message) {
    try {
        af::array var_tssa;
        af::array var_tssb;
        check_and_retain_arrays(tssa, tssb, var_tssa, var_tssb);
        af::array distance;
        af::array index;

        khiva::matrix::matrixProfile(var_tssa, var_tssb, *m, distance, index);

        af_retain_array(p, distance.get());
        af_retain_array(i, index.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("matrix_profile", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("matrix_profile", error_message, error_code, -1);
    }
}

void matrix_profile_self_join(khiva_array *tss, long *m, khiva_array *p, khiva_array *i, int *error_code,
                              char *error_message) {
    try {
        af::array var_tss = af::array(*tss);
        af_retain_array(tss, var_tss.get());
        af::array profile;
        af::array index;

        khiva::matrix::matrixProfile(var_tss, *m, profile, index);

        af_retain_array(p, profile.get());
        af_retain_array(i, index.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("matrix_profile_self_join", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("matrix_profile_self_join", error_message, error_code, -1);
    }
}

void matrix_profile_lr(khiva_array *tss, long *m, khiva_array *pleft, khiva_array *ileft, khiva_array *pright,
                       khiva_array *iright, int *error_code, char *error_message) {
    try {
        af::array var_tss = af::array(*tss);
        af_retain_array(tss, var_tss.get());
        af::array profileLeft, indexesLeft, profileRight, indexesRight;

        khiva::matrix::matrixProfileLR(var_tss, *m, profileLeft, indexesLeft, profileRight, indexesRight);

        af_retain_array(pleft, profileLeft.get());
        af_retain_array(ileft, indexesLeft.get());
        af_retain_array(pright, profileRight.get());
        af_retain_array(iright, indexesRight.get());

        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("matrix_profile_lr", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("matrix_profile_lr", error_message, error_code, -1);
    }
}

void get_chains(khiva_array *tss, long *m, khiva_array *c, int *error_code, char *error_message) {
    try {
        af::array var_tss = af::array(*tss);
        af_retain_array(tss, var_tss.get());
        af::array chains;

        khiva::matrix::getChains(var_tss, *m, chains);

        af_retain_array(c, chains.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("get_chains", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("get_chains", error_message, error_code, -1);
    }
}
