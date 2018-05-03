// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <tsa/dimensionality.h>
#include <tsa/simplification.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "tsaTest.h"

void ramerDouglasPeucker() {
    std::vector<tsa::dimensionality::Point> pointList;
    std::vector<tsa::dimensionality::Point> pointListOut;
    std::vector<tsa::dimensionality::Point> expected = {
        tsa::dimensionality::Point(0.0, 0.0), tsa::dimensionality::Point(2.0, -0.1),
        tsa::dimensionality::Point(3.0, 5.0), tsa::dimensionality::Point(6.0, 8.1),
        tsa::dimensionality::Point(9.0, 9.0)};

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

    pointListOut = tsa::dimensionality::ramerDouglasPeucker(pointList, 1.0);

    for (size_t i = 0; i < pointListOut.size(); i++) {
        ASSERT_EQ(pointListOut[i].first, expected[i].first);
        ASSERT_EQ(pointListOut[i].first, expected[i].first);
    }
}

void visvalingam() {
    std::vector<tsa::dimensionality::Point> pointList;
    std::vector<tsa::dimensionality::Point> out;
    std::vector<tsa::dimensionality::Point> expected = {
        tsa::dimensionality::Point(0.0, 0.0), tsa::dimensionality::Point(2.0, -0.1),
        tsa::dimensionality::Point(5.0, 7.0), tsa::dimensionality::Point(7.0, 9.0),
        tsa::dimensionality::Point(9.0, 9.0)};

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

    out = tsa::dimensionality::visvalingam(pointList, 5);

    for (size_t i = 0; i < out.size(); i++) {
        ASSERT_EQ(out[i].first, expected[i].first);
        ASSERT_EQ(out[i].second, expected[i].second);
    }
}

void paaNorm() {
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

    auto out = tsa::dimensionality::PAA(pointList, 6);

    std::vector<tsa::dimensionality::Point> expected = {
        tsa::dimensionality::Point(0.75, 0.05), tsa::dimensionality::Point(2.25, -0.1),
        tsa::dimensionality::Point(3.75, 5.5),  tsa::dimensionality::Point(5.25, 7.0),
        tsa::dimensionality::Point(6.75, 8.55), tsa::dimensionality::Point(8.25, 9.0)};

    for (size_t i = 0; i < out.size(); i++) {
        ASSERT_EQ(out[i].first, expected[i].first);
        ASSERT_EQ(out[i].second, expected[i].second);
    }
}

void paa() {
    float pointList[] = {0.0, 0.1, -0.1, 5.0, 6.0, 7.0, 8.1, 9.0, 9.0, 9.0};
    af::array a(10, 1, pointList);

    af::array out = tsa::dimensionality::PAA(a, 5);

    float *out_h = out.host<float>();
    std::vector<float> expected = {0.05, 2.45, 6.5, 8.55, 9.0};

    for (size_t i = 0; i < 5; i++) {
        ASSERT_EQ(out_h[i], expected[i]);
    }
}

void sax() {
    float pointList[] = {0.05, 2.45, 6.5, 8.55, 9.0};
    af::array a(5, 1, pointList);

    std::vector<int> out_h = tsa::dimensionality::SAX(a, 3);

    std::vector<int> expected = {0, 0, 1, 2, 2};

    for (size_t i = 0; i < 5; i++) {
        EXPECT_DOUBLE_EQ(out_h[i], expected[i]);
    }
}

void pip() {
    float exp_x[] = {0.0, 2.0, 4.0, 5.0, 6.0, 9.0};
    float exp_y[] = {0.0, -0.1, 6.0, 7.0, 8.1, 9.0};
    float px[] = {0.0, 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
    float py[] = {0.0, 0.1, -0.1, 5.0, 6.0, 7.0, 8.1, 9.0, 9.0, 9.0};

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

TSA_TEST(SimplificationTests, RamerDouglasPeucker, ramerDouglasPeucker);
TSA_TEST(SimplificationTests, Visvalingam, visvalingam);
TSA_TEST(DimensionalityTests, PAA_NORM, paaNorm);
TSA_TEST(DimensionalityTests, PAA, paa);
TSA_TEST(DimensionalityTests, SAX, sax);
TSA_TEST(DimensionalityTests, PIP, pip);
