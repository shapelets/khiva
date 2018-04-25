// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <vector>

namespace tsa {

namespace dimensionality {

/**
 * @brief Definition of Point structure to represent 2D points.
 */
typedef std::pair<float, float> Point;

/**
 * @brief Reduces a set of points by applying the RamerDouglasPeucker method depending on the perpendicular
 * distance of the points and epsilon, the greater epsilon, more points are deleted.
 *
 * @param pointList Set of input points.
 *
 * @param epsilon It acts as the threshold value to decide which points should be considered meaningful or not.
 *
 * @return std:vector<tsa::dimensionality::Point> Array with the same dimensions the selected points.
 */
std::vector<Point> ramerDouglasPeucker(std::vector<Point> pointList, double epsilon);

/**
 * @brief Reduces a set of points by applying the visvalingam method (minimun triangle area) until the number
 * of points is reduced to numPoints.
 *
 * @param pointList Expects an input vector of points.
 *
 * @param numPoints Sets the number of points returned after the execution of the method.
 *
 * @return std:vector<tsa::dimensionality::Point> where the number of points has been reduced to numPoints.
 */
std::vector<Point> visvalingam(std::vector<Point> pointList, int numPoints);

/**
 * @brief Piecewise Aggregate Approximation. It reduces the dimensionality of the time series given by begin and
 * last iterators to a number equal to bins. This algorithim divides the whole timeseries in bins partitions and
 * computes the average of each partition.
 *
 * @param a Set of points.
 *
 * @param bins Sets the total number of divisions.
 *
 * @return result A vector with the reduced dimensionality.
 */
af::array PAA(af::array a, int bins);

/**
 * @brief Piecewise Aggregate Approximation. It reduces the dimensionality of the time series given by begin and last
 * iterators to a number equal to bins. This algorithim divides the whole timeseries in bins partitions and computes
 * the average of each partition.
 *
 * @param begin Iterator to the first element.
 *
 * @param last Iterator to the last element.
 *
 * @param bins Sets the total number of divisions.
 *
 * @return result A vector with the reduced dimensionality.
 */
template <class InputIt>
std::vector<Point> PAA_CPU(InputIt begin, InputIt last, int bins) {
    double xrange = (*(last - 1)).first - (*begin).first;
    double width_bin = xrange / bins;
    double reduction = bins / xrange;

    std::vector<double> sum(bins, 0.0);
    std::vector<int> counter(bins, 0);
    std::vector<Point> result(bins, Point(0.0, 0.0));

    // Iterating over the  timeseries
    for (auto i = begin; i != last; i++) {
        int pos = std::min((*i).first * reduction, (double)(bins - 1));
        sum[pos] += (*i).second;
        counter[pos] = counter[pos] + 1;
    }

    // Compute the average per bin
    for (int i = 0; i < bins; i++) {
        result[i].first = (width_bin * i) + (width_bin / 2.0);
        result[i].second = sum[i] / counter[i];
    }
    return result;
}

/**
 * @brief Symbolic Aggregate approXimation. It transforms a numeric time series into a time series of symbols with
 * the same size.
 *
 * @param a Array with the input time series.
 *
 * @param alphabet_size Number of element within the alphabet.
 *
 * @return result An array of symbols.
 */
std::vector<int> SAX(af::array a, int alphabet_size);

/**
 * @brief Calculates the number of Perceptually Important Points in the time series.
 * Fu TC, Chung FL, Luk R, and Ng CM (2008) Representing financial time series based on data point
 * importance. Engineering Applications of Artificial Intelligence, 21(2):277-300.
 *
 * @param ts Expects an input array whose dimension zero is the length of the time series.
 *
 * @param numberIPs The number of points to be returned.
 *
 * @return af::array Array with the numPoints most Perceptually Important.
 */
af::array PIP(af::array ts, int numberIPs);

// PLA
// Principal Components A.
// Random Projections
};  // namespace dimensionality
};  // namespace tsa