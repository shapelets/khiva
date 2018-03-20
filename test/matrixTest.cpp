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

    float query[] = {10, 11, 12};
    af::array q = af::array(3, query);

    af::array sdp = tsa::matrix::slidingDotProduct(q, t);
    ASSERT_EQ(sdp.dims(0), 12);

    float expected[] = {330, 342, 365, 374, 361, 340, 342, 365, 374, 361, 340, 330};
    float *result = sdp.host<float>();
    for (int i = 0; i < 12; i++) {
        ASSERT_EQ(result[i], expected[i]);
    }
}

void meanStdev() {
    float data[] = {10, 10, 11, 11, 12, 11, 10, 10, 11, 12, 11, 10, 10, 11};
    af::array t = af::array(14, data);

    long m = 3;
    af::array mean;
    af::array stdev;

    tsa::matrix::meanStdev(t, m, mean, stdev);

    ASSERT_EQ(mean.dims(0), 12);
    ASSERT_EQ(stdev.dims(0), 12);

    float expectedMean[] = {10.333333333, 10.666666666, 11.333333333, 11.333333333, 11,           10.333333333,
                            10.333333333, 11,           11.333333333, 11,           10.333333333, 10.333333333};
    float expectedStdev[] = {0.471404521, 0.471404521, 0.471404521, 0.471404521, 0.816496581, 0.471404521,
                             0.471404521, 0.816496581, 0.471404521, 0.816496581, 0.471404521, 0.471404521};
    float *resultingMean = mean.host<float>();
    float *resultingStdev = stdev.host<float>();
    for (int i = 0; i < 12; i++) {
        ASSERT_NEAR(resultingMean[i], expectedMean[i], EPSILON * 3e3);
        ASSERT_NEAR(resultingStdev[i], expectedStdev[i], EPSILON * 3e3);
    }
}

void generateMask() {
    af::array mask = tsa::matrix::generateMask(3, 4, 2, 8);

    float *maskCalculated = af::transpose(mask).as(af::dtype::f32).host<float>();

    float maskExpected[] = {0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0,
                            0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0};

    for (int i = 0; i < 32; i++) {
        ASSERT_EQ(maskCalculated[i], maskExpected[i]);
    }
}

void calculateDistanceProfile() {
    float data[] = {10, 10, 11, 11, 12, 11, 10, 10, 11, 12, 11, 10, 10, 11};
    af::array t = af::array(14, data);

    float query[] = {10, 11, 12};
    af::array q = af::array(3, query);

    long m = 3;
    af::array mean;
    af::array stdev;
    af::array aux;

    af::array qt = tsa::matrix::slidingDotProduct(q, t);
    tsa::matrix::meanStdev(t, aux, m, mean, stdev);

    af::array distance;
    af::array index;

    tsa::matrix::calculateDistanceProfile(m, qt, aux, af::sum(q), af::sum(af::pow(q, 2)), mean, stdev, distance, index);

    float expectedDistance = 19.0552097998;
    int expectedIndex = 7;
    float *resultingDistance = distance.host<float>();

    unsigned int resultingIndex;
    index.host(&resultingIndex);

    ASSERT_NEAR(*resultingDistance, expectedDistance, EPSILON * 1e1);
    ASSERT_EQ(resultingIndex, expectedIndex);
}

void calculateDistanceProfileMiddle() {
    float data[] = {10, 10, 10, 11, 12, 11, 10, 10, 11, 12, 11, 10, 10, 10};
    af::array t = af::array(14, data);

    float query[] = {10, 11, 12};
    af::array q = af::array(3, query);

    long m = 3;
    af::array mean;
    af::array stdev;
    af::array aux;

    af::array qt = tsa::matrix::slidingDotProduct(q, t);
    tsa::matrix::meanStdev(t, aux, m, mean, stdev);

    af::array distance;
    af::array index;

    af::array mask = tsa::matrix::generateMask(m, 1, 0, 12);

    tsa::matrix::calculateDistanceProfile(m, qt, aux, af::sum(q), af::sum(af::pow(q, 2)), mean, stdev, mask, distance,
                                          index);

    float expectedDistance = 19.0552097998;
    int expectedIndex = 7;
    float *resultingDistance = distance.host<float>();

    unsigned int resultingIndex;
    index.host(&resultingIndex);

    ASSERT_NEAR(*resultingDistance, expectedDistance, EPSILON * 1e1);
    ASSERT_EQ(resultingIndex, expectedIndex);
}

void massIgnoreTrivial() {
    float data[] = {10, 10, 10, 11, 12, 11, 10, 10, 11, 12, 11, 10, 10, 10};
    af::array t = af::array(14, data);

    float query[] = {10, 11, 12};
    af::array q = af::array(3, query);

    long m = 3;

    af::array mean;
    af::array stdev;
    af::array aux;

    af::array qt = tsa::matrix::slidingDotProduct(q, t);
    tsa::matrix::meanStdev(t, aux, m, mean, stdev);

    af::array distance;
    af::array index;

    af::array mask = tsa::matrix::generateMask(m, 1, 0, 12);

    tsa::matrix::mass(q, t, m, aux, mean, stdev, mask, distance, index);

    float expectedDistance = 0.0;
    int expectedIndex = 7;
    float *resultingDistance = distance.host<float>();

    unsigned int resultingIndex;
    index.host(&resultingIndex);

    ASSERT_NEAR(*resultingDistance, expectedDistance, 1e-2);
    ASSERT_EQ(resultingIndex, expectedIndex);
}

void massConsiderTrivial() {
    float data[] = {10, 10, 10, 11, 12, 11, 10, 10, 11, 12, 11, 10, 10, 10};
    af::array t = af::array(14, data);

    float query[] = {10, 11, 12};
    af::array q = af::array(3, query);

    long m = 3;

    af::array mean;
    af::array stdev;
    af::array aux;

    af::array qt = tsa::matrix::slidingDotProduct(q, t);
    tsa::matrix::meanStdev(t, aux, m, mean, stdev);

    af::array distance;
    af::array index;

    tsa::matrix::mass(q, t, m, aux, mean, stdev, distance, index);

    float expectedDistance = 0.0;
    int expectedIndex = 7;
    float *resultingDistance = distance.host<float>();

    unsigned int resultingIndex;
    index.host(&resultingIndex);

    ASSERT_NEAR(*resultingDistance, expectedDistance, 1e-2);
    ASSERT_EQ(resultingIndex, expectedIndex);
}

void stompOneTimeSeries() {
    float data[] = {10, 10, 11, 11, 10, 11, 10, 10, 11, 11, 10, 11, 10, 10};
    af::array t = af::array(14, data);

    long m = 3;

    af::array distance;
    af::array index;

    tsa::matrix::stomp(t, m, distance, index);

    unsigned int expectedIndex[] = {6, 7, 8, 9, 10, 11, 0, 1, 2, 3, 4, 5};
    float *resultingDistance = distance.host<float>();

    unsigned int resultingIndex[12];
    index.host(&resultingIndex);

    for (int i = 0; i < 12; i++) {
        ASSERT_NEAR(resultingDistance[i], 0.0, 1e-2);
        ASSERT_EQ(resultingIndex[i], expectedIndex[i]);
    }
}

void stompTwoTimeSeries() {
    float data[] = {10, 10, 11, 11, 10, 11, 10};
    af::array t = af::array(7, data);

    long m = 3;

    af::array distance;
    af::array index;

    tsa::matrix::stomp(t, t, m, distance, index);

    unsigned int expectedIndex[] = {0, 1, 2, 3, 4};
    int backend = af::getActiveBackend();
    int device = af::getDevice();
    float *resultingDistance = distance.host<float>();

    unsigned int resultingIndex[5];
    index.host(&resultingIndex);

    for (int i = 0; i < 5; i++) {
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
    double data_a[] = {10, 11, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 10};
    af::array ta = af::array(14, data_a);

    double data_b[] = {10, 9, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 9, 10};
    af::array tb = af::array(14, data_b);

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

    ASSERT_EQ(subsequenceIndicesHost[0], 0);
    ASSERT_EQ(subsequenceIndicesHost[1], 11);
}

TSA_TEST(MatrixTests, SlidingDotProduct, slidingDotProduct);
TSA_TEST(MatrixTests, MeanStdev, meanStdev);
TSA_TEST(MatrixTests, GenerateMask, generateMask);
TSA_TEST(MatrixTests, CalculateDistanceProfile, calculateDistanceProfile);
TSA_TEST(MatrixTests, CalculateDistanceProfileMiddle, calculateDistanceProfileMiddle);
TSA_TEST(MatrixTests, MassIgnoreTrivial, massIgnoreTrivial);
TSA_TEST(MatrixTests, MassConsiderTrivial, massConsiderTrivial);
TSA_TEST(MatrixTests, StompOneTimeSeries, stompOneTimeSeries);
TSA_TEST(MatrixTests, StompTwoTimeSeries, stompTwoTimeSeries);
TSA_TEST(MatrixTests, FindBestMotifs, findBestMotifs);
TSA_TEST(MatrixTests, FindBestDiscords, findBestDiscords);
