// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Piecewise Aggregate Approximation (PAA) approximates a time series \f$X\f$ of length \f$n\f$ into vector
 * \f$\bar{X}=(\bar{x}_{1},…,\bar{x}_{M})\f$ of any arbitrary length \f$M \leq n\f$ where each of \f$\bar{x_{i}}\f$ is
 * calculated as follows:
 * \f[
 * \bar{x}_{i} = \frac{M}{n} \sum_{j=n/M(i-1)+1}^{(n/M)i} x_{j}.
 * \f]
 * Which simply means that in order to reduce the dimensionality from \f$n\f$ to \f$M\f$, we first divide the original
 * time series into \f$M\f$ equally sized frames and secondly compute the mean values for each frame. The sequence
 * assembled from the mean values is the PAA approximation (i.e., transform) of the original time series.
 *
 * @param ref Set of points.
 * @param bins Sets the total number of divisions.
 *
 * @return The updated ref and an array of points with the reduced dimensionality.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Dimensionality_paa(JNIEnv *env, jobject, jlong ref, jint bins);

/**
 * @brief Calculates the number of Perceptually Important Points (PIP) in the time series.
 *
 * [1] Fu TC, Chung FL, Luk R, and Ng CM. Representing financial time series based on data point importance.
 * Engineering Applications of Artificial Intelligence, 21(2):277-300, 2008.
 *
 * @param ref Expects an input array whose dimension zero is the length of the time series.
 * @param numberIPs The number of points to be returned.
 *
 * @return The updated ref and an array with the most Perceptually Important numberIPs.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Dimensionality_pip(JNIEnv *env, jobject, jlong ref,
                                                                         jint numberIPs);

/**
 * @brief Applies the Piecewise Linear Approximation (PLA BottomUP) to the time series.
 *
 * [1] Zhu Y, Wu D, Li Sh (2007). A Piecewise Linear Representation Method of Time Series Based on Feature Points.
 * Knowledge-Based Intelligent Information and Engineering Systems 4693:1066-1072.
 *
 * @param ref Expects a reference to an array containing the set of points to be reduced. The first component of the
 * points in the first column and the second component of the points in the second column.
 * @param maxError The maximum approximation error allowed.
 *
 * @return The updated reference and a reference to an Array with the reduced number of points.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Dimensionality_PLABottomUp(JNIEnv *env, jobject, jlong ref,
                                                                                 jfloat maxError);

/**
 * @brief Applies the Piecewise Linear Approximation (PLA Sliding Window) to the time series.
 *
 * [1] Zhu Y, Wu D, Li Sh (2007). A Piecewise Linear Representation Method of Time Series Based on Feature Points.
 * Knowledge-Based Intelligent Information and Engineering Systems 4693:1066-1072.
 *
 * @param ref Expects a reference to an array containing the set of points to be reduced. The first component of the
 * points in the first column and the second component of the points in the second column.
 * @param maxError The maximum approximation error allowed.
 *
 * @return The updated reference and a reference to an Array with the reduced number of points.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Dimensionality_PLASlidingWindow(JNIEnv *env, jobject, jlong ref,
                                                                                      jfloat maxError);

/**
 * @brief The Ramer–Douglas–Peucker algorithm (RDP) is an algorithm for reducing the number of points in a curve that is
 * approximated by a series of points. It reduces a set of points depending on the perpendicular distance of the points
 * and epsilon, the greater epsilon, more points are deleted.
 *
 * [1] Urs Ramer, "An iterative procedure for the polygonal approximation of plane curves", Computer Graphics and Image
 * Processing, 1(3), 244–256 (1972) doi:10.1016/S0146-664X(72)80017-0.
 *
 * [2] David Douglas & Thomas Peucker, "Algorithms for the reduction of the number of points required to represent a
 * digitized line or its caricature", The Canadian Cartographer 10(2), 112–122 (1973) doi:10.3138/FM57-6770-U75U-7727
 *
 * @param ref Array with the x-coordinates and y-coordinates of the input points (x in column 0 and y in column 1).
 * @param epsilon It acts as the threshold value to decide which points should be considered meaningful or not.
 *
 * @return The updated ref and an array with the x-coordinates and y-coordinates of the selected points (x in column 0
 * and y in column 1).
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Dimensionality_ramerDouglasPeucker(JNIEnv *env, jobject,
                                                                                         jlong ref, jdouble epsilon);

/**
 * @brief Symbolic Aggregate approXimation (SAX). It transforms a numeric time series into a time series of symbols with
 * the same size. The algorithm was proposed by Lin et al.) and extends the PAA-based approach inheriting the original
 * algorithm simplicity and low computational complexity while providing satisfactory sensitivity and selectivity in
 * range query processing. Moreover, the use of a symbolic representation opened a door to the existing wealth of
 * data-structures and string-manipulation algorithms in computer science such as hashing, regular expression, pattern
 * matching, suffix trees, and grammatical inference.
 *
 * [1] Lin, J., Keogh, E., Lonardi, S. & Chiu, B. (2003) A Symbolic Representation of Time Series, with Implications for
 * Streaming Algorithms. In proceedings of the 8th ACM SIGMOD Workshop on Research Issues in Data Mining and Knowledge
 * Discovery. San Diego, CA. June 13.
 *
 * @param ref Array with the input time series.
 * @param alphabetSize Number of element within the alphabet.
 *
 * @return The updated ref and an array of symbols.
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Dimensionality_sax(JNIEnv *env, jobject, jlong ref,
                                                                         jint alphabetSize);

/**
 * @brief Reduces a set of points by applying the Visvalingam method (minimun triangle area) until the number
 * of points is reduced to numPoints.
 *
 * [1] M. Visvalingam and J. D. Whyatt, Line generalisation by repeated elimination of points,
 * The Cartographic Journal, 1993.
 *
 * @param ref Array with the x-coordinates and y-coordinates of the input points (x in column 0 and y in column 1).
 * @param numPoints Sets the number of points returned after the execution of the method.
 *
 * @return The updated ref and an array with the x-coordinates and y-coordinates of the selected points (x in column 0
 * and y in column 1).
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Dimensionality_visvalingam(JNIEnv *env, jobject, jlong ref,
                                                                                 jint numPoints);

#ifdef __cplusplus
}
#endif
