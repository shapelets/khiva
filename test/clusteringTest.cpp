// Copyright (c) 2018 Shapelets.io
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

    af::array means;
    af::array labels;

    khiva::clustering::kmeans(tss, 3, means, labels);

    ASSERT_EQ(means.dims(0), 4);
    ASSERT_EQ(means.dims(1), 3);
    ASSERT_EQ(labels.dims(0), 1);
    ASSERT_EQ(labels.dims(1), 6);
}

KHIVA_TEST(ClusteringTests, KMEANS, kmeans)