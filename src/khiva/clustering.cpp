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

    // This for loop could be parallel, not parallelized to keep memory footprint low
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

/**
 * Computes the 2-norm for each time series.
 *
 * @param tss Contains the time series.
 * @param axis this value sets if the normalization should be applied by columns (0) or rows (1).
 * @return Normalized time series.
 */
af::array matrixNorm(af::array tss, int axis = 0) {
    af::array res;

    if (axis == 0) {
         res = af::sqrt(af::sum(af::pow(tss, 2)));
    } else {
        res = af::sqrt(af::sum(af::pow(tss, 2), 1));
    }

    return res;
}

/**
 * This function returns a subset of time series from tss, where all time series belong to the group of the
 * centroid given by centroidId.
 * @param tss The set of time series in columnar mode.
 * @param labels The centroid's id where each time series belongs to.
 * @param centroidId the given centroid ID.
 * @return a subset of time series.
 */
af::array selectSubset(af::array tss, af::array labels, int centroidId){
    return af::lookup(tss, af::where((labels == centroidId)), 1);
}

/**
 * This function returns the first Eigenvector of tss.
 * @param tss The set of time series in columnar mode.
 * @return The first Eigenvector of tss.
 */
af::array getFirstEigenVector(af::array tss) {

    float *matHost = tss.host<float>();
    Eigen::MatrixXf mat = Eigen::Map<Eigen::MatrixXf>(matHost, tss.dims(0), tss.dims(1));

    Eigen::EigenSolver<Eigen::MatrixXf> solution(mat);
    Eigen::MatrixXf re = solution.eigenvectors().real().col(0);

    return af::array(tss.dims(0), re.data());
}

/**
 * This function computes the Normalized Crosscorrelation between ts and the reference centroid.
 * @param ts The time series.
 * @param centroid The reference centroid.
 * @return The normalized crosscorrelation.
 */
af::array ncc(af::array ts, af::array centroid){
    af::array tsNorm = af::sqrt(af::sum(af::pow(ts, 2), 0));
    af::array centroidNorm = af::sqrt(af::sum(af::pow(centroid, 2), 0));

    return af::convolve(centroidNorm, af::flip(tsNorm, 0), AF_CONV_EXPAND) / (centroidNorm * tsNorm);
}

/**
 * This function computes the Shape based distance.
 * @param ts The target time series.
 * @param centroid The centroid acting as reference.
 * @param shiftedTS The resulting shift over the original time series that gets the maximum correlation with centroid.
 * @param distance The distance to the best shift of the ts.
 */
void SBD(af::array ts, af::array centroid, af::array &shiftedTS, float &distance) {
    float * value;
    unsigned * index;

    af::array normCrossCorr = ncc(ts, centroid);
    af::max(value, index, normCrossCorr);

    distance = 1.0f - *value;
    std::cout << "Length ts in ncc: " << ts.dims(0) << std::endl;
    int end = ts.dims(0);
    int shift = *index - ts.dims(0);

    if (shift >= 0){
        shiftedTS = af::join(0, af::constant(0.0f, shift), ts(af::seq(1, end-shift)));

    }else{
        shift = - shift;
        shiftedTS = af::join(0, ts(af::seq(1 + shift, end)), af::constant(0.0f, shift + 1));
    }
    af_print(shiftedTS);
}

/**
 * This function returns an updated shape of the centroid passed as argument w.r.t. the tss that are passed
 * as arguments.
 * @param tss The subset of time series acting on the centroid.
 * @param centroid The given centroid.
 * @return The updated shape of the centroid.
 */
af::array shapeExtraction(af::array tss, af::array centroid) {
    int ntss = tss.dims(1);
    int nelements = tss.dims(0);
    af::array shiftedTSS;
    af::array shiftedTSi;
    float dist;

    for (int i = 0; i < ntss; i++) {
        SBD(tss.col(i), centroid, shiftedTSi, dist);
        shiftedTSS.col(i) = shiftedTSi;
    }

    af::array s = af::matmul(shiftedTSS.T(), shiftedTSS);
    af::array q = af::identity(nelements, nelements) - (af::constant(1.0, nelements, nelements) / nelements);
    af::array m = af::matmul(af::matmul(q.T(), s), q);
    return getFirstEigenVector(m);
}

/**
 * This function performs the refinement step.
 * @param tss The set of time series in columnar manner.
 * @param centroids The set of centroids in columnar mode.
 * @param labels The set of labels.
 * @return The new centroids.
 */
af::array refinementStep(af::array tss, af::array centroids, af::array labels){
    int ntss = tss.dims(1);
    int ncentroids = centroids.dims(1);
    af::array subset;

    for (int j = 0; j < ncentroids; j++) {
        for (int i = 0; i < ntss; i++) {
            subset = selectSubset(tss, labels, j);
        }
        centroids.col(j) = shapeExtraction(subset, centroids.col(j));
    }

    // TODO: Analyse if returning centroids via &centroids is better
    return centroids;
}

/**
 * This function computes the assignment step. It is the update of time series labels w.r.t. the dinamics of the
 * centroids.
 * @param tss The set of time series in columnar manner.
 * @param centroids The set of centroids in columnar mode.
 * @param labels The set of labels.
 * @return The new set of labels.
 */
af::array assignmentStep(af::array tss, af::array centroids, af::array labels){

    float dist = 0.0;
    float mindist = 0.0;
    af::array shiftedTS;
    af::array nlabels = labels;

    for (int i = 0; i < tss.dims(1); i++){
        mindist = std::numeric_limits<float>::max();
        // TODO: Probably this for loop can be executed in parallel
        for (int j = 0; j < centroids.dims(1); j++){
            SBD(tss.col(i), centroids.col(j), shiftedTS, dist);
            if (dist < mindist){
                mindist = dist;
                nlabels(i) = j;
            }
        }
    }
    return nlabels;
}

/**
 *  Computes the kShape algorithm, it return the computed centroids and the time series membership in labels vectors.
 * @param tss
 * @param k
 * @param centroids
 * @param labels
 * @param tolerance
 * @param maxIterations
 */
void khiva::clustering::kShape(af::array tss, int k, af::array &centroids, af::array &labels, float tolerance,
        int maxIterations) {
    unsigned int nTimeseries = static_cast<unsigned int>(tss.dims(1));
    unsigned int nElements = static_cast<unsigned int>(tss.dims(0));

    if (centroids.isempty()) {
        centroids = af::constant(0.0f, nElements, k);
    }

    if (labels.isempty()) {
        // assigns a random centroid to every time series
        labels = af::floor(af::randu(nTimeseries) * (k)).as(af::dtype::s32);
    }

    af::array normTSS = khiva::normalization::znorm(tss);
    af::array distances = af::constant(0, nTimeseries, k);
    af::array newCentroids;

    float error = std::numeric_limits<float>::max();
    int iter = 0;

    // Stop Criteria: Stop updating after convergence is reached.
    while ((error > tolerance) && (iter < maxIterations)) {

        // 1. Refinement step. New centroids computation.
        af_print(centroids);
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
