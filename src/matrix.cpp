// Copyright (c) 2018 Grumpy Cat Software S.L.
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa.h>
#include <limits>

#define BATCH_SIZE 2048
#define EPSILON 1e-8

af::array tsa::matrix::slidingDotProduct(af::array q, af::array t){
    long n = t.dims(0);
    long m = q.dims(0);

    af::array qr = af::flip(q, 0);

    af::array qt = af::real(af::convolve(t, qr, AF_CONV_EXPAND));

    return qt(af::seq(m - 1, n - 1), span, span, span);
}

void tsa::matrix::meanStdev(af::array t, af::array *a, long m, af::array *mean, af::array *stdev){
    long na = t.dims(0);

    af::array cumulative_sum_t = af::accum(t);
    af::array cumulative_sum_t2 = af::accum(af::pow(t, 2));
    af::array sum_t = af::constant(0, na - m + 1, t.type());
    af::array sum_t2 = af::constant(0, na - m + 1, t.type());

    double tmp[] = {0.0};

    sum_t = cumulative_sum_t(af::seq(m - 1, na - 1)) - join(0, af::array(1, tmp), cumulative_sum_t(af::seq(0, na - m - 1)));
    sum_t2 = cumulative_sum_t2(af::seq(m - 1, na - 1)) - join(0, af::array(1, tmp), cumulative_sum_t2(af::seq(0, na - m - 1)));

    *mean = sum_t / m;
    array mean_t2 = sum_t2 / m;
    array mean_t_p2 = af::pow(*mean, 2);
    array sigma_t2 = mean_t2 - mean_t_p2;
    *stdev = af::sqrt(sigma_t2);

    *a = (sum_t2 - 2 * sum_t * (*mean) + m * mean_t_p2) / af::max(sigma_t2, af::constant(EPSILON, sigma_t2.dims(), t.type()));
}

void tsa::matrix::meanStdev(af::array t, long m, af::array *mean, af::array *stdev){
    long na = t.dims(0);

    af::array cumulative_sum_t = af::accum(t);
    af::array cumulative_sum_t2 = af::accum(af::pow(t, 2));
    af::array sum_t = af::constant(0, na - m + 1, t.type());
    af::array sum_t2 = af::constant(0, na - m + 1, t.type());

    double tmp[] = {0.0};

    sum_t = cumulative_sum_t(af::seq(m - 1, na - 1)) - join(0, af::array(1, tmp), cumulative_sum_t(af::seq(0, na - m - 1)));
    sum_t2 = cumulative_sum_t2(af::seq(m - 1, na - 1)) - join(0, af::array(1, tmp), cumulative_sum_t2(af::seq(0, na - m - 1)));

    *mean = sum_t / m;
    array mean_t2 = sum_t2 / m;
    array mean_t_p2 = af::pow(*mean, 2);
    array sigma_t2 = mean_t2 - mean_t_p2;
    *stdev = af::sqrt(sigma_t2);
}

void tsa::matrix::calculateDistanceProfile(long m, af::array qt, af::array a,
                                af::array sum_q, af::array sum_q2, af::array mean_t, af::array sigma_t, bool ignoreTrivial,
                                af::array *distance, af::array *index, long batchStart) {
    long batchSize = qt.dims(3);
    long tsLength = qt.dims(0);
    af::array a_tiled = af::tile(a, 1, 1, 1, batchSize);
    af::array sum_q_tiled = af::tile(sum_q, tsLength);
    af::array sum_q2_tiled = af::tile(sum_q2, tsLength);
    af::array mean_t_tiled = af::tile(mean_t, 1, 1, 1, batchSize);
    af::array sigma_t_tiled = af::tile(sigma_t, 1, 1, 1, batchSize);

    af::array dist = a_tiled + (-2 * (qt - sum_q_tiled * mean_t_tiled) / af::max(sigma_t_tiled, af::constant(EPSILON, sigma_t_tiled.dims(), qt.type()))) + sum_q2_tiled;
    dist = af::sqrt(af::abs(dist));

    dist = af::reorder(dist, 3, 0, 1, 2);

    double d = ignoreTrivial;
    long bandSize = std::ceil(m/2.0)+1;

    int tmp = batchStart > 0;
    af::array mask = af::convolve2(af::shift(af::identity(std::max(batchSize, bandSize) + 1, tsLength + bandSize - 1), 0, batchStart - tmp), af::constant(1, bandSize, bandSize)) > 0.0;
    mask = mask(seq(tmp, batchSize - 1 + tmp), seq(tsLength));
    dist += d * 1/EPSILON * mask.as(qt.type());

    af::min(*distance, *index, dist, 1);
}

void tsa::matrix::mass(af::array q, af::array t, long m, af::array a, af::array mean_t, af::array sigma_t, bool ignoreTrivial,
                        af::array *distance, af::array *index, long batchStart) {
    q = tsa::normalization::znorm(q, EPSILON);

    af::array qt = tsa::matrix::slidingDotProduct(q, t);
    af::array sum_q = af::sum(q);
    af::array sum_q2 = af::sum(af::pow(q, 2));

    tsa::matrix::calculateDistanceProfile(m, qt, a, sum_q, sum_q2, mean_t, sigma_t, ignoreTrivial, distance, index, batchStart);
}

void stamp_batched(af::array ta, af::array tb, long m, long batch_size, af::array *profile, af::array *index) {
    long nb = tb.dims(0);

    af::array aux;
    af::array mean;
    af::array stdev;

    (*profile) = af::array(0, ta.type());
    (*index) = af::array(0, af::dtype::u32);

    tsa::matrix::meanStdev(ta, &aux, m, &mean, &stdev);

    long chunkSize = std::min(nb - m + 1, batch_size);

    af::array input = af::array(m, chunkSize, tb.type());

    for(long i = 0; i < (nb - m); i+=chunkSize)
    {
        long iterationSize = std::min(chunkSize, nb - m - i + 1);

        if(iterationSize != chunkSize) {
            input = af::array(m, iterationSize, tb.type());
        }

        for(long j = 0; j < m; j++){
            input(j, span, span, span) = tb(af::seq(i + j, i + j + iterationSize - 1));
        }

        gfor(af::seq idx, iterationSize) {
            af::array distance;
            af::array pidx;

            tsa::matrix::mass(input(span, idx, span, span), ta, m, aux, mean, stdev, false, &distance, &pidx);

            *profile = join(0, *profile, distance);
            *index = join(0, *index, pidx);
        }
    }
}

void stamp_batched_two_levels(af::array ta, af::array tb, long m, long batch_size_b, long batch_size_a, af::array *profile, af::array *index) {
    long nb = tb.dims(0);
    long na = ta.dims(0);

    (*profile) = af::array(0, ta.type());
    (*index) = af::array(0, af::dtype::u32);

    long chunkSizeB = std::min(nb - m + 1, batch_size_b);
    long chunkSizeA = std::min(na, batch_size_a);    

    af::array input = af::array(m, chunkSizeB, tb.type());

    for(long i = 0; i < (nb - m); i+=chunkSizeB)
    {
        long iterationSizeB = std::min(chunkSizeB, nb - m - i + 1);

        if(iterationSizeB != chunkSizeB) {
            input = af::array(m, iterationSizeB, tb.type());
        }

        for(long j = 0; j < m; j++){
            input(j, span, span, span) = tb(af::seq(i + j, i + j + iterationSizeB - 1));
        }

        af::array distance = af::array(0, ta.type());
        af::array pidx = af::array(0, af::dtype::u32);

        for(long k = 0; k < na; k+=chunkSizeA) {
            long start = k/chunkSizeA * (chunkSizeA - m + 1);
            long iterationSizeA = std::min(chunkSizeA, na - start);
            long end = start + iterationSizeA - 1;
            af::array taChunk = ta(seq(start, end));
            af::array aux;
            af::array mean;
            af::array stdev;
            tsa::matrix::meanStdev(taChunk, &aux, m, &mean, &stdev);
            gfor(af::seq idx, iterationSizeB) {
                af::array distanceTmp;
                af::array pidxTmp;

                tsa::matrix::mass(input(span, idx, span, span), taChunk, m, aux, mean, stdev, false, &distanceTmp, &pidxTmp);

                pidxTmp += start;

                distance = join(1, distance, distanceTmp);
                pidx = join(1, pidx, pidxTmp);
            }
        }

        af::array idx;
        af::array min;

        af::min(min, idx, distance, 1);

        af::dim4 dims = min.dims();
        double sliceStride = dims[0]*dims[1];

        array bidx = af::iota(af::dim4(dims[0], dims[1]));

        af::array flatIndices = af::flat(idx*sliceStride+bidx);

        af::array flatPidx = af::flat(pidx);
        af::array vFromPidx = flatPidx(flatIndices);

        *profile = af::join(0, *profile, min);
        *index   = af::join(0, *index, af::moddims(vFromPidx, af::dim4(dims[0], dims[1])));
    }
}

void stamp_parallel(af::array ta, af::array tb, long m, af::array *profile, af::array *index) {
    long nb = tb.dims(0);

    af::array aux;
    af::array mean;
    af::array stdev;

    tsa::matrix::meanStdev(ta, &aux, m, &mean, &stdev);

    af::array input = af::array(m, nb - m + 1, tb.type());

    for(int i = 0; i < m; i++){
        input(i, span, span, span) = tb(af::seq(i, nb - m + i));
    }

    gfor(af::seq idx, nb - m + 1) {
        tsa::matrix::mass(input(span, idx, span, span), ta, m, aux, mean, stdev, false, profile, index);
    }
}

void tsa::matrix::stamp(af::array ta, af::array tb, long m, af::array *profile, af::array *index) { 
    if(tb.dims(0) > BATCH_SIZE) {
        if(ta.dims(0) > BATCH_SIZE) {
            return stamp_batched_two_levels(ta, tb, m, BATCH_SIZE, BATCH_SIZE, profile, index);
        } else {
            return stamp_batched(ta, tb, m, BATCH_SIZE, profile, index);
        }
    } else {
        return stamp_parallel(ta, tb, m, profile, index);
    }
}

void stamp_batched(af::array t, long m, long batch_size, af::array *profile, af::array *index) {
    long nb = t.dims(0);

    af::array aux;
    af::array mean;
    af::array stdev;

    (*profile) = af::array(0, t.type());
    (*index) = af::array(0, af::dtype::u32);

    tsa::matrix::meanStdev(t, &aux, m, &mean, &stdev);

    long chunkSize = std::min(nb - m + 1, batch_size);

    af::array input = af::array(m, chunkSize, t.type());

    for(long i = 0; i < (nb - m); i+=chunkSize)
    {
        long iterationSize = std::min(chunkSize, nb - m - i + 1);

        if(iterationSize != chunkSize) {
            input = af::array(m, iterationSize, t.type());
        }

        for(long j = 0; j < m; j++){
            input(j, span, span, span) = t(af::seq(i + j, i + j + iterationSize - 1));
        }

        gfor(af::seq idx, iterationSize) {
            af::array distance;
            af::array pidx;

            tsa::matrix::mass(input(span, idx, span, span), t, m, aux, mean, stdev, true, &distance, &pidx, i);

            *profile = join(0, *profile, distance);
            *index = join(0, *index, pidx);
        }
    }
}

void stamp_parallel(af::array t, long m, af::array *profile, af::array *index) {
    long n = t.dims(0);

    af::array aux;
    af::array mean;
    af::array stdev;

    tsa::matrix::meanStdev(t, &aux, m, &mean, &stdev);

    af::array input = af::array(m, n - m + 1, t.type());

    for(int i = 0; i < m; i++){
        input(i, span, span, span) = t(af::seq(i, n - m + i));
    }

    gfor(af::seq idx, n - m + 1) {
        tsa::matrix::mass(input(span, idx, span, span), t, m, aux, mean, stdev, true, profile, index);
    }
}

void tsa::matrix::stamp(array t, long m, af::array *profile, af::array *index) { 
    if(t.dims(0) > BATCH_SIZE) {
        return stamp_batched(t, m, BATCH_SIZE, profile, index);
    } else {
        return stamp_parallel(t, m, profile, index);
    }
}