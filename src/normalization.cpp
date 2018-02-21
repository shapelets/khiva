// Copyright (c) 2018 Grumpy Cat Software S.L.
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.


#include <tsa.h>

af::array tsa::normalization::znorm(af::array tss, double epsilon) {
    auto mean = af::tile(af::mean(tss, 0), tss.dims(0));
    auto stdev = af::tile(af::max(epsilon, af::stdev(tss, 0)), tss.dims(0));
    return (tss - mean) / stdev;
}

void tsa::normalization::znormInPlace(af::array &tss, double epsilon) {
    auto mean = af::tile(af::mean(tss, 0), tss.dims(0));
    auto stdev = af::tile(af::max(epsilon, af::stdev(tss, 0)), tss.dims(0));
    tss -= mean;
    tss /= stdev;
}
