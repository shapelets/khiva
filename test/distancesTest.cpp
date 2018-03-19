// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <tsa.h>
#include "tsatest.h"

// Simple test, does not use gmock
void euclidean() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(4, 3, data);

    auto result = tsa::distances::euclidean(tss);

    // check dimensions
    auto dims = result.dims();
    ASSERT_EQ(dims[0], 3);
    ASSERT_EQ(dims[1], 3);
    ASSERT_EQ(dims[2], 1);
    ASSERT_EQ(dims[3], 1);

    // check distances
    float *hostResult = result.host<float>();
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

// Simple test, does not use gmock
void squaredEuclidean() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(4, 3, data);

    auto result = tsa::distances::squaredEuclidean(tss);

    // check dimensions
    auto dims = result.dims();
    ASSERT_EQ(dims[0], 3);
    ASSERT_EQ(dims[1], 3);
    ASSERT_EQ(dims[2], 1);
    ASSERT_EQ(dims[3], 1);

    // check distances
    float *hostResult = result.host<float>();
    ASSERT_EQ(0.0, hostResult[0]);
    ASSERT_EQ(0.0, hostResult[1]);
    ASSERT_EQ(0.0, hostResult[2]);
    ASSERT_EQ(64.0, hostResult[3]);
    ASSERT_EQ(0.0, hostResult[4]);
    ASSERT_EQ(0.0, hostResult[5]);
    ASSERT_EQ(256.0, hostResult[6]);
    ASSERT_EQ(64.0, hostResult[7]);
    ASSERT_EQ(0.0, hostResult[8]);
}

TSA_TEST(DistanceTests, Euclidean, euclidean);
TSA_TEST(DistanceTests, SquaredEuclidean, squaredEuclidean);
