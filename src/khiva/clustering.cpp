// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#include <arrayfire.h>
#include <khiva/clustering.h>
#include <khiva/distances.h>
#include <khiva/normalization.h>
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
af::array calculateInitialMeans(af::array tss, int k) {
    af::array indices = (af::randu(k, 1) * k).as(af::dtype::u32);
    return af::lookup(tss, indices, 1);
}

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
 * Compute the new means for the i-th iteration.
 *
 * @param tss       The time series.
 * @param labels    The ids for each time series which indicates the closest mean.
 * @param k         Number of means.
 * @return          The new means.
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
 * Computes the means' difference between two iterations.
 *
 * @param means     The last iteration means
 * @param newMeans  The newMeans
 * @return          The accumulated change ratio between iterations.
 */
float computeError(af::array means, af::array newMeans) {
    float *error = af::sum(af::sqrt(af::sum(af::pow(means - newMeans, 2), 0))).as(af::dtype::f32).host<float>();
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
