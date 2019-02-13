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

    khiva::clustering::kMeans(tss, 3, means, labels);

    ASSERT_EQ(means.dims(0), 4);
    ASSERT_EQ(means.dims(1), 3);
    ASSERT_EQ(labels.dims(0), 1);
    ASSERT_EQ(labels.dims(1), 6);
}

void kShape() {
    float a[35] = { 1.0f,  2.0f,   3.0f,   4.0f,  5.0f,  6.0f,  7.0f,
                    0.0f, 10.0f,   4.0f,   5.0f,  7.0f, -3.0f,  0.0f,
                   -1.0f, 15.0f, -12.0f,   8.0f,  9.0f,  4.0f,  5.0f,
                    2.0f,  8.0f,   7.0f,  -6.0f, -1.0f,  2.0f,  9.0f,
                   -5.0f, -5.0f,  -6.0f,   7.0f,  9.0f,  9.0f,  0.0f};
    af::array data = af::array(7, 5, a);


    af::array idx;
    af::array centroids;

    khiva::clustering::kShape(data, 3, centroids, idx);

    af_print(idx);
    af_print(centroids);

    /*float *index = idx.host<float>();
    for (unsigned int i = 0; i < static_cast<unsigned int>(idx.dims(0)); i++) {
        ASSERT_EQ(index[i], indices[i]);
    }*/
}

void kShape2() {
    float a[80] = {1.0f,   2.0f,   3.0f,   4.0f,   5.0f,   6.0f,   7.0f,   8.0f,   9.0f,   10.0f,  15.0f, 16.0f,
                   17.0f,  18.0f,  19.0f,  20.0f,  21.0f,  22.0f,  23.0f,  24.0f,  0.0f,   5.88f,  9.50f, 9.50f,
                   5.9f,   0.0f,   -5.87f, -9.50f, -9.50f, -5.9f,  2.0f,   7.88f,  11.50f, 11.50f, 7.9f,  2.0f,
                   -3.87f, -7.50f, -7.50f, -3.9f,  1.0f,   2.0f,   3.0f,   4.0f,   5.0f,   6.0f,   7.0f,  8.0f,
                   9.0f,   10.0f,  15.0f,  16.0f,  17.0f,  18.0f,  19.0f,  20.0f,  21.0f,  22.0f,  23.0f, 24.0f,
                   0.0f,   5.88f,  9.50f,  9.50f,  5.9f,   0.0f,   -5.87f, -9.50f, -9.50f, -5.9f,  2.0f,  7.88f,
                   11.50f, 11.50f, 7.9f,   2.0f,   -3.87f, -7.50f, -7.50f, -3.9f};

    af::array data = af::array(10, 8, a);
    af_print(data);

    af::array idx;
    af::array centroids;

    khiva::clustering::kShape(data, 2, centroids, idx);

    af_print(idx);
    af_print(centroids);

    // float *index = idx.host<float>();

    /*for (unsigned int i = 0; i < static_cast<unsigned int>(idx.dims(0)); i++)
    {
        ASSERT_EQ(index[i], indices[i]);
    }*/
}

void kShape3() {
    af::array a = af::randu(10, 4);
    af_print(a);
    af_print(a.T());
    af::array aux = af::matmul(a.T(), a);
    af_print(aux);
}

KHIVA_TEST(ClusteringTests, KMEANS, kmeans)
KHIVA_TEST(ClusteringTests, KShape, kShape)
//KHIVA_TEST(ClusteringTests, KShape2, kShape2)
//KHIVA_TEST(ClusteringTests, KShape3, kShape3)


