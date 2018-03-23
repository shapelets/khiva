// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <tsa/matrix.h>
#include "tsaTest.h"

void slidingDotProduct() {
    float data[] = {10, 10, 10, 11, 12, 11, 10, 10, 11, 12, 11, 10, 10, 10};
    af::array t = af::array(14, data);
    af::array tss = af::tile(t, 1, 2);

    float query[] = {10, 11, 12};
    af::array q = af::array(3, query);

    af::array sdp = tsa::matrix::slidingDotProduct(q, tss);
    ASSERT_EQ(sdp.dims(0), 12);
    ASSERT_EQ(sdp.dims(1), 2);

    float expected[] = {330, 342, 365, 374, 361, 340, 342, 365, 374, 361, 340, 330};
    float *result = sdp.host<float>();
    for (int i = 0; i < 24; i++) {
        ASSERT_EQ(result[i % 12], expected[i % 12]);
    }
}

void meanStdev() {
    float data[] = {10, 10, 11, 11, 12, 11, 10, 10, 11, 12, 11, 10, 10, 11};
    af::array t = af::array(14, data);
    af::array tss = af::tile(t, 1, 2);

    long m = 3;
    af::array mean;
    af::array stdev;

    tsa::matrix::meanStdev(tss, m, mean, stdev);

    ASSERT_EQ(mean.dims(0), 12);
    ASSERT_EQ(mean.dims(1), 2);
    ASSERT_EQ(stdev.dims(0), 12);
    ASSERT_EQ(stdev.dims(1), 2);

    float expectedMean[] = {10.333333333, 10.666666666, 11.333333333, 11.333333333, 11,           10.333333333,
                            10.333333333, 11,           11.333333333, 11,           10.333333333, 10.333333333};
    float expectedStdev[] = {0.471404521, 0.471404521, 0.471404521, 0.471404521, 0.816496581, 0.471404521,
                             0.471404521, 0.816496581, 0.471404521, 0.816496581, 0.471404521, 0.471404521};
    float *resultingMean = mean.host<float>();
    float *resultingStdev = stdev.host<float>();
    for (int i = 0; i < 24; i++) {
        ASSERT_NEAR(resultingMean[i % 12], expectedMean[i % 12], EPSILON * 3e3);
        ASSERT_NEAR(resultingStdev[i % 12], expectedStdev[i % 12], EPSILON * 3e3);
    }
}

void generateMask() {
    af::array mask = tsa::matrix::generateMask(3, 4, 2, 8, 2);

    ASSERT_EQ(mask.dims(0), 4);
    ASSERT_EQ(mask.dims(1), 8);
    ASSERT_EQ(mask.dims(2), 2);

    float *maskCalculated = af::transpose(mask).as(af::dtype::f32).host<float>();

    float maskExpected[] = {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0,
                            0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0};

    for (int i = 0; i < 64; i++) {
        ASSERT_EQ(maskCalculated[i % 32], maskExpected[i % 32]);
    }
}

void calculateDistanceProfile() {
    float data[] = {10, 10, 11, 11, 12, 11, 10, 10, 11, 12, 11, 10, 10, 11};
    af::array t = af::array(14, data);
    af::array tss = af::tile(t, 1, 2);

    float query[] = {10, 11, 12};
    af::array q = af::array(3, query);

    long m = 3;
    af::array mean;
    af::array stdev;
    af::array aux;

    af::array qtss = tsa::matrix::slidingDotProduct(q, tss);
    tsa::matrix::meanStdev(tss, aux, m, mean, stdev);

    af::array distance;
    af::array index;

    tsa::matrix::calculateDistanceProfile(m, qtss, aux, af::sum(q, 0), af::sum(af::pow(q, 2), 0), mean, stdev, distance,
                                          index);

    float expectedDistance = 19.0552097998;
    int expectedIndex = 7;

    ASSERT_EQ(distance.dims(), af::dim4(1, 2, 1, 1));
    ASSERT_EQ(index.dims(), af::dim4(1, 2, 1, 1));

    float *resultingDistance = distance.host<float>();

    unsigned int resultingIndex[2];
    index.host(&resultingIndex);

    ASSERT_NEAR(resultingDistance[0], expectedDistance, EPSILON * 1e1);
    ASSERT_NEAR(resultingDistance[1], expectedDistance, EPSILON * 1e1);
    ASSERT_EQ(resultingIndex[0], expectedIndex);
    ASSERT_EQ(resultingIndex[1], expectedIndex);
}

void calculateDistanceProfileMiddle() {
    float data[] = {10, 10, 10, 11, 12, 11, 10, 10, 11, 12, 11, 10, 10, 10};
    af::array t = af::array(14, data);
    af::array tss = af::tile(t, 1, 2);

    float query[] = {10, 11, 12};
    af::array q = af::array(3, query);

    long m = 3;
    af::array mean;
    af::array stdev;
    af::array aux;

    af::array qtss = tsa::matrix::slidingDotProduct(q, tss);
    tsa::matrix::meanStdev(tss, aux, m, mean, stdev);

    af::array distance;
    af::array index;

    af::array mask = tsa::matrix::generateMask(m, 1, 0, 12, 2);

    tsa::matrix::calculateDistanceProfile(m, qtss, aux, af::sum(q, 0), af::sum(af::pow(q, 2), 0), mean, stdev, mask,
                                          distance, index);

    float expectedDistance = 19.0552097998;
    int expectedIndex = 7;

    ASSERT_EQ(distance.dims(), af::dim4(1, 2, 1, 1));
    ASSERT_EQ(index.dims(), af::dim4(1, 2, 1, 1));

    float *resultingDistance = distance.host<float>();

    unsigned int resultingIndex[2];
    index.host(&resultingIndex);

    ASSERT_NEAR(resultingDistance[0], expectedDistance, EPSILON * 1e1);
    ASSERT_NEAR(resultingDistance[1], expectedDistance, EPSILON * 1e1);
    ASSERT_EQ(resultingIndex[0], expectedIndex);
    ASSERT_EQ(resultingIndex[1], expectedIndex);
}

void massIgnoreTrivial() {
    float data[] = {10, 10, 10, 11, 12, 11, 10, 10, 11, 12, 11, 10, 10, 10};
    af::array t = af::array(14, data);
    af::array tss = af::tile(t, 1, 2);

    float query[] = {10, 11, 12};
    af::array q = af::array(3, query);

    long m = 3;

    af::array mean;
    af::array stdev;
    af::array aux;

    tsa::matrix::meanStdev(tss, aux, m, mean, stdev);

    af::array distance;
    af::array index;

    af::array mask = tsa::matrix::generateMask(m, 1, 0, 12, 2);

    tsa::matrix::mass(q, tss, m, aux, mean, stdev, mask, distance, index);

    float expectedDistance = 0.0;
    int expectedIndex = 7;

    ASSERT_EQ(distance.dims(), af::dim4(1, 2, 1, 1));
    ASSERT_EQ(index.dims(), af::dim4(1, 2, 1, 1));

    float *resultingDistance = distance.host<float>();

    unsigned int resultingIndex[2];
    index.host(&resultingIndex);

    ASSERT_NEAR(resultingDistance[0], expectedDistance, 1e-2);
    ASSERT_NEAR(resultingDistance[1], expectedDistance, 1e-2);
    ASSERT_EQ(resultingIndex[0], expectedIndex);
    ASSERT_EQ(resultingIndex[1], expectedIndex);
}

void massConsiderTrivial() {
    float data[] = {10, 10, 10, 11, 12, 11, 10, 10, 11, 12, 11, 10, 10, 10};
    af::array t = af::array(14, data);
    af::array tss = af::tile(t, 1, 2);

    float query[] = {10, 11, 12};
    af::array q = af::array(3, query);

    long m = 3;

    af::array mean;
    af::array stdev;
    af::array aux;

    tsa::matrix::meanStdev(tss, aux, m, mean, stdev);

    af::array distance;
    af::array index;

    tsa::matrix::mass(q, tss, m, aux, mean, stdev, distance, index);

    float expectedDistance = 0.0;
    int expectedIndex = 7;

    ASSERT_EQ(distance.dims(), af::dim4(1, 2, 1, 1));
    ASSERT_EQ(index.dims(), af::dim4(1, 2, 1, 1));

    float *resultingDistance = distance.host<float>();

    unsigned int resultingIndex[2];
    index.host(&resultingIndex);

    ASSERT_NEAR(resultingDistance[0], expectedDistance, 1e-2);
    ASSERT_NEAR(resultingDistance[1], expectedDistance, 1e-2);
    ASSERT_EQ(resultingIndex[0], expectedIndex);
    ASSERT_EQ(resultingIndex[1], expectedIndex);
}

void stompIgnoreTrivialOneSeries() {
    float data[] = {10, 10, 11, 11, 10, 11, 10, 10, 11, 11, 10, 11, 10, 10};
    af::array tss = af::array(14, data);

    long m = 3;

    af::array distance;
    af::array index;

    tsa::matrix::stomp(tss, m, distance, index);

    unsigned int expectedIndex[] = {6, 7, 8, 9, 10, 11, 0, 1, 2, 3, 4, 5};

    ASSERT_EQ(distance.dims(), af::dim4(12, 1, 1, 1));
    ASSERT_EQ(index.dims(), af::dim4(12, 1, 1, 1));

    float *resultingDistance = distance.host<float>();

    unsigned int resultingIndex[12];
    index.host(&resultingIndex);

    for (int i = 0; i < 12; i++) {
        ASSERT_NEAR(resultingDistance[i], 0.0, 2e-2);
        ASSERT_EQ(resultingIndex[i], expectedIndex[i]);
    }
}

void stompIgnoreTrivialMultipleSeries() {
    float data[] = {10, 10, 11, 11, 10, 11, 10, 10, 11, 11, 10, 11, 10, 10,
                    11, 10, 10, 11, 10, 11, 11, 10, 11, 11, 10, 10, 11, 10};
    af::array tss = af::array(14, 2, data);

    long m = 3;

    af::array distance;
    af::array index;

    tsa::matrix::stomp(tss, m, distance, index);

    unsigned int expectedIndex[] = {6, 7, 8, 9, 10, 11, 0, 1, 2, 3, 4, 5, 9, 10, 11, 6, 7, 8, 3, 4, 5, 0, 1, 2};

    ASSERT_EQ(distance.dims(), af::dim4(12, 2, 1, 1));
    ASSERT_EQ(index.dims(), af::dim4(12, 2, 1, 1));

    float *resultingDistance = distance.host<float>();

    unsigned int resultingIndex[24];
    index.host(&resultingIndex);

    for (int i = 0; i < 24; i++) {
        ASSERT_NEAR(resultingDistance[i], 0.0, 2e-2);
        ASSERT_EQ(resultingIndex[i], expectedIndex[i]);
    }
}

void stompConsiderTrivialOneSeries() {
    float data[] = {10, 10, 11, 11, 10, 11, 10, 10};
    af::array t = af::array(8, data);

    long m = 3;

    af::array distance;
    af::array index;

    tsa::matrix::stomp(t, t, m, distance, index);

    unsigned int expectedIndex[] = {0, 1, 2, 3, 4, 5};
    float *resultingDistance = distance.host<float>();

    unsigned int resultingIndex[6];
    index.host(&resultingIndex);

    for (int i = 0; i < 6; i++) {
        ASSERT_NEAR(resultingDistance[i], 0.0, 1e-2);
        ASSERT_EQ(resultingIndex[i], expectedIndex[i]);
    }
}

void stompConsiderTrivialOneSeries2() {
    float dataA[] = {10, 11, 10, 11, 10, 11, 10, 11};
    af::array ta = af::array(4, 2, dataA);

    float dataB[] = {10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11};
    af::array tb = af::array(8, 2, dataB);

    long m = 3;

    af::array distance;
    af::array index;

    tsa::matrix::stomp(ta, tb, m, distance, index);

    unsigned int expectedIndex[] = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
    float *resultingDistance = distance.host<float>();

    unsigned int resultingIndex[24];
    index.host(&resultingIndex);

    for (int i = 0; i < 24; i++) {
        ASSERT_NEAR(resultingDistance[i], 0.0, 1e-2);
        ASSERT_EQ(resultingIndex[i], expectedIndex[i]);
    }
}

void stompConsiderTrivialMultipleSeries() {
    float dataA[] = {10, 10, 11, 11, 10, 11, 10, 10, 10, 10, 11, 11, 10, 11, 10, 10, 11, 10, 10, 11, 10, 11, 11, 10};
    af::array ta = af::array(8, 3, dataA);

    float dataB[] = {10, 10, 11, 11, 10, 11, 10, 10, 11, 10, 10, 11, 10, 11, 11, 10};
    af::array tb = af::array(8, 2, dataB);

    long m = 3;

    af::array distance;
    af::array index;

    tsa::matrix::stomp(ta, tb, m, distance, index);

    unsigned int expectedIndex[] = {0, 1, 2, 3, 4, 5, 0, 1, 2, 3, 4, 5, 1, 4, 5, 3, 2, 0,
                                    5, 0, 4, 3, 1, 2, 5, 0, 4, 3, 1, 2, 0, 1, 2, 3, 4, 5};
    float *resultingDistance = distance.host<float>();

    unsigned int resultingIndex[36];
    index.host(&resultingIndex);

    for (int i = 0; i < 36; i++) {
        ASSERT_NEAR(resultingDistance[i], 0.0, 1e-2);
        ASSERT_EQ(resultingIndex[i], expectedIndex[i]);
    }
}

void findBestMotifs() {
    float data_a[] = {10, 10, 10, 10, 10, 10, 9, 10, 10, 10, 10, 10, 11, 10, 9};
    af::array ta = af::array(15, data_a);

    float data_b[] = {10, 11, 10, 9};
    af::array tb = af::array(4, data_b);

    long m = 3;

    af::array distance;
    af::array index;

    tsa::matrix::stomp(ta, tb, m, distance, index);

    af::array motifs;
    af::array motifsIndices;
    af::array subsequenceIndices;

    tsa::matrix::findBestNMotifs(distance, index, 2, motifs, motifsIndices, subsequenceIndices);

    unsigned int *motifsIndicesHost = motifsIndices.host<unsigned int>();
    unsigned int *subsequenceIndicesHost = subsequenceIndices.host<unsigned int>();

    ASSERT_EQ(motifsIndicesHost[0], 12);
    ASSERT_EQ(motifsIndicesHost[1], 11);

    ASSERT_EQ(subsequenceIndicesHost[0], 1);
    ASSERT_EQ(subsequenceIndicesHost[1], 0);
}

void findBestDiscords() {
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data_a[] = {11, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11};
    af::array ta = af::array(12, data_a);

    double data_b[] = {9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9};
    af::array tb = af::array(12, data_b);

    long m = 3;

    af::array distance;
    af::array index;

    tsa::matrix::stomp(ta, tb, m, distance, index);

    af::array discords;
    af::array discordsIndices;
    af::array subsequenceIndices;

    tsa::matrix::findBestNDiscords(distance, index, 2, discords, discordsIndices, subsequenceIndices);

    unsigned int *discordsIndicesHost = discordsIndices.host<unsigned int>();
    unsigned int *subsequenceIndicesHost = subsequenceIndices.host<unsigned int>();

    ASSERT_EQ(subsequenceIndicesHost[0], 9);
    ASSERT_EQ(subsequenceIndicesHost[1], 0);
}

TSA_TEST(MatrixTests, SlidingDotProduct, slidingDotProduct);
TSA_TEST(MatrixTests, MeanStdev, meanStdev);
TSA_TEST(MatrixTests, GenerateMask, generateMask);
TSA_TEST(MatrixTests, CalculateDistanceProfile, calculateDistanceProfile);
TSA_TEST(MatrixTests, CalculateDistanceProfileMiddle, calculateDistanceProfileMiddle);
TSA_TEST(MatrixTests, MassIgnoreTrivial, massIgnoreTrivial);
TSA_TEST(MatrixTests, MassConsiderTrivial, massConsiderTrivial);
TSA_TEST(MatrixTests, StompIgnoreTrivialOneSeries, stompIgnoreTrivialOneSeries);
TSA_TEST(MatrixTests, StompIgnoreTrivialMultipleSeries, stompIgnoreTrivialMultipleSeries);
TSA_TEST(MatrixTests, StompConsiderTrivialOneSeries, stompConsiderTrivialOneSeries);
TSA_TEST(MatrixTests, StompConsiderTrivialOneSeries2, stompConsiderTrivialOneSeries2);
TSA_TEST(MatrixTests, StompConsiderTrivialMultipleSeries, stompConsiderTrivialMultipleSeries);
TSA_TEST(MatrixTests, FindBestMotifs, findBestMotifs);
TSA_TEST(MatrixTests, FindBestDiscords, findBestDiscords);
