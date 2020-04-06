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
    std::vector<double> a = {4.0, 4.0, 5.0, 5.0, 6.0, 6.0, 7.0, 7.0};
    std::vector<double> b = {23.0, 4.0, 5.0, 6.0, 7.0};

    double result = khiva::distances::dtw(a, b);

    ASSERT_EQ(result, 19.0);
}

void dtw2() {
    float data[] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f,
                    3.0f, 3.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f};
    af::array tss(5, 5, data);

    af::array result = khiva::distances::dtw(tss);

    // check dimensions
    auto dims = result.dims();
    auto expectedDims = af::dim4(5, 5, 1, 1);
    EXPECT_EQ(expectedDims, dims);

    // check distances
    auto hostResult = khiva::utils::makeScopedHostPtr(result.host<float>());
    auto resultVector = std::vector<float>(hostResult.get(), hostResult.get() + result.elements());
    auto expected =
        std::vector<float>{0.0f, 0.0f, 0.0f,  0.0f,  0.0f, 5.0f, 0.0f, 0.0f,  0.0f,  0.0f,  10.0f, 5.0f, 0.0f,
                           0.0f, 0.0f, 15.0f, 10.0f, 5.0f, 0.0f, 0.0f, 20.0f, 15.0f, 10.0f, 5.0f,  0.0f};

    ASSERT_EQ(resultVector, expected);
}

void euclidean() {
    float data[] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f};
    af::array tss(4, 3, data);

    auto result = khiva::distances::euclidean(tss);

    // check dimensions
    auto dims = result.dims();
    auto expectedDims = af::dim4(3, 3, 1, 1);
    ASSERT_EQ(dims, expectedDims);

    // check distances
    auto hostResult = khiva::utils::makeScopedHostPtr(result.host<float>());

    auto resultVector = std::vector<float>(hostResult.get(), hostResult.get() + result.elements());
    auto expected = std::vector<float>{0.0f, 0.0f, 0.0f, 8.0f, 0.0f, 0.0f, 16.0f, 8.0f, 0.0f};
    ASSERT_EQ(resultVector, expected);
}

void hamming() {
    float data[] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f,
                    3.0f, 3.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f};
    af::array tss(5, 5, data);

    af::array result = khiva::distances::hamming(tss);

    // check dimensions
    auto dims = result.dims();
    auto expectedDims = af::dim4(5, 5, 1, 1);
    EXPECT_EQ(expectedDims, dims);

    // check distances
    auto hostResult = khiva::utils::makeScopedHostPtr(result.host<float>());
    auto resultVector = std::vector<float>(hostResult.get(), hostResult.get() + result.elements());
    auto expected = std::vector<float>{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 5.0f, 0.0f,
                                       0.0f, 0.0f, 5.0f, 5.0f, 5.0f, 0.0f, 0.0f, 5.0f, 5.0f, 5.0f, 5.0f, 0.0f};
    ASSERT_EQ(resultVector, expected);
}

void manhattan() {
    float data[] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f, 3.0f, 3.0f, 3.0f,
                    3.0f, 3.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f};
    af::array tss(5, 5, data);

    af::array result = khiva::distances::manhattan(tss);

    // check dimensions
    auto dims = result.dims();
    auto expectedDims = af::dim4(5, 5, 1, 1);
    EXPECT_EQ(expectedDims, dims);

    // check distances
    auto hostResult = khiva::utils::makeScopedHostPtr(result.host<float>());
    auto resultVector = std::vector<float>(hostResult.get(), hostResult.get() + result.elements());
    auto expected =
        std::vector<float>{0.0f, 0.0f, 0.0f,  0.0f,  0.0f, 5.0f, 0.0f, 0.0f,  0.0f,  0.0f,  10.0f, 5.0f, 0.0f,
                           0.0f, 0.0f, 15.0f, 10.0f, 5.0f, 0.0f, 0.0f, 20.0f, 15.0f, 10.0f, 5.0f,  0.0f};

    ASSERT_EQ(resultVector, expected);
}

void sbd() {
    float data[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 10.0f, 12.0f, 0.0f, 0.0f, 1.0f};
    af::array tss(5, 3, data);

    auto result = khiva::distances::sbd(tss);

    // check dimensions
    auto dims = result.dims();
    auto expectedDims = af::dim4(3, 3, 1, 1);
    EXPECT_EQ(expectedDims, dims);

    // check distances
    auto hostResult = khiva::utils::makeScopedHostPtr(result.host<float>());
    auto resultVector = std::vector<float>(hostResult.get(), hostResult.get() + result.elements());
    auto expected = std::vector<float>{0.0f, 0.0f,  0.0f,  0.505025f, 0.0f,  0.0f, 0.458583f, 0.564093f, 0.0f};

    EXPECT_EQ(expected.size(), resultVector.size());
    for (size_t i = 0; i < resultVector.size(); i++) {
        ASSERT_NEAR(expected[i], hostResult[i], EPSILON);
    }
}

void squaredEuclidean() {
    float data[] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f, 11.0f};
    af::array tss(4, 3, data);

    auto result = khiva::distances::squaredEuclidean(tss);

    // check dimensions
    auto dims = result.dims();
    auto expectedDims = af::dim4(3, 3, 1, 1);
    EXPECT_EQ(expectedDims, dims);

    // check distances
    auto hostResult = khiva::utils::makeScopedHostPtr(result.host<float>());
    auto resultVector = std::vector<float>(hostResult.get(), hostResult.get() + result.elements());
    auto expected = std::vector<float>{0.0f, 0.0f, 0.0f, 64.0f, 0.0f, 0.0f, 256.0f, 64.0f, 0.0f};
    ASSERT_EQ(resultVector, expected);
}

KHIVA_TEST(DistanceTests, DTW, dtw)
KHIVA_TEST(DistanceTests, DTW2, dtw2)
KHIVA_TEST(DistanceTests, Euclidean, euclidean)
KHIVA_TEST(DistanceTests, Hamming, hamming)
KHIVA_TEST(DistanceTests, Manhattam, manhattan)
KHIVA_TEST(DistanceTests, SBD, sbd)
KHIVA_TEST(DistanceTests, SquaredEuclidean, squaredEuclidean)
