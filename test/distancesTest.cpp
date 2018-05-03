// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <tsa/distances.h>
#include "tsaTest.h"

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

void dwt() {
    std::vector<double> a;
    std::vector<double> b;

    a.push_back(4);
    a.push_back(4);
    a.push_back(5);
    a.push_back(5);
    a.push_back(6);
    a.push_back(6);
    a.push_back(7);
    a.push_back(7);

    b.push_back(23);
    b.push_back(4);
    b.push_back(5);
    b.push_back(6);
    b.push_back(7);

    double result = tsa::distances::dwt(a, b);

    ASSERT_EQ(result, 19);
}

void dwt2() {
    float data[] = {1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5};
    af::array tss(5, 5, data);

    af::array result = tsa::distances::dwt(tss);

    // check dimensions
    auto dims = result.dims();
    ASSERT_EQ(dims[0], 5);
    ASSERT_EQ(dims[1], 5);
    ASSERT_EQ(dims[2], 1);
    ASSERT_EQ(dims[3], 1);

    // check distances
    float *hostResult = result.host<float>();
    int i = 0;
    ASSERT_EQ(0.0, hostResult[i++]);
    ASSERT_EQ(0.0, hostResult[i++]);
    ASSERT_EQ(0.0, hostResult[i++]);
    ASSERT_EQ(0.0, hostResult[i++]);
    ASSERT_EQ(0.0, hostResult[i++]);

    ASSERT_EQ(5.0, hostResult[i++]);
    ASSERT_EQ(0.0, hostResult[i++]);
    ASSERT_EQ(0.0, hostResult[i++]);
    ASSERT_EQ(0.0, hostResult[i++]);
    ASSERT_EQ(0.0, hostResult[i++]);

    ASSERT_EQ(10.0, hostResult[i++]);
    ASSERT_EQ(5.0, hostResult[i++]);
    ASSERT_EQ(0.0, hostResult[i++]);
    ASSERT_EQ(0.0, hostResult[i++]);
    ASSERT_EQ(0.0, hostResult[i++]);

    ASSERT_EQ(15.0, hostResult[i++]);
    ASSERT_EQ(10.0, hostResult[i++]);
    ASSERT_EQ(5.0, hostResult[i++]);
    ASSERT_EQ(0.0, hostResult[i++]);
    ASSERT_EQ(0.0, hostResult[i++]);

    ASSERT_EQ(20.0, hostResult[i++]);
    ASSERT_EQ(15.0, hostResult[i++]);
    ASSERT_EQ(10.0, hostResult[i++]);
    ASSERT_EQ(5.0, hostResult[i++]);
    ASSERT_EQ(0.0, hostResult[i++]);
}

TSA_TEST(DistanceTests, Euclidean, euclidean);
TSA_TEST(DistanceTests, SquaredEuclidean, squaredEuclidean);
TSA_TEST(DistanceTests, DWT, dwt);
TSA_TEST(DistanceTests, DWT2, dwt2);
