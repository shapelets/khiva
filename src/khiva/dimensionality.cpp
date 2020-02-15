// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/dimensionality.h>
#include <khiva/internal/scopedHostPtr.h>

#include <algorithm>
#include <boost/math/distributions/normal.hpp>
#include <cmath>
#include <iostream>
#include <iterator>
#include <limits>
#include <stdexcept>
#include <utility>
#include <vector>

float computeTriangleArea(khiva::dimensionality::Point a, khiva::dimensionality::Point b,
                          khiva::dimensionality::Point c) {
    float res = 0.0;

    float f1 = a.first * (b.second - c.second);
    float f2 = b.first * (c.second - a.second);
    float f3 = c.first * (a.second - b.second);
    res = std::abs((f1 + f2 + f3) / 2);

    return res;
}

std::vector<float> computeBreakpoints(int alphabet_size, float mean_value, float std_value) {
    std::vector<float> res;
    boost::math::normal dist(mean_value, std_value);

    for (int i = 1; i < alphabet_size; i++) {
        float value = static_cast<float>(quantile(dist, (float)i * (1 / (float)alphabet_size)));
        res.push_back(value);
    }
    return res;
}

std::vector<int> generateAlphabet(int alphabet_size) {
    std::vector<int> res;
    for (int i = 0; i < alphabet_size; i++) {
        res.push_back(i);
    }
    return res;
}

double PerpendicularDistance(const khiva::dimensionality::Point &pt, const khiva::dimensionality::Point &lineStart,
                             const khiva::dimensionality::Point &lineEnd) {
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

/**
 * @brief We compute the vertical distance of the point p w.r.t. the line that connects start and end points.
 * We use the point-slope equiation to solve it.
 */
float verticalDistance(khiva::dimensionality::Point p, khiva::dimensionality::Point start,
                       khiva::dimensionality::Point end) {
    float res = 0.0;
    float dy = end.second - start.second;
    float dx = end.first - start.first;
    float m = dy / dx;
    float line_y = (p.first - start.first) * m + start.second;
    res = (p.second - line_y) * (p.second - line_y);

    return res;
}

/**
 * @brief This function just inserts a point in the given position of a vector.
 */
void insertPointBetweenSelected(khiva::dimensionality::Point p, int position,
                                std::vector<khiva::dimensionality::Point> &selected) {
    auto it = selected.begin();
    selected.insert(it + position, p);
}

/**
 * @brief This function just checks if the given point is already in the vector.
 */
bool isPointInDesiredList(khiva::dimensionality::Point point, std::vector<khiva::dimensionality::Point> selected) {
    bool found = false;
    for (size_t i = 0; i < selected.size(); i++) {
        // We just compare the horizontal component as it is unique
        if (selected[i].first == point.first) {
            found = true;
            break;
        }
    }
    return found;
}

/**
 * @brief This function calculates the segment indices that we need to compare the point.
 */
std::pair<int, int> getSegmentFromSelected(khiva::dimensionality::Point point,
                                           std::vector<khiva::dimensionality::Point> selected) {
    int lower = 0, upper = 0;
    // We do not check the first element, as it is fixed and set to the first element of the time series
    size_t i = 0;
    bool rebased = false;
    while (!rebased && (i < selected.size() - 1)) {
        // We check points until point.first > selected[i]
        if (point.first > selected[i].first) {
            lower = static_cast<int>(i);
            upper = static_cast<int>(i + 1);
        } else {
            rebased = true;
        }
        i++;
    }
    return std::make_pair(lower, upper);
}

std::vector<khiva::dimensionality::Point> khiva::dimensionality::PAA(std::vector<khiva::dimensionality::Point> points,
                                                                     int bins) {
    auto begin = points.begin();
    auto last = points.end();
    float xrange = (*(last - 1)).first - (*begin).first;
    float width_bin = xrange / bins;
    float reduction = bins / xrange;

    std::vector<float> sum(bins, 0.0);
    std::vector<int> counter(bins, 0);
    std::vector<khiva::dimensionality::Point> result(bins, khiva::dimensionality::Point(0.0, 0.0));

    // Iterating over the time series
    for (auto i = begin; i != last; i++) {
        int pos = static_cast<int>(std::min((*i).first * reduction, (float)(bins - 1)));
        sum[pos] += (*i).second;
        counter[pos] = counter[pos] + 1;
    }

    // Compute the average per bin
    for (int i = 0; i < bins; i++) {
        result[i].first = (width_bin * i) + (width_bin / 2.0f);
        result[i].second = sum[i] / counter[i];
    }
    return result;
}

template <typename T>
af::array PAA_CPU(af::array a, int bins) {
    af::array result;
    int n = a.dims(0);

    T *column = static_cast<T *>(malloc(sizeof(T) * n));
    T *reducedColumn = static_cast<T *>(malloc(sizeof(T) * bins));

    // Find out the number of elements per bin
    T elemPerBin = static_cast<T>(n) / static_cast<T>(bins);

    // For each column
    for (int i = 0; i < a.dims(1); i++) {
        af::array aux = a.col(i);
        aux.host(column);
        T start = 0.0;
        T end = elemPerBin - 1;

        // For each column
        for (int j = 0; j < bins; j++) {
            T avg = 0.0;
            int count = 0;

            // Compute avg for this segment
            for (int k = start; k <= end; k++) {
                avg = avg + column[k];
                count++;
            }
            avg = avg / count;
            reducedColumn[j] = avg;

            // Compute next segment
            start = std::ceil(end);
            end = end + elemPerBin;
            end = (end > n) ? n : end;
        }

        // First Column
        if (i == 0) {
            af::array aux(bins, 1, static_cast<T *>(reducedColumn));
            result = aux;
        } else {
            af::array aux(bins, 1, static_cast<T *>(reducedColumn));
            result = af::join(1, result, aux);
        }
    }
    free(reducedColumn);
    free(column);

    return result;
}

af::array khiva::dimensionality::PAA(af::array a, int bins) {
    // Resulting array
    af::array result;

    // Check dimensions are divisible, if not, call CPU version
    if (a.dims(0) % bins == 0) {
        dim_t n = a.dims(0);
        dim_t elem_row = n / bins;

        af::array b = af::moddims(a, elem_row, bins, a.dims(1));
        af::array addition = af::sum(b, 0);
        result = af::reorder(addition / elem_row, 1, 2, 0, 3);
    } else {
        // Call the CPU version
        if (a.type() == af::dtype::f64) {
            result = PAA_CPU<double>(a, bins);
        } else if (a.type() == af::dtype::f32) {
            result = PAA_CPU<float>(a, bins);
        }
    }

    return result;
}

af::array khiva::dimensionality::PIP(af::array ts, int numberIPs) {
    if (ts.dims(1) != 2) {
        throw std::invalid_argument("Invalid dims. Khiva array with two columns expected (x axis and y axis).");
    }
    dim_t n = ts.dims(0);
    int end = static_cast<int>(n - 1);

    if (n < 2) {
        throw std::invalid_argument("We can't delete all those important points");
    } else if (n <= numberIPs) {
        return ts;
    }

    // Extracting info from af::array
    auto h_x = khiva::utils::makeScopedHostPtr(ts.col(0).host<float>());
    auto h_y = khiva::utils::makeScopedHostPtr(ts.col(1).host<float>());

    // Converting c-arrays to vector of points
    std::vector<Point> points;
    for (int i = 0; i < n; i++) {
        points.emplace_back(h_x[i], h_y[i]);
    }

    // Allocating vectors for selected points
    std::vector<khiva::dimensionality::Point> selected;
    selected.push_back(points[0]);
    selected.push_back(points[end]);

    // we have to find (numberIPs - 2) points, as we have already included P[0] and P[end].
    // Number of passes over the collection
    for (int p = 0; p < (numberIPs - 2); p++) {
        float dmax = -1.0;
        int index = -1;
        int position = -1;

        // Find the next PIP
        for (int i = 1; i < end; i++) {
            // We first check if the point is already in the list.
            if (!isPointInDesiredList(points[i], selected)) {
                // segment contains the indices of the selected points which are the boundaries for the point i.
                std::pair<int, int> segment = getSegmentFromSelected(points[i], selected);
                float d = verticalDistance(points[i], selected[segment.first], selected[segment.second]);
                // We store the point with the maximum distance to the line that connects the segment.
                if (d > dmax) {
                    index = static_cast<int>(i);
                    dmax = d;
                    position = segment.second;
                }
            }
        }
        insertPointBetweenSelected(points[index], position, selected);
    }

    // Converting from vector to array
    float *x = (float *)malloc(sizeof(float) * selected.size());
    float *y = (float *)malloc(sizeof(float) * selected.size());
    for (size_t i = 0; i < selected.size(); i++) {
        x[i] = selected[i].first;
        y[i] = selected[i].second;
    }

    // from c-array to af::array
    af::array tsx(selected.size(), 1, x);
    af::array tsy(selected.size(), 1, y);
    af::array res = af::join(1, tsx, tsy);

    free(x);
    free(y);

    return res;
}

float calculateError(std::vector<khiva::dimensionality::Point> ts, int start, int end) {
    float res = 0;

    khiva::dimensionality::Point p1 = ts[start];
    khiva::dimensionality::Point p2 = ts[end];

    // We use the point-slope equation for the middle points between start and end: y = mx - mx_1 + y_1
    // where m = (y_2 - y_1) / (x_2 - x_1)
    float m = (p2.second - p1.second) / (p2.first - p1.first);
    for (int i = start; i <= end; i++) {
        res += std::pow(ts[i].second - (m * (ts[i].first - p1.first) + p1.second), 2);
    }

    return res;
}

khiva::dimensionality::Segment merge(khiva::dimensionality::Segment s1, khiva::dimensionality::Segment s2) {
    khiva::dimensionality::Segment res;

    res.first = s1.first;
    res.second = s2.second;

    return res;
}

std::vector<khiva::dimensionality::Point> khiva::dimensionality::PLABottomUp(std::vector<Point> ts, float maxError) {
    std::vector<khiva::dimensionality::Segment> segments;
    std::vector<float> mergeCost;

    // Allocating vector of segments
    for (size_t i = 0; i < ts.size() - 1; i = i + 2) {
        segments.push_back(std::make_pair(i, i + 1));
    }

    for (size_t i = 0; i < segments.size() - 1; i++) {
        mergeCost.push_back(calculateError(ts, segments[i].first, segments[i + 1].second));
    }

    // Calculate minimum, calculating in advance
    std::vector<float>::iterator minCost = std::min_element(std::begin(mergeCost), std::end(mergeCost));
    while ((segments.size() > 2) && (*minCost < maxError)) {
        // We have to merge
        int index = static_cast<int>(std::distance(std::begin(mergeCost), minCost));

        // Merge candidate segments
        segments[index] = merge(segments[index], segments[index + 1]);

        // Delete fused segment
        segments.erase(segments.begin() + index + 1);
        mergeCost.erase(mergeCost.begin() + index + 1);

        // Calculate new cost
        mergeCost[index] = calculateError(ts, segments[index].first, segments[index + 1].second);
        mergeCost[index - 1] = calculateError(ts, segments[index - 1].first, segments[index].second);

        // Calculate new minimum
        minCost = std::min_element(std::begin(mergeCost), std::end(mergeCost));
    }

    // Build a polyline from a set of segments
    std::vector<khiva::dimensionality::Point> result;
    for (size_t i = 0; i < segments.size(); i++) {
        result.push_back(ts[segments[i].first]);
        result.push_back(ts[segments[i].second]);
    }

    return result;
}

af::array khiva::dimensionality::PLABottomUp(af::array ts, float maxError) {
    if (ts.dims(1) != 2) {
        throw std::invalid_argument("Invalid dims. Khiva array with two columns expected (x axis and y axis).");
    }
    // Extracting info from af::array
    auto h_x = khiva::utils::makeScopedHostPtr(ts.col(0).host<float>());
    auto h_y = khiva::utils::makeScopedHostPtr(ts.col(1).host<float>());

    std::vector<khiva::dimensionality::Point> points;

    // Creating a vector of Points
    for (int i = 0; i < ts.dims(0); i++) {
        points.emplace_back(h_x[i], h_y[i]);
    }

    std::vector<khiva::dimensionality::Point> reducedPoints = khiva::dimensionality::PLABottomUp(points, maxError);
    std::vector<float> x;
    x.reserve(reducedPoints.size());
    std::vector<float> y;
    y.reserve(reducedPoints.size());

    // Converting from vector to array
    for (const auto &point : reducedPoints) {
        x.emplace_back(point.first);
        y.emplace_back(point.second);
    }

    // from c-array to af::array
    af::array tsx(reducedPoints.size(), 1, x.data());
    af::array tsy(reducedPoints.size(), 1, y.data());
    af::array res = af::join(1, tsx, tsy);

    return res;
}

std::vector<khiva::dimensionality::Point> khiva::dimensionality::PLASlidingWindow(
    std::vector<khiva::dimensionality::Point> ts, float maxError) {
    std::vector<khiva::dimensionality::Point> result;
    std::vector<khiva::dimensionality::Segment> segments;

    size_t anchor = 0;
    size_t i;

    // We haven´t explored the whole time series
    while (anchor < (ts.size() - 1)) {
        i = 1;
        while (((anchor + i) < ts.size()) &&
               (calculateError(ts, static_cast<int>(anchor), static_cast<int>(anchor + i)) < maxError)) {
            i = i + 1;
        }

        if ((anchor + i) == (ts.size() - 1)) {
            segments.emplace_back(anchor, anchor + i);
        } else {
            segments.emplace_back(anchor, anchor + i - 1);
        }
        anchor += i;
    }

    // Build a polyline from a set of segments
    for (auto &segment : segments) {
        result.emplace_back(ts[segment.first]);
        result.emplace_back(ts[segment.second]);
    }

    return result;
}

af::array khiva::dimensionality::PLASlidingWindow(af::array ts, float maxError) {
    if (ts.dims(1) != 2) {
        throw std::invalid_argument("Invalid dims. Khiva array with two columns expected (x axis and y axis).");
    }
    // Extracting info from af::array
    auto h_x = khiva::utils::makeScopedHostPtr(ts.col(0).host<float>());
    auto h_y = khiva::utils::makeScopedHostPtr(ts.col(1).host<float>());

    std::vector<khiva::dimensionality::Point> points;

    // Creating a vector of Points
    for (int i = 0; i < ts.dims(0); i++) {
        points.emplace_back(h_x[i], h_y[i]);
    }

    std::vector<khiva::dimensionality::Point> reducedPoints = khiva::dimensionality::PLASlidingWindow(points, maxError);
    std::vector<float> x;
    x.reserve(reducedPoints.size());
    std::vector<float> y;
    y.reserve(reducedPoints.size());
    // Converting from vector to array
    for (const auto &point : reducedPoints) {
        x.emplace_back(point.first);
        y.emplace_back(point.second);
    }

    // from c-array to af::array
    af::array tsx(reducedPoints.size(), 1, x.data());
    af::array tsy(reducedPoints.size(), 1, y.data());
    af::array res = af::join(1, tsx, tsy);

    return res;
}

std::vector<khiva::dimensionality::Point> khiva::dimensionality::ramerDouglasPeucker(
    std::vector<khiva::dimensionality::Point> pointList, double epsilon) {
    std::vector<khiva::dimensionality::Point> out;

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
        std::vector<khiva::dimensionality::Point> recResults1;
        std::vector<khiva::dimensionality::Point> recResults2;
        std::vector<khiva::dimensionality::Point> firstLine(pointList.begin(), pointList.begin() + index + 1);
        std::vector<khiva::dimensionality::Point> lastLine(pointList.begin() + index, pointList.end());
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

af::array khiva::dimensionality::ramerDouglasPeucker(af::array pointList, double epsilon) {
    if (pointList.dims(1) != 2) {
        throw std::invalid_argument("Invalid dims. Khiva array with two columns expected (x axis and y axis).");
    }
    std::vector<khiva::dimensionality::Point> points;
    auto x = khiva::utils::makeScopedHostPtr(pointList.col(0).host<float>());
    auto y = khiva::utils::makeScopedHostPtr(pointList.col(1).host<float>());

    for (int i = 0; i < pointList.dims(0); i++) {
        points.emplace_back(x[i], y[i]);
    }

    std::vector<khiva::dimensionality::Point> rPoints = khiva::dimensionality::ramerDouglasPeucker(points, epsilon);
    af::array out = af::constant(0, rPoints.size(), 2);

    std::vector<float> vx;
    vx.reserve(rPoints.size());
    std::vector<float> vy;
    vy.reserve(rPoints.size());

    for (const auto &rPoint : rPoints) {
        vx.emplace_back(rPoint.first);
        vy.emplace_back(rPoint.second);
    }

    af::array ox(rPoints.size(), vx.data());
    af::array oy(rPoints.size(), vy.data());

    return af::join(1, ox, oy);
}

af::array khiva::dimensionality::SAX(af::array a, int alphabet_size) {
    if (a.dims(1) != 2) {
        throw std::invalid_argument("Invalid dims. Khiva array with two columns expected (x axis and y axis).");
    }

    af::array result = af::constant(0.0, a.dims());
    // Let's store the x-axis.
    result(af::span, 0) += a.col(0);

    // Let's compute the y-axis.
    for (int k = 1; k < a.dims(1); k++) {
        af::array ts = a.col(k);
        auto mean_value = af::mean<float>(ts);
        auto std_value = af::stdev<float>(ts);
        dim_t n = ts.dims(0);
        std::vector<int> aux(n, 0);
        
        if (std_value > 0) {
            std::vector<float> breakingPoints = computeBreakpoints(alphabet_size, mean_value, std_value);
            std::vector<int> alphabet = generateAlphabet(alphabet_size);
            auto a_h = khiva::utils::makeScopedHostPtr(ts.host<float>());

            // Iterate across elements of ts
            for (int i = 0; i < n; i++) {
                size_t j = 0;                
                while ((j < breakingPoints.size()) && (a_h[i] > breakingPoints[j])) {
                    j++;
                }
                aux[i] = alphabet[j];
            }
        }

        // from c-array to af::array
        af::array res(aux.size(), 1, aux.data());

        result(af::span, k) += res;
    }

    return result;
}

struct VisvalingamSummaryPoint {
    float x;
    float y;
    float area;
};

void computeTriangleArea(VisvalingamSummaryPoint &a, VisvalingamSummaryPoint &b, VisvalingamSummaryPoint &c) {
    float res = 0.0;

    float f1 = a.x * (b.y - c.y);
    float f2 = b.x * (c.y - a.y);
    float f3 = c.x * (a.y - b.y);
    a.area = std::abs((f1 + f2 + f3) / 2);
}

#include <iterator>
template <typename Iter, typename Distance>
Iter shiftIterator(Iter iter, Distance positions) {
    auto it_shifted = iter;
    std::advance(it_shifted, positions);
    return it_shifted;
}

std::vector<khiva::dimensionality::Point> khiva::dimensionality::visvalingam(
    std::vector<khiva::dimensionality::Point> pointList, int num_points_allowed) {
    // variables
    std::vector<VisvalingamSummaryPoint> out(pointList.size());
    std::transform(pointList.begin(), pointList.end(), out.begin(), [](const khiva::dimensionality::Point &point) {
        return VisvalingamSummaryPoint{point.first, point.second, std::numeric_limits<float>::max()};
    });

    int iterations = static_cast<int>(out.size()) - num_points_allowed;

    if (pointList.size() < 4 || num_points_allowed < 3) {
        throw std::invalid_argument(
            "Invalid dimension of the series. Series to be reduce should be larger than 3 points "
            "and the number of resulting points larger than 2.");
    }

    // Precompute areas
    for (auto it = out.begin(); it != shiftIterator(out.end(), -2); ++it) {
        computeTriangleArea(*it, *shiftIterator(it, 1), *shiftIterator(it, 2));
    }

    // One point to be deleted on each iteration
    for (int iter = 0; iter < iterations; iter++) {
        auto min_element = std::min_element(
            out.cbegin(), out.cend(),
            [](const VisvalingamSummaryPoint &v1, const VisvalingamSummaryPoint &v2) { return v1.area < v2.area; });
        auto min_position = std::distance(out.cbegin(), min_element);

        // delete point and area with smallest area
        out.erase(shiftIterator(out.begin(), min_position + 1));
        auto beg = out.begin();
        if (min_position < 2) {
            computeTriangleArea(*beg, *shiftIterator(beg, 1), *shiftIterator(beg, 2));
            computeTriangleArea(*shiftIterator(beg, 1), *shiftIterator(beg, 2), *shiftIterator(beg, 3));
            computeTriangleArea(*shiftIterator(beg, 2), *shiftIterator(beg, 3), *shiftIterator(beg, 4));

        } else if (min_position >= 2 && min_position < out.size() - 3) {
            computeTriangleArea(*shiftIterator(beg, min_position), *shiftIterator(beg, min_position + 1),
                                *shiftIterator(beg, min_position + 2));
            computeTriangleArea(*shiftIterator(beg, min_position - 1), *shiftIterator(beg, min_position),
                                *shiftIterator(beg, min_position + 1));

        } else if (min_position >= out.size() - 3) {
            (*shiftIterator(beg, min_position)).area = std::numeric_limits<float>::max();
        }
    }

    std::vector<khiva::dimensionality::Point> outVector(num_points_allowed);
    std::transform(out.begin(), out.end(), outVector.begin(), [](const VisvalingamSummaryPoint &point) {
        return khiva::dimensionality::Point{point.x, point.y};
    });

    return outVector;
}

af::array khiva::dimensionality::visvalingam(af::array pointList, int numPoints) {
    if (pointList.dims(1) != 2) {
        throw std::invalid_argument("Invalid dims. Khiva array with two columns expected (x axis and y axis).");
    }
    std::vector<khiva::dimensionality::Point> points;
    points.reserve(pointList.dims(0));
    auto x = khiva::utils::makeScopedHostPtr(pointList.col(0).host<float>());
    auto y = khiva::utils::makeScopedHostPtr(pointList.col(1).host<float>());

    for (int i = 0; i < pointList.dims(0); i++) {
        points.emplace_back(x[i], y[i]);
    }

    std::vector<khiva::dimensionality::Point> rPoints = khiva::dimensionality::visvalingam(points, numPoints);
    af::array out = af::constant(0, rPoints.size(), 2);

    std::vector<float> vx;
    vx.reserve(rPoints.size());
    std::vector<float> vy;
    vy.reserve(rPoints.size());

    for (const auto &rPoint : rPoints) {
        vx.emplace_back(rPoint.first);
        vy.emplace_back(rPoint.second);
    }

    af::array ox(rPoints.size(), vx.data());
    af::array oy(rPoints.size(), vy.data());

    return af::join(1, ox, oy);
}
