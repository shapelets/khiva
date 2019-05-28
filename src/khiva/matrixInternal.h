// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_CORE_MATRIX_INTERNAL_H
#define KHIVA_CORE_MATRIX_INTERNAL_H

#ifndef BUILDING_KHIVA
#error Internal headers cannot be included from user code
#endif

#include <arrayfire.h>

namespace khiva {
namespace matrix {
namespace internal {

/**
 * @brief Given a tile indices and sizes it returns true when tile would not be affected
 * by a identity band matrix
 *
 * @param bandSize The band size.
 * @param numRows Number of rows of the tile.
 * @param row Starting row of the tile.
 * @param numColumns Number of columns of the tile.
 * @param column Starting column of the tile.
 *
 * @return If it is far or not.
 */
bool tileIsFarFromDiagonal(long bandSize, long numRows, long row, long numColumns, long column);

/**
 * @brief Generate an identity band matrix for a given tile indices.
 *
 * @param m The query size.
 * @param numRows Number of rows of the tile.
 * @param row Starting row of the tile.
 * @param numColumns Number of columns of the tile.
 * @param column Starting column of the tile.
 * @param nTimeSeries Number of time series.
 *
 * @return The mask.
 */
af::array generateMask(long m, long numRows, long row, long numColumns, long column, long nTimeSeries = 1);

}  // namespace internal
}  // namespace matrix
}  // namespace khiva

#endif
