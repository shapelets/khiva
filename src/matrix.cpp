// Copyright (c) 2018 Grumpy Cat Software S.L.
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa.h>
#include <float.h>

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

    *a = af::constant(0, na - m + 1, t.type());

    gfor (af::seq i, na - m + 1) {
        (*a)(i) = (sum_t2(i) - 2 * sum_t(i) * (*mean)(i) + m * mean_t_p2(i)) / sigma_t2(i);
    }
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

void tsa::matrix::calculateDistanceProfile(af::array qt, af::array a,
                                af::array sum_q, af::array sum_q2, af::array mean_t, af::array sigma_t,
                                af::array *distance, af::array *index) {
    af::array a_tiled = af::tile(a, 1, 1, 1, qt.dims(3));
    af::array sum_q_tiled = af::tile(sum_q, qt.dims(0));
    af::array sum_q2_tiled = af::tile(sum_q2, qt.dims(0));
    af::array mean_t_tiled = af::tile(mean_t, 1, 1, 1, qt.dims(3));
    af::array sigma_t_tiled = af::tile(sigma_t, 1, 1, 1, qt.dims(3));

    af::array dist = a_tiled + (-2 * (qt - sum_q_tiled * mean_t_tiled) / sigma_t_tiled) + sum_q2_tiled;
    dist = af::sqrt(af::abs(dist));

    dist = af::reorder(dist, 3, 0, 1, 2);

    af_array minimum = 0;
    af_array idx = 0;

    af_imin(&minimum, &idx, dist.get(), 1);

    *distance = af::array(minimum);
    *index = af::array(idx);
}

void tsa::matrix::mass(array q, array t, array a, array mean_t, array sigma_t, array *distance, array *index) {
    q = tsa::normalization::znorm(q, DBL_MIN);

    af::array qt = tsa::matrix::slidingDotProduct(q, t);
    af::array sum_q = af::sum(q);
    af::array sum_q2 = af::sum(af::pow(q, 2));

    calculateDistanceProfile(qt, a, sum_q, sum_q2, mean_t, sigma_t, distance, index);
}

void stamp_batched(af::array ta, af::array tb, long m, long batch_size, af::array *profile, af::array *index) {
    long nb = tb.dims(0);

    af::array aux;
    af::array mean;
    af::array stdev;

    (*profile) = af::array(0, ta.type());
    (*index) = af::array(0, u32);

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

            tsa::matrix::mass(input(span, idx, span, span), ta, aux, mean, stdev, &distance, &pidx);

            *profile = join(0, *profile, distance);
            *index = join(0, *index, pidx);
        }
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
        tsa::matrix::mass(input(span, idx, span, span), ta, aux, mean, stdev, profile, index);
    }
}

void tsa::matrix::stamp(array ta, array tb, long m, af::array *profile, af::array *index) { 
    if(tb.dims(0) > 4096) {
        return stamp_batched(ta, tb, m, 4096, profile, index);
    } else {
        return stamp_parallel(ta, tb, m, profile, index);
    }
}