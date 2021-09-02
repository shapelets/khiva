// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <khiva/dimensionality.h>
#include <khiva/internal/scopedHostPtr.h>

#include "khivaTest.h"

void paaDivisible() {
    float pointList[] = {0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};
    af::array a(10, 1, pointList);

    af::array out = khiva::dimensionality::PAA(a, 5);

    auto out_h = khiva::utils::makeScopedHostPtr(out.host<float>());
    auto outVector = std::vector<float>(out_h.get(), out_h.get() + out.elements());
    std::vector<float> expected = {0.05f, 2.45f, 6.5f, 8.55f, 9.0f};

    ASSERT_EQ(outVector, expected);
}

void paaNonDivisibleFloat() {
    float pointList[] = {0.0f, 1.0f, 2.0f,  3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f,
                         0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};
    af::array a(10, 2, pointList);

    af::array out = khiva::dimensionality::PAA(a, 3);

    auto col0 = khiva::utils::makeScopedHostPtr(out.col(0).host<float>());
    auto col1 = khiva::utils::makeScopedHostPtr(out.col(1).host<float>());
    std::vector<float> col0_expected = {1.0f, 4.0f, 7.5f};
    std::vector<float> col1_expected = {0.0f, 6.0f, 8.7750f};

    for (size_t i = 0; i < 3; i++) {
        ASSERT_NEAR(col0[i], col0_expected[i], EPSILON);
        ASSERT_NEAR(col1[i], col1_expected[i], EPSILON);
    }
}

void paaNonDivisibleDouble() {
    if (!af::isDoubleAvailable(af::getDevice())) return;

    double pointList[] = {0.0, 1.0, 2.0,  3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0,
                          0.0, 0.1, -0.1, 5.0, 6.0, 7.0, 8.1, 9.0, 9.0, 9.0};
    af::array a(10, 2, pointList);

    af::array out = khiva::dimensionality::PAA(a, 3);

    auto col0 = khiva::utils::makeScopedHostPtr(out.col(0).host<double>());
    auto col1 = khiva::utils::makeScopedHostPtr(out.col(1).host<double>());
    std::vector<double> col0_expected = {1.0, 4.0, 7.5};
    std::vector<double> col1_expected = {0.0, 6.0, 8.7750};

    for (size_t i = 0; i < 3; i++) {
        ASSERT_NEAR(col0[i], col0_expected[i], EPSILON);
        ASSERT_NEAR(col1[i], col1_expected[i], EPSILON);
    }
}

void paaNorm() {
    std::vector<khiva::dimensionality::Point> pointList = {{0.0, 0.0}, {1.0, 0.1}, {2.0, -0.1}, {3.0, 5.0}, {4.0, 6.0},
                                                           {5.0, 7.0}, {6.0, 8.1}, {7.0, 9.0},  {8.0, 9.0}, {9.0, 9.0}};

    auto out = khiva::dimensionality::PAA(pointList, 6);

    std::vector<khiva::dimensionality::Point> expected = {{0.75, 0.05}, {2.25, -0.1}, {3.75, 5.5},
                                                          {5.25, 7.0},  {6.75, 8.55}, {8.25, 9.0}};

    ASSERT_EQ(expected, out);
}

void pip() {
    float px[] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
    float py[] = {0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};

    af::array tsx(10, 1, px);
    af::array tsy(10, 1, py);
    af::array tss = join(1, tsx, tsy);

    af::array pointsOut = khiva::dimensionality::PIP(tss, 6);

    auto pox_h = khiva::utils::makeScopedHostPtr(pointsOut.col(0).host<float>());
    auto poy_h = khiva::utils::makeScopedHostPtr(pointsOut.col(1).host<float>());

    auto poxVector = std::vector<float>(pox_h.get(), pox_h.get() + pointsOut.col(0).elements());
    auto poyVector = std::vector<float>(poy_h.get(), poy_h.get() + pointsOut.col(1).elements());

    auto expectedX = std::vector<float>{0.0f, 2.0f, 3.0f, 6.0f, 7.0f, 9.0f};
    auto expectedY = std::vector<float>{0.0f, -0.1f, 5.0f, 8.1f, 9.0f, 9.0f};

    ASSERT_EQ(expectedX, poxVector);
    ASSERT_EQ(expectedY, poyVector);
}

void pipException() {
    float pointList[] = {0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};
    af::array a(10, 1, pointList);
    ASSERT_THROW(khiva::dimensionality::PIP(a, 6), std::invalid_argument);
}

void plaBottomUp() {
    float maxError = 1.0;
    std::vector<khiva::dimensionality::Point> pointList = {{0.0, 0.0}, {1.0, 0.1}, {2.0, -0.1}, {3.0, 5.0}, {4.0, 6.0},
                                                           {5.0, 7.0}, {6.0, 8.1}, {7.0, 9.0},  {8.0, 9.0}, {9.0, 9.0}};

    auto out = khiva::dimensionality::PLABottomUp(pointList, maxError);

    std::vector<khiva::dimensionality::Point> expected = {{0.0, 0.0}, {1.0, 0.1}, {2.0, -0.1}, {3.0, 5.0},
                                                          {4.0, 6.0}, {7.0, 9.0}, {8.0, 9.0},  {9.0, 9.0}};

    ASSERT_EQ(expected, out);
}

void plaBottomUp2() {
    float maxError = 1.0;
    float px[] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
    float py[] = {0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};

    af::array tsx(10, 1, px);
    af::array tsy(10, 1, py);
    af::array tss = join(1, tsx, tsy);

    auto d_out = khiva::dimensionality::PLABottomUp(tss, maxError);
    auto pox = khiva::utils::makeScopedHostPtr(d_out.col(0).host<float>());
    auto poy = khiva::utils::makeScopedHostPtr(d_out.col(1).host<float>());

    auto expectedX = std::vector<float>{0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 7.0f, 8.0f, 9.0f};
    auto expectedY = std::vector<float>{0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 9.0f, 9.0f, 9.0f};

    auto poxVector = std::vector<float>(pox.get(), pox.get() + d_out.col(0).elements());
    auto poyVector = std::vector<float>(poy.get(), poy.get() + d_out.col(1).elements());

    ASSERT_EQ(expectedX, poxVector);
    ASSERT_EQ(expectedY, poyVector);
}

void plaBottomUpException() {
    float pointList[] = {0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};
    af::array a(10, 1, pointList);

    ASSERT_THROW(khiva::dimensionality::PLABottomUp(a, 6), std::invalid_argument);
}

void plaSlidingWindow() {
    float maxError = 1.0;
    std::vector<khiva::dimensionality::Point> pointList = {{0.0, 0.0}, {1.0, 0.1}, {2.0, -0.1}, {3.0, 5.0}, {4.0, 6.0},
                                                           {5.0, 7.0}, {6.0, 8.1}, {7.0, 9.0},  {8.0, 9.0}, {9.0, 9.0}};

    auto out = khiva::dimensionality::PLASlidingWindow(pointList, maxError);

    std::vector<khiva::dimensionality::Point> expected = {{0.0, 0.0}, {2.0, -0.1}, {3.0, 5.0},
                                                          {7.0, 9.0}, {8.0, 9.0},  {9.0, 9.0}};

    ASSERT_EQ(expected, out);
}

void plaSlidingWindow2() {
    float maxError = 1.0f;
    float px[] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
    float py[] = {0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};

    af::array tsx(10, 1, px);
    af::array tsy(10, 1, py);
    af::array tss = join(1, tsx, tsy);

    auto out = khiva::dimensionality::PLASlidingWindow(tss, maxError);

    auto pox_h = khiva::utils::makeScopedHostPtr(out.col(0).host<float>());
    auto poy_h = khiva::utils::makeScopedHostPtr(out.col(1).host<float>());

    auto expectedX = std::vector<float>{0.0f, 2.0f, 3.0f, 7.0f, 8.0f, 9.0f};
    auto expectedY = std::vector<float>{0.0f, -0.1f, 5.0f, 9.0f, 9.0f, 9.0f};

    auto poxVector = std::vector<float>(pox_h.get(), pox_h.get() + out.col(0).elements());
    auto poyVector = std::vector<float>(poy_h.get(), poy_h.get() + out.col(1).elements());

    ASSERT_EQ(expectedX, poxVector);
    ASSERT_EQ(expectedY, poyVector);
}

void plaSlidingWindowException() {
    float pointList[] = {0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};
    af::array a(10, 1, pointList);
    ASSERT_THROW(khiva::dimensionality::PLASlidingWindow(a, 6), std::invalid_argument);
}

void ramerDouglasPeucker() {
    std::vector<khiva::dimensionality::Point> pointList = {{0.0, 0.0}, {1.0, 0.1}, {2.0, -0.1}, {3.0, 5.0}, {4.0, 6.0},
                                                           {5.0, 7.0}, {6.0, 8.1}, {7.0, 9.0},  {8.0, 9.0}, {9.0, 9.0}};
    std::vector<khiva::dimensionality::Point> expected = {{0.0, 0.0}, {2.0, -0.1}, {3.0, 5.0}, {6.0, 8.1}, {9.0, 9.0}};

    auto out = khiva::dimensionality::ramerDouglasPeucker(pointList, 1.0);

    ASSERT_EQ(expected, out);
}

void ramerDouglasPeucker2() {
    float pointList[] = {0.0f, 1.0f, 2.0f,  3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f,
                         0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};
    af::array points(10, 2, pointList);
    std::vector<khiva::dimensionality::Point> expected = {{0.0, 0.0}, {2.0, -0.1}, {3.0, 5.0}, {6.0, 8.1}, {9.0, 9.0}};

    af::array res = khiva::dimensionality::ramerDouglasPeucker(points, 1.0);
    auto points_x = khiva::utils::makeScopedHostPtr(res.col(0).host<float>());
    auto points_y = khiva::utils::makeScopedHostPtr(res.col(1).host<float>());

    auto expectedX = std::vector<float>{0.0f, 2.0f, 3.0f, 6.0f, 9.0f};
    auto expectedY = std::vector<float>{0.0f, -0.1f, 5.0f, 8.1f, 9.0f};

    auto pxVector = std::vector<float>(points_x.get(), points_x.get() + res.col(0).elements());
    auto pyVector = std::vector<float>(points_y.get(), points_y.get() + res.col(1).elements());

    ASSERT_EQ(expectedX, pxVector);
    ASSERT_EQ(expectedY, pyVector);
}

void ramerDouglasPeuckerException() {
    float pointList[] = {0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};
    af::array a(10, 1, pointList);
    ASSERT_THROW(khiva::dimensionality::ramerDouglasPeucker(a, 6), std::invalid_argument);
}

void sax() {
    float pointList[] = {0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};
    af::array a(5, 2, pointList);

    af::array out = khiva::dimensionality::SAX(a, 3);

    auto out_h = khiva::utils::makeScopedHostPtr(out.host<float>());
    auto outVector = std::vector<float>(out_h.get(), out_h.get() + out.elements());
    auto expected = std::vector<float>{0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 0.0, 1.0, 2.0, 2.0, 2.0};
    EXPECT_EQ(expected, outVector);
}

void sax2() {
    float pointList[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f};
    af::array a(5, 2, pointList);

    af::array out = khiva::dimensionality::SAX(a, 3);

    auto out_h = khiva::utils::makeScopedHostPtr(out.host<float>());
    auto outVector = std::vector<float>(out_h.get(), out_h.get() + out.elements());
    auto expected = std::vector<float>{1.0, 2.0, 3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    EXPECT_EQ(expected, outVector);
}

void saxException() {
    float pointList[] = {0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};
    af::array a(10, 1, pointList);
    ASSERT_THROW(khiva::dimensionality::SAX(a, 6), std::invalid_argument);
}

template <typename T>
void visvalingam_templated() {
    T pointList[] = {0.0, 1.0, 2.0,  3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0,
                     0.0, 0.1, -0.1, 5.0, 6.0, 7.0, 8.1, 9.0, 9.0, 9.0};
    af::array points(10, 2, pointList);

    std::vector<khiva::dimensionality::TPoint<T>> expected = {
        {0.0, 0.0}, {2.0, -0.1}, {3.0, 5.0}, {7.0, 9.0}, {9.0, 9.0}};

    af::array res = khiva::dimensionality::visvalingam(points, 5);

    auto points_x = khiva::utils::makeScopedHostPtr(res.col(0).host<T>());
    auto points_y = khiva::utils::makeScopedHostPtr(res.col(1).host<T>());

    auto expectedX = std::vector<T>{0.0, 2.0, 3.0, 7.0, 9.0};
    auto expectedY = std::vector<T>{0.0, -0.1, 5.0, 9.0, 9.0};

    auto pxVector = std::vector<T>(points_x.get(), points_x.get() + res.col(0).elements());
    auto pyVector = std::vector<T>(points_y.get(), points_y.get() + res.col(1).elements());

    std::vector<T> xsbs;
    std::vector<T> ysbs;
    std::transform(expectedX.begin(), expectedX.end(), pxVector.begin(), std::back_inserter(xsbs),
                   [](const T &e, const T &a) { return std::abs(e - a); });
    std::transform(expectedY.begin(), expectedY.end(), pyVector.begin(), std::back_inserter(ysbs),
                   [](const T &e, const T &a) { return std::abs(e - a); });

    for (auto diff : xsbs) {
        ASSERT_LT(diff, 1e-08);
    }

    for (auto diff : ysbs) {
        ASSERT_LT(diff, 1e-08);
    }
}

void visvalingam_af() {
    SCOPED_TRACE("f32 types...");
    visvalingam_templated<float>();
    if (af::isDoubleAvailable(af::getDevice())) {
        SCOPED_TRACE("f64 types...");
        visvalingam_templated<double>();
    }
}

void visvalingamException() {
    float pointList[] = {0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};
    af::array a(10, 1, pointList);
    ASSERT_THROW(khiva::dimensionality::visvalingam(a, 6), std::invalid_argument);
}

KHIVA_TEST(DimensionalityTests, PAA_Divisible, paaDivisible)
KHIVA_TEST(DimensionalityTests, PAA_NonDivisibleFloat, paaNonDivisibleFloat)
KHIVA_TEST(DimensionalityTests, PAA_NonDivisibleDouble, paaNonDivisibleDouble)
KHIVA_TEST(DimensionalityTests, PAA_NORM, paaNorm)
KHIVA_TEST(DimensionalityTests, PIP, pip)
KHIVA_TEST(DimensionalityTests, PIPException, pipException)
KHIVA_TEST(DimensionalityTests, PLABottomUp, plaBottomUp)
KHIVA_TEST(DimensionalityTests, PLABottomUp2, plaBottomUp2)
KHIVA_TEST(DimensionalityTests, PLABottomUpException, plaBottomUpException)
KHIVA_TEST(DimensionalityTests, PLASlidingWindow, plaSlidingWindow)
KHIVA_TEST(DimensionalityTests, PLASlidingWindow2, plaSlidingWindow2)
KHIVA_TEST(DimensionalityTests, PLASlidingWindowException, plaSlidingWindowException)
KHIVA_TEST(DimensionalityTests, RamerDouglasPeucker, ramerDouglasPeucker)
KHIVA_TEST(DimensionalityTests, RamerDouglasPeucker2, ramerDouglasPeucker2)
KHIVA_TEST(DimensionalityTests, RamerDouglasPeuckerException, ramerDouglasPeuckerException)
KHIVA_TEST(DimensionalityTests, SAX, sax)
KHIVA_TEST(DimensionalityTests, SAX2, sax2)
KHIVA_TEST(DimensionalityTests, SAXException, saxException)
KHIVA_TEST(DimensionalityTests, VisvalingamAF, visvalingam_af)
KHIVA_TEST(DimensionalityTests, VisvalingamException, visvalingamException)
