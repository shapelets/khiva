// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <gtest/gtest.h>
#include <khiva.h>
#include <khiva/internal/vectorUtil.h>

#include "khivaTest.h"

void vector1Dim() {
    std::vector<int> data = {10, 10, 10, 11, 12, 11, 10, 10, 11, 12, 11, 10, 10, 10};
    af::array t = af::array(data.size(), data.data());

    auto vect = khiva::vectorutil::get<int>(t);
    ASSERT_EQ(vect, data);
}

void vector2Dim() {
    std::vector<int> data = {10, 10, 10, 11, 12, 11, 10, 10, 11, 12, 11, 10, 10, 10};
    auto num_cols = 2;
    af::array t = af::array(data.size() / num_cols, num_cols, data.data());

    auto vect = khiva::vectorutil::get<int>(t);
    ASSERT_EQ(vect, data);
}

void vector3Dim() {
    std::vector<int> data = {10, 10, 10, 11, 12, 11, 10, 10};
    af::array t = af::array(2, 2, 2, data.data());

    auto vect = khiva::vectorutil::get<int>(t);
    ASSERT_EQ(vect, data);
}

void vector4Dim() {
    std::vector<int> data = {10, 10, 10, 11, 12, 11, 10, 10, 11, 12, 11, 10, 10, 10, 12, 44};
    af::array t = af::array(2, 2, 2, 2, data.data());

    auto vect = khiva::vectorutil::get<int>(t);
    ASSERT_EQ(vect, data);
}

void arr0Dim() {
    std::vector<int> vect = {1, 3, 2};
    auto arr = khiva::vectorutil::createArray(vect);
    ASSERT_EQ(arr.dims(0), 3);
    ASSERT_EQ(arr.dims(1), 1);
    ASSERT_EQ(arr.dims(2), 1);
    ASSERT_EQ(arr.dims(3), 1);
}

void arr0DimInitializer() {
    auto arr = khiva::vectorutil::createArray({1, 3, 2});
    ASSERT_EQ(arr.dims(0), 3);
    ASSERT_EQ(arr.dims(1), 1);
    ASSERT_EQ(arr.dims(2), 1);
    ASSERT_EQ(arr.dims(3), 1);
}

void arr1Dim() {
    std::vector<int> vect = {1, 3, 2, 4};
    auto arr = khiva::vectorutil::createArray(vect, 4);
    ASSERT_EQ(arr.dims(0), 4);
    ASSERT_EQ(arr.dims(1), 1);
    ASSERT_EQ(arr.dims(2), 1);
    ASSERT_EQ(arr.dims(3), 1);
}

void arr1DimInitializer() {
    auto arr = khiva::vectorutil::createArray({1, 3, 2, 4}, 4);
    ASSERT_EQ(arr.dims(0), 4);
    ASSERT_EQ(arr.dims(1), 1);
    ASSERT_EQ(arr.dims(2), 1);
    ASSERT_EQ(arr.dims(3), 1);
}

void arr2Dim() {
    std::vector<int> vect = {1, 3, 2, 4};
    auto arr = khiva::vectorutil::createArray(vect, 2, 2);
    ASSERT_EQ(arr.dims(0), 2);
    ASSERT_EQ(arr.dims(1), 2);
    ASSERT_EQ(arr.dims(2), 1);
    ASSERT_EQ(arr.dims(3), 1);
}

void arr2DimInitializer() {
    auto arr = khiva::vectorutil::createArray({1, 3, 2, 4}, 2, 2);
    ASSERT_EQ(arr.dims(0), 2);
    ASSERT_EQ(arr.dims(1), 2);
    ASSERT_EQ(arr.dims(2), 1);
    ASSERT_EQ(arr.dims(3), 1);
}

KHIVA_TEST(VectorTest, Vector1Dim, vector1Dim)
KHIVA_TEST(VectorTest, Vector2Dim, vector2Dim)
KHIVA_TEST(VectorTest, Vector3Dim, vector3Dim)
KHIVA_TEST(VectorTest, Vector4Dim, vector4Dim)
KHIVA_TEST(VectorTest, Arr0Dim, arr0Dim)
KHIVA_TEST(VectorTest, Arr0DimInitializer, arr0DimInitializer)
KHIVA_TEST(VectorTest, Arr1Dim, arr1Dim)
KHIVA_TEST(VectorTest, Arr1DimInitializer, arr1DimInitializer)
KHIVA_TEST(VectorTest, Arr2Dim, arr2Dim)
KHIVA_TEST(VectorTest, Arr2DimInitializer, arr2DimInitializer)
