// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <khiva/dimensionality.h>
#include <khiva/internal/scopedHostPtr.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "khivaTest.h"

void paaDivisible() {
    float pointList[] = {0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};
    af::array a(10, 1, pointList);

    af::array out = khiva::dimensionality::PAA(a, 5);

    auto out_h = khiva::utils::makeScopedHostPtr(out.host<float>());
    std::vector<float> expected = {0.05f, 2.45f, 6.5f, 8.55f, 9.0f};

    for (size_t i = 0; i < 5; i++) {
        ASSERT_EQ(out_h[i], expected[i]);
    }
}

void paaNonDivisibleFloat() {
    float pointList[] = {0.0f, 1.0f, 2.0f,  3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f,
                         0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};
    af::array a(10, 2, pointList);

    af::array out = khiva::dimensionality::PAA(a, 3);

    auto col0 = khiva::utils::makeScopedHostPtr(out.col(0).host<float>());
    auto col1 = khiva::utils::makeScopedHostPtr(out.col(1).host<float>());
    std::vector<float> col0_expected = {1.0, 4.0f, 7.5f};
    std::vector<float> col1_expected = {0.0f, 6.0f, 8.7750f};

    for (size_t i = 0; i < 3; i++) {
        ASSERT_NEAR(col0[i], col0_expected[i], EPSILON);
        ASSERT_NEAR(col1[i], col1_expected[i], EPSILON);
    }
}

void paaNonDivisibleDouble() {
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
    std::vector<khiva::dimensionality::Point> pointList;
    pointList.push_back(khiva::dimensionality::Point(0.0f, 0.0f));
    pointList.push_back(khiva::dimensionality::Point(1.0f, 0.1f));
    pointList.push_back(khiva::dimensionality::Point(2.0f, -0.1f));
    pointList.push_back(khiva::dimensionality::Point(3.0f, 5.0f));
    pointList.push_back(khiva::dimensionality::Point(4.0f, 6.0f));
    pointList.push_back(khiva::dimensionality::Point(5.0f, 7.0f));
    pointList.push_back(khiva::dimensionality::Point(6.0f, 8.1f));
    pointList.push_back(khiva::dimensionality::Point(7.0f, 9.0f));
    pointList.push_back(khiva::dimensionality::Point(8.0f, 9.0f));
    pointList.push_back(khiva::dimensionality::Point(9.0f, 9.0f));

    auto out = khiva::dimensionality::PAA(pointList, 6);

    std::vector<khiva::dimensionality::Point> expected = {
        khiva::dimensionality::Point(0.75, 0.05), khiva::dimensionality::Point(2.25, -0.1f),
        khiva::dimensionality::Point(3.75, 5.5),  khiva::dimensionality::Point(5.25, 7.0f),
        khiva::dimensionality::Point(6.75, 8.55), khiva::dimensionality::Point(8.25, 9.0f)};

    for (size_t i = 0; i < out.size(); i++) {
        ASSERT_EQ(out[i].first, expected[i].first);
        ASSERT_EQ(out[i].second, expected[i].second);
    }
}

void paaException() {
    float pointList[] = {0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};
    af::array a(10, 1, pointList);

    try {
        af::array out = khiva::dimensionality::PAA(a, 6);
    } catch (std::invalid_argument &ia) {
        EXPECT_EQ(ia.what(), std::string("Invalid number of points. The number of important points should be a factor "
                                         "of the total number of points."));
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

    af::array pointsOut = khiva::dimensionality::PIP(tss, 6);

    auto pox_h = khiva::utils::makeScopedHostPtr(pointsOut.col(0).host<float>());
    auto poy_h = khiva::utils::makeScopedHostPtr(pointsOut.col(1).host<float>());

    for (size_t i = 0; i < 6; i++) {
        ASSERT_EQ(pox_h[i], exp_x[i]);
        ASSERT_EQ(poy_h[i], exp_y[i]);
    }
}

void pipException() {
    float pointList[] = {0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};
    af::array a(10, 1, pointList);

    try {
        af::array out = khiva::dimensionality::PIP(a, 6);
    } catch (std::invalid_argument &ia) {
        EXPECT_EQ(ia.what(), std::string("Invalid dims. Khiva array with two columns expected (x axis and y axis)."));
    }
}

void plaBottomUp() {
    float maxError = 1.0;
    std::vector<khiva::dimensionality::Point> pointList;
    pointList.push_back(khiva::dimensionality::Point(0.0, 0.0));
    pointList.push_back(khiva::dimensionality::Point(1.0, 0.1));
    pointList.push_back(khiva::dimensionality::Point(2.0, -0.1));
    pointList.push_back(khiva::dimensionality::Point(3.0, 5.0));
    pointList.push_back(khiva::dimensionality::Point(4.0, 6.0));
    pointList.push_back(khiva::dimensionality::Point(5.0, 7.0));
    pointList.push_back(khiva::dimensionality::Point(6.0, 8.1));
    pointList.push_back(khiva::dimensionality::Point(7.0, 9.0));
    pointList.push_back(khiva::dimensionality::Point(8.0, 9.0));
    pointList.push_back(khiva::dimensionality::Point(9.0, 9.0));

    auto out = khiva::dimensionality::PLABottomUp(pointList, maxError);

    std::vector<khiva::dimensionality::Point> expected = {
        khiva::dimensionality::Point(0.0, 0.0),  khiva::dimensionality::Point(1.0, 0.1),
        khiva::dimensionality::Point(2.0, -0.1), khiva::dimensionality::Point(3.0, 5.0),
        khiva::dimensionality::Point(4.0, 6.0),  khiva::dimensionality::Point(7.0, 9.0),
        khiva::dimensionality::Point(8.0, 9.0),  khiva::dimensionality::Point(9.0, 9.0)};

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

    auto d_out = khiva::dimensionality::PLABottomUp(tss, maxError);
    auto pox = khiva::utils::makeScopedHostPtr(d_out.col(0).host<float>());
    auto poy = khiva::utils::makeScopedHostPtr(d_out.col(1).host<float>());

    std::vector<khiva::dimensionality::Point> expected = {
        khiva::dimensionality::Point(0.0, 0.0),  khiva::dimensionality::Point(1.0, 0.1),
        khiva::dimensionality::Point(2.0, -0.1), khiva::dimensionality::Point(3.0, 5.0),
        khiva::dimensionality::Point(4.0, 6.0),  khiva::dimensionality::Point(7.0, 9.0),
        khiva::dimensionality::Point(8.0, 9.0),  khiva::dimensionality::Point(9.0, 9.0)};

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

void plaBottomUpException() {
    float pointList[] = {0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};
    af::array a(10, 1, pointList);

    try {
        af::array out = khiva::dimensionality::PLABottomUp(a, 6);
    } catch (std::invalid_argument &ia) {
        EXPECT_EQ(ia.what(), std::string("Invalid dims. Khiva array with two columns expected (x axis and y axis)."));
    }
}

void plaSlidingWindow() {
    float maxError = 1.0;
    std::vector<khiva::dimensionality::Point> pointList;
    pointList.push_back(khiva::dimensionality::Point(0.0, 0.0));
    pointList.push_back(khiva::dimensionality::Point(1.0, 0.1));
    pointList.push_back(khiva::dimensionality::Point(2.0, -0.1));
    pointList.push_back(khiva::dimensionality::Point(3.0, 5.0));
    pointList.push_back(khiva::dimensionality::Point(4.0, 6.0));
    pointList.push_back(khiva::dimensionality::Point(5.0, 7.0));
    pointList.push_back(khiva::dimensionality::Point(6.0, 8.1));
    pointList.push_back(khiva::dimensionality::Point(7.0, 9.0));
    pointList.push_back(khiva::dimensionality::Point(8.0, 9.0));
    pointList.push_back(khiva::dimensionality::Point(9.0, 9.0));

    auto out = khiva::dimensionality::PLASlidingWindow(pointList, maxError);

    std::vector<khiva::dimensionality::Point> expected = {
        khiva::dimensionality::Point(0.0, 0.0), khiva::dimensionality::Point(2.0, -0.1),
        khiva::dimensionality::Point(3.0, 5.0), khiva::dimensionality::Point(7.0, 9.0),
        khiva::dimensionality::Point(8.0, 9.0), khiva::dimensionality::Point(9.0, 9.0)};

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

    std::vector<khiva::dimensionality::Point> expected = {
        khiva::dimensionality::Point(0.0, 0.0), khiva::dimensionality::Point(2.0, -0.1),
        khiva::dimensionality::Point(3.0, 5.0), khiva::dimensionality::Point(7.0, 9.0),
        khiva::dimensionality::Point(8.0, 9.0), khiva::dimensionality::Point(9.0, 9.0)};

    auto out = khiva::dimensionality::PLASlidingWindow(tss, maxError);

    auto pox_h = khiva::utils::makeScopedHostPtr(out.col(0).host<float>());
    auto poy_h = khiva::utils::makeScopedHostPtr(out.col(1).host<float>());

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

void plaSlidingWindowException() {
    float pointList[] = {0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};
    af::array a(10, 1, pointList);

    try {
        af::array out = khiva::dimensionality::PLASlidingWindow(a, 6);
    } catch (std::invalid_argument &ia) {
        EXPECT_EQ(ia.what(), std::string("Invalid dims. Khiva array with two columns expected (x axis and y axis)."));
    }
}

void ramerDouglasPeucker() {
    std::vector<khiva::dimensionality::Point> pointList;
    std::vector<khiva::dimensionality::Point> pointListOut;
    std::vector<khiva::dimensionality::Point> expected = {
        khiva::dimensionality::Point(0.0f, 0.0f), khiva::dimensionality::Point(2.0f, -0.1f),
        khiva::dimensionality::Point(3.0f, 5.0f), khiva::dimensionality::Point(6.0f, 8.1f),
        khiva::dimensionality::Point(9.0f, 9.0f)};

    pointList.push_back(khiva::dimensionality::Point(0.0f, 0.0f));
    pointList.push_back(khiva::dimensionality::Point(1.0f, 0.1f));
    pointList.push_back(khiva::dimensionality::Point(2.0f, -0.1f));
    pointList.push_back(khiva::dimensionality::Point(3.0f, 5.0f));
    pointList.push_back(khiva::dimensionality::Point(4.0f, 6.0f));
    pointList.push_back(khiva::dimensionality::Point(5.0f, 7.0f));
    pointList.push_back(khiva::dimensionality::Point(6.0f, 8.1f));
    pointList.push_back(khiva::dimensionality::Point(7.0f, 9.0f));
    pointList.push_back(khiva::dimensionality::Point(8.0f, 9.0f));
    pointList.push_back(khiva::dimensionality::Point(9.0f, 9.0f));

    pointListOut = khiva::dimensionality::ramerDouglasPeucker(pointList, 1.0);

    for (size_t i = 0; i < pointListOut.size(); i++) {
        ASSERT_EQ(pointListOut[i].first, expected[i].first);
        ASSERT_EQ(pointListOut[i].first, expected[i].first);
    }
}

void ramerDouglasPeucker2() {
    float pointList[] = {0.0f, 1.0f, 2.0f,  3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f,
                         0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};
    af::array points(10, 2, pointList);
    std::vector<khiva::dimensionality::Point> expected = {
        khiva::dimensionality::Point(0.0f, 0.0f), khiva::dimensionality::Point(2.0f, -0.1f),
        khiva::dimensionality::Point(3.0f, 5.0f), khiva::dimensionality::Point(6.0f, 8.1f),
        khiva::dimensionality::Point(9.0f, 9.0f)};

    af::array res = khiva::dimensionality::ramerDouglasPeucker(points, 1.0);
    auto points_x = khiva::utils::makeScopedHostPtr(res.col(0).host<float>());
    auto points_y = khiva::utils::makeScopedHostPtr(res.col(1).host<float>());

    for (size_t i = 0; i < expected.size(); i++) {
        ASSERT_EQ(points_x[i], expected[i].first);
        ASSERT_EQ(points_y[i], expected[i].second);
    }
}

void ramerDouglasPeuckerException() {
    float pointList[] = {0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};
    af::array a(10, 1, pointList);

    try {
        af::array out = khiva::dimensionality::ramerDouglasPeucker(a, 6);
    } catch (std::invalid_argument &ia) {
        EXPECT_EQ(ia.what(), std::string("Invalid dims. Khiva array with two columns expected (x axis and y axis)."));
    }
}

void sax() {
    float pointList[] = {0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};
    af::array a(5, 2, pointList);

    af::array out = khiva::dimensionality::SAX(a, 3);

    auto out_h = khiva::utils::makeScopedHostPtr(out.host<float>());
    float expected[] = {0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 0.0, 1.0, 2.0, 2.0, 2.0};

    for (size_t i = 0; i < 10; i++) {
        EXPECT_DOUBLE_EQ(out_h[i], expected[i]);
    }
}

void sax2() {
    float pointList[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 2.0f, 2.0f, 2.0f, 2.0f, 2.0f};
    af::array a(5, 2, pointList);

    af::array out = khiva::dimensionality::SAX(a, 3);

    auto out_h = khiva::utils::makeScopedHostPtr(out.host<float>());
    float expected[] = {1.0, 2.0, 3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 0.0};

    for (size_t i = 0; i < 10; i++) {
        EXPECT_DOUBLE_EQ(out_h[i], expected[i]);
    }
}

void saxException() {
    float pointList[] = {0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};
    af::array a(10, 1, pointList);

    try {
        af::array out = khiva::dimensionality::SAX(a, 6);
    } catch (std::invalid_argument &ia) {
        EXPECT_EQ(ia.what(), std::string("Invalid dims. Khiva array with two columns expected (x axis and y axis)."));
    }
}

void visvalingam() {
    std::vector<khiva::dimensionality::Point> pointList;
    std::vector<khiva::dimensionality::Point> out;
    std::vector<khiva::dimensionality::Point> expected = {
        khiva::dimensionality::Point(0.0f, 0.0f), khiva::dimensionality::Point(2.0f, -0.1f),
        khiva::dimensionality::Point(3.0f, 5.0f), khiva::dimensionality::Point(7.0f, 9.0f),
        khiva::dimensionality::Point(9.0f, 9.0f)};

    pointList.push_back(khiva::dimensionality::Point(0.0f, 0.0f));
    pointList.push_back(khiva::dimensionality::Point(1.0f, 0.1f));
    pointList.push_back(khiva::dimensionality::Point(2.0f, -0.1f));
    pointList.push_back(khiva::dimensionality::Point(3.0f, 5.0f));
    pointList.push_back(khiva::dimensionality::Point(4.0f, 6.0f));
    pointList.push_back(khiva::dimensionality::Point(5.0f, 7.0f));
    pointList.push_back(khiva::dimensionality::Point(6.0f, 8.1f));
    pointList.push_back(khiva::dimensionality::Point(7.0f, 9.0f));
    pointList.push_back(khiva::dimensionality::Point(8.0f, 9.0f));
    pointList.push_back(khiva::dimensionality::Point(9.0f, 9.0f));

    out = khiva::dimensionality::visvalingam(pointList, 5);

    for (size_t i = 0; i < out.size(); i++) {
        ASSERT_EQ(out[i].first, expected[i].first);
        ASSERT_EQ(out[i].second, expected[i].second);
    }
}

void visvalingam2() {
    float pointList[] = {0.0f, 1.0f, 2.0f,  3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f,
                         0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};
    af::array points(10, 2, pointList);
    std::vector<khiva::dimensionality::Point> expected = {
        khiva::dimensionality::Point(0.0f, 0.0f), khiva::dimensionality::Point(2.0f, -0.1f),
        khiva::dimensionality::Point(3.0f, 5.0f), khiva::dimensionality::Point(7.0f, 9.0f),
        khiva::dimensionality::Point(9.0f, 9.0f)};

    af::array res = khiva::dimensionality::visvalingam(points, 5);
    auto points_x = khiva::utils::makeScopedHostPtr(res.col(0).host<float>());
    auto points_y = khiva::utils::makeScopedHostPtr(res.col(1).host<float>());

    for (size_t i = 0; i < expected.size(); i++) {
        ASSERT_EQ(points_x[i], expected[i].first);
        ASSERT_EQ(points_y[i], expected[i].second);
    }
}

void visvalingamException() {
    float pointList[] = {0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};
    af::array a(10, 1, pointList);

    try {
        af::array out = khiva::dimensionality::visvalingam(a, 6);
    } catch (std::invalid_argument &ia) {
        EXPECT_EQ(ia.what(), std::string("Invalid dims. Khiva array with two columns expected (x axis and y axis)."));
    }
}

KHIVA_TEST(DimensionalityTests, PAA_Divisible, paaDivisible)
KHIVA_TEST(DimensionalityTests, PAA_NonDivisibleFloat, paaNonDivisibleFloat)
KHIVA_TEST(DimensionalityTests, PAA_NonDivisibleDouble, paaNonDivisibleDouble)
KHIVA_TEST(DimensionalityTests, PAA_NORM, paaNorm)
KHIVA_TEST(DimensionalityTests, PAAException, paaException)
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
KHIVA_TEST(DimensionalityTests, Visvalingam, visvalingam)
KHIVA_TEST(DimensionalityTests, Visvalingam2, visvalingam2)
KHIVA_TEST(DimensionalityTests, VisvalingamException, visvalingamException)
