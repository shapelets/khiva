// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <vector>

using namespace af;

namespace tsa {

const char *version();

namespace simplification {

/**
 * @brief Definition of Point structure to represent 2D points
 */
typedef std::pair<float, float> Point;

/**
 * @brief Simplifies a set of points by applying the RamerDouglasPeucker method
 * depending on the perpendicular distance of the points and epsilon, the greater epsilon,
 * ore points are deleted.
 *
 * @param epsilon It acts as  the threshold value to decide which points should be considered
 * meaningful or not.
 *
 * @return array Array with the same dimensions as tss where the time series have been
 * adjusted for zero mean and one as standard deviation.
 */
std::vector<tsa::simplification::Point> ramerDouglasPeucker(std::vector<tsa::simplification::Point> pointList,
                                                            double epsilon);

/**
 * @brief Simplifies a set of points by applying the RamerDouglasPeucker method
 * depending on the perpendicular distance of the points and epsilon, the greater epsilon,
 * ore points are deleted.
 *
 * @param epsilon It acts as  the threshold value to decide which points should be considered
 * meaningful or not.
 *
 * @return array Array with the same dimensions as tss where the time series have been
 * adjusted for zero mean and one as standard deviation.
 */
af::array ramerDouglasPeucker(af::array pointList, double epsilon);

/**
 * @brief Simplifies a set of points by applying the visvalingam method (minimun triangle area)
 * until the number of points is reduced to @num_points_allowed.
 *
 * @param pointList Expects an input array whose dimension zero is the length of the time
 * series.
 *
 * @param numPoints Sets the number of points in pointList after the execution of the method.
 *
 * @return a vector with the same dimensions as poinList where the number of points has been
 * reduced up to numPoints.
 */
std::vector<tsa::simplification::Point> visvalingam_simplify(std::vector<tsa::simplification::Point> pointList,
                                                             int numPoints);

/**
 * @brief Simplifies a set of points by applying the visvalingam method (minimun triangle area)
 * until the number of points is reduced to @num_points_allowed.
 *
 * @param pointList Expects an input array whose dimension zero is the length of the time
 * series.
 *
 * @param numPoints Sets the number of points in pointList after the execution of the method.
 *
 * @return a vector with the same dimensions as poinList where the number of points has been
 * reduced up to numPoints.
 */
af::array visvalingam_simplify(af::array pointList, int numPoints);
};  // namespace simplification
};  // namespace tsa
