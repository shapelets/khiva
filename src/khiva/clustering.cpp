// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#include <arrayfire.h>
#include <khiva/clustering.h>
#include <khiva/distances.h>
#include <khiva/normalization.h>
#include <Eigen/Eigenvalues>
#include <limits>
#include <iostream>

/**
 * Computes The euclidean distance for a tiled time series agains k-means.
 * @param tts The tiled time series.
 * @param means.
 * @return The distance from a time series to all k-means.
 */
af::array kEuclideanDistance(af::array tts, af::array means) {
    return af::reorder(af::sqrt(af::sum(af::pow((tts - means), 2), 0)), 1, 0);
}

/***
 * Computes the euclidean distance of each time series w.r.t. all k-means.
 * @param tss The time series.
 * @param means The k-means.
 * @param minDistance The resulting distance for each time series to all k-means.
 * @param labels The ids of the closes mean for all time series.
 */
void euclideanDistance(af::array tss, af::array means, af::array &minDistance, af::array &idxs) {
    int nseries = tss.dims(1);
    af::array kDistances = af::constant(0.0, means.dims(1), nseries);

    // This for loop could be parallel, not parallelized to keep low memory footprint
    for (int i = 0; i < nseries; i++) {
        af::array tiledSerie = af::tile(tss.col(i), 1, means.dims(1));
        kDistances(af::span, i) = kEuclideanDistance(tiledSerie, means);
    }
    af::min(minDistance, idxs, kDistances, 0);
}

/**
 * Computes the initial means. Randomly selected.
 * @param tss The time series.
 * @param k Number of means.
 * @return The initial k randomly calculated means.
 */
af::array calculateInitialMeans(af::array tss, int k) {
    // Note idxs may have repeated values
    af::array idxs = (af::randu(k) * tss.dims(1)).as(af::dtype::s32);
    return af::lookup(tss, idxs, 1);
}

/**
 * Compute the new means for the i-th iteration.
 * @param tss The time series.
 * @param labels The ids for each time series which indicates the closest mean.
 * @param k.
 * @return The new means.
 */
af::array computeNewMeans(af::array tss, af::array labels, int k) {
    af::array labelsTiled = af::tile(labels, tss.dims(0));
    af::array newMeans = af::constant(0.0, tss.dims(0), k);

    gfor(af::seq ii, k) {
        newMeans(af::span, ii) = af::sum(tss * (labelsTiled == ii), 1) / (af::sum(af::sum((labels == ii), 3), 1));
    }
    return newMeans;
}

/**
 * Computes the means' difference between two iterations.
 * @param means the last iteration means
 * @param newMeans the newMeans
 * @return the accumulated change ratio between iterations.
 */
float computeError(af::array means, af::array newMeans) {
    float *error = af::sum(af::sqrt(af::sum(af::pow(means - newMeans, 2), 0))).as(af::dtype::f32).host<float>();
    return error[0];
}

void khiva::clustering::kmeans(af::array tss, int k, af::array &centroids, af::array &labels, float tolerance,
        int maxIterations) {
    float error = std::numeric_limits<float>::max();

    // initial guess of means, select k random time series
    centroids = calculateInitialMeans(tss, k);

    labels = af::constant(0, tss.dims(1));
    af::array distances = af::constant(0.0, tss.dims(1));
    af::array newMeans;
    int iter = 0;

    // Stop updating after convergence is reached.
    while ((error > tolerance) && (iter < maxIterations)) {
        // 1. Compute distances to current means
        euclideanDistance(tss, centroids, distances, labels);

        // 2. Compute new means
        newMeans = computeNewMeans(tss, labels, k);

        // 3. Compute convergence
        error = computeError(centroids, newMeans);

        // 4. Update Means
        centroids = newMeans;
        iter++;
    }
}

af::array matrixNorm(af::array x, int axis = 0)
{ // for 2 dimensional matrix
    // int _axis = (axis+1)%2;
    if (axis == 0)
    {
        return af::sqrt(af::sum(af::pow(x, 2)));
    }
    else
    {
        return af::sqrt(af::sum(af::pow(x, 2), 1));
    }
}

/**
 * 'x'.: 2D Array containing the input data
 * 'y'.: 1D Array usually containing the centroid
 *  Every signal is supposed to have been znormlized beforehand
 *  Returns a single arrayFire where the first column represents the distance
 *  and the second column, the indexes for the minimum distance
 */
void ncc2Dim(af::array x, af::array y, af::array &correlation, af::array &maxIndex)
{
    af::array den = af::matmul(matrixNorm(x, 0).T(), matrixNorm(y, 0));
    af::array conv = af::constant(0, 2 * x.dims(0) - 1, x.dims(1));

    for (unsigned int i = 0; i < static_cast<unsigned int>(x.dims(1)); i++)
    { // TODO gfor en vez de for
        conv.col(i) = af::convolve(x.col(i), af::flip(y, 0), AF_CONV_EXPAND) / (den(i).scalar<float>());
    }
    conv = af::flip(conv, 0);
    af::max(correlation, maxIndex, conv, 0);
}

/**
 * 'x'........: signals compared against 'y'
 * 'y'........: reference signal
 * 'distance'.: output argument containing the distance between signals
 * 'xShifted'.: 'x' signal shifted in order to obtain minimal distance
 */
void sbdPrivate(af::array x, af::array y, af::array &distance, af::array &xShifted)
{
    af::array correlation;
    af::array index;

    xShifted = af::constant(0, x.dims(), x.type());
    ncc2Dim(x, y, correlation, index);

    distance = 1 - correlation;

    af::array shift = index - x.dims(0) + 1;
    float xLength = static_cast<float>(x.dims(0));
    for (int i = 0; i < static_cast<int>(x.dims(1)); i++)
    {
        if (shift(i).scalar<int>() >= 0)
        {
            xShifted.col(i) =
                    af::join(0, af::constant(0, shift(i).scalar<int>()), x(af::range(xLength - shift(i).scalar<int>()), 0));
        }
        else
        {
            xShifted.col(i) = af::join(0, x(af::range(xLength + shift(i).scalar<int>()) - shift(i).scalar<int>(), 0),
                                       af::constant(0, -shift(i).scalar<int>()));
        }
    }
}

/**
 * 'x'.: stands for the input data 2D array
 * 'y'.: will usually be used as the centroids' array
 */
af::array ncc3Dim(af::array x, af::array y)
{
    af::array den = af::matmul(matrixNorm(y, 0).T(), matrixNorm(x, 0)); // combination of every pair of norms
    den(den == 0) = af::Inf;
    int distanceSize = static_cast<unsigned int>(y.dims(0)) * 2 - 1;

    af::array cc =
            af::constant(0, static_cast<unsigned int>(y.dims(1)), static_cast<unsigned int>(x.dims(1)), distanceSize);
    // TODO: el tamaño de la fft y el tamaño del resultado
    for (unsigned int i = 0; i < static_cast<unsigned int>(y.dims(1)); i++)
    {
        for (unsigned int j = 0; j < static_cast<unsigned int>(x.dims(1)); j++)
            cc(i, j, af::span) = af::convolve(x.col(j), af::flip(y.col(i), 0), AF_CONV_EXPAND);
    }
    den = af::tile(den, 1, 1, distanceSize);

    return (cc / den);
}

af::array eigenVectors(af::array matrix)
{
    float *matHost = matrix.host<float>();
    Eigen::MatrixXf mat = Eigen::Map<Eigen::MatrixXf>(matHost, matrix.dims(0), matrix.dims(1));

    Eigen::EigenSolver<Eigen::MatrixXf> solution(mat);

    Eigen::MatrixXf re;
    re = solution.eigenvectors().real();

    return af::array(matrix.dims(0), matrix.dims(1), re.data());
}

af::array eigenValues(af::array matrix)
{
    float *matHost = matrix.host<float>();
    Eigen::MatrixXf mat = Eigen::Map<Eigen::MatrixXf>(matHost, matrix.dims(0), matrix.dims(1));

    Eigen::VectorXcf eivals = mat.eigenvalues();

    Eigen::VectorXf re = eivals.real();
    return af::array(matrix.dims(0), re.data());
}

af::array shapeExtraction(af::array tss, af::array centroid){

    af::array newCentroid;

    for(int i = 0; i < static_cast<int>(tss.dims(1); i ++)){

    }

    return newCentroid;
}


/**
 * 'idx'.............: 1D Array containing the centroid every signal is assigned to
 * 'x'...............: 2D Array containing the input data
 * 'j'...............: number of the iteration (centroid)
 * 'currentCentroid'.: 1D Array containing the centroid we want to recalculate
 */
af::array refinementStep(af::array idx, af::array x, af::array centroids)
{
    af::array xShifted;
    af::array result = af::constant(0.0, centroids.dims(), af::dtype::f32);
    af::array distance;

    // Lets compute each centroid
    for (int i = 0; i < static_cast<int>(centroids.dims(1)); i++) {

        // 1. Filling part
        std::cout << "Before filling step" << std::endl;
        af::array a;
        for (int j = 0; j < static_cast<int>(idx.dims(0)); j++) {
            if (idx(j).scalar<int>() == i) {
                if (af::allTrue(af::iszero(centroids.col(i))).scalar<char>()) {
                    xShifted = x.col(j);
                } else {
                    sbdPrivate(x.col(j), centroids.col(i), distance, xShifted);
                }
                a = af::join(1, a, xShifted);
            }
        }

        if (a.isempty()) {
            result.col(i) = af::constant(0, static_cast<unsigned int>(x.dims(0)));
            continue;
        }
        std::cout << "After filling step" << std::endl;

        // 2. Shape extraction part
        std::cout << "Before Shape Extraction step" << std::endl;

        int matrixSize = static_cast<unsigned int>(a.dims(0));
        af::array y = khiva::normalization::znorm(a);
        af::array S = af::matmul(y, y.T());

        af::array Q = af::constant(1.0 / matrixSize, matrixSize, matrixSize, x.type());
        af::array diagonal = af::constant(1, matrixSize, x.type());
        Q = af::diag(diagonal, 0, false) - Q;

        af::array M = af::matmul(af::matmul(Q, S), Q); // Q_T*S*Q. Q is a simmetric matrix
        af::array eigenvalues = eigenValues(M);
        af::array maxEigenValue;
        af::array indMaxEigenValue;
        af::max(maxEigenValue, indMaxEigenValue, eigenvalues, 0);
        result.col(i) = eigenVectors(M).col(indMaxEigenValue(0).scalar<int>()); // highest order eigenvector

        float findDistance1 = af::sqrt(af::sum(af::pow((a(af::span, 0) - result.col(i)), 2))).scalar<float>();
        float findDistance2 = af::sqrt(af::sum(af::pow((a(af::span, 0) + result.col(i)), 2))).scalar<float>();

        if (findDistance1 >= findDistance2)
            result.col(i) = khiva::normalization::znorm(result.col(i) * (-1));
        else
            result.col(i) = khiva::normalization::znorm(result.col(i));
    }
    std::cout << "After Shape Extraction step" << std::endl;

    return result;
}

//float computeError(af::array centroids, af::array newCentroids)
//{
//    //af_print(af::sum(af::sqrt(af::sum(af::pow(centroids - newCentroids, 2), 0))).as(af::dtype::f32));
//    float *error = af::sum(af::sqrt(af::sum(af::pow(centroids - newCentroids, 2), 0))).as(af::dtype::f32).host<float>();
//    return error[0];
//}

void khiva::clustering::kShape(af::array tss, int k, af::array &centroids, af::array &labels, float tolerance,
        int maxIterations) {
    unsigned int nTimeSeries = static_cast<unsigned int>(tss.dims(1));

    if (centroids.isempty()) {
        centroids = af::constant(0.0f, tss.dims(0), k);
    }

    if (labels.isempty()) {
        // assigns a random centroid to every time series
        labels = af::floor(af::randu(nTimeSeries) * (k)).as(af::dtype::s32);
    }

    af::array normalizedTss = khiva::normalization::znorm(tss);

    af::array oldLabels = labels;
    af::array minimums = af::constant(0, tss.dims(1)); // used to storage the minimum values

    af::array distances = af::constant(0, nTimeSeries, k);
    af::array newCentroids;

    float error = std::numeric_limits<float>::max();
    int iter = 0;

    // Stop updating after convergence is reached.
    while ((error > tolerance) && (iter < maxIterations)) {
        oldLabels = labels;

        // 1. Refinement step. New centroids computation.
        std::cout << "Before refinement step" << std::endl;
        newCentroids = refinementStep(labels, normalizedTss, centroids);
        std::cout << "After refinement step" << std::endl;


        // 3. Compute convergence
        error = computeError(centroids, newCentroids);

        distances = 1 - af::max(ncc3Dim(normalizedTss, newCentroids), 2);

        // 4. Update Centroids
        centroids = newCentroids;
        iter++;

        af::min(minimums, labels, distances, 0);
        labels = labels.T();
    }
}
