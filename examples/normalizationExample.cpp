// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva.h>

void maxMinNorm() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    af::array tss(4, 2, data);

    auto *resultingData = khiva::normalization::maxMinNorm(tss, 2.0, 1.0).host<float>();
    af::freeHost(resultingData);
}

void maxMinNormInPlace() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    af::array tss(4, 2, data);

    khiva::normalization::maxMinNormInPlace(tss, 2.0, 1.0);

    auto *resultingData = tss.host<float>();
    af::freeHost(resultingData);
}

void zNorm() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    af::array tss(4, 2, data);

    auto *resultingData = khiva::normalization::znorm(tss).host<float>();
    af::freeHost(resultingData);
}

void zNormInPlace() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7};
    af::array tss(4, 2, data);

    khiva::normalization::znormInPlace(tss);

    auto *resultingData = tss.host<float>();
    af::freeHost(resultingData);
}

int main() {
    maxMinNorm();
    maxMinNormInPlace();

    zNorm();
    zNormInPlace();

    return 0;
}
