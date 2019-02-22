// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <khiva/clustering.h>
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

    float *calculated_c = means.host<float>();

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

    float *calculated_c = means.host<float>();

    for (size_t i = 0; i < 3; i++) {
        ASSERT_NEAR(calculated_c[i] + calculated_c[i + 4] + calculated_c[i + 8],
                    expected_c[i] + expected_c[i + 4] + expected_c[i + 8], 1e-3);
    }
}

KHIVA_TEST(ClusteringTests, KMeans, kmeans)
KHIVA_TEST(ClusteringTests, KMeans2, kmeans2)

