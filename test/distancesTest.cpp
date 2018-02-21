// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "tsa.h"
#include "gtest/gtest.h"

// Simple test, does not use gmock
TEST(DistanceTests, Euclidian)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(4, 3, data);

    auto result = tsa::distances::euclidian(tss);
    
    // check dimensions
    auto dims = result.dims();
    ASSERT_EQ(dims[0], 3);
    ASSERT_EQ(dims[1], 3);
    ASSERT_EQ(dims[2], 1);
    ASSERT_EQ(dims[3], 1);

    // check distances
    double* hostResult = result.host<double>();    
    ASSERT_EQ(0.0, hostResult[0]);
    ASSERT_EQ(0.0, hostResult[1]);
    ASSERT_EQ(0.0, hostResult[2]);
    ASSERT_EQ(8.0, hostResult[3]);
    ASSERT_EQ(0.0, hostResult[4]);
    ASSERT_EQ(0.0, hostResult[5]);
    ASSERT_EQ(16.0, hostResult[6]);
    ASSERT_EQ(8.0, hostResult[7]);
    ASSERT_EQ(0.0, hostResult[8]);
}
