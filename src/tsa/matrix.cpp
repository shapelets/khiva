// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa/matrix.h>
#include <tsa/normalization.h>
#include <limits>

#define BATCH_SIZE 2048
#define EPSILON 1e-8

af::array tsa::matrix::slidingDotProduct(af::array q, af::array t) {
    long n = t.dims(0);
    long m = q.dims(0);

    af::array qr = af::flip(q, 0);

    af::array qt = af::real(af::convolve(t, qr, AF_CONV_EXPAND));

    return qt(af::seq(m - 1, n - 1), span, span, span);
}

void tsa::matrix::meanStdev(af::array t, af::array &a, long m, af::array &mean, af::array &stdev) {
    long na = t.dims(0);

    af::array cumulative_sum_t = af::accum(t, 0);
    af::array cumulative_sum_t2 = af::accum(af::pow(t, 2), 0);
    af::array sum_t = af::constant(0, na - m + 1, t.dims(1), t.type());
    af::array sum_t2 = af::constant(0, na - m + 1, t.dims(1), t.type());

    af::array tmp = af::constant(0, 1, t.dims(1), t.type());

    sum_t = cumulative_sum_t(af::seq(m - 1, na - 1), span) -
            af::join(0, tmp, cumulative_sum_t(af::seq(0, na - m - 1), span));
    sum_t2 = cumulative_sum_t2(af::seq(m - 1, na - 1), span) -
             af::join(0, tmp, cumulative_sum_t2(af::seq(0, na - m - 1), span));

    mean = sum_t / m;
    array mean_t2 = sum_t2 / m;
    array mean_t_p2 = af::pow(mean, 2);
    array sigma_t2 = mean_t2 - mean_t_p2;
    stdev = af::sqrt(sigma_t2);

    a = (sum_t2 - 2 * sum_t * mean + m * mean_t_p2) /
        af::max(sigma_t2, af::constant(EPSILON, sigma_t2.dims(), t.type()));
}

void tsa::matrix::meanStdev(af::array t, long m, af::array &mean, af::array &stdev) {
    long na = t.dims(0);

    af::array cumulative_sum_t = af::accum(t, 0);
    af::array cumulative_sum_t2 = af::accum(af::pow(t, 2), 0);
    af::array sum_t = af::constant(0, na - m + 1, t.dims(1), t.type());
    af::array sum_t2 = af::constant(0, na - m + 1, t.dims(1), t.type());

    af::array tmp = af::constant(0, 1, t.dims(1), t.type());

    sum_t = cumulative_sum_t(af::seq(m - 1, na - 1), span) -
            af::join(0, tmp, cumulative_sum_t(af::seq(0, na - m - 1), span));
    sum_t2 = cumulative_sum_t2(af::seq(m - 1, na - 1), span) -
             af::join(0, tmp, cumulative_sum_t2(af::seq(0, na - m - 1), span));

    mean = sum_t / m;
    array mean_t2 = sum_t2 / m;
    array mean_t_p2 = af::pow(mean, 2);
    array sigma_t2 = mean_t2 - mean_t_p2;
    stdev = af::sqrt(sigma_t2);
}

af::array tsa::matrix::generateMask(long m, long batchSize, long batchStart, long tsLength, long nTimeSeries) {
    long bandSize = std::ceil(m / 2.0);

    int tmp = batchStart > 0;
    af::array identity = af::identity(std::max(batchSize, bandSize) + 1, tsLength + bandSize - 1, nTimeSeries);
    af::array mask = af::convolve2(af::shift(identity, 0, batchStart - tmp, 0),
                                   af::constant(1, bandSize, bandSize, nTimeSeries)) > 0;
    mask = mask(af::seq(tmp, batchSize - 1 + tmp), af::seq(tsLength), span);

    return mask;
}

void tsa::matrix::calculateDistanceProfile(long m, af::array qt, af::array a, af::array sum_q, af::array sum_q2,
                                           af::array mean_t, af::array sigma_t, af::array mask, af::array &distance,
                                           af::array &index) {
    long batchSize = qt.dims(3);
    long tsLength = qt.dims(0);
    long nTimeSeries = qt.dims(1);
    af::array a_tiled = af::tile(a, 1, 1, 1, batchSize);
    af::array sum_q_tiled = af::tile(sum_q, tsLength, nTimeSeries);
    af::array sum_q2_tiled = af::tile(sum_q2, tsLength, nTimeSeries);
    af::array mean_t_tiled = af::tile(mean_t, 1, 1, 1, batchSize);
    af::array sigma_t_tiled = af::tile(sigma_t, 1, 1, 1, batchSize);

    af::array den = af::max(sigma_t_tiled, af::constant(EPSILON, sigma_t_tiled.dims(), qt.type()));
    af::array dist = a_tiled + (-2 * (qt - sum_q_tiled * mean_t_tiled) / den) + sum_q2_tiled;
    dist = af::sqrt(af::abs(dist));

    dist = af::reorder(dist, 3, 0, 1, 2);

    dist += 1 / EPSILON * mask.as(qt.type());

    dist = af::reorder(dist, 0, 2, 1, 3);

    af::min(distance, index, dist, 2);
}

void tsa::matrix::calculateDistanceProfile(long m, af::array qt, af::array a, af::array sum_q, af::array sum_q2,
                                           af::array mean_t, af::array sigma_t, af::array &distance, af::array &index) {
    long batchSize = qt.dims(3);
    long tsLength = qt.dims(0);
    long nTimeSeries = qt.dims(1);
    af::array a_tiled = af::tile(a, 1, 1, 1, batchSize);
    af::array sum_q_tiled = af::tile(sum_q, tsLength, nTimeSeries);
    af::array sum_q2_tiled = af::tile(sum_q2, tsLength, nTimeSeries);
    af::array mean_t_tiled = af::tile(mean_t, 1, 1, 1, batchSize);
    af::array sigma_t_tiled = af::tile(sigma_t, 1, 1, 1, batchSize);

    af::array den = af::max(sigma_t_tiled, af::constant(EPSILON, sigma_t_tiled.dims(), qt.type()));
    af::array dist = a_tiled + (-2 * (qt - sum_q_tiled * mean_t_tiled) / den) + sum_q2_tiled;
    dist = af::sqrt(af::abs(dist));

    dist = af::reorder(dist, 3, 1, 0, 2);

    af::min(distance, index, dist, 2);
}

void tsa::matrix::mass(af::array q, af::array t, long m, af::array a, af::array mean_t, af::array sigma_t,
                       af::array mask, af::array &distance, af::array &index) {
    q = tsa::normalization::znorm(q, EPSILON);

    af::array qt = tsa::matrix::slidingDotProduct(q, t);
    af::array sum_q = af::sum(q);
    af::array sum_q2 = af::sum(af::pow(q, 2));

    tsa::matrix::calculateDistanceProfile(m, qt, a, sum_q, sum_q2, mean_t, sigma_t, mask, distance, index);
}

void tsa::matrix::mass(af::array q, af::array t, long m, af::array a, af::array mean_t, af::array sigma_t,
                       af::array &distance, af::array &index) {
    q = tsa::normalization::znorm(q, EPSILON);

    af::array qt = tsa::matrix::slidingDotProduct(q, t);
    af::array sum_q = af::sum(q);
    af::array sum_q2 = af::sum(af::pow(q, 2));

    tsa::matrix::calculateDistanceProfile(m, qt, a, sum_q, sum_q2, mean_t, sigma_t, distance, index);
}

void stomp_batched(af::array ta, af::array tb, long m, long batch_size, af::array &profile, af::array &index) {
    long nb = tb.dims(0);

    af::array aux;
    af::array mean;
    af::array stdev;

    profile = af::array(0, ta.type());
    index = af::array(0, af::dtype::u32);

    tsa::matrix::meanStdev(ta, aux, m, mean, stdev);

    long chunkSize = std::min(nb - m + 1, batch_size);

    af::array input = af::array(m, chunkSize, tb.dims(1), tb.type());

    for (long i = 0; i < (nb - m + 1); i += chunkSize) {
        long iterationSize = std::min(chunkSize, nb - m - i + 1);

        if (iterationSize != chunkSize) {
            input = af::array(m, iterationSize, tb.dims(1), tb.type());
        }

        for (long j = 0; j < m; j++) {
            input(j, span, span, span) = af::reorder(tb(af::seq(i + j, i + j + iterationSize - 1), span), 2, 0, 1, 3);
        }

        gfor(af::seq idx, iterationSize) {
            af::array distance;
            af::array pidx;

            tsa::matrix::mass(input(span, idx, span, span), ta, m, aux, mean, stdev, distance, pidx);

            profile = join(0, profile, distance);
            index = join(0, index, pidx);
        }

        profile = af::reorder(profile, 0, 1, 3, 2);
        index = af::reorder(index, 0, 1, 3, 2);

        af::sync();
    }
}

void stomp_batched_two_levels(af::array ta, af::array tb, long m, long batch_size_b, long batch_size_a,
                              af::array &profile, af::array &index) {
    long nb = tb.dims(0);
    long na = ta.dims(0);
    long nTimeSeriesA = ta.dims(1);
    long nTimeSeriesB = tb.dims(1);

    profile = af::array(0, ta.type());
    index = af::array(0, af::dtype::u32);

    long chunkSizeB = std::min(nb - m + 1, batch_size_b);
    long chunkSizeA = std::min(na, batch_size_a);

    af::array input = af::array(m, chunkSizeB, nTimeSeriesB, tb.type());

    for (long i = 0; i < (nb - m + 1); i += chunkSizeB) {
        long iterationSizeB = std::min(chunkSizeB, nb - m - i + 1);

        if (iterationSizeB != chunkSizeB) {
            input = af::array(m, iterationSizeB, nTimeSeriesB, tb.type());
        }

        for (long j = 0; j < m; j++) {
            input(j, span, span, span) = af::reorder(tb(af::seq(i + j, i + j + iterationSizeB - 1), span), 2, 0, 1, 3);
        }

        af::array distance = af::array(0, ta.type());
        af::array pidx = af::array(0, af::dtype::u32);

        for (long k = 0; k < (na + m - 1); k += chunkSizeA) {
            long start = k / chunkSizeA * (chunkSizeA - m + 1);
            long iterationSizeA = std::min(chunkSizeA, na - start);
            long end = start + iterationSizeA - 1;
            af::array taChunk = ta(af::seq(start, end), span);
            af::array aux;
            af::array mean;
            af::array stdev;
            tsa::matrix::meanStdev(taChunk, aux, m, mean, stdev);
            gfor(af::seq idx, iterationSizeB) {
                af::array distanceTmp;
                af::array pidxTmp;

                tsa::matrix::mass(input(span, idx, span, span), taChunk, m, aux, mean, stdev, distanceTmp, pidxTmp);

                distanceTmp = af::reorder(distanceTmp, 0, 2, 1, 3);
                pidxTmp = af::reorder(pidxTmp, 0, 2, 1, 3);

                pidxTmp += start;

                distance = af::join(1, distance, distanceTmp);
                pidx = af::join(1, pidx, pidxTmp);
            }
            af::sync();
        }

        af::array idx;
        af::array min;

        af::min(min, idx, distance, 1);

        min = af::reorder(min, 0, 2, 3, 1);
        idx = af::reorder(idx, 0, 2, 3, 1);

        af::array toSum = af::seq(0, (nTimeSeriesA * nTimeSeriesB - 1) * distance.dims(1), distance.dims(1));
        af::array aux = af::transpose(toSum).as(idx.type());
        aux = af::moddims(aux, 1, idx.dims(1), idx.dims(2), 1);
        aux = af::tile(aux, idx.dims(0));

        idx += aux;

        af::dim4 dims = min.dims();
        float sliceStride = dims[0];

        af::array bidx = af::tile(af::iota(af::dim4(dims[0])), 1, idx.dims(1), nTimeSeriesB);

        af::array flatIndices = af::flat(idx * sliceStride + bidx);

        af::array flatPidx = af::flat(pidx);
        af::array vFromPidx = flatPidx(flatIndices);

        profile = af::join(0, profile, min);
        index = af::join(0, index, af::moddims(vFromPidx, af::dim4(dims[0], dims[1], dims[2], 1)));
    }
}

void stomp_parallel(af::array ta, af::array tb, long m, af::array &profile, af::array &index) {
    long nb = tb.dims(0);

    af::array aux;
    af::array mean;
    af::array stdev;

    tsa::matrix::meanStdev(ta, aux, m, mean, stdev);

    af::array input = af::array(m, nb - m + 1, tb.dims(1), tb.type());

    for (int i = 0; i < m; i++) {
        input(i, span, span, span) = af::reorder(tb(af::seq(i, nb - m + i), span), 2, 0, 1, 3);
    }

    gfor(af::seq idx, nb - m + 1) {
        tsa::matrix::mass(input(span, idx, span, span), ta, m, aux, mean, stdev, profile, index);
    }

    profile = af::reorder(profile, 0, 1, 3, 2);
    index = af::reorder(index, 0, 1, 3, 2);

    af::sync();
}

void tsa::matrix::stomp(af::array ta, af::array tb, long m, af::array &profile, af::array &index) {
    if (tb.dims(0) > BATCH_SIZE) {
        if (ta.dims(0) > BATCH_SIZE) {
            return stomp_batched_two_levels(ta, tb, m, BATCH_SIZE, BATCH_SIZE, profile, index);
        } else {
            return stomp_batched(ta, tb, m, BATCH_SIZE, profile, index);
        }
    } else {
        return stomp_parallel(ta, tb, m, profile, index);
    }
}

void stomp_batched_two_levels(af::array t, long m, long batch_size_b, long batch_size_a, af::array &profile,
                              af::array &index) {
    long n = t.dims(0);
    long nTimeSeries = t.dims(1);

    profile = af::array(0, t.type());
    index = af::array(0, af::dtype::u32);

    long chunkSizeB = std::min(n - m + 1, batch_size_b);
    long chunkSizeA = std::min(n, batch_size_a);

    af::array input = af::array(m, chunkSizeB, nTimeSeries, t.type());

    for (long i = 0; i < (n - m + 1); i += chunkSizeB) {
        long iterationSizeB = std::min(chunkSizeB, n - m - i + 1);

        if (iterationSizeB != chunkSizeB) {
            input = af::array(m, iterationSizeB, nTimeSeries, t.type());
        }

        for (long j = 0; j < m; j++) {
            input(j, span, span, span) = af::reorder(t(af::seq(i + j, i + j + iterationSizeB - 1), span), 2, 0, 1, 3);
        }

        af::array distance = af::array(0, t.type());
        af::array pidx = af::array(0, af::dtype::u32);

        af::array mask = tsa::matrix::generateMask(m, iterationSizeB, i, n - m + 1, nTimeSeries);

        for (long k = 0; k < (n + m - 1); k += chunkSizeA) {
            long start = k / chunkSizeA * (chunkSizeA - m + 1);
            long iterationSizeA = std::min(chunkSizeA, n - start);
            long end = start + iterationSizeA - 1;
            af::array tChunk = t(seq(start, end), span);
            af::array aux;
            af::array mean;
            af::array stdev;
            tsa::matrix::meanStdev(tChunk, aux, m, mean, stdev);

            gfor(af::seq idx, iterationSizeB) {
                af::array distanceTmp;
                af::array pidxTmp;

                tsa::matrix::mass(input(span, idx, span, span), tChunk, m, aux, mean, stdev,
                                  mask(span, af::seq(start, start + iterationSizeA - m), span), distanceTmp, pidxTmp);

                distanceTmp = af::reorder(af::diag(af::reorder(distanceTmp, 3, 1, 0, 2)), 2, 1, 0, 3);
                pidxTmp = af::reorder(af::diag(af::reorder(pidxTmp, 3, 1, 0, 2)), 2, 1, 0, 3);

                pidxTmp += start;

                distance = af::join(1, distance, distanceTmp);

                pidx = af::join(1, pidx, pidxTmp);
            }
            af::sync();
        }

        af::array idx;
        af::array min;

        af::min(min, idx, distance, 1);

        min = af::reorder(min, 0, 2, 1, 3);
        idx = af::reorder(idx, 0, 2, 1, 3);

        af::array toSum = af::seq(0, (nTimeSeries - 1) * distance.dims(1), distance.dims(1));
        af::array aux = af::transpose(toSum).as(idx.type());
        aux = af::tile(aux, idx.dims(0));

        idx += aux;

        af::dim4 dims = min.dims();
        float sliceStride = dims[0];

        af::array bidx = af::tile(af::iota(af::dim4(dims[0])), 1, nTimeSeries);

        af::array flatIndices = af::flat(idx * sliceStride + bidx);

        af::array flatPidx = af::flat(pidx);
        af::array vFromPidx = flatPidx(flatIndices);

        profile = af::join(0, profile, min);
        index = af::join(0, index, af::moddims(vFromPidx, af::dim4(dims[0], dims[1])));
    }
}

void stomp_parallel(af::array t, long m, af::array &profile, af::array &index) {
    long n = t.dims(0);
    long nTimeSeries = t.dims(1);

    af::array aux;
    af::array mean;
    af::array stdev;

    tsa::matrix::meanStdev(t, aux, m, mean, stdev);

    af::array input = af::array(m, n - m + 1, nTimeSeries, t.type());

    for (int i = 0; i < m; i++) {
        input(i, span, span, span) = af::reorder(t(af::seq(i, n - m + i), span), 2, 0, 1, 3);
    }

    af::array mask = tsa::matrix::generateMask(m, n - m + 1, 0, n - m + 1, nTimeSeries);

    gfor(af::seq idx, n - m + 1) {
        tsa::matrix::mass(input(span, idx, span, span), t, m, aux, mean, stdev, mask, profile, index);
    }

    profile = af::reorder(af::diag(af::reorder(profile, 1, 3, 0, 2)), 2, 0, 1, 3);
    index = af::reorder(af::diag(af::reorder(index, 1, 3, 0, 2)), 2, 0, 1, 3);

    af::sync();
}

void tsa::matrix::stomp(array t, long m, af::array &profile, af::array &index) {
    if (t.dims(0) > BATCH_SIZE) {
        return stomp_batched_two_levels(t, m, BATCH_SIZE, BATCH_SIZE, profile, index);
    } else {
        return stomp_parallel(t, m, profile, index);
    }
}

void tsa::matrix::findBestNMotifs(af::array profile, af::array index, long n, af::array &motifs,
                                  af::array &motifsIndices, af::array &subsequenceIndices) {
    af::array profileTiled = af::tile(profile, 1, 2);
    af::array joined = af::join(1, index, af::range(index.dims(0), 1, 1, 1, -1, index.type()));
    af::array sortedDistances;
    af::array sortedIndices;
    af::sort(sortedDistances, sortedIndices, profileTiled, joined, 0, true);
    af::array bestNIndices = sortedIndices(af::seq(n), span);
    motifs = sortedDistances(af::seq(n));
    motifsIndices = bestNIndices.col(0);
    subsequenceIndices = bestNIndices.col(1);
}

void tsa::matrix::findBestNDiscords(af::array profile, af::array index, long n, af::array &discords,
                                    af::array &discordsIndices, af::array &subsequenceIndices) {
    af::array profileTiled = af::tile(profile, 1, 2);
    af::array joined = af::join(1, index, af::range(index.dims(0), 1, 1, 1, -1, index.type()));
    af::array sortedDistances;
    af::array sortedIndices;
    af::sort(sortedDistances, sortedIndices, profileTiled, joined, 0, false);
    af::array bestNIndices = sortedIndices(af::seq(n), span);
    discords = sortedDistances(af::seq(n));
    discordsIndices = bestNIndices.col(0);
    subsequenceIndices = bestNIndices.col(1);
}