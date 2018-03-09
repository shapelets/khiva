// Copyright (c) 2018 Grumpy Cat Software S.L.
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa.h>

af::array tsa::statistics::covariance(af::array xss, af::array yss) {
    long n = xss.dims(0);
    af::array result = af::constant(0, 2, 2, xss.dims(1), xss.type());

    //using a regular for loop since the matmul operation is not supported inside GFOR
    for(long currentCol = 0; currentCol < xss.dims(1); currentCol++) {
        af::array input = af::join(1, xss(span, currentCol), yss(span, currentCol));

        input -= af::tile(af::mean(input, 0), n, 1, 1);

        result(span, span, currentCol) = af::matmul(af::transpose(input), af::conjg(input)) / 2;
    }

    return result;
}