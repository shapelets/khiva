// Copyright (c) 2018 Grumpy Cat Software S.L.
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "tsa.h"
#include "gtest/gtest.h"

TEST(FeatureTests, absEnergy)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    af::array tss(10, 1, data);

    auto result = tsa::features::absEnergy(tss);

    double expected[] = {385};
    double* host_res = result.host<double>();
    
    for (int i=0; i<1; i++) {
        ASSERT_NEAR(host_res[i], expected[i], 0.00000001);
    }
}

TEST(FeatureTests, absEnergy2)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4};
    af::array tss(4, 3, data);

    auto result = tsa::features::absEnergy(tss);

    double expected[] = {30, 30, 30, 30};
    double* host_res = result.host<double>();
    
    for (int i=0; i<1; i++) {
        ASSERT_NEAR(host_res[i], expected[i], 0.00000001);
    }
}