// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "tsa.h"
#include "gtest/gtest.h"

#define EPSILON 1e-6

TEST(MatrixTests, SlidingDotProduct)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {10, 10, 10, 11, 12, 11, 10, 10, 11, 12, 11, 10, 10, 10};
    af::array t = af::array(14, data);

    double query[] = {10, 11, 12};
    af::array q = af::array(3, query);
    
    af::array sdp = tsa::matrix::slidingDotProduct(q, t);
    ASSERT_EQ(sdp.dims(0), 12);

    double expected[] = {330, 342, 365, 374, 361, 340, 342, 365, 374, 361, 340, 330};
    double *result = sdp.host<double>();
    for(int i = 0; i < 12; i++) {
        ASSERT_EQ(result[i], expected[i]);
    }
}

TEST(MatrixTests, MeanStdev)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {10, 10, 10, 11, 12, 11, 10, 10, 11, 12, 11, 10, 10, 10};
    af::array t = af::array(14, data);

    long m = 3;
    af::array mean;
    af::array stdev;

    tsa::matrix::meanStdev(t, m, &mean, &stdev);

    ASSERT_EQ(mean.dims(0), 12);
    ASSERT_EQ(stdev.dims(0), 12);

    double expectedMean[] = {10, 10.333333333, 11, 11.333333333, 11, 10.333333333, 10.333333333, 11, 11.333333333, 11, 10.333333333, 10};
    double expectedStdev[] = {0, 0.471404521, 0.816496581, 0.471404521, 0.816496581, 0.471404521, 0.471404521, 0.816496581, 0.471404521, 0.816496581, 0.471404521, 0};    
    double *resultingMean = mean.host<double>();
    double *resultingStdev = stdev.host<double>();    
    for(int i = 0; i < 12; i++) {
        ASSERT_NEAR(resultingMean[i], expectedMean[i], EPSILON);
        ASSERT_NEAR(resultingStdev[i], expectedStdev[i], EPSILON);        
    }
}

TEST(MatrixTests, GenerateMask)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    tsa::matrix::generateMask(3, 4, 2, 8);
}

TEST(MatrixTests, CalculateDistanceProfile)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {10, 10, 10, 11, 12, 11, 10, 10, 11, 12, 11, 10, 10, 10};
    af::array t = af::array(14, data);

    double query[] = {10, 11, 12};
    af::array q = af::array(3, query);

    long m = 3;
    af::array mean;
    af::array stdev;
    af::array aux;

    af::array qt = tsa::matrix::slidingDotProduct(q, t);
    tsa::matrix::meanStdev(t, &aux, m, &mean, &stdev);

    af::array distance;
    af::array index;

    tsa::matrix::calculateDistanceProfile(m, qt, aux, af::sum(q), af::sum(af::pow(q, 2)), mean, stdev, &distance, &index);

    double expectedDistance = 19.0552097998;
    int expectedIndex = 7;    
    double *resultingDistance = distance.host<double>();

    unsigned int resultingIndex;
    index.host(&resultingIndex);    

    ASSERT_NEAR(*resultingDistance, expectedDistance, EPSILON);
    ASSERT_EQ(resultingIndex, expectedIndex);
}

TEST(MatrixTests, CalculateDistanceProfileMiddle)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {10, 10, 10, 11, 12, 11, 10, 10, 11, 12, 11, 10, 10, 10};
    af::array t = af::array(14, data);

    double query[] = {10, 11, 12};
    af::array q = af::array(3, query);

    long m = 3;
    af::array mean;
    af::array stdev;
    af::array aux;

    af::array qt = tsa::matrix::slidingDotProduct(q, t);
    tsa::matrix::meanStdev(t, &aux, m, &mean, &stdev);

    af::array distance;
    af::array index;

    af::array mask = tsa::matrix::generateMask(m, 1, 0, 12);

    tsa::matrix::calculateDistanceProfile(m, qt, aux, af::sum(q), af::sum(af::pow(q, 2)), mean, stdev, mask, &distance, &index);

    double expectedDistance = 19.0552097998;
    int expectedIndex = 7;    
    double *resultingDistance = distance.host<double>();

    unsigned int resultingIndex;
    index.host(&resultingIndex);    

    ASSERT_NEAR(*resultingDistance, expectedDistance, EPSILON);
    ASSERT_EQ(resultingIndex, expectedIndex);
}

TEST(MatrixTests, MassIgnoreTrivial)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {10, 10, 10, 11, 12, 11, 10, 10, 11, 12, 11, 10, 10, 10};
    af::array t = af::array(14, data);

    double query[] = {10, 11, 12};
    af::array q = af::array(3, query);

    long m = 3;

    af::array mean;
    af::array stdev;
    af::array aux;

    af::array qt = tsa::matrix::slidingDotProduct(q, t);
    tsa::matrix::meanStdev(t, &aux, m, &mean, &stdev);

    af::array distance;
    af::array index;

    af::array mask = tsa::matrix::generateMask(m, 1, 0, 12);

    tsa::matrix::mass(q, t, m, aux, mean, stdev, mask, &distance, &index);

    double expectedDistance = 0.00000004712;
    int expectedIndex = 7;    
    double *resultingDistance = distance.host<double>();

    unsigned int resultingIndex;
    index.host(&resultingIndex);    

    ASSERT_NEAR(*resultingDistance, expectedDistance, EPSILON);
    ASSERT_EQ(resultingIndex, expectedIndex);
}

TEST(MatrixTests, MassConsiderTrivial)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {10, 10, 10, 11, 12, 11, 10, 10, 11, 12, 11, 10, 10, 10};
    af::array t = af::array(14, data);

    double query[] = {10, 11, 12};
    af::array q = af::array(3, query);

    long m = 3;

    af::array mean;
    af::array stdev;
    af::array aux;

    af::array qt = tsa::matrix::slidingDotProduct(q, t);
    tsa::matrix::meanStdev(t, &aux, m, &mean, &stdev);

    af::array distance;
    af::array index;

    tsa::matrix::mass(q, t, m, aux, mean, stdev, &distance, &index);

    double expectedDistance = 0.00000004712;
    int expectedIndex = 7;    
    double *resultingDistance = distance.host<double>();

    unsigned int resultingIndex;
    index.host(&resultingIndex);    

    ASSERT_NEAR(*resultingDistance, expectedDistance, EPSILON);
    ASSERT_EQ(resultingIndex, expectedIndex);
}

TEST(MatrixTests, StampOneTimeSeries)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {10, 10, 10, 11, 12, 11, 10, 10, 11, 12, 11, 10, 10, 10};
    af::array t = af::array(14, data);

    long m = 3;

    af::array distance;
    af::array index;

    tsa::matrix::stamp(t, m, &distance, &index);

    unsigned int expectedIndex[] = {11, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 0};    
    double *resultingDistance = distance.host<double>();

    unsigned int resultingIndex[12];
    index.host(&resultingIndex);    

    for(int i = 0; i < 12; i++){
        ASSERT_NEAR(resultingDistance[i], 0.0, EPSILON);
        ASSERT_EQ(resultingIndex[i], expectedIndex[i]);
    }
}

TEST(MatrixTests, StampTwoTimeSeries)
{
    af::setBackend(af::Backend::AF_BACKEND_CPU);
    double data[] = {10, 10, 10, 11, 12, 11, 10, 10, 11, 12, 11, 10, 10, 10};
    af::array t = af::array(14, data);

    long m = 3;

    af::array distance;
    af::array index;

    tsa::matrix::stamp(t, t, m, &distance, &index);

    unsigned int expectedIndex[] = {11, 1, 2, 8, 9, 5, 1, 2, 8, 9, 5, 11};    
    double *resultingDistance = distance.host<double>();

    unsigned int resultingIndex[12];
    index.host(&resultingIndex);    

    for(int i = 0; i < 12; i++){
        ASSERT_NEAR(resultingDistance[i], 0.0, EPSILON);
        ASSERT_EQ(resultingIndex[i], expectedIndex[i]);
    }
}