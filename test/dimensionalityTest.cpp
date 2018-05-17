// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <tsa/dimensionality.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "tsaTest.h"

void paa() {
    float pointList[] = {0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};
    af::array a(10, 1, pointList);

    af::array out = tsa::dimensionality::PAA(a, 5);

    float *out_h = out.host<float>();
    std::vector<float> expected = {0.05f, 2.45f, 6.5f, 8.55f, 9.0f};

    for (size_t i = 0; i < 5; i++) {
        ASSERT_EQ(out_h[i], expected[i]);
    }
}

void paaNorm() {
    std::vector<tsa::dimensionality::Point> pointList;
    pointList.push_back(tsa::dimensionality::Point(0.0f, 0.0f));
    pointList.push_back(tsa::dimensionality::Point(1.0f, 0.1f));
    pointList.push_back(tsa::dimensionality::Point(2.0f, -0.1f));
    pointList.push_back(tsa::dimensionality::Point(3.0f, 5.0f));
    pointList.push_back(tsa::dimensionality::Point(4.0f, 6.0f));
    pointList.push_back(tsa::dimensionality::Point(5.0f, 7.0f));
    pointList.push_back(tsa::dimensionality::Point(6.0f, 8.1f));
    pointList.push_back(tsa::dimensionality::Point(7.0f, 9.0f));
    pointList.push_back(tsa::dimensionality::Point(8.0f, 9.0f));
    pointList.push_back(tsa::dimensionality::Point(9.0f, 9.0f));

    auto out = tsa::dimensionality::PAA(pointList, 6);

    std::vector<tsa::dimensionality::Point> expected = {
        tsa::dimensionality::Point(0.75, 0.05), tsa::dimensionality::Point(2.25, -0.1f),
        tsa::dimensionality::Point(3.75, 5.5),  tsa::dimensionality::Point(5.25, 7.0f),
        tsa::dimensionality::Point(6.75, 8.55), tsa::dimensionality::Point(8.25, 9.0f)};

    for (size_t i = 0; i < out.size(); i++) {
        ASSERT_EQ(out[i].first, expected[i].first);
        ASSERT_EQ(out[i].second, expected[i].second);
    }
}

void pip() {
    float exp_x[] = {0.0f, 2.0f, 3.0f, 6.0f, 7.0f, 9.0f};
    float exp_y[] = {0.0f, -0.1f, 5.0f, 8.1f, 9.0f, 9.0f};
    float px[] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
    float py[] = {0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};

    af::array tsx(10, 1, px);
    af::array tsy(10, 1, py);
    af::array tss = join(1, tsx, tsy);

    af::array pointsOut = tsa::dimensionality::PIP(tss, 6);

    float *pox_h = pointsOut.col(0).host<float>();
    float *poy_h = pointsOut.col(1).host<float>();

    for (size_t i = 0; i < 6; i++) {
        ASSERT_EQ(pox_h[i], exp_x[i]);
        ASSERT_EQ(poy_h[i], exp_y[i]);
    }
}

void plaBottomUp() {
    float maxError = 1.0;
    std::vector<tsa::dimensionality::Point> pointList;
    pointList.push_back(tsa::dimensionality::Point(0.0, 0.0));
    pointList.push_back(tsa::dimensionality::Point(1.0, 0.1));
    pointList.push_back(tsa::dimensionality::Point(2.0, -0.1));
    pointList.push_back(tsa::dimensionality::Point(3.0, 5.0));
    pointList.push_back(tsa::dimensionality::Point(4.0, 6.0));
    pointList.push_back(tsa::dimensionality::Point(5.0, 7.0));
    pointList.push_back(tsa::dimensionality::Point(6.0, 8.1));
    pointList.push_back(tsa::dimensionality::Point(7.0, 9.0));
    pointList.push_back(tsa::dimensionality::Point(8.0, 9.0));
    pointList.push_back(tsa::dimensionality::Point(9.0, 9.0));

    auto out = tsa::dimensionality::PLABottomUp(pointList, maxError);

    std::vector<tsa::dimensionality::Point> expected = {
        tsa::dimensionality::Point(0.0, 0.0),  tsa::dimensionality::Point(1.0, 0.1),
        tsa::dimensionality::Point(2.0, -0.1), tsa::dimensionality::Point(3.0, 5.0),
        tsa::dimensionality::Point(4.0, 6.0),  tsa::dimensionality::Point(7.0, 9.0),
        tsa::dimensionality::Point(8.0, 9.0),  tsa::dimensionality::Point(9.0, 9.0)};

    ASSERT_EQ(out[0].first, expected[0].first);
    ASSERT_EQ(out[0].second, expected[0].second);

    ASSERT_EQ(out[1].first, expected[1].first);
    ASSERT_EQ(out[1].second, expected[1].second);

    ASSERT_EQ(out[2].first, expected[2].first);
    ASSERT_EQ(out[2].second, expected[2].second);

    ASSERT_EQ(out[3].first, expected[3].first);
    ASSERT_EQ(out[3].second, expected[3].second);

    ASSERT_EQ(out[4].first, expected[4].first);
    ASSERT_EQ(out[4].second, expected[4].second);

    ASSERT_EQ(out[5].first, expected[5].first);
    ASSERT_EQ(out[5].second, expected[5].second);

    ASSERT_EQ(out[6].first, expected[6].first);
    ASSERT_EQ(out[6].second, expected[6].second);

    ASSERT_EQ(out[7].first, expected[7].first);
    ASSERT_EQ(out[7].second, expected[7].second);
}

void plaBottomUp2() {
    float maxError = 1.0;
    float px[] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
    float py[] = {0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};

    af::array tsx(10, 1, px);
    af::array tsy(10, 1, py);
    af::array tss = join(1, tsx, tsy);

    auto d_out = tsa::dimensionality::PLABottomUp(tss, maxError);
    float *pox = d_out.col(0).host<float>();
    float *poy = d_out.col(1).host<float>();

    std::vector<tsa::dimensionality::Point> expected = {
        tsa::dimensionality::Point(0.0, 0.0),  tsa::dimensionality::Point(1.0, 0.1),
        tsa::dimensionality::Point(2.0, -0.1), tsa::dimensionality::Point(3.0, 5.0),
        tsa::dimensionality::Point(4.0, 6.0),  tsa::dimensionality::Point(7.0, 9.0),
        tsa::dimensionality::Point(8.0, 9.0),  tsa::dimensionality::Point(9.0, 9.0)};

    ASSERT_EQ(pox[0], expected[0].first);
    ASSERT_EQ(poy[0], expected[0].second);

    ASSERT_EQ(pox[1], expected[1].first);
    ASSERT_EQ(poy[1], expected[1].second);

    ASSERT_EQ(pox[2], expected[2].first);
    ASSERT_EQ(poy[2], expected[2].second);

    ASSERT_EQ(pox[3], expected[3].first);
    ASSERT_EQ(poy[3], expected[3].second);

    ASSERT_EQ(pox[4], expected[4].first);
    ASSERT_EQ(poy[4], expected[4].second);

    ASSERT_EQ(pox[5], expected[5].first);
    ASSERT_EQ(poy[5], expected[5].second);

    ASSERT_EQ(pox[6], expected[6].first);
    ASSERT_EQ(poy[6], expected[6].second);

    ASSERT_EQ(pox[7], expected[7].first);
    ASSERT_EQ(poy[7], expected[7].second);
}

void plaSlidingWindow() {
    float maxError = 1.0;
    std::vector<tsa::dimensionality::Point> pointList;
    pointList.push_back(tsa::dimensionality::Point(0.0, 0.0));
    pointList.push_back(tsa::dimensionality::Point(1.0, 0.1));
    pointList.push_back(tsa::dimensionality::Point(2.0, -0.1));
    pointList.push_back(tsa::dimensionality::Point(3.0, 5.0));
    pointList.push_back(tsa::dimensionality::Point(4.0, 6.0));
    pointList.push_back(tsa::dimensionality::Point(5.0, 7.0));
    pointList.push_back(tsa::dimensionality::Point(6.0, 8.1));
    pointList.push_back(tsa::dimensionality::Point(7.0, 9.0));
    pointList.push_back(tsa::dimensionality::Point(8.0, 9.0));
    pointList.push_back(tsa::dimensionality::Point(9.0, 9.0));

    auto out = tsa::dimensionality::PLASlidingWindow(pointList, maxError);

    std::vector<tsa::dimensionality::Point> expected = {
        tsa::dimensionality::Point(0.0, 0.0), tsa::dimensionality::Point(2.0, -0.1),
        tsa::dimensionality::Point(3.0, 5.0), tsa::dimensionality::Point(7.0, 9.0),
        tsa::dimensionality::Point(8.0, 9.0), tsa::dimensionality::Point(9.0, 9.0)};

    ASSERT_EQ(out[0].first, expected[0].first);
    ASSERT_EQ(out[0].second, expected[0].second);

    ASSERT_EQ(out[1].first, expected[1].first);
    ASSERT_EQ(out[1].second, expected[1].second);

    ASSERT_EQ(out[2].first, expected[2].first);
    ASSERT_EQ(out[2].second, expected[2].second);

    ASSERT_EQ(out[3].first, expected[3].first);
    ASSERT_EQ(out[3].second, expected[3].second);

    ASSERT_EQ(out[4].first, expected[4].first);
    ASSERT_EQ(out[4].second, expected[4].second);

    ASSERT_EQ(out[5].first, expected[5].first);
    ASSERT_EQ(out[5].second, expected[5].second);
}

void plaSlidingWindow2() {
    float maxError = 1.0f;
    float px[] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
    float py[] = {0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};

    af::array tsx(10, 1, px);
    af::array tsy(10, 1, py);
    af::array tss = join(1, tsx, tsy);

    std::vector<tsa::dimensionality::Point> expected = {
        tsa::dimensionality::Point(0.0, 0.0), tsa::dimensionality::Point(2.0, -0.1),
        tsa::dimensionality::Point(3.0, 5.0), tsa::dimensionality::Point(7.0, 9.0),
        tsa::dimensionality::Point(8.0, 9.0), tsa::dimensionality::Point(9.0, 9.0)};

    auto out = tsa::dimensionality::PLASlidingWindow(tss, maxError);

    float *pox_h = out.col(0).host<float>();
    float *poy_h = out.col(1).host<float>();

    ASSERT_EQ(pox_h[0], expected[0].first);
    ASSERT_EQ(poy_h[0], expected[0].second);

    ASSERT_EQ(pox_h[1], expected[1].first);
    ASSERT_EQ(poy_h[1], expected[1].second);

    ASSERT_EQ(pox_h[2], expected[2].first);
    ASSERT_EQ(poy_h[2], expected[2].second);

    ASSERT_EQ(pox_h[3], expected[3].first);
    ASSERT_EQ(poy_h[3], expected[3].second);

    ASSERT_EQ(pox_h[4], expected[4].first);
    ASSERT_EQ(poy_h[4], expected[4].second);

    ASSERT_EQ(pox_h[5], expected[5].first);
    ASSERT_EQ(poy_h[5], expected[5].second);
}

void ramerDouglasPeucker() {
    std::vector<tsa::dimensionality::Point> pointList;
    std::vector<tsa::dimensionality::Point> pointListOut;
    std::vector<tsa::dimensionality::Point> expected = {
        tsa::dimensionality::Point(0.0f, 0.0f), tsa::dimensionality::Point(2.0f, -0.1f),
        tsa::dimensionality::Point(3.0f, 5.0f), tsa::dimensionality::Point(6.0f, 8.1f),
        tsa::dimensionality::Point(9.0f, 9.0f)};

    pointList.push_back(tsa::dimensionality::Point(0.0f, 0.0f));
    pointList.push_back(tsa::dimensionality::Point(1.0f, 0.1f));
    pointList.push_back(tsa::dimensionality::Point(2.0f, -0.1f));
    pointList.push_back(tsa::dimensionality::Point(3.0f, 5.0f));
    pointList.push_back(tsa::dimensionality::Point(4.0f, 6.0f));
    pointList.push_back(tsa::dimensionality::Point(5.0f, 7.0f));
    pointList.push_back(tsa::dimensionality::Point(6.0f, 8.1f));
    pointList.push_back(tsa::dimensionality::Point(7.0f, 9.0f));
    pointList.push_back(tsa::dimensionality::Point(8.0f, 9.0f));
    pointList.push_back(tsa::dimensionality::Point(9.0f, 9.0f));

    pointListOut = tsa::dimensionality::ramerDouglasPeucker(pointList, 1.0);

    for (size_t i = 0; i < pointListOut.size(); i++) {
        ASSERT_EQ(pointListOut[i].first, expected[i].first);
        ASSERT_EQ(pointListOut[i].first, expected[i].first);
    }
}

void ramerDouglasPeucker2() {
    float pointList[] = {0.0f, 1.0f, 2.0f,  3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f,
                         0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};
    af::array points(10, 2, pointList);
    std::vector<tsa::dimensionality::Point> expected = {
        tsa::dimensionality::Point(0.0f, 0.0f), tsa::dimensionality::Point(2.0f, -0.1f),
        tsa::dimensionality::Point(3.0f, 5.0f), tsa::dimensionality::Point(6.0f, 8.1f),
        tsa::dimensionality::Point(9.0f, 9.0f)};

    af::array res = tsa::dimensionality::ramerDouglasPeucker(points, 1.0);
    float *points_x = res.col(0).host<float>();
    float *points_y = res.col(1).host<float>();

    for (size_t i = 0; i < expected.size(); i++) {
        ASSERT_EQ(points_x[i], expected[i].first);
        ASSERT_EQ(points_y[i], expected[i].second);
    }
}

void sax() {
    float pointList[] = {0.05f, 2.45f, 6.5f, 8.55f, 9.0f, 0.05f, 2.45f, 6.5f, 8.55f, 9.0f};
    af::array a(5, 2, pointList);

    int *out_h = tsa::dimensionality::SAX(a, 3).host<int>();

    int expected[] = {0, 0, 1, 2, 2, 0, 0, 1, 2, 2};

    for (size_t i = 0; i < 10; i++) {
        EXPECT_DOUBLE_EQ(out_h[i], expected[i]);
    }
}

void visvalingam() {
    std::vector<tsa::dimensionality::Point> pointList;
    std::vector<tsa::dimensionality::Point> out;
    std::vector<tsa::dimensionality::Point> expected = {
        tsa::dimensionality::Point(0.0f, 0.0f), tsa::dimensionality::Point(2.0f, -0.1f),
        tsa::dimensionality::Point(5.0f, 7.0f), tsa::dimensionality::Point(7.0f, 9.0f),
        tsa::dimensionality::Point(9.0f, 9.0f)};

    pointList.push_back(tsa::dimensionality::Point(0.0f, 0.0f));
    pointList.push_back(tsa::dimensionality::Point(1.0f, 0.1f));
    pointList.push_back(tsa::dimensionality::Point(2.0f, -0.1f));
    pointList.push_back(tsa::dimensionality::Point(3.0f, 5.0f));
    pointList.push_back(tsa::dimensionality::Point(4.0f, 6.0f));
    pointList.push_back(tsa::dimensionality::Point(5.0f, 7.0f));
    pointList.push_back(tsa::dimensionality::Point(6.0f, 8.1f));
    pointList.push_back(tsa::dimensionality::Point(7.0f, 9.0f));
    pointList.push_back(tsa::dimensionality::Point(8.0f, 9.0f));
    pointList.push_back(tsa::dimensionality::Point(9.0f, 9.0f));

    out = tsa::dimensionality::visvalingam(pointList, 5);

    for (size_t i = 0; i < out.size(); i++) {
        ASSERT_EQ(out[i].first, expected[i].first);
        ASSERT_EQ(out[i].second, expected[i].second);
    }
}

void visvalingam2() {
    float pointList[] = {0.0f, 1.0f, 2.0f,  3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f,
                         0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};
    af::array points(10, 2, pointList);
    std::vector<tsa::dimensionality::Point> expected = {
        tsa::dimensionality::Point(0.0f, 0.0f), tsa::dimensionality::Point(2.0f, -0.1f),
        tsa::dimensionality::Point(5.0f, 7.0f), tsa::dimensionality::Point(7.0f, 9.0f),
        tsa::dimensionality::Point(9.0f, 9.0f)};

    af::array res = tsa::dimensionality::visvalingam(points, 5);
    float *points_x = res.col(0).host<float>();
    float *points_y = res.col(1).host<float>();

    for (size_t i = 0; i < expected.size(); i++) {
        ASSERT_EQ(points_x[i], expected[i].first);
        ASSERT_EQ(points_y[i], expected[i].second);
    }
}

TSA_TEST(DimensionalityTests, PAA, paa)
TSA_TEST(DimensionalityTests, PAA_NORM, paaNorm)
TSA_TEST(DimensionalityTests, PIP, pip)
TSA_TEST(DimensionalityTests, PLABottomUp, plaBottomUp)
TSA_TEST(DimensionalityTests, PLABottomUp2, plaBottomUp2)
TSA_TEST(DimensionalityTests, PLASlidingWindow, plaSlidingWindow)
TSA_TEST(DimensionalityTests, PLASlidingWindow2, plaSlidingWindow2)
TSA_TEST(DimensionalityTests, RamerDouglasPeucker, ramerDouglasPeucker)
TSA_TEST(DimensionalityTests, RamerDouglasPeucker2, ramerDouglasPeucker2)
TSA_TEST(DimensionalityTests, SAX, sax)
TSA_TEST(DimensionalityTests, Visvalingam, visvalingam)
TSA_TEST(DimensionalityTests, Visvalingam2, visvalingam2)
