// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/clustering.h>
#include <limits>

/**
 * Computes The euclidean distance fot a tiled time series agains k-means.
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
 * Compute the new means for the ith iteration.
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

void khiva::clustering::kmeans(af::array tss, int k, af::array &means, af::array &labels) {
    float tolerance = 10e-10;
    float error = std::numeric_limits<float>::max();

    // initial guess of means, select k random time series
    means = calculateInitialMeans(tss, k);

    labels = af::constant(0, tss.dims(1));
    af::array distances = af::constant(0.0, tss.dims(1));
    af::array newMeans;

    // Stop updating after convergence is reached.
    while (error > tolerance) {
        // 1. Compute distances to current means
        euclideanDistance(tss, means, distances, labels);

        // 2. Compute new means
        newMeans = computeNewMeans(tss, labels, k);

        // 3. Compute convergence
        error = computeError(means, newMeans);

        // 4. Update Means
        means = newMeans;
    }
}
