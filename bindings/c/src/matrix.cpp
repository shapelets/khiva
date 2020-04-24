// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/array.h>
#include <khiva/internal/util.h>
#include <khiva/matrix.h>
#include <khiva_c/internal/util.h>
#include <khiva_c/matrix.h>

#include <iostream>

using namespace khiva;
using namespace khiva::util;

void find_best_n_discords(const khiva_array *profile, const khiva_array *index, long m, long n,
                          khiva_array *discord_distances, khiva_array *discord_indices,
                          khiva_array *subsequence_indices, bool self_join, int *error_code, char *error_message) {
    try {
        auto var_profile = array::from_af_array(*profile);
        auto var_index = array::from_af_array(*index);

        af::array discords;
        af::array discordIndices;
        af::array subsequenceIndices;

        khiva::matrix::findBestNDiscords(var_profile, var_index, m, n, discords, discordIndices, subsequenceIndices,
                                         self_join);
        *discord_distances = array::increment_ref_count(discords.get());
        *discord_indices = array::increment_ref_count(discordIndices.get());
        *subsequence_indices = array::increment_ref_count(subsequenceIndices.get());

    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void find_best_n_motifs(const khiva_array *profile, const khiva_array *index, long m, long n,
                        khiva_array *motif_distances, khiva_array *motif_indices, khiva_array *subsequence_indices,
                        bool self_join, int *error_code, char *error_message) {
    try {
        auto var_profile = array::from_af_array(*profile);
        auto var_index = array::from_af_array(*index);

        af::array motifs;
        af::array motifIndices;
        af::array subsequenceIndices;

        khiva::matrix::findBestNMotifs(var_profile, var_index, m, n, motifs, motifIndices, subsequenceIndices,
                                       self_join);
        *motif_distances = array::increment_ref_count(motifs.get());
        *motif_indices = array::increment_ref_count(motifIndices.get());
        *subsequence_indices = array::increment_ref_count(subsequenceIndices.get());
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void find_best_n_occurrences(const khiva_array *q, const khiva_array *t, long n, khiva_array *distances,
                             khiva_array *indexes, int *error_code, char *error_message) {
    try {
        auto var_q = array::from_af_array(*q);
        auto var_t = array::from_af_array(*t);

        af::array distancesAux;
        af::array indexesAux;

        khiva::matrix::findBestNOccurrences(var_q, var_t, n, distancesAux, indexesAux);

        *distances = array::increment_ref_count(distancesAux.get());
        *indexes = array::increment_ref_count(indexesAux.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void mass(const khiva_array *q, const khiva_array *t, khiva_array *distances, int *error_code, char *error_message) {
    try {
        auto var_q = array::from_af_array(*q);
        auto var_t = array::from_af_array(*t);
        af::array distancesAux;

        khiva::matrix::mass(var_q, var_t, distancesAux);

        *distances = array::increment_ref_count(distancesAux.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void stomp(const khiva_array *tssa, const khiva_array *tssb, long m, khiva_array *p, khiva_array *i, int *error_code,
           char *error_message) {
    try {
        auto var_tssa = array::from_af_array(*tssa);
        auto var_tssb = array::from_af_array(*tssb);
        af::array distance;
        af::array index;

        khiva::matrix::stomp(var_tssa, var_tssb, m, distance, index);

        *p = array::increment_ref_count(distance.get());
        *i = array::increment_ref_count(index.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void stomp_self_join(const khiva_array *tss, long m, khiva_array *p, khiva_array *i, int *error_code,
                     char *error_message) {
    try {
        auto var_tss = array::from_af_array(*tss);
        af::array profile;
        af::array index;

        khiva::matrix::stomp(var_tss, m, profile, index);

        *p = array::increment_ref_count(profile.get());
        *i = array::increment_ref_count(index.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void matrix_profile(const khiva_array *tssa, khiva_array *tssb, long m, khiva_array *p, khiva_array *i, int *error_code,
                    char *error_message) {
    try {
        auto var_tssa = array::from_af_array(*tssa);
        auto var_tssb = array::from_af_array(*tssb);
        af::array distance;
        af::array index;

        khiva::matrix::matrixProfile(var_tssa, var_tssb, m, distance, index);

        *p = array::increment_ref_count(distance.get());
        *i = array::increment_ref_count(index.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void matrix_profile_self_join(const khiva_array *tss, long m, khiva_array *p, khiva_array *i, int *error_code,
                              char *error_message) {
    try {
        auto var_tss = array::from_af_array(*tss);
        af::array profile;
        af::array index;

        khiva::matrix::matrixProfile(var_tss, m, profile, index);

        *p = array::increment_ref_count(profile.get());
        *i = array::increment_ref_count(index.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void matrix_profile_lr(const khiva_array *tss, long m, khiva_array *pleft, khiva_array *ileft, khiva_array *pright,
                       khiva_array *iright, int *error_code, char *error_message) {
    try {
        auto var_tss = array::from_af_array(*tss);
        af::array profileLeft;
        af::array indexesLeft;
        af::array profileRight;
        af::array indexesRight;

        khiva::matrix::matrixProfileLR(var_tss, m, profileLeft, indexesLeft, profileRight, indexesRight);

        *pleft = array::increment_ref_count(profileLeft.get());
        *ileft = array::increment_ref_count(indexesLeft.get());
        *pright = array::increment_ref_count(profileRight.get());
        *iright = array::increment_ref_count(indexesRight.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void get_chains(const khiva_array *tss, long m, khiva_array *c, int *error_code, char *error_message) {
    try {
        auto var_tss = array::from_af_array(*tss);
        af::array chains;

        khiva::matrix::getChains(var_tss, m, chains);

        *c = array::increment_ref_count(chains.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}
