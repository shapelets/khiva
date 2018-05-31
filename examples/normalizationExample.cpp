// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <tsa.h>

void maxMinNorm() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    af::array tss(4, 2, data);

    float *resultingData = tsa::normalization::maxMinNorm(tss, 2.0, 1.0).host<float>();
}

void maxMinNormInPlace() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    af::array tss(4, 2, data);

    tsa::normalization::maxMinNormInPlace(tss, 2.0, 1.0);

    float *resultingData = tss.host<float>();
}

void zNorm() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    af::array tss(4, 2, data);

    float *resultingData = tsa::normalization::znorm(tss).host<float>();
}

void zNormInPlace() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    af::array tss(4, 2, data);

    tsa::normalization::znormInPlace(tss);

    float *resultingData = tss.host<float>();
}

int main() {
    maxMinNorm();
    maxMinNormInPlace();

    zNorm();
    zNormInPlace();

    return 0;
}