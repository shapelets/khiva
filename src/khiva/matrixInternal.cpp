// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "matrixInternal.h"

#include <cmath>

namespace khiva {
namespace matrix {
namespace internal {

bool tileIsFarFromDiagonal(long bandSize, long numRows, long row, long numColumns, long column) {
    // Check if the band would cross the tile
    return !(std::abs(row - column) < bandSize ||                     // Upper-Left corner
             std::abs(row + numRows - 1 - column) < bandSize ||       // Lower-Left corner
             std::abs(row - (column + numColumns - 1)) < bandSize ||  // Upper-Right corner
             (row - column) * (row + numRows - 1 - column) < 0 ||     // Cross the Left side
             (row - column) * (row - (column + numColumns - 1)) < 0   // Cross the Upper side
    );
}

af::array generateMask(long m, long numRows, long row, long numColumns, long column, long nTimeSeries) {
    auto bandSize = static_cast<long>(std::ceil(m / 2.0f)) + 1;
    if (tileIsFarFromDiagonal(bandSize, numRows, row, numColumns, column)) {
        return af::constant(0, numRows, numColumns, nTimeSeries);
    }

    // Expand the identity by a band in the four side of the tail.
    auto expandedSizeB = numRows + 2 * bandSize;
    auto expandedSizeA = numColumns + 2 * bandSize;
    auto identity = af::identity(expandedSizeB, expandedSizeA);

    // Check what side cross the diagonal: Upper, Left, the Upper-Left corner
    auto shifted = identity;
    auto shifting = std::abs(column - row);
    if (row > column) {
        // Crossing upper side
        shifted = af::shift(identity, 0, shifting);
        shifted(af::span, af::seq(0, shifting - 1)) = af::constant(0, expandedSizeB, shifting);
    } else if (row < column) {
        // Crossing left side
        shifted = af::shift(identity, shifting, 0);
        shifted(af::seq(0, shifting - 1), af::span) = af::constant(0, shifting, expandedSizeA);
    }
    // else: Matching the diagonal -> No shift

    auto kernel = af::constant(1, bandSize, bandSize);
    auto convolved = af::convolve2(shifted, kernel) > 0;
    auto mask = convolved(af::seq(bandSize, bandSize + numRows - 1), af::seq(bandSize, bandSize + numColumns - 1));

    return af::tile(mask, 1, 1, static_cast<unsigned int>(nTimeSeries));
}

}  // namespace internal
}  // namespace matrix
}  // namespace khiva
