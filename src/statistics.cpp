// Copyright (c) 2018 Grumpy Cat Software S.L.
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa.h>

af::array tsa::statistics::covariance(af::array x, af::array y, bool bias) {
    long n = x.dims(0);
    long fact = n - !bias;

    af::array input = af::join(1, x, y);

    input -= af::tile(af::mean(input, 0), n, 1);

    return af::matmul(af::transpose(input),af::conjg(input)) / 2;
}