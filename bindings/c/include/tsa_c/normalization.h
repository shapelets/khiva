// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Calculates a new set of timeseries with zero mean and standard deviation one.
 *
 * @param tss Time series concatenated in a single row.
 * @param tss_l Time series length (All time series need to have the same length).
 * @param tss_n Number of time series.
 * @param epsilon Minimum standard deviation to consider.  It acts a a gatekeeper for
 * those time series that may be constant or near constant.
 * @param result Array with the same dimensions as tss where the time series have been
 * adjusted for zero mean and one as standard deviation.
 */
void znorm(af_array *tss, double *epsilon, af_array *result);

/**
 * @brief Adjusts the time series in the given input and performs z-norm
 * inplace (without allocating further memory).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @param epsilon Minimum standard deviation to consider.  It acts a a gatekeeper for
 * those Time series that may be constant or near constant.
 */
void znorm_in_place(af_array *tss, double *epsilon);

#ifdef __cplusplus
}
#endif