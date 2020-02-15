// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <khiva/distances.h>
#include <khiva/internal/scopedHostPtr.h>
#include "khivaTest.h"

void dtw() {
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

    double result = khiva::distances::dtw(a, b);

    ASSERT_EQ(result, 19);
}

void dtw2() {
    float data[] = {1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5};
    af::array tss(5, 5, data);

    af::array result = khiva::distances::dtw(tss);

    // check dimensions
    auto dims = result.dims();
    ASSERT_EQ(dims[0], 5);
    ASSERT_EQ(dims[1], 5);
    ASSERT_EQ(dims[2], 1);
    ASSERT_EQ(dims[3], 1);

    // check distances
    auto hostResult = khiva::utils::makeScopedHostPtr(result.host<float>());
    int i = 0;
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);

    ASSERT_EQ(5.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);

    ASSERT_EQ(10.0f, hostResult[i++]);
    ASSERT_EQ(5.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);

    ASSERT_EQ(15.0f, hostResult[i++]);
    ASSERT_EQ(10.0f, hostResult[i++]);
    ASSERT_EQ(5.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);

    ASSERT_EQ(20.0f, hostResult[i++]);
    ASSERT_EQ(15.0f, hostResult[i++]);
    ASSERT_EQ(10.0f, hostResult[i++]);
    ASSERT_EQ(5.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
}

void euclidean() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(4, 3, data);

    auto result = khiva::distances::euclidean(tss);

    // check dimensions
    auto dims = result.dims();
    ASSERT_EQ(dims[0], 3);
    ASSERT_EQ(dims[1], 3);
    ASSERT_EQ(dims[2], 1);
    ASSERT_EQ(dims[3], 1);

    // check distances
    auto hostResult = khiva::utils::makeScopedHostPtr(result.host<float>());
    ASSERT_EQ(0.0f, hostResult[0]);
    ASSERT_EQ(0.0f, hostResult[1]);
    ASSERT_EQ(0.0f, hostResult[2]);
    ASSERT_EQ(8.0f, hostResult[3]);
    ASSERT_EQ(0.0f, hostResult[4]);
    ASSERT_EQ(0.0f, hostResult[5]);
    ASSERT_EQ(16.0f, hostResult[6]);
    ASSERT_EQ(8.0f, hostResult[7]);
    ASSERT_EQ(0.0f, hostResult[8]);
}

void hamming() {
    float data[] = {1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5};
    af::array tss(5, 5, data);

    af::array result = khiva::distances::hamming(tss);

    // check dimensions
    auto dims = result.dims();
    ASSERT_EQ(dims[0], 5);
    ASSERT_EQ(dims[1], 5);
    ASSERT_EQ(dims[2], 1);
    ASSERT_EQ(dims[3], 1);

    // check distances
    auto hostResult = khiva::utils::makeScopedHostPtr(result.host<float>());
    int i = 0;
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);

    ASSERT_EQ(5.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);

    ASSERT_EQ(5.0f, hostResult[i++]);
    ASSERT_EQ(5.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);

    ASSERT_EQ(5.0f, hostResult[i++]);
    ASSERT_EQ(5.0f, hostResult[i++]);
    ASSERT_EQ(5.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);

    ASSERT_EQ(5.0f, hostResult[i++]);
    ASSERT_EQ(5.0f, hostResult[i++]);
    ASSERT_EQ(5.0f, hostResult[i++]);
    ASSERT_EQ(5.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
}

void manhattan() {
    float data[] = {1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5};
    af::array tss(5, 5, data);

    af::array result = khiva::distances::manhattan(tss);

    // check dimensions
    auto dims = result.dims();
    ASSERT_EQ(dims[0], 5);
    ASSERT_EQ(dims[1], 5);
    ASSERT_EQ(dims[2], 1);
    ASSERT_EQ(dims[3], 1);

    // check distances
    auto hostResult = khiva::utils::makeScopedHostPtr(result.host<float>());
    int i = 0;
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);

    ASSERT_EQ(5.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);

    ASSERT_EQ(10.0f, hostResult[i++]);
    ASSERT_EQ(5.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);

    ASSERT_EQ(15.0f, hostResult[i++]);
    ASSERT_EQ(10.0f, hostResult[i++]);
    ASSERT_EQ(5.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);

    ASSERT_EQ(20.0f, hostResult[i++]);
    ASSERT_EQ(15.0f, hostResult[i++]);
    ASSERT_EQ(10.0f, hostResult[i++]);
    ASSERT_EQ(5.0f, hostResult[i++]);
    ASSERT_EQ(0.0f, hostResult[i++]);
}

void sbd() {
    float data[] = {1, 2, 3, 4, 5, 1, 1, 0, 1, 1, 10, 12, 0, 0, 1};
    af::array tss(5, 3, data);

    auto result = khiva::distances::sbd(tss);

    // check dimensions
    auto dims = result.dims();
    ASSERT_EQ(dims[0], 3);
    ASSERT_EQ(dims[1], 3);
    ASSERT_EQ(dims[2], 1);
    ASSERT_EQ(dims[3], 1);

    // check distances
    auto hostResult = khiva::utils::makeScopedHostPtr(result.host<float>());
    ASSERT_EQ(0.0f, hostResult[0]);
    ASSERT_EQ(0.0f, hostResult[1]);
    ASSERT_EQ(0.0f, hostResult[2]);
    ASSERT_NEAR(0.505025f, hostResult[3], EPSILON);
    ASSERT_EQ(0.0f, hostResult[4]);
    ASSERT_EQ(0.0f, hostResult[5]);
    ASSERT_NEAR(0.458583f, hostResult[6], EPSILON);
    ASSERT_NEAR(0.564093f, hostResult[7], EPSILON);
    ASSERT_EQ(0.0f, hostResult[8]);
}

void squaredEuclidean() {
    float data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    af::array tss(4, 3, data);

    auto result = khiva::distances::squaredEuclidean(tss);

    // check dimensions
    auto dims = result.dims();
    ASSERT_EQ(dims[0], 3);
    ASSERT_EQ(dims[1], 3);
    ASSERT_EQ(dims[2], 1);
    ASSERT_EQ(dims[3], 1);

    // check distances
    auto hostResult = khiva::utils::makeScopedHostPtr(result.host<float>());
    ASSERT_EQ(0.0f, hostResult[0]);
    ASSERT_EQ(0.0f, hostResult[1]);
    ASSERT_EQ(0.0f, hostResult[2]);
    ASSERT_EQ(64.0f, hostResult[3]);
    ASSERT_EQ(0.0f, hostResult[4]);
    ASSERT_EQ(0.0f, hostResult[5]);
    ASSERT_EQ(256.0f, hostResult[6]);
    ASSERT_EQ(64.0f, hostResult[7]);
    ASSERT_EQ(0.0f, hostResult[8]);
}

KHIVA_TEST(DistanceTests, DTW, dtw)
KHIVA_TEST(DistanceTests, DTW2, dtw2)
KHIVA_TEST(DistanceTests, Euclidean, euclidean)
KHIVA_TEST(DistanceTests, Hamming, hamming)
KHIVA_TEST(DistanceTests, Manhattam, manhattan)
KHIVA_TEST(DistanceTests, SBD, sbd)
KHIVA_TEST(DistanceTests, SquaredEuclidean, squaredEuclidean)
