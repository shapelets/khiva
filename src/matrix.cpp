// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa.h>
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

    af::array cumulative_sum_t = af::accum(t);
    af::array cumulative_sum_t2 = af::accum(af::pow(t, 2));
    af::array sum_t = af::constant(0, na - m + 1, t.type());
    af::array sum_t2 = af::constant(0, na - m + 1, t.type());

    af::array tmp = af::constant(0, 1, t.type());

    sum_t = cumulative_sum_t(af::seq(m - 1, na - 1)) - af::join(0, tmp, cumulative_sum_t(af::seq(0, na - m - 1)));
    sum_t2 = cumulative_sum_t2(af::seq(m - 1, na - 1)) - af::join(0, tmp, cumulative_sum_t2(af::seq(0, na - m - 1)));

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

    af::array cumulative_sum_t = af::accum(t);
    af::array cumulative_sum_t2 = af::accum(af::pow(t, 2));
    af::array sum_t = af::constant(0, na - m + 1, t.type());
    af::array sum_t2 = af::constant(0, na - m + 1, t.type());

    af::array tmp = af::constant(0, 1, t.type());

    sum_t = cumulative_sum_t(af::seq(m - 1, na - 1)) - af::join(0, tmp, cumulative_sum_t(af::seq(0, na - m - 1)));
    sum_t2 = cumulative_sum_t2(af::seq(m - 1, na - 1)) - af::join(0, tmp, cumulative_sum_t2(af::seq(0, na - m - 1)));

    mean = sum_t / m;
    af::array mean_t2 = sum_t2 / m;
    af::array mean_t_p2 = af::pow(mean, 2);
    af::array sigma_t2 = mean_t2 - mean_t_p2;
    stdev = af::sqrt(sigma_t2);
}

af::array tsa::matrix::generateMask(long m, long batchSize, long batchStart, long tsLength) {
    long bandSize = std::ceil(m / 2.0);

    int tmp = batchStart > 0;
    af::array identity = af::identity(std::max(batchSize, bandSize) + 1, tsLength + bandSize - 1);
    af::array mask = af::convolve2(af::shift(identity, 0, batchStart - tmp), af::constant(1, bandSize, bandSize)) > 0;
    mask = mask(af::seq(tmp, batchSize - 1 + tmp), af::seq(tsLength));

    return mask;
}

void tsa::matrix::calculateDistanceProfile(long m, af::array qt, af::array a, af::array sum_q, af::array sum_q2,
                                           af::array mean_t, af::array sigma_t, af::array mask, af::array &distance,
                                           af::array &index) {
    long batchSize = qt.dims(3);
    long tsLength = qt.dims(0);
    af::array a_tiled = af::tile(a, 1, 1, 1, batchSize);
    af::array sum_q_tiled = af::tile(sum_q, tsLength);
    af::array sum_q2_tiled = af::tile(sum_q2, tsLength);
    af::array mean_t_tiled = af::tile(mean_t, 1, 1, 1, batchSize);
    af::array sigma_t_tiled = af::tile(sigma_t, 1, 1, 1, batchSize);

    af::array den = af::max(sigma_t_tiled, af::constant(EPSILON, sigma_t_tiled.dims(), qt.type()));
    af::array dist = a_tiled + (-2 * (qt - sum_q_tiled * mean_t_tiled) / den) + sum_q2_tiled;
    dist = af::sqrt(af::abs(dist));

    dist = af::reorder(dist, 3, 0, 1, 2);

    dist += 1 / EPSILON * mask.as(qt.type());

    af::min(distance, index, dist, 1);
}

void tsa::matrix::calculateDistanceProfile(long m, af::array qt, af::array a, af::array sum_q, af::array sum_q2,
                                           af::array mean_t, af::array sigma_t, af::array &distance, af::array &index) {
    long batchSize = qt.dims(3);
    long tsLength = qt.dims(0);
    af::array a_tiled = af::tile(a, 1, 1, 1, batchSize);
    af::array sum_q_tiled = af::tile(sum_q, tsLength);
    af::array sum_q2_tiled = af::tile(sum_q2, tsLength);
    af::array mean_t_tiled = af::tile(mean_t, 1, 1, 1, batchSize);
    af::array sigma_t_tiled = af::tile(sigma_t, 1, 1, 1, batchSize);

    af::array den = af::max(sigma_t_tiled, af::constant(EPSILON, sigma_t_tiled.dims(), qt.type()));
    af::array dist = a_tiled + (-2 * (qt - sum_q_tiled * mean_t_tiled) / den) + sum_q2_tiled;
    dist = af::sqrt(af::abs(dist));

    dist = af::reorder(dist, 3, 0, 1, 2);

    af::min(distance, index, dist, 1);
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

    af::array input = af::array(m, chunkSize, tb.type());

    for (long i = 0; i < (nb - m); i += chunkSize) {
        long iterationSize = std::min(chunkSize, nb - m - i + 1);

        if (iterationSize != chunkSize) {
            input = af::array(m, iterationSize, tb.type());
        }

        for (long j = 0; j < m; j++) {
            input(j, span, span, span) = tb(af::seq(i + j, i + j + iterationSize - 1));
        }

        gfor(af::seq idx, iterationSize) {
            af::array distance;
            af::array pidx;

            tsa::matrix::mass(input(span, idx, span, span), ta, m, aux, mean, stdev, distance, pidx);

            profile = join(0, profile, distance);
            index = join(0, index, pidx);
        }
        af::sync();
    }
}

void stomp_batched_two_levels(af::array ta, af::array tb, long m, long batch_size_b, long batch_size_a,
                              af::array &profile, af::array &index) {
    long nb = tb.dims(0);
    long na = ta.dims(0);

    profile = af::array(0, ta.type());
    index = af::array(0, af::dtype::u32);

    long chunkSizeB = std::min(nb - m + 1, batch_size_b);
    long chunkSizeA = std::min(na, batch_size_a);

    af::array input = af::array(m, chunkSizeB, tb.type());

    for (long i = 0; i < (nb - m); i += chunkSizeB) {
        long iterationSizeB = std::min(chunkSizeB, nb - m - i + 1);

        if (iterationSizeB != chunkSizeB) {
            input = af::array(m, iterationSizeB, tb.type());
        }

        for (long j = 0; j < m; j++) {
            input(j, span, span, span) = tb(af::seq(i + j, i + j + iterationSizeB - 1));
        }

        af::array distance = af::array(0, ta.type());
        af::array pidx = af::array(0, af::dtype::u32);

        for (long k = 0; k < na; k += chunkSizeA) {
            long start = k / chunkSizeA * (chunkSizeA - m + 1);
            long iterationSizeA = std::min(chunkSizeA, na - start);
            long end = start + iterationSizeA - 1;
            af::array taChunk = ta(seq(start, end));
            af::array aux;
            af::array mean;
            af::array stdev;
            tsa::matrix::meanStdev(taChunk, aux, m, mean, stdev);
            gfor(af::seq idx, iterationSizeB) {
                af::array distanceTmp;
                af::array pidxTmp;

                tsa::matrix::mass(input(span, idx, span, span), taChunk, m, aux, mean, stdev, distanceTmp, pidxTmp);

                pidxTmp += start;

                distance = af::join(1, distance, distanceTmp);
                pidx = af::join(1, pidx, pidxTmp);
            }
            af::sync();
        }

        af::array idx;
        af::array min;

        af::min(min, idx, distance, 1);

        af::dim4 dims = min.dims();
        double sliceStride = dims[0] * dims[1];

        array bidx = af::iota(af::dim4(dims[0], dims[1]));

        af::array flatIndices = af::flat(idx * sliceStride + bidx);

        af::array flatPidx = af::flat(pidx);
        af::array vFromPidx = flatPidx(flatIndices);

        profile = af::join(0, profile, min);
        index = af::join(0, index, af::moddims(vFromPidx, af::dim4(dims[0], dims[1])));
    }
}

void stomp_parallel(af::array ta, af::array tb, long m, af::array &profile, af::array &index) {
    long nb = tb.dims(0);

    af::array aux;
    af::array mean;
    af::array stdev;

    tsa::matrix::meanStdev(ta, aux, m, mean, stdev);

    af::array input = af::array(m, nb - m + 1, tb.type());

    for (int i = 0; i < m; i++) {
        input(i, span, span, span) = tb(af::seq(i, nb - m + i));
    }

    gfor(af::seq idx, nb - m + 1) {
        tsa::matrix::mass(input(span, idx, span, span), ta, m, aux, mean, stdev, profile, index);
    }
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

    profile = af::array(0, t.type());
    index = af::array(0, af::dtype::u32);

    long chunkSizeB = std::min(n - m + 1, batch_size_b);
    long chunkSizeA = std::min(n, batch_size_a);

    af::array input = af::array(m, chunkSizeB, t.type());

    for (long i = 0; i < (n - m); i += chunkSizeB) {
        long iterationSizeB = std::min(chunkSizeB, n - m - i + 1);

        if (iterationSizeB != chunkSizeB) {
            input = af::array(m, iterationSizeB, t.type());
        }

        for (long j = 0; j < m; j++) {
            input(j, span, span, span) = t(af::seq(i + j, i + j + iterationSizeB - 1));
        }

        af::array distance = af::array(0, t.type());
        af::array pidx = af::array(0, af::dtype::u32);

        af::array mask = tsa::matrix::generateMask(m, iterationSizeB, i, chunkSizeA - m + 1);

        for (long k = 0; k < n; k += chunkSizeA) {
            long start = k / chunkSizeA * (chunkSizeA - m + 1);
            long iterationSizeA = std::min(chunkSizeA, n - start);
            long end = start + iterationSizeA - 1;
            af::array tChunk = t(seq(start, end));
            af::array aux;
            af::array mean;
            af::array stdev;
            tsa::matrix::meanStdev(tChunk, aux, m, mean, stdev);

            gfor(af::seq idx, iterationSizeB) {
                af::array distanceTmp;
                af::array pidxTmp;

                tsa::matrix::mass(input(span, idx, span, span), tChunk, m, aux, mean, stdev,
                                  mask(span, af::seq(iterationSizeA - m + 1)), distanceTmp, pidxTmp);

                pidxTmp += start;

                distance = af::join(1, distance, distanceTmp);
                pidx = af::join(1, pidx, pidxTmp);
            }
            af::sync();
        }

        af::array idx;
        af::array min;

        af::min(min, idx, distance, 1);

        af::dim4 dims = min.dims();
        double sliceStride = dims[0] * dims[1];

        array bidx = af::iota(af::dim4(dims[0], dims[1]));

        af::array flatIndices = af::flat(idx * sliceStride + bidx);

        af::array flatPidx = af::flat(pidx);
        af::array vFromPidx = flatPidx(flatIndices);

        profile = af::join(0, profile, min);
        index = af::join(0, index, af::moddims(vFromPidx, af::dim4(dims[0], dims[1])));
    }
}

void stomp_parallel(af::array t, long m, af::array &profile, af::array &index) {
    long n = t.dims(0);

    af::array aux;
    af::array mean;
    af::array stdev;

    tsa::matrix::meanStdev(t, aux, m, mean, stdev);

    af::array input = af::array(m, n - m + 1, t.type());

    for (int i = 0; i < m; i++) {
        input(i, span, span, span) = t(af::seq(i, n - m + i));
    }

    af::array mask = tsa::matrix::generateMask(m, n - m + 1, 0, n - m + 1);

    gfor(af::seq idx, n - m + 1) {
        tsa::matrix::mass(input(span, idx, span, span), t, m, aux, mean, stdev, mask, profile, index);
    }
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

#ifdef __cplusplus
extern "C" {
#endif

void find_best_n_discords(double *profile, unsigned int *index, long *length_profile, long *n,
                          double *discord_distances, int *discord_indices, int *subsequence_indices) {
    af::array discords;
    af::array discordIndices;
    af::array subsequenceIndices;
    tsa::matrix::findBestNDiscords(array(*length_profile, profile), array(*length_profile, index), *n, discords,
                                   discordIndices, subsequenceIndices);
    discords.host(discord_distances);
    discordIndices.host(discord_indices);
    subsequenceIndices.host(subsequence_indices);
}

void find_best_n_motifs(double *profile, unsigned int *index, long *length_profile, long *n, double *motif_distances,
                        int *motif_indices, int *subsequence_indices) {
    af::array motifs;
    af::array motifIndices;
    af::array subsequenceIndices;
    tsa::matrix::findBestNMotifs(array(*length_profile, profile), array(*length_profile, index), *n, motifs,
                                 motifIndices, subsequenceIndices);
    motifs.host(motif_distances);
    motifIndices.host(motif_indices);
    subsequenceIndices.host(subsequence_indices);
}

void stomp(double *ta, double *tb, long *lta, long *ltb, long *m, double *p, unsigned int *i) {
    af::array distance;
    af::array index;
    tsa::matrix::stomp(array(*lta, ta), array(*ltb, tb), *m, distance, index);
    distance.host(p);
    index.host(i);
}

void stomp_self_join(double *ta, long *lta, long *m, double *p, unsigned int *i) {
    af::array distance;
    af::array index;
    tsa::matrix::stomp(array(*lta, ta), *m, distance, index);
    distance.host(p);
    index.host(i);
}

void info() { af::info(); }

void set_backend(int *backend) {
    switch (*backend) {
        case 0:
            af::setBackend(AF_BACKEND_CPU);
            break;
        case 1:
            af::setBackend(AF_BACKEND_OPENCL);
            break;
        case 2:
            af::setBackend(AF_BACKEND_CUDA);
            break;
        default:
            af::setBackend(AF_BACKEND_CPU);
            break;
    }
}

void set_device(int *device) { af::setDevice(*device); }

JNIEXPORT void JNICALL Java_tsa_Matrix_findBestNDiscords(JNIEnv *env, jobject thisObj, jdoubleArray profile,
                                                         jintArray index, jlong lengthProfile, jlong n,
                                                         jdoubleArray jDiscordDistances, jintArray jDiscordIndices,
                                                         jintArray jSubsequenceIndices) {
    af::array discords;
    af::array discordIndices;
    af::array subsequenceIndices;

    jdouble inputP[lengthProfile];
    jint inputI[lengthProfile];

    env->GetDoubleArrayRegion(profile, 0, lengthProfile, &inputP[0]);
    env->GetIntArrayRegion(index, 0, lengthProfile, &inputI[0]);

    tsa::matrix::findBestNDiscords(array(lengthProfile, inputP), array(lengthProfile, inputI), n, discords,
                                   discordIndices, subsequenceIndices);

    jdouble inputDiscords[n];
    jint inputDiscordIndices[n];
    jint inputSubsequenceIndices[n];

    discords.host(inputDiscords);
    discordIndices.host(inputDiscordIndices);
    subsequenceIndices.host(inputSubsequenceIndices);

    env->SetDoubleArrayRegion(jDiscordDistances, 0, n, &inputDiscords[0]);
    env->SetIntArrayRegion(jDiscordIndices, 0, n, &inputDiscordIndices[0]);
    env->SetIntArrayRegion(jSubsequenceIndices, 0, n, &inputSubsequenceIndices[0]);

    return;
}

JNIEXPORT void JNICALL Java_tsa_Matrix_findBestNMotifs(JNIEnv *env, jobject thisObj, jdoubleArray profile,
                                                       jintArray index, jlong lengthProfile, jlong n,
                                                       jdoubleArray jMotifDistances, jintArray jMotifIndices,
                                                       jintArray jSubsequenceIndices) {
    af::array motifs;
    af::array motifIndices;
    af::array subsequenceIndices;

    jdouble inputP[lengthProfile];
    jint inputI[lengthProfile];

    env->GetDoubleArrayRegion(profile, 0, lengthProfile, &inputP[0]);
    env->GetIntArrayRegion(index, 0, lengthProfile, &inputI[0]);

    tsa::matrix::findBestNMotifs(array(lengthProfile, inputP), array(lengthProfile, inputI), n, motifs, motifIndices,
                                 subsequenceIndices);

    jdouble inputMotifs[n];
    jint inputMotifIndices[n];
    jint inputSubsequenceIndices[n];

    motifs.host(inputMotifs);
    motifIndices.host(inputMotifIndices);
    subsequenceIndices.host(inputSubsequenceIndices);

    env->SetDoubleArrayRegion(jMotifDistances, 0, n, &inputMotifs[0]);
    env->SetIntArrayRegion(jMotifIndices, 0, n, &inputMotifIndices[0]);
    env->SetIntArrayRegion(jSubsequenceIndices, 0, n, &inputSubsequenceIndices[0]);

    return;
}

JNIEXPORT void JNICALL Java_tsa_Matrix_stomp(JNIEnv *env, jobject thisObj, jdoubleArray ta, jdoubleArray tb, jlong lta,
                                             jlong ltb, jlong m, jdoubleArray p, jintArray i) {
    af::array distance;
    af::array index;

    jdouble input_ta[lta];
    jdouble input_tb[ltb];

    env->GetDoubleArrayRegion(ta, 0, lta, &input_ta[0]);
    env->GetDoubleArrayRegion(tb, 0, ltb, &input_tb[0]);

    af::array ata = array(lta, input_ta);
    af::array atb = array(ltb, input_tb);

    long subsequence = m;

    tsa::matrix::stomp(ata, atb, subsequence, distance, index);

    jdouble input_p[ltb - m + 1];
    jint input_i[ltb - m + 1];

    distance.host(input_p);
    index.host(input_i);

    env->SetDoubleArrayRegion(p, 0, ltb - m + 1, &input_p[0]);
    env->SetIntArrayRegion(i, 0, ltb - m + 1, &input_i[0]);

    return;
}

JNIEXPORT void JNICALL Java_tsa_Matrix_stompSelfJoin(JNIEnv *env, jobject thisObj, jdoubleArray ta, jlong lta, jlong m,
                                                     jdoubleArray p, jintArray i) {
    af::array distance;
    af::array index;

    jdouble input_ta[lta];

    env->GetDoubleArrayRegion(ta, 0, lta, &input_ta[0]);

    af::array ata = array(lta, input_ta);

    long subsequence = m;

    tsa::matrix::stomp(ata, subsequence, distance, index);

    jdouble input_p[lta - m + 1];
    jint input_i[lta - m + 1];

    distance.host(input_p);
    index.host(input_i);

    env->SetDoubleArrayRegion(p, 0, lta - m + 1, &input_p[0]);
    env->SetIntArrayRegion(i, 0, lta - m + 1, &input_i[0]);

    return;
}

JNIEXPORT void JNICALL Java_tsa_Library_info(JNIEnv *env, jobject thisObj) { af::info(); }

JNIEXPORT void JNICALL Java_tsa_Library_setBackend(JNIEnv *env, jobject thisObj, jint backend) {
    switch (backend) {
        case 0:
            af::setBackend(AF_BACKEND_CPU);
            break;
        case 1:
            af::setBackend(AF_BACKEND_OPENCL);
            break;
        case 2:
            af::setBackend(AF_BACKEND_CUDA);
            break;
        default:
            af::setBackend(AF_BACKEND_CPU);
            break;
    }
}
JNIEXPORT void JNICALL Java_tsa_Library_setDevice(JNIEnv *env, jobject thisObj, jint device) { af::setDevice(device); }

#ifdef __cplusplus
}
#endif
