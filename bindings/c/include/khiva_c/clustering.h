// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva_c/defines.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Calculates the clusterization based on SBD.
 *
 * @param tss       Expects a 2D-Array of Time-Series.
 * @param k         Is the number of clusters that will be calculated. Must be an integer number
 *                  greater than zero.
 * @param tolerance Clusterization is stopping if the accumulative error between successive groups of centroids
 *                  is smaller than this parameter.
 * @param centroids Is an output array containing the calculated centroids.
 */
KHIVAAPI void kShape(khiva_array *tss, int *k, float *tolerance, khiva_array *idx, khiva_array *centroids);

#ifdef __cplusplus
}
#endif