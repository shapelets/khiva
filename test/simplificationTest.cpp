// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <tsa/simplification.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "tsaTest.h"

std::vector<tsa::simplification::Point> getNextLineAndSplitIntoTokens(std::istream &str_input) {
    std::vector<tsa::simplification::Point> result;
    std::vector<int> dates;
    std::vector<double> values;

    std::string line;
    std::stringstream linestream;
    std::string cell;
    int rown = 0;
    int celln = 0;

    struct tm mytm;
    time_t t;

    // read line
    while (std::getline(str_input, line)) {
        linestream.str(line);
        // read cells
        while (std::getline(linestream, cell, ',')) {
            tsa::simplification::Point p;

            strptime(cell.c_str(), "%Y-%m-%d", &mytm);
            t = mktime(&mytm);
            p.first = (long)t;
            // std::cout << "Date: " << cell << " " << " Unix: " << (long)t << std::endl;
            std::getline(linestream, cell, ',');

            p.second = std::stof(cell);
            result.push_back(p);
            values.push_back(p.second);
            dates.push_back(t);
        }
        linestream.clear();
        rown++;
    }
    return result;
}

void saveVectorToCSV(std::vector<tsa::simplification::Point> out, std::string filename) {
    std::ofstream myfile(filename);
    int vsize = out.size();
    for (int n = 0; n < vsize; n++) {
        myfile << (long)out[n].first << ", " << out[n].second << std::endl;
    }
}

void ramerDouglasPeucker() {
    std::vector<tsa::simplification::Point> pointList;
    std::vector<tsa::simplification::Point> pointListOut;
    std::vector<tsa::simplification::Point> expected = {
        tsa::simplification::Point(0.0, 0.0), tsa::simplification::Point(2.0, -0.1),
        tsa::simplification::Point(3.0, 5.0), tsa::simplification::Point(6.0, 8.1),
        tsa::simplification::Point(9.0, 9.0)};

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

    pointListOut = tsa::simplification::ramerDouglasPeucker(pointList, 1.0);

    for (size_t i = 0; i < pointListOut.size(); i++) {
        ASSERT_EQ(pointListOut[i].first, expected[i].first);
        ASSERT_EQ(pointListOut[i].first, expected[i].first);
    }
}

void visvalingam() {
    std::vector<tsa::simplification::Point> pointList;
    std::vector<tsa::simplification::Point> out;
    std::vector<tsa::simplification::Point> expected = {
        tsa::simplification::Point(0.0, 0.0), tsa::simplification::Point(2.0, -0.1),
        tsa::simplification::Point(5.0, 7.0), tsa::simplification::Point(7.0, 9.0),
        tsa::simplification::Point(9.0, 9.0)};

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

    out = tsa::simplification::visvalingam_simplify(pointList, 5);

    for (size_t i = 0; i < out.size(); i++) {
        ASSERT_EQ(out[i].first, expected[i].first);
        ASSERT_EQ(out[i].second, expected[i].second);
    }
}

TSA_TEST(SimplificationTests, RamerDouglasPeucker, ramerDouglasPeucker);
TSA_TEST(SimplificationTests, Visvalingam, visvalingam);