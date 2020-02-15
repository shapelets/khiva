// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#include <arrayfire.h>
#include <khiva/clustering.h>
#include <khiva/distances.h>
#include <khiva/normalization.h>
#include <khiva/internal/scopedHostPtr.h>
#include <Eigen/Eigenvalues>
#include <iostream>
#include <limits>

/**
 * Computes initial k means or centroids.
 *
 * @param tts       The time series.
 * @param k         The number of centroids.
 * @return          The new centroids.
 */
af::array calculateInitialMeans(af::array tss, int k) { return af::constant(0, tss.dims(0), k, tss.type()); }

/**
 * Computes The euclidean distance for a tiled time series agains k-means.
 *
 * @param tts       The tiled time series.
 * @param means     The centroids.
 * @return          The distance from a time series to all k-means.
 */
af::array kEuclideanDistance(af::array tts, af::array means) {
    return af::reorder(af::sqrt(af::sum(af::pow((tts - means), 2), 0)), 1, 0);
}

/***
 * Computes the euclidean distance of each time series w.r.t. all k-means.
 *
 * @param tss           The time series.
 * @param means         The k-means.
 * @param minDistance   The resulting distance for each time series to all k-means.
 * @param labels        The ids of the closes mean for all time series.
 */
void euclideanDistance(af::array tss, af::array means, af::array &minDistance, af::array &idxs) {
    int nSeries = tss.dims(1);
    af::array kDistances = af::constant(0.0, means.dims(1), nSeries, tss.type());

    // This for loop could be parallel, not parallelized to keep memory footprint low
    for (int i = 0; i < nSeries; i++) {
        af::array tiledSeries = af::tile(tss.col(i), 1, means.dims(1));
        kDistances(af::span, i) = kEuclideanDistance(tiledSeries, means);
    }
    af::min(minDistance, idxs, kDistances, 0);
}

/**
 * Compute the new means for the i-th iteration.
 *
 * @param tss       The time series.
 * @param labels    The ids for each time series which indicates the closest mean.
 * @param k         Number of means.
 * @return          The new means.
 */
af::array computeNewMeans(af::array tss, af::array labels, int k) {
    af::array labelsTiled = af::tile(labels, tss.dims(0));
    af::array newMeans = af::constant(0.0, tss.dims(0), k, tss.type());

    gfor(af::seq ii, k) {
        newMeans(af::span, ii) = af::sum(tss * (labelsTiled == ii), 1) / (af::sum(af::sum((labels == ii), 3), 1));
    }
    return newMeans;
}

/**
 *  This function generates random labels for n time series.
 *
 * @param nTimeSeries   Number of time series to be labeled.
 * @param k             The number of groups.
 * @return              The random labels.
 */
af::array generateRandomLabels(int nTimeSeries, int k) {
    std::vector<int> idx(nTimeSeries, 0);

    // Fill with sequential data
    for (int i = 0; i < nTimeSeries; i++) {
        idx[i] = i % k;
    }

    // Randomize
    std::random_shuffle(idx.begin(), idx.end());
    return af::array(nTimeSeries, 1, idx.data());
}

/**
 *  This function generates uniform labels for n time series.
 *
 * @param nTimeSeries   Number of time series to be labeled.
 * @param k             The number of groups.
 * @return              The random labels.
 */
af::array generateUniformLabels(int nTimeSeries, int k) {
    std::vector<int> idx(nTimeSeries, 0);

    // Fill with sequential data
    for (int i = 0; i < nTimeSeries; i++) {
        idx[i] = i % k;
    }

    return af::array(nTimeSeries, 1, idx.data());
}

/**
 * Computes the means' difference between two iterations.
 *
 * @param means     The last iteration means
 * @param newMeans  The newMeans
 * @return          The accumulated change ratio between iterations.
 */
float computeError(af::array means, af::array newMeans) {
    auto error = khiva::utils::makeScopedHostPtr(af::sum(af::sqrt(af::sum(af::pow(means - newMeans, 2), 0)))
                      .as(af::dtype::f32)
                      .host<float>());
    return error[0];
}

void khiva::clustering::kMeans(af::array tss, int k, af::array &centroids, af::array &labels, float tolerance,
                               int maxIterations) {
    float error = std::numeric_limits<float>::max();

    if (centroids.isempty()) {
        // initial guess of means, select k random time series
        centroids = calculateInitialMeans(tss, k);
    }

    if (labels.isempty()) {
        // assigns a random centroid to every time series
        labels = generateRandomLabels(tss.dims(1), k);
    }

    af::array distances = af::constant(0, tss.dims(1), tss.type());
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

/**
 * Computes the 2-norm for each time series.
 *
 * @param tss   Contains the time series.
 * @return      Normalized time series.
 */
af::array matrixNorm(af::array tss) { return af::sqrt(af::sum(af::pow(tss, 2))); }

/**
 * This function returns a subset of time series from tss, where all time series belong to the centroid's
 * given by centroidId.
 *
 * @param tss           The set of time series in columnar mode.
 * @param labels        The centroid id where each time series belongs to.
 * @param centroidId    The given centroid ID.
 * @return              A subset of time series.
 */
af::array selectSubset(af::array tss, af::array labels, int centroidId) {
    return af::lookup(tss, af::where((labels == centroidId)), 1);
}

af::array eigenVectors(af::array matrix) {
    auto matHost = khiva::utils::makeScopedHostPtr(matrix.host<float>());
    Eigen::MatrixXf mat = Eigen::Map<Eigen::MatrixXf>(matHost.get(), matrix.dims(0), matrix.dims(1));

    Eigen::EigenSolver<Eigen::MatrixXf> solution(mat);

    Eigen::MatrixXf re;
    re = solution.eigenvectors().real();
    return af::array(matrix.dims(0), matrix.dims(1), re.data());
}

af::array eigenValues(af::array matrix) {
    auto matHost = khiva::utils::makeScopedHostPtr(matrix.host<float>());
    Eigen::MatrixXf mat = Eigen::Map<Eigen::MatrixXf>(matHost.get(), matrix.dims(0), matrix.dims(1));

    Eigen::VectorXcf eivals = mat.eigenvalues();

    Eigen::VectorXf re = eivals.real();
    return af::array(matrix.dims(0), re.data());
}

/**
 * This function computes the first EigenVector of a matrix.
 *
 * @param m     The input matrix.
 * @return      The first Eigen vector.
 */
af::array getFirstEigenVector(af::array m) {
    af::array eigenValues;
    af::array eigenVectors;

    if (m.type() == af::dtype::f64) {
        auto matHost = khiva::utils::makeScopedHostPtr(m.host<double>());
        Eigen::MatrixXd mat = Eigen::Map<Eigen::MatrixXd>(matHost.get(), m.dims(0), m.dims(1));

        // Compute Eigen Values.
        Eigen::VectorXcd eivals = mat.eigenvalues();
        Eigen::VectorXd reEIVals = eivals.real();
        eigenValues = af::array(m.dims(0), reEIVals.data());

        // Compute Eigen Vectors.
        Eigen::EigenSolver<Eigen::MatrixXd> solution(mat);
        Eigen::MatrixXd reEIVectors = solution.eigenvectors().real();
        eigenVectors = af::array(m.dims(0), m.dims(1), reEIVectors.data());
    } else if (m.type() == af::dtype::f32) {
        auto matHost = khiva::utils::makeScopedHostPtr(m.host<float>());
        Eigen::MatrixXf mat = Eigen::Map<Eigen::MatrixXf>(matHost.get(), m.dims(0), m.dims(1));

        // Compute Eigen Values.
        Eigen::VectorXcf eivals = mat.eigenvalues();
        Eigen::VectorXf reEIVals = eivals.real();
        eigenValues = af::array(m.dims(0), reEIVals.data());

        // Compute Eigen Vectors.
        Eigen::EigenSolver<Eigen::MatrixXf> solution(mat);
        Eigen::MatrixXf reEIVectors = solution.eigenvectors().real();
        eigenVectors = af::array(m.dims(0), m.dims(1), reEIVectors.data());
    }

    // Get maximum Eigen Value
    af::array maxEigenValue;
    af::array indMaxEigenValue;
    af::max(maxEigenValue, indMaxEigenValue, eigenValues, 0);

    // Extract first EigenVector
    return af::lookup(eigenVectors, indMaxEigenValue, 1);
}

/**
 * This function computes the Normalized Crosscorrelation between ts and the reference centroid.
 *
 * @param ts        The time series.
 * @param centroid  The reference centroid.
 * @return          The normalized crosscorrelation.
 */
af::array ncc(af::array ts, af::array centroid) {
    int nElements = ts.dims(0);

    af::array tsNorm = af::sqrt(af::sum(af::pow(ts, 2)));
    af::array centroidNorm = af::sqrt(af::sum(af::pow(centroid, 2)));

    return af::convolve(centroid, af::flip(ts, 0), AF_CONV_EXPAND) / af::tile(centroidNorm * tsNorm, nElements * 2 - 1);
}

/**
 * Computes the normalized crosscorrelation for all time series and all centroids.
 *
 * @param tss       The set of time series.
 * @param centroids The set of centroids.
 * @return          The computed normalized CrossCorrelation.
 */
af::array ncc3Dim(af::array tss, af::array centroids) {
    // Combination of all pairs of norms
    af::array den = af::matmul(matrixNorm(centroids).T(), matrixNorm(tss));
    den(den == 0) = af::Inf;
    int distanceSize = static_cast<unsigned int>(centroids.dims(0)) * 2 - 1;

    af::array cc = af::constant(0, static_cast<unsigned int>(centroids.dims(1)), static_cast<unsigned int>(tss.dims(1)),
                                distanceSize, tss.type());
    for (unsigned int i = 0; i < static_cast<unsigned int>(centroids.dims(1)); i++) {
        for (unsigned int j = 0; j < static_cast<unsigned int>(tss.dims(1)); j++) {
            cc(i, j, af::span) = af::convolve(tss.col(j), af::flip(centroids.col(i), 0), AF_CONV_EXPAND);
        }
    }

    den = af::tile(den, 1, 1, distanceSize);
    return (cc / den);
}

/**
 * This function computes the Shape based distance.
 *
 * @param ts            The target time series.
 * @param centroid      The centroid acting as reference.
 * @return              The resulting shift over the original time series that gets the maximum correlation with
 * centroid.
 */
af::array SBDShifted(af::array ts, af::array centroid) {
    unsigned int index;
    float correlation;
    af::array shiftedTS;
    af::array normCrossCorr = ncc(ts, centroid);
    af::max(&correlation, &index, normCrossCorr);

    unsigned tsLength = static_cast<float>(ts.dims(0));
    int shift = index - tsLength + 1;

    if (shift >= 0) {
        shiftedTS = af::join(0, af::constant(0, shift, ts.type()), ts(af::range(tsLength - shift), 0));
    } else {
        shiftedTS = af::join(0, ts(af::range(tsLength + shift) - shift, 0), af::constant(0, -shift, ts.type()));
    }

    return shiftedTS;
}

/**
 * This function returns an updated shape of the centroid passed as argument w.r.t. the tss.
 *
 * @param tss       The subset of time series acting on the centroid.
 * @param centroid  The given centroid.
 * @return          The updated shape of the centroid.
 */
af::array shapeExtraction(af::array tss, af::array centroid) {
    int ntss = tss.dims(1);
    int nelements = tss.dims(0);
    af::array shiftedTSS = af::constant(0, tss.dims(0), tss.dims(1), tss.type());
    af::array shiftedTSi = af::constant(0, tss.dims(0), 1, tss.type());
    af::array dist;

    for (int i = 0; i < ntss; i++) {
        af::array condition = af::tile(af::allTrue(af::iszero(centroid)), nelements, 1);
        shiftedTSi = af::select(condition, tss.col(i), SBDShifted(tss.col(i), centroid));
        shiftedTSS(af::span, i) = shiftedTSi;
    }

    shiftedTSS = khiva::normalization::znorm(shiftedTSS);
    af::array s = af::matmul(shiftedTSS, shiftedTSS.T());
    af::array q =
        af::identity(nelements, nelements) - (af::constant(1.0, nelements, nelements, tss.type()) / nelements);
    af::array m = af::matmul(q.T(), s, q);

    af::array first = getFirstEigenVector(m);

    af::array findDistance1 = af::sqrt(af::sum(af::pow((shiftedTSS(af::span, 0) - first), 2)));
    af::array findDistance2 = af::sqrt(af::sum(af::pow((shiftedTSS(af::span, 0) + first), 2)));

    af::array condition = findDistance1 >= findDistance2;
    first = af::select(af::tile(condition, first.dims(0), 1), khiva::normalization::znorm(first * (-1)),
                       khiva::normalization::znorm(first));

    return first;
}

/**
 * This function performs the refinement step.
 *
 * @param tss       The set of time series in columnar manner.
 * @param centroids The set of centroids in columnar mode.
 * @param labels    The set of labels.
 * @return          The new centroids.
 */
af::array refinementStep(af::array tss, af::array centroids, af::array labels) {
    int ntss = tss.dims(1);
    int ncentroids = centroids.dims(1);
    af::array subset;

    for (int j = 0; j < ncentroids; j++) {
        subset = selectSubset(tss, labels, j);
        // if centroid j has at least one labeled time series.
        if (!subset.isempty()) {
            centroids(af::span, j) = shapeExtraction(subset, centroids.col(j));
        }
    }

    return centroids;
}

/**
 * This function computes the assignment step. It is the update of time series labels w.r.t. the dinamics of the
 * centroids.
 *
 * @param tss       The set of time series in columnar manner.
 * @param centroids The set of centroids in columnar mode.
 * @param labels    The set of labels.
 * @return          The new set of labels.
 */
af::array assignmentStep(af::array tss, af::array centroids, af::array labels) {
    af::array min = af::constant(std::numeric_limits<float>::max(), tss.dims(1), tss.type());
    af::array distances = 1 - af::max(ncc3Dim(tss, centroids), 2);
    af::min(min, labels, distances, 0);
    labels = labels.T();

    return labels;
}

void khiva::clustering::kShape(af::array tss, int k, af::array &centroids, af::array &labels, float tolerance,
                               int maxIterations) {
    unsigned int nTimeseries = static_cast<unsigned int>(tss.dims(1));
    unsigned int nElements = static_cast<unsigned int>(tss.dims(0));

    if (centroids.isempty()) {
        centroids = af::constant(0, nElements, k, tss.type());
    }

    if (labels.isempty()) {
        labels = generateUniformLabels(nTimeseries, k);
    }

    af::array normTSS = khiva::normalization::znorm(tss);
    af::array distances = af::constant(0, nTimeseries, k, tss.type());
    af::array newCentroids;

    float error = std::numeric_limits<float>::max();
    int iter = 0;

    // Stop Criteria: Stop updating after convergence or maximum number iterations is reached.
    while ((error > tolerance) && (iter < maxIterations)) {
        // 1. Refinement step. New centroids computation.
        newCentroids = refinementStep(normTSS, centroids, labels);

        // 2. Assignment step. New labels computation.
        labels = assignmentStep(normTSS, newCentroids, labels);

        // 3. Compute convergence
        error = computeError(centroids, newCentroids);

        // 4. Update Centroids
        centroids = newCentroids;

        iter++;
    }
}
