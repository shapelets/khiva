// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa/matrix.h>
#include <tsa/normalization.h>
#include <algorithm>
#include <limits>

#define BATCH_SIZE 2048
#define EPSILON 1e-8

af::array tsa::matrix::slidingDotProduct(af::array q, af::array t) {
    long n = static_cast<long>(t.dims(0));
    long m = static_cast<long>(q.dims(0));

    // Flipping all the query sequences contained in q
    af::array qr = af::flip(q, 0);

    // Calculating the convolve of all the query sequences contained in qr
    // against all the time series contained in t
    af::array qt = af::real(af::convolve(t, qr, AF_CONV_EXPAND));

    return qt(af::seq(m - 1, n - 1), af::span, af::span, af::span);
}

void tsa::matrix::meanStdev(af::array t, af::array &a, long m, af::array &mean, af::array &stdev) {
    long na = static_cast<long>(t.dims(0));

    af::array tmp = af::constant(0, 1, t.dims(1), t.type());

    // Cumulative sum of all the time series contained in t
    af::array cumulative_sum_t = af::join(0, tmp, af::accum(t, 0));
    // Cumulative sum of the square of all the time series contained in t
    af::array cumulative_sum_t2 = af::join(0, tmp, af::accum(af::pow(t, 2), 0));

    af::array sum_t = cumulative_sum_t(af::seq(m, na), af::span) - cumulative_sum_t(af::seq(0, na - m), af::span);
    // Cumulative sum of the element-wise square of each subsequence of all the time series contained in t
    af::array sum_t2 = cumulative_sum_t2(af::seq(m, na), af::span) - cumulative_sum_t2(af::seq(0, na - m), af::span);

    // Mean of each subsequence of all the time series
    mean = sum_t / m;
    // Mean of the element-wise square of each subsequence of t
    af::array mean_t2 = sum_t2 / m;
    // Square of the mean
    af::array mean_t_p2 = af::pow(mean, 2);
    // Variance
    af::array sigma_t2 = mean_t2 - mean_t_p2;
    // Standard deviation
    stdev = af::sqrt(sigma_t2);

    double eps = (sigma_t2.type() == 0) ? EPSILON * 1e4 : EPSILON;

    af::array lessThanEpsilon = eps >= sigma_t2;
    sigma_t2 = lessThanEpsilon * lessThanEpsilon.as(sigma_t2.type()) + !lessThanEpsilon * sigma_t2;

    // Auxiliary variable to be used for the distance calculation
    a = (sum_t2 - 2 * sum_t * mean + m * mean_t_p2) / sigma_t2;
}

void tsa::matrix::meanStdev(af::array t, long m, af::array &mean, af::array &stdev) {
    long na = static_cast<long>(t.dims(0));

    af::array tmp = af::constant(0, 1, t.dims(1), t.type());

    // Cumulative sum of all the time series contained in t
    af::array cumulative_sum_t = af::join(0, tmp, af::accum(t, 0));
    // Cumulative sum of the square of all the time series contained in t
    af::array cumulative_sum_t2 = af::join(0, tmp, af::accum(af::pow(t, 2), 0));

    af::array sum_t = cumulative_sum_t(af::seq(m, na), af::span) - cumulative_sum_t(af::seq(0, na - m), af::span);
    // Cumulative sum of the element-wise square of each subsequence of all the time series contained in t
    af::array sum_t2 = cumulative_sum_t2(af::seq(m, na), af::span) - cumulative_sum_t2(af::seq(0, na - m), af::span);

    // Mean of each subsequence of all the time series
    mean = sum_t / m;
    // Mean of the element-wise square of each subsequence of t
    af::array mean_t2 = sum_t2 / m;
    // Square of the mean
    af::array mean_t_p2 = af::pow(mean, 2);
    // Variance
    af::array sigma_t2 = mean_t2 - mean_t_p2;
    // Standard deviation
    stdev = af::sqrt(sigma_t2);
}

af::array tsa::matrix::generateMask(long m, long batchSize, long batchStart, long tsLength, long nTimeSeries) {
    long bandSize = static_cast<long>(std::ceil(m / 2.0)) + 1;

    if (m * tsLength <= 2097152) {
        // Limit the faster method using convolve for up to the previous number of points which uses approximately
        // 1.42GB of memory
        int tmp = batchStart > 0;
        // Identity matrix of batch or band size (the max of both) rows and
        // tsLength + band size columns
        af::array identity = af::identity(std::max(batchSize, bandSize) + bandSize, tsLength + bandSize - 1);
        // Shifting the identity matrix to the batch start position
        identity = af::shift(identity, 0, static_cast<int>(batchStart - tmp), 0);

        // Calculating the band matrix using the convolve function
        af::array mask = af::convolve2(identity, af::constant(1, bandSize, bandSize)) > 0;
        mask = mask(af::seq(tmp, batchSize - 1 + tmp), af::seq(tsLength));

        // Tiling the same mask to all the time series
        mask = af::tile(mask, 1, 1, static_cast<unsigned int>(nTimeSeries));

        return mask;
    } else {
        af::array mask = af::array(batchSize, tsLength);
        af::array tmp =
            af::transpose(af::join(0, af::constant(1, 2 * (bandSize - 1) + 1), af::constant(0, tsLength - 1)));
        for (int i = 0; i < batchSize; i++) {
            af::array tmp2 = af::shift(tmp, 0, i + static_cast<int>(batchStart));
            mask(i, af::span) = tmp2(af::seq(bandSize - 1, tsLength + bandSize - 2));
        }

        // Tiling the same mask to all the time series
        mask = af::tile(mask, 1, 1, static_cast<unsigned int>(nTimeSeries));

        return mask;
    }
}

void tsa::matrix::calculateDistanceProfile(af::array qt, af::array a, af::array sum_q, af::array sum_q2,
                                           af::array mean_t, af::array sigma_t, af::array mask, af::array &distance,
                                           af::array &index) {
    long batchSize = static_cast<long>(qt.dims(3));
    long tsLength = static_cast<long>(qt.dims(0));
    long nTimeSeries = static_cast<long>(qt.dims(1));

    // Tiling the input data to match the batch size, the time series length and the number of time series
    af::array a_tiled = af::tile(a, 1, 1, 1, static_cast<unsigned int>(batchSize));
    af::array sum_q_tiled =
        af::tile(sum_q, static_cast<unsigned int>(tsLength), static_cast<unsigned int>(nTimeSeries));
    af::array sum_q2_tiled =
        af::tile(sum_q2, static_cast<unsigned int>(tsLength), static_cast<unsigned int>(nTimeSeries));
    af::array mean_t_tiled = af::tile(mean_t, 1, 1, 1, static_cast<unsigned int>(batchSize));
    af::array sigma_t_tiled = af::tile(sigma_t, 1, 1, 1, static_cast<unsigned int>(batchSize));

    // Required to avoid a division by zero when the standard deviation is zero
    double eps = (sigma_t_tiled.type() == 0) ? EPSILON * 1e4 : EPSILON;
    af::array lessThanEpsilon = eps >= sigma_t_tiled;
    sigma_t_tiled = lessThanEpsilon * lessThanEpsilon.as(sigma_t_tiled.type()) + !lessThanEpsilon * sigma_t_tiled;
    // Computing the distance
    af::array dist = a_tiled + (-2 * (qt - sum_q_tiled * mean_t_tiled) / sigma_t_tiled) + sum_q2_tiled;
    dist = af::sqrt(af::abs(dist));

    // The 1st dimension reflects the number of subsequences of the reference time series.
    // The 2nd dimension reflects the number of query time series.
    // The 3rd dimension reflects the number of reference time series
    // The 4th dimension reflects the batch size of query subsequences from the query time series
    // Reordering to match the mask band matrix dimensions
    dist = af::reorder(dist, 3, 0, 1, 2);

    // Increasing the distance using the mask band matrix to filter trivial matches
    dist += 1 / EPSILON * mask.as(qt.type());

    // The 1st dimension reflects the number of subsequences of the reference time series.
    // The 2nd dimension reflects the number of reference time series.
    // The 3rd dimension reflects the batch size of query subsequences from the query time series
    // The 4th dimension reflects the number of query time series
    dist = af::reorder(dist, 0, 2, 1, 3);

    af::min(distance, index, dist, 2);
}

void tsa::matrix::calculateDistanceProfile(af::array qt, af::array a, af::array sum_q, af::array sum_q2,
                                           af::array mean_t, af::array sigma_t, af::array &distance, af::array &index) {
    long batchSize = static_cast<long>(qt.dims(3));
    long tsLength = static_cast<long>(qt.dims(0));
    long nTimeSeries = static_cast<long>(qt.dims(1));

    // Tiling the input data to match the batch size, the time series length and the number of time series
    af::array a_tiled = af::tile(a, 1, 1, 1, static_cast<unsigned int>(batchSize));
    af::array sum_q_tiled =
        af::tile(sum_q, static_cast<unsigned int>(tsLength), static_cast<unsigned int>(nTimeSeries));
    af::array sum_q2_tiled =
        af::tile(sum_q2, static_cast<unsigned int>(tsLength), static_cast<unsigned int>(nTimeSeries));
    af::array mean_t_tiled = af::tile(mean_t, 1, 1, 1, static_cast<unsigned int>(batchSize));
    af::array sigma_t_tiled = af::tile(sigma_t, 1, 1, 1, static_cast<unsigned int>(batchSize));

    // Required to avoid a division by zero when the standard deviation is zero
    double eps = (sigma_t_tiled.type() == 0) ? EPSILON * 1e4 : EPSILON;
    af::array lessThanEpsilon = eps >= sigma_t_tiled;
    sigma_t_tiled = lessThanEpsilon * lessThanEpsilon.as(sigma_t_tiled.type()) + !lessThanEpsilon * sigma_t_tiled;
    // Computing the distance
    af::array dist = a_tiled + (-2 * (qt - sum_q_tiled * mean_t_tiled) / sigma_t_tiled) + sum_q2_tiled;
    dist = af::sqrt(af::abs(dist));

    // The 1st dimension reflects the number of subsequences of the reference time series.
    // The 2nd dimension reflects the number of reference time series.
    // The 3rd dimension reflects the number of query time series
    // The 4th dimension reflects the batch size of query subsequences from the query time series
    dist = af::reorder(dist, 3, 1, 0, 2);

    af::min(distance, index, dist, 2);
}

void tsa::matrix::mass(af::array q, af::array t, af::array a, af::array mean_t, af::array sigma_t, af::array mask,
                       af::array &distance, af::array &index) {
    // Normalizing the query sequence. q can contain query sequences from multiple series
    q = tsa::normalization::znorm(q, EPSILON);

    // Sliding dot product of the subsequence q of all the query time series against all the reference time series
    // contained in t
    af::array qt = tsa::matrix::slidingDotProduct(q, t);
    // Cumulative sum of all the elements contained in q (for each time series, that is why it is done using the first
    // dimension)
    af::array sum_q = af::sum(q, 0);
    // Cumulative sum of squares of all the elements contained in q (for each time series, that is why it is done using
    // the first dimension)
    af::array sum_q2 = af::sum(af::pow(q, 2), 0);

    // Calculate the distance and index profiles for all the combinations of query sequences and reference time series
    tsa::matrix::calculateDistanceProfile(qt, a, sum_q, sum_q2, mean_t, sigma_t, mask, distance, index);
}

void tsa::matrix::mass(af::array q, af::array t, af::array a, af::array mean_t, af::array sigma_t, af::array &distance,
                       af::array &index) {
    // Normalizing the query sequence. q can contain query sequences from multiple series
    q = tsa::normalization::znorm(q, EPSILON);

    // Sliding dot product of the subsequence q of all the query time series against all the reference time series
    // contained in t
    af::array qt = tsa::matrix::slidingDotProduct(q, t);
    // Cumulative sum of all the elements contained in q (for each time series, that is why it is done using the first
    // dimension)
    af::array sum_q = af::sum(q, 0);
    // Cumulative sum of squares of all the elements contained in q (for each time series, that is why it is done using
    // the first dimension)
    af::array sum_q2 = af::sum(af::pow(q, 2), 0);

    // Calculate the distance and index profiles for all the combinations of query sequences and reference time series
    tsa::matrix::calculateDistanceProfile(qt, a, sum_q, sum_q2, mean_t, sigma_t, distance, index);
}

void stomp_batched(af::array ta, af::array tb, long m, long batch_size, af::array &profile, af::array &index) {
    long nb = static_cast<long>(tb.dims(0));

    af::array aux;
    af::array mean;
    af::array stdev;

    profile = af::array(0, ta.type());
    index = af::array(0, af::dtype::u32);

    // Computing the mean and standard deviation of all the reference time series contained in ta
    tsa::matrix::meanStdev(ta, aux, m, mean, stdev);

    // The chunk size cannot be greater than the length of the input time series tb minus m + 1
    long chunkSize = std::min(nb - m + 1, batch_size);

    // Array that will hold all the query sequences for the given chunk. One per column
    af::array input = af::array(m, chunkSize, tb.dims(1), tb.type());

    for (long i = 0; i < (nb - m + 1); i += chunkSize) {
        // The iteration space cannot be greater than what is left (nb - m - i + 1)
        long iterationSize = std::min(chunkSize, nb - m - i + 1);

        // If the iteration size has changed, resize input array
        if (iterationSize != chunkSize) {
            input = af::array(m, iterationSize, tb.dims(1), tb.type());
        }

        // Store all the subsequences of all the time series from t in input
        for (long j = 0; j < m; j++) {
            input(static_cast<int>(j), af::span, af::span, af::span) =
                af::reorder(tb(af::seq(i + j, i + j + iterationSize - 1), af::span), 2, 0, 1, 3);
        }

        // For all the subsequences in input for the given batch
        gfor(af::seq idx, iterationSize) {
            af::array distance;
            af::array pidx;

            // Compute the distance and index profiles using Mueens algorithm for similarity search
            tsa::matrix::mass(input(af::span, idx, af::span, af::span), ta, aux, mean, stdev, distance, pidx);

            // Concat the profiles of the given chunk to the general result
            profile = join(0, profile, distance);
            index = join(0, index, pidx);
        }

        // The 1st dimension reflects the batch size of query subsequences from the query time series
        // The 2nd dimension reflects the number of reference time series.
        // The 3rd dimension reflects the number of query time series
        profile = af::reorder(profile, 0, 1, 3, 2);
        index = af::reorder(index, 0, 1, 3, 2);

        af::sync();
    }
}

void stomp_batched_two_levels(af::array ta, af::array tb, long m, long batch_size_b, long batch_size_a,
                              af::array &profile, af::array &index) {
    long nb = static_cast<long>(tb.dims(0));
    long na = static_cast<long>(ta.dims(0));
    long nTimeSeriesA = static_cast<long>(ta.dims(1));
    long nTimeSeriesB = static_cast<long>(tb.dims(1));

    profile = af::array(0, ta.type());
    index = af::array(0, af::dtype::u32);

    // The chunk size cannot be greater than the length of the input time series tb minus m + 1
    long chunkSizeB = std::min(nb - m + 1, batch_size_b);
    // The chunk size cannot be greater than the length of the input time series ta
    long chunkSizeA = std::min(na, batch_size_a);
    chunkSizeA = std::max(m, chunkSizeA);

    // Array that will hold all the query sequences for the given chunk. One per column
    af::array input = af::array(m, chunkSizeB, nTimeSeriesB, tb.type());

    for (long i = 0; i < (nb - m + 1); i += chunkSizeB) {
        // The iteration space cannot be greater than what is left (nb - m - i + 1)
        long iterationSizeB = std::min(chunkSizeB, nb - m - i + 1);

        // If the iteration size has changed, resize input array
        if (iterationSizeB != chunkSizeB) {
            input = af::array(m, iterationSizeB, nTimeSeriesB, tb.type());
        }

        // Store all the subsequences of all the time series from t in input
        for (long j = 0; j < m; j++) {
            input(static_cast<int>(j), af::span, af::span, af::span) =
                af::reorder(tb(af::seq(i + j, i + j + iterationSizeB - 1), af::span), 2, 0, 1, 3);
        }

        af::array distance = af::array(0, ta.type());
        af::array pidx = af::array(0, af::dtype::u32);

        // Splitting the reference time series
        for (long k = 0; k < (na - m + 1); k += chunkSizeA) {
            // Start of the given time series chunk
            long start = k / chunkSizeA * (chunkSizeA - m + 1);
            // The iteration space cannot be greater than what is left (na - start)
            long iterationSizeA = std::min(chunkSizeA, na - start);
            // End of the given time series chunk
            long end = start + iterationSizeA - 1;

            // Reference time series chunk to compare to
            af::array taChunk = ta(af::seq(start, end), af::span);

            af::array aux;
            af::array mean;
            af::array stdev;
            // Computing the mean and standard deviation of all the reference time series contained in taChunk
            tsa::matrix::meanStdev(taChunk, aux, m, mean, stdev);
            // For all the subsequences in input for the given batch
            gfor(af::seq idx, iterationSizeB) {
                af::array distanceTmp;
                af::array pidxTmp;

                // Compute the distance and index profiles using Mueens algorithm for similarity search
                tsa::matrix::mass(input(af::span, idx, af::span, af::span), taChunk, aux, mean, stdev, distanceTmp,
                                  pidxTmp);

                // Leaving 2nd dimension blank to join the partial results using it
                distanceTmp = af::reorder(distanceTmp, 0, 2, 1, 3);
                pidxTmp = af::reorder(pidxTmp, 0, 2, 1, 3);

                // Adding the offset of the chunk to the index profile
                pidxTmp += start;

                // Concat the profiles of the given chunk to a partial result for the batch of tb
                distance = af::join(1, distance, distanceTmp);
                pidx = af::join(1, pidx, pidxTmp);
            }
            af::sync();
        }

        af::array idx;
        af::array min;

        // Calculating the minimum distance of the ta chunks
        af::min(min, idx, distance, 1);

        // The second dimension is not useful anymore after calculating the min over it, moving it to the 4th dimension
        min = af::reorder(min, 0, 2, 3, 1);
        idx = af::reorder(idx, 0, 2, 3, 1);

        // Auxiliary variables to add to the index in order to obtain the real index where the minimum occurs
        af::array toSum = af::seq(0, (nTimeSeriesA * nTimeSeriesB - 1) * static_cast<double>(distance.dims(1)),
                                  static_cast<double>(distance.dims(1)));
        af::array aux = af::transpose(toSum).as(idx.type());
        aux = af::moddims(aux, 1, idx.dims(1), idx.dims(2), 1);
        aux = af::tile(aux, static_cast<unsigned int>(idx.dims(0)));

        // Adding the offset to the intermediate index
        idx += aux;

        af::dim4 dims = min.dims();
        float sliceStride = static_cast<float>(dims[0]);

        // Offset inside the batch
        af::array bidx = af::tile(af::iota(af::dim4(dims[0])), 1, static_cast<unsigned int>(idx.dims(1)),
                                  static_cast<unsigned int>(nTimeSeriesB));

        // Flat array containing the real indices to obtain from the index profile
        af::array flatIndices = af::flat(idx * sliceStride + bidx);

        // Flat index profile
        af::array flatPidx = af::flat(pidx);
        // Indexing the profile index with the flat array containing the real indices
        af::array vFromPidx = flatPidx(flatIndices);

        // Setting the actual outputs (profile and index)
        profile = af::join(0, profile, min);
        index = af::join(0, index, af::moddims(vFromPidx, af::dim4(dims[0], dims[1], dims[2], 1)));
    }
}

void stomp_parallel(af::array ta, af::array tb, long m, af::array &profile, af::array &index) {
    long nb = static_cast<long>(tb.dims(0));

    af::array aux;
    af::array mean;
    af::array stdev;

    // Computing the mean and standard deviation of all the reference time series contained in ta
    tsa::matrix::meanStdev(ta, aux, m, mean, stdev);

    // If the iteration size has changed, resize input array
    af::array input = af::array(m, nb - m + 1, tb.dims(1), tb.type());

    // Store all the subsequences of all the time series from tb in input
    for (int i = 0; i < m; i++) {
        input(i, af::span, af::span, af::span) = af::reorder(tb(af::seq(i, nb - m + i), af::span), 2, 0, 1, 3);
    }

    // For all the subsequences of tb
    gfor(af::seq idx, nb - m + 1) {
        // Compute the distance and index profiles using Mueens algorithm for similarity search
        tsa::matrix::mass(input(af::span, idx, af::span, af::span), ta, aux, mean, stdev, profile, index);
    }

    // Moving the number of time series in tb, which is in the 4th dimension to the 3rd dimension
    profile = af::reorder(profile, 0, 1, 3, 2);
    index = af::reorder(index, 0, 1, 3, 2);

    af::sync();
}

void tsa::matrix::stomp(af::array ta, af::array tb, long m, af::array &profile, af::array &index) {
    if (tb.dims(0) > BATCH_SIZE) {
        if (ta.dims(0) > BATCH_SIZE) {
            // Calculates the distance and index profiles using a double batching strategy. First by the number of query
            // sequences from tb to compare simultaneously; and second, the chunk size of the reference time series ta
            return stomp_batched_two_levels(ta, tb, m, BATCH_SIZE, BATCH_SIZE, profile, index);
        } else {
            // Calculates the distance and index profiles using a batching strategy by the number of query
            // sequences from tb to compare simultaneously
            return stomp_batched(ta, tb, m, BATCH_SIZE, profile, index);
        }
    } else {
        // Doing it in parallel
        return stomp_parallel(ta, tb, m, profile, index);
    }
}

void stomp_batched_two_levels(af::array t, long m, long batch_size_b, long batch_size_a, af::array &profile,
                              af::array &index) {
    long n = static_cast<long>(t.dims(0));
    long nTimeSeries = static_cast<long>(t.dims(1));

    profile = af::array(0, t.type());
    index = af::array(0, af::dtype::u32);

    // The chunk size cannot be greater than the length of the input time series tb minus m + 1
    long chunkSizeB = std::min(n - m + 1, batch_size_b);
    // The chunk size cannot be greater than the length of the input time series ta
    long chunkSizeA = std::min(n, batch_size_a);
    chunkSizeA = std::max(m, chunkSizeA);

    // Array that will hold all the query sequences for the given chunk. One per column
    af::array input = af::array(m, chunkSizeB, nTimeSeries, t.type());

    for (long i = 0; i < (n - m + 1); i += chunkSizeB) {
        // The iteration space cannot be greater than what is left (nb - m - i + 1)
        long iterationSizeB = std::min(chunkSizeB, n - m - i + 1);

        // If the iteration size has changed, resize input array
        if (iterationSizeB != chunkSizeB) {
            input = af::array(m, iterationSizeB, nTimeSeries, t.type());
        }

        // Store all the subsequences of all the time series from t in input
        for (long j = 0; j < m; j++) {
            input(static_cast<int>(j), af::span, af::span, af::span) =
                af::reorder(t(af::seq(i + j, i + j + iterationSizeB - 1), af::span), 2, 0, 1, 3);
        }

        af::array distance = af::array(0, t.type());
        af::array pidx = af::array(0, af::dtype::u32);

        // Calculating the mask required to filter the trivial matches
        af::array mask = tsa::matrix::generateMask(m, iterationSizeB, i, n - m + 1, nTimeSeries);

        // Splitting the reference time series
        for (long k = 0; k < (n - m + 1); k += chunkSizeA) {
            // Start of the given time series chunk
            long start = k / chunkSizeA * (chunkSizeA - m + 1);
            // The iteration space cannot be greater than what is left (na - start)
            long iterationSizeA = std::min(chunkSizeA, n - start);
            // End of the given time series chunk
            long end = start + iterationSizeA - 1;

            // Reference time series chunk to compare to
            af::array tChunk = t(af::seq(start, end), af::span);

            af::array aux;
            af::array mean;
            af::array stdev;
            // Computing the mean and standard deviation of all the reference time series contained in taChunk
            tsa::matrix::meanStdev(tChunk, aux, m, mean, stdev);
            // For all the subsequences in input for the given batch
            gfor(af::seq idx, iterationSizeB) {
                af::array distanceTmp;
                af::array pidxTmp;

                // Compute the distance and index profiles using Mueens algorithm for similarity search
                tsa::matrix::mass(input(af::span, idx, af::span, af::span), tChunk, aux, mean, stdev,
                                  mask(af::span, af::seq(start, start + iterationSizeA - m), af::span), distanceTmp,
                                  pidxTmp);

                // Leaving 2nd dimension blank to join the partial results using it. Using the diag method because
                // we only want the distances of a time series with itself
                distanceTmp = af::reorder(af::diag(af::reorder(distanceTmp, 3, 1, 0, 2)), 2, 1, 0, 3);
                pidxTmp = af::reorder(af::diag(af::reorder(pidxTmp, 3, 1, 0, 2)), 2, 1, 0, 3);

                // Adding the offset of the chunk to the index profile
                pidxTmp += start;

                // Concat the profiles of the given chunk to a partial result for the batch of tb
                distance = af::join(1, distance, distanceTmp);
                pidx = af::join(1, pidx, pidxTmp);
            }
            af::sync();
        }

        af::array idx;
        af::array min;

        // Calculating the minimum distance of the ta chunks
        af::min(min, idx, distance, 1);

        // The second dimension is not useful anymore after calculating the min over it, moving it to the 4th dimension
        min = af::reorder(min, 0, 2, 1, 3);
        idx = af::reorder(idx, 0, 2, 1, 3);

        // Auxiliary variables to add to the index in order to obtain the real index where the minimum occurs
        af::array toSum = af::seq(0, (nTimeSeries - 1) * static_cast<double>(distance.dims(1)),
                                  static_cast<double>(distance.dims(1)));
        af::array aux = af::transpose(toSum).as(idx.type());
        aux = af::tile(aux, static_cast<unsigned int>(idx.dims(0)));

        // Adding the offset to the intermediate index
        idx += aux;

        af::dim4 dims = min.dims();
        float sliceStride = static_cast<float>(dims[0]);

        // Offset inside the batch
        af::array bidx = af::tile(af::iota(af::dim4(dims[0])), 1, static_cast<unsigned int>(nTimeSeries));

        // Flat array containing the real indices to obtain from the index profile
        af::array flatIndices = af::flat(idx * sliceStride + bidx);

        // Flat index profile
        af::array flatPidx = af::flat(pidx);
        // Indexing the profile index with the flat array containing the real indices
        af::array vFromPidx = flatPidx(flatIndices);

        // Setting the actual outputs (profile and index)
        profile = af::join(0, profile, min);
        index = af::join(0, index, af::moddims(vFromPidx, af::dim4(dims[0], dims[1])));
    }
}

void stomp_parallel(af::array t, long m, af::array &profile, af::array &index) {
    long n = static_cast<long>(t.dims(0));
    long nTimeSeries = static_cast<long>(t.dims(1));

    af::array aux;
    af::array mean;
    af::array stdev;

    // Computing the mean and standard deviation of all the reference time series contained in ta
    tsa::matrix::meanStdev(t, aux, m, mean, stdev);

    // If the iteration size has changed, resize input array
    af::array input = af::array(m, n - m + 1, nTimeSeries, t.type());

    // Store all the subsequences of all the time series from tb in input
    for (int i = 0; i < m; i++) {
        input(i, af::span, af::span, af::span) = af::reorder(t(af::seq(i, n - m + i), af::span), 2, 0, 1, 3);
    }

    // Calculating the mask required to filter the trivial matches
    af::array mask = tsa::matrix::generateMask(m, n - m + 1, 0, n - m + 1, nTimeSeries);

    // For all the subsequences of tb
    gfor(af::seq idx, n - m + 1) {
        // Compute the distance and index profiles using Mueens algorithm for similarity search
        tsa::matrix::mass(input(af::span, idx, af::span, af::span), t, aux, mean, stdev, mask, profile, index);
    }

    // Using the diag method because
    // we only want the distances of a time series with itself
    profile = af::reorder(af::diag(af::reorder(profile, 1, 3, 0, 2)), 2, 0, 1, 3);
    index = af::reorder(af::diag(af::reorder(index, 1, 3, 0, 2)), 2, 0, 1, 3);

    af::sync();
}

void tsa::matrix::stomp(af::array t, long m, af::array &profile, af::array &index) {
    if (t.dims(0) > BATCH_SIZE) {
        // Calculates the distance and index profiles using a double batching strategy. First by the number of query
        // sequences from t to compare simultaneously; and second, the chunk size of the reference time series t
        return stomp_batched_two_levels(t, m, BATCH_SIZE, BATCH_SIZE, profile, index);
    } else {
        // Doing it in parallel
        return stomp_parallel(t, m, profile, index);
    }
}

void tsa::matrix::findBestNMotifs(af::array profile, af::array index, long n, af::array &motifs,
                                  af::array &motifsIndices, af::array &subsequenceIndices) {
    // Repeat the profile in the second dimension
    af::array profileTiled = af::tile(profile, 1, 2);
    // Joining it with an array from 1 to n in order to obtain the query subsequence index later on
    af::array joined = af::join(1, index, af::range(index.dims(0), 1, 1, 1, -1, index.type()));
    af::array sortedDistances;
    af::array sortedIndices;

    // Sort the profile and the indices using the profile as keys
    af::sort(sortedDistances, sortedIndices, profileTiled, joined, 0, true);

    // Taking the best n indices
    af::array bestNIndices = sortedIndices(af::seq(n), af::span);
    // Distance of the best n motifs
    motifs = sortedDistances(af::seq(n));
    // Index of the reference subsequence producing the minimum
    motifsIndices = bestNIndices.col(0);
    // Index of the query subsequences producing the minimum
    subsequenceIndices = bestNIndices.col(1);
}

void tsa::matrix::findBestNDiscords(af::array profile, af::array index, long n, af::array &discords,
                                    af::array &discordsIndices, af::array &subsequenceIndices) {
    // Repeat the profile in the second dimension
    af::array profileTiled = af::tile(profile, 1, 2);
    // Joining it with an array from 1 to n in order to obtain the query subsequence index later on
    af::array joined = af::join(1, index, af::range(index.dims(0), 1, 1, 1, -1, index.type()));
    af::array sortedDistances;
    af::array sortedIndices;

    // Sort the profile and the indices using the profile as keys
    af::sort(sortedDistances, sortedIndices, profileTiled, joined, 0, false);

    // Taking the best n indices
    af::array bestNIndices = sortedIndices(af::seq(n), af::span);
    // Distance of the best n discords
    discords = sortedDistances(af::seq(n));
    // Index of the reference subsequence producing the maximum
    discordsIndices = bestNIndices.col(0);
    // Index of the query subsequences producing the maximum
    subsequenceIndices = bestNIndices.col(1);
}