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
#include <iterator>
#include <limits>
#include <stdexcept>
#include <utility>
#include <vector>
#include <map>
#include <set>

using namespace khiva::dimensionality;

struct VisvalingamSummaryPoint {
    float x;
    float y;
    int64_t area;
};

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

double PerpendicularDistance(const Point &pt, const Point &lineStart, const Point &lineEnd) {
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
float verticalDistance(Point p, Point start, Point end) {
    float dy = end.second - start.second;
    float dx = end.first - start.first;
    float m = dy / dx;
    float line_y = (p.first - start.first) * m + start.second;
    return (p.second - line_y) * (p.second - line_y);
}

/**
 * @brief This function just inserts a point in the given position of a vector.
 */
void insertPointBetweenSelected(Point p, int position,
                                std::vector<Point> &selected) {
    auto it = selected.begin();
    selected.insert(it + position, p);
}

/**
 * @brief This function just checks if the given point is already in the vector.
 */
bool isPointInDesiredList(khiva::dimensionality::Point point,
                          const std::vector<khiva::dimensionality::Point> &selected) {
    auto it = std::find_if(selected.cbegin(), selected.cend(),
                 [&point](const khiva::dimensionality::Point &p) { return p.first == point.first; });
    return it != selected.end();
}

/**
 * @brief This function calculates the segment indices that we need to compare the point.
 */
std::pair<int, int> getSegmentFromSelected(Point point, const std::vector<Point>& selected) {
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

std::vector<Point> khiva::dimensionality::PAA(const std::vector<Point>& points, int bins) {
    auto begin = points.begin();
    auto last = points.end();
    float xrange = (*(last - 1)).first - (*begin).first;
    float width_bin = xrange / bins;
    float reduction = bins / xrange;

    std::vector<float> sum(bins, 0.0);
    std::vector<int> counter(bins, 0);
    std::vector<Point> result(bins, Point(0.0, 0.0));

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

    std::vector<T> column;
    column.reserve(n);
    std::vector<T> reducedColumn;
    reducedColumn.reserve(bins);

    // Find out the number of elements per bin
    T elemPerBin = static_cast<T>(n) / static_cast<T>(bins);

    // For each column
    for (int i = 0; i < a.dims(1); i++) {
        af::array aux = a.col(i);
        aux.host(column.data());
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
        af::array col(bins, 1, reducedColumn.data());
        if (i == 0) {
            result = col;
        } else {
            result = af::join(1, result, col);
        }
    }
    return result;
}

af::array khiva::dimensionality::PAA(const af::array& a, int bins) {
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
    std::vector<Point> selected;
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
                    index = i;
                    dmax = d;
                    position = segment.second;
                }
            }
        }
        insertPointBetweenSelected(points[index], position, selected);
    }

    // Converting from vector to array
    std::vector<float> x;
    x.reserve(selected.size());
    std::vector<float> y;
    y.reserve(selected.size());
    for (size_t i = 0; i < selected.size(); i++) {
        x[i] = selected[i].first;
        y[i] = selected[i].second;
    }

    // from c-array to af::array
    af::array tsx(selected.size(), 1, x.data());
    af::array tsy(selected.size(), 1, y.data());
    af::array res = af::join(1, tsx, tsy);

    return res;
}

float calculateError(std::vector<Point> ts, int start, int end) {
    float res = 0.0f;

    Point p1 = ts[start];
    Point p2 = ts[end];

    // We use the point-slope equation for the middle points between start and end: y = mx - mx_1 + y_1
    // where m = (y_2 - y_1) / (x_2 - x_1)
    float m = (p2.second - p1.second) / (p2.first - p1.first);
    for (int i = start; i <= end; i++) {
        res += std::pow(ts[i].second - (m * (ts[i].first - p1.first) + p1.second), 2);
    }

    return res;
}

Segment merge(Segment s1, Segment s2) {
    Segment res;

    res.first = s1.first;
    res.second = s2.second;

    return res;
}

std::vector<Point> khiva::dimensionality::PLABottomUp(const std::vector<Point>& ts, float maxError) {
    std::vector<Segment> segments;
    segments.reserve(ts.size());

    // Allocating vector of segments
    for (size_t i = 0; i < ts.size() - 1; i = i + 2) {
        segments.emplace_back(i, i + 1);
    }

    std::vector<float> mergeCost;
    mergeCost.reserve(segments.size());
    for (size_t i = 0; i < segments.size() - 1; i++) {
        mergeCost.push_back(calculateError(ts, segments[i].first, segments[i + 1].second));
    }

    // Calculate minimum, calculating in advance
    auto minCost = std::min_element(std::begin(mergeCost), std::end(mergeCost));
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
    std::vector<Point> result;
    for (auto & segment : segments) {
        result.push_back(ts[segment.first]);
        result.push_back(ts[segment.second]);
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

    std::vector<Point> points;

    // Creating a vector of Points
    for (int i = 0; i < ts.dims(0); i++) {
        points.emplace_back(h_x[i], h_y[i]);
    }

    std::vector<Point> reducedPoints = PLABottomUp(points, maxError);
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

std::vector<Point> khiva::dimensionality::PLASlidingWindow(const std::vector<Point>& ts, float maxError) {
    std::vector<Point> result;
    std::vector<Segment> segments;

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

    std::vector<Point> points;

    // Creating a vector of Points
    for (int i = 0; i < ts.dims(0); i++) {
        points.emplace_back(h_x[i], h_y[i]);
    }

    std::vector<Point> reducedPoints = PLASlidingWindow(points, maxError);
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

std::vector<Point> khiva::dimensionality::ramerDouglasPeucker(
    std::vector<Point> pointList, double epsilon) {
    std::vector<Point> out;

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
        std::vector<Point> recResults1;
        std::vector<Point> recResults2;
        std::vector<Point> firstLine(pointList.begin(), pointList.begin() + index + 1);
        std::vector<Point> lastLine(pointList.begin() + index, pointList.end());
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
    std::vector<Point> points;
    auto x = khiva::utils::makeScopedHostPtr(pointList.col(0).host<float>());
    auto y = khiva::utils::makeScopedHostPtr(pointList.col(1).host<float>());

    for (int i = 0; i < pointList.dims(0); i++) {
        points.emplace_back(x[i], y[i]);
    }

    std::vector<Point> rPoints = ramerDouglasPeucker(points, epsilon);
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

int64_t computeTriangleArea(const VisvalingamSummaryPoint &a,
        const VisvalingamSummaryPoint &b,
        const VisvalingamSummaryPoint &c,
        const long scale = 1e9) {

    float f1 = a.x * (b.y - c.y);
    float f2 = b.x * (c.y - a.y);
    float f3 = c.x * (a.y - b.y);
    return  static_cast<int64_t>(std::abs((f1 + f2 + f3) / 2.0f) * scale);
}

#include <iterator>
template <typename Iter, typename Distance>
Iter shiftIterator(Iter iter, Distance positions) {
    std::advance(iter, positions);
    return iter;
}

class mapComparator {
public:
    bool operator()(const std::pair<int64_t, int64_t> &p1, const std::pair<int64_t, int64_t> &p2) const {
        return ((p1.first < p2.first) || ((p1.first == p2.first) && (p1.second < p2.second)));
    }
};

void recomputeAreaNeighbor(std::map<int64_t, VisvalingamSummaryPoint>::iterator &iterator_point,
                            std::set<std::pair<int64_t, int64_t>, mapComparator> &point_indexer,
                            std::map<int64_t, VisvalingamSummaryPoint> &points,
                            const int64_t scale){

    auto im1m1 = shiftIterator(iterator_point, -1);
    auto im1p1 = shiftIterator(iterator_point, 1);
    auto original_position_minus1 = iterator_point->first;

    auto old_area_minus1 = iterator_point->second.area;
    auto new_area_minus1 = computeTriangleArea(im1m1->second, iterator_point->second, im1p1->second, scale);
    points[iterator_point->first] = VisvalingamSummaryPoint{iterator_point->second.x,
                                                             iterator_point->second.y,
                                                             new_area_minus1};

    auto it = point_indexer.find(std::make_pair(old_area_minus1, original_position_minus1));
    point_indexer.erase(it);

    point_indexer.insert(std::pair<int64_t, int64_t>(
            std::make_pair(new_area_minus1, original_position_minus1)));
}

std::vector<Point> khiva::dimensionality::visvalingam(const std::vector<Point>& pointList, int64_t numPoints, int64_t scale) {

    std::map<int64_t, VisvalingamSummaryPoint> points;
    std::set<std::pair<int64_t, int64_t>, mapComparator> point_indexer;
    int64_t counter = 0;

    std::transform(pointList.cbegin(), pointList.cend(), std::inserter(points, points.end()),
                   [&counter](const Point &point) {
                       return std::make_pair(counter++,
                               VisvalingamSummaryPoint{point.first, point.second, std::numeric_limits<int64_t>::max()});
                   });

    auto points_to_be_deleted = pointList.size() - numPoints;
    auto point_iterator = point_indexer.begin();

    // Precompute areas
    for (auto it = shiftIterator(points.begin(), 1); it != shiftIterator(points.end(), -1); ++it) {
        auto area = computeTriangleArea(shiftIterator(it, -1)->second, it->second, shiftIterator(it, 1)->second, scale);
        it->second.area = area;
        point_iterator = point_indexer.insert(point_iterator, std::make_pair(area, it->first));
    }

    // One point to be deleted on each iteration
    for (int64_t iter = 0; iter < points_to_be_deleted; iter++) {

        auto min_index_iterator = point_indexer.begin();
        int64_t min_element = min_index_iterator->second;
        point_indexer.erase(min_index_iterator);

        auto iterator_point = points.find(min_element);
        auto iterator_point_minus1 = shiftIterator(iterator_point, -1);
        auto iterator_point_plus1 = shiftIterator(iterator_point, 1);

        points.erase(iterator_point);

        if (iterator_point_minus1->first > 0) {
            recomputeAreaNeighbor(iterator_point_minus1, point_indexer, points, scale);
        }

        if (iterator_point_plus1->first < counter - 1) {
            recomputeAreaNeighbor(iterator_point_plus1, point_indexer, points, scale);
        }
    }

    std::vector<Point> out_vector;
    out_vector.reserve(numPoints);
    std::transform(points.cbegin(), points.cend(), std::back_inserter(out_vector),
                   [](const std::pair<int64_t, VisvalingamSummaryPoint> &p) {
                       return Point{p.second.x, p.second.y};
                   });

    return out_vector;
}
af::array khiva::dimensionality::visvalingam(af::array pointList, int numPoints) {
    if (pointList.dims(1) != 2) {
        throw std::invalid_argument("Invalid dims. Khiva array with two columns expected (x axis and y axis).");
    }
    std::vector<Point> points;
    points.reserve(pointList.dims(0));
    auto x = khiva::utils::makeScopedHostPtr(pointList.col(0).host<float>());
    auto y = khiva::utils::makeScopedHostPtr(pointList.col(1).host<float>());

    for (int i = 0; i < pointList.dims(0); i++) {
        points.emplace_back(x[i], y[i]);
    }

    std::vector<Point> rPoints = visvalingam(points, numPoints);
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
