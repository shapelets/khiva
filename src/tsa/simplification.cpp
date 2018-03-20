// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa/simplification.h>
#include <cmath>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <utility>

double PerpendicularDistance(const tsa::simplification::Point &pt, const tsa::simplification::Point &lineStart,
                             const tsa::simplification::Point &lineEnd) {
    double dx = lineEnd.first - lineStart.first;
    double dy = lineEnd.second - lineStart.second;

    // Normalise
    double mag = pow(pow(dx, 2.0) + pow(dy, 2.0), 0.5);
    if (mag > 0.0) {
        dx /= mag;
        dy /= mag;
    }

    double pvx = pt.first - lineStart.first;
    double pvy = pt.second - lineStart.second;

    // Get dot product (project pv onto normalized direction)
    double pvdot = dx * pvx + dy * pvy;

    // Scale line direction vector
    double dsx = pvdot * dx;
    double dsy = pvdot * dy;

    // Subtract this from pv
    double ax = pvx - dsx;
    double ay = pvy - dsy;

    return pow(pow(ax, 2.0) + pow(ay, 2.0), 0.5);
}

std::vector<tsa::simplification::Point> tsa::simplification::ramerDouglasPeucker(
    std::vector<tsa::simplification::Point> pointList, double epsilon) {
    std::vector<tsa::simplification::Point> out;

    if (pointList.size() < 2) throw std::invalid_argument("Not enough points to simplify ...");

    // Find the point with the maximum distance from line between start and end
    double dmax = 0.0;
    size_t index = 0;
    size_t end = pointList.size() - 1;

    for (size_t i = 1; i < end; i++) {
        double d = PerpendicularDistance(pointList[i], pointList[0], pointList[end]);
        if (d > dmax) {
            index = i;
            dmax = d;
        }
    }

    // If max distance is greater than epsilon, recursively simplify
    if (dmax > epsilon) {
        std::vector<tsa::simplification::Point> recResults1;
        std::vector<tsa::simplification::Point> recResults2;
        std::vector<tsa::simplification::Point> firstLine(pointList.begin(), pointList.begin() + index + 1);
        std::vector<tsa::simplification::Point> lastLine(pointList.begin() + index, pointList.end());
        recResults1 = ramerDouglasPeucker(firstLine, epsilon);
        recResults2 = ramerDouglasPeucker(lastLine, epsilon);

        // Build the result list
        out.assign(recResults1.begin(), recResults1.end() - 1);
        out.insert(out.end(), recResults2.begin(), recResults2.end());
        if (out.size() < 2) throw std::runtime_error("Problem assembling output");
    } else {
        // Just return start and end points
        out.clear();
        out.push_back(pointList[0]);
        out.push_back(pointList[end]);
    }
    return out;
}

// array tsa::simplification::ramerDouglasPeucker(array pointList, double epsilon){
// 	int elems = pointList.elements();
// 	tsa::simplification::Point * a = pointList.host<tsa::simplification::Point>();
// 	std::vector<tsa::simplification::Point> arrayPoints(a, a + elems);

// 	std::vector<tsa::simplification::Point> res = tsa::simplification::ramerDouglasPeucker(arrayPoints, epsilon);
// 	tsa::simplification::Point * arr = (tsa::simplification::Point *) malloc(sizeof(tsa::simplification::Point) *
// elems); 	std::copy(res.begin(), res.end(), arr);

// 	array result = af::array(elems, arr);
// 	return result;
// }

float computeTriangleArea(tsa::simplification::Point a, tsa::simplification::Point b, tsa::simplification::Point c) {
    float res = 0.0;

    float base = std::sqrt(std::pow((c.first - a.first), 2) + std::pow((c.second - a.second), 2));
    float height = std::abs(b.first - a.first);
    res = base * height / 2.0;

    return res;
}

std::vector<tsa::simplification::Point> tsa::simplification::visvalingam_simplify(
    std::vector<tsa::simplification::Point> pointList, int num_points_allowed) {
    // variables
    std::vector<tsa::simplification::Point> out(pointList.begin(), pointList.end());
    float min_area = std::numeric_limits<float>::max();
    int candidate_point = -1;
    int iterations = out.size() - num_points_allowed;

    // One point to be deleted in each iteration
    for (int iter = 0; iter < iterations; iter++) {
        for (int p = 0; p < out.size() - 2; p++) {
            float area = computeTriangleArea(out[p], out[p + 1], out[p + 2]);
            if (area < min_area) {
                min_area = area;
                candidate_point = p + 1;
            }
        }
        std::vector<tsa::simplification::Point>::iterator nth = out.begin() + candidate_point;
        out.erase(nth);
        min_area = std::numeric_limits<float>::max();
    }
    return out;
}

// array tsa::simplification::visvalingam_simplify(array pointList, int numPoints){
// 	int elems = pointList.elements();
// 	tsa::simplification::Point * a = pointList.host<tsa::simplification::Point>();
// 	std::vector<tsa::simplification::Point> arrayPoints(a, a + elems);

// 	std::vector<tsa::simplification::Point> res = tsa::simplification::visvalingam_simplify(arrayPoints, numPoints);
// 	tsa::simplification::Point * arr = (tsa::simplification::Point *) malloc(sizeof(tsa::simplification::Point) *
// elems); 	std::copy(res.begin(), res.end(), arr); 	array result = af::array(elems, arr); 	return result;
// }
