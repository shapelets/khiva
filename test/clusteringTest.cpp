// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <khiva/clustering.h>
#include <khiva/internal/scopedHostPtr.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "khivaTest.h"

void kmeans() {
    float data[] = {0.0f, 1.0f, 2.0f, 3.0f, 6.0f,  7.0f,  8.0f, 9.0f, 2.0f, -2.0f, 4.0f, -4.0f,
                    8.0f, 5.0,  3.0,  1.0,  15.0f, 10.0f, 5.0f, 0.0f, 7.0f, -7.0,  1.0f, -1.0f};

    af::array tss(4, 6, data);

    float expected_c[] = {0.0, 0.1667, 0.3333, 0.5, 1.5, -1.5, 0.8333, -0.8333, 4.8333, 3.6667, 2.6667, 1.6667};
    af::array means;

    unsigned int initial_l[] = {0, 1, 2, 0, 1, 2};
    af::array labels(6, 1, initial_l);
    unsigned int expected_l[] = {0, 2, 1, 2, 2, 1};

    khiva::clustering::kMeans(tss, 3, means, labels);

    auto calculated_c = khiva::utils::makeScopedHostPtr(means.host<float>());

    for (size_t i = 0; i < 4; i++) {
        ASSERT_NEAR(calculated_c[i] + calculated_c[i + 4] + calculated_c[i + 8],
                    expected_c[i] + expected_c[i + 4] + expected_c[i + 8], 1e-3);
    }
}

void kmeans2() {
    float data[] = {0.0f, 1.0f, 2.0f, 3.0f, 6.0f,  7.0f,  8.0f, 9.0f, 2.0f, -2.0f, 4.0f, -4.0f,
                    8.0f, 5.0,  3.0,  1.0,  15.0f, 10.0f, 5.0f, 0.0f, 7.0f, -7.0,  1.0f, -1.0f};

    af::array tss(4, 6, data);

    float expected_c[] = {0.0, 0.1667, 0.3333, 0.5, 1.5, -1.5, 0.8333, -0.8333, 4.8333, 3.6667, 2.6667, 1.6667};
    af::array means;

    af::array labels;
    khiva::clustering::kMeans(tss, 3, means, labels);

    auto calculated_c = khiva::utils::makeScopedHostPtr(means.host<float>());

    for (size_t i = 0; i < 4; i++) {
        ASSERT_NEAR(calculated_c[i] + calculated_c[i + 4] + calculated_c[i + 8],
                    expected_c[i] + expected_c[i + 4] + expected_c[i + 8], 1e-3);
    }
}

void kShapeFloat() {
    float tolerance = 1e-10;
    int maxIter = 100;
    float a[35] = {1.0f,  2.0f,  3.0f,  4.0f,  5.0f,   6.0f,  7.0f,  0.0f, 10.0f, 4.0f, 5.0f, 7.0f,
                   -3.0f, 0.0f,  -1.0f, 15.0f, -12.0f, 8.0f,  9.0f,  4.0f, 5.0f,  2.0f, 8.0f, 7.0f,
                   -6.0f, -1.0f, 2.0f,  9.0f,  -5.0f,  -5.0f, -6.0f, 7.0f, 9.0f,  9.0f, 0.0f};

    unsigned int idxh[5] = {0, 1, 2, 0, 1};

    float expected_c[21] = {-0.5234, 0.1560, -0.3627, -1.2764, -0.7781, 0.9135,  1.8711,
                            -0.7825, 1.5990, 0.1701,  0.4082,  0.8845,  -1.4969, -0.7825,
                            -0.6278, 1.3812, -2.0090, 0.5022,  0.6278,  -0.0000, 0.1256};
    int k = 3;
    int nElements = 7;
    int ntss = 5;

    af::array data = af::array(nElements, ntss, a);
    af::array idx = af::array(ntss, 1, idxh);
    af::array centroids = af::constant(0.0f, nElements, k);

    khiva::clustering::kShape(data, k, centroids, idx, tolerance, maxIter);

    auto calculated_c = khiva::utils::makeScopedHostPtr(centroids.host<float>());
    auto calculated_l = khiva::utils::makeScopedHostPtr(idx.host<unsigned int>());

    for (size_t i = 0; i < 21; i++) {
        ASSERT_NEAR(calculated_c[i], expected_c[i], 1e-3);
    }
}

void kShapeDouble() {
    double tolerance = 1e-10;
    int maxIter = 100;
    double a[35] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0,  0.0,  10.0, 4.0, 5.0,  7.0,  -3.0, 0.0, -1.0, 15.0, -12.0, 8.0,
                    9.0, 4.0, 5.0, 2.0, 8.0, 7.0, -6.0, -1.0, 2.0,  9.0, -5.0, -5.0, -6.0, 7.0, 9.0,  9.0,  0.0};

    unsigned int idxh[5] = {0, 1, 2, 0, 1};

    double expected_c[21] = {-0.5234, 0.1560, -0.3627, -1.2764, -0.7781, 0.9135,  1.8711,
                             -0.7825, 1.5990, 0.1701,  0.4082,  0.8845,  -1.4969, -0.7825,
                             -0.6278, 1.3812, -2.0090, 0.5022,  0.6278,  -0.0000, 0.1256};
    int k = 3;
    int nElements = 7;
    int ntss = 5;

    af::array data = af::array(nElements, ntss, a);
    af::array idx = af::array(ntss, 1, idxh);
    af::array centroids = af::constant(0, nElements, k, data.type());

    khiva::clustering::kShape(data, k, centroids, idx, tolerance, maxIter);

    auto calculated_c = khiva::utils::makeScopedHostPtr(centroids.host<double>());
    auto calculated_l = khiva::utils::makeScopedHostPtr(idx.host<unsigned int>());

    for (size_t i = 0; i < 21; i++) {
        ASSERT_NEAR(calculated_c[i], expected_c[i], 1e-3);
    }
}

KHIVA_TEST(ClusteringTests, KMeans, kmeans)
KHIVA_TEST(ClusteringTests, KMeans2, kmeans2)
KHIVA_TEST(ClusteringTests, KShapeFloat, kShapeFloat)
KHIVA_TEST(ClusteringTests, KShapeDouble, kShapeDouble)
