// Copyright (c) 2018 Grumpy Cat Software S.L.
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "tsa.h"
#include "gtest/gtest.h"
#include <iostream>
#include <fstream>
#include <sstream>

TEST(DimensionalityTests, PAA_NORM)
{
    std::vector<tsa::simplification::Point> pointList;
	pointList.push_back(tsa::simplification::Point(0.0, 0.0));
	pointList.push_back(tsa::simplification::Point(1.0, 0.1));
	pointList.push_back(tsa::simplification::Point(2.0, -0.1));
	pointList.push_back(tsa::simplification::Point(3.0, 5.0));
	pointList.push_back(tsa::simplification::Point(4.0, 6.0));
	pointList.push_back(tsa::simplification::Point(5.0, 7.0));
	pointList.push_back(tsa::simplification::Point(6.0, 8.1));
	pointList.push_back(tsa::simplification::Point(7.0, 9.0));
	pointList.push_back(tsa::simplification::Point(8.0, 9.0));
	pointList.push_back(tsa::simplification::Point(9.0, 9.0));

	auto out = tsa::dimensionality::PAA_CPU(pointList.begin(), pointList.end(), 6);
	
    std::vector<tsa::simplification::Point> expected = {tsa::simplification::Point(0.75, 0.05), 
		tsa::simplification::Point(2.25, -0.1), tsa::simplification::Point(3.75, 5.5), 
		tsa::simplification::Point(5.25, 7.0), tsa::simplification::Point(6.75, 8.55), 
        tsa::simplification::Point(8.25, 9.0)};
	
    for(size_t i = 0; i < out.size();i++){
        EXPECT_DOUBLE_EQ(out[i].first, expected[i].first);
        EXPECT_DOUBLE_EQ(out[i].second, expected[i].second);
	}
}

TEST(DimensionalityTests, PAA)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);

    double pointList[] = {0.0, 0.1, -0.1, 5.0, 6.0, 7.0, 8.1, 9.0, 9.0, 9.0};
    af::array a(10, 1, pointList);

	af::array out = tsa::dimensionality::PAA(a, 5);
    
    double* out_h = out.host<double>();
    std::vector<double> expected = {0.05, 2.45, 6.5, 8.55, 9.0};
	
    for(size_t i = 0; i < 5;i++){
        EXPECT_DOUBLE_EQ(out_h[i], expected[i]);
	}
}


TEST(DimensionalityTests, SAX)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);

    float pointList[] = {0.05, 2.45, 6.5, 8.55, 9.0};
    af::array a(5, 1, pointList);

	std::vector<int> out_h = tsa::dimensionality::SAX(a, 3);
    
    std::vector<int> expected = {0, 0, 1, 2, 2};
	
    for(size_t i = 0; i < 5;i++){
        EXPECT_DOUBLE_EQ(out_h[i], expected[i]);
	}
}