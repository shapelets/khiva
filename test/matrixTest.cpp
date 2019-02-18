// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <khiva/matrix.h>
#include <stdexcept>
#include "khivaTest.h"

void slidingDotProduct() {
    float data[] = {10, 10, 10, 11, 12, 11, 10, 10, 11, 12, 11, 10, 10, 10};
    af::array t = af::array(14, data);
    af::array tss = af::tile(t, 1, 2);

    float query[] = {10, 11, 12};
    af::array q = af::array(3, query);

    af::array sdp = khiva::matrix::slidingDotProduct(q, tss);
    ASSERT_EQ(sdp.dims(0), 12);
    ASSERT_EQ(sdp.dims(1), 2);

    float expected[] = {330, 342, 365, 374, 361, 340, 342, 365, 374, 361, 340, 330};
    float *result = sdp.host<float>();
    for (int i = 0; i < 24; i++) {
        ASSERT_EQ(result[i], expected[i % 12]);
    }
}

void meanStdev() {
    float data[] = {10, 10, 11, 11, 12, 11, 10, 10, 11, 12, 11, 10, 10, 11};
    af::array t = af::array(14, data);
    af::array tss = af::tile(t, 1, 2);

    long m = 3;
    af::array mean;
    af::array stdev;

    khiva::matrix::meanStdev(tss, m, mean, stdev);

    ASSERT_EQ(mean.dims(0), 12);
    ASSERT_EQ(mean.dims(1), 2);
    ASSERT_EQ(stdev.dims(0), 12);
    ASSERT_EQ(stdev.dims(1), 2);

    float expectedMean[] = {10.333333333f,
                            10.666666666f,
                            11.333333333f,
                            11.333333333f,
                            11,
                            10.333333333f,
                            10.333333333f,
                            11,
                            11.333333333f,
                            11,
                            10.333333333f,
                            10.333333333f};
    float expectedStdev[] = {0.471404521f, 0.471404521f, 0.471404521f, 0.471404521f, 0.816496581f, 0.471404521f,
                             0.471404521f, 0.816496581f, 0.471404521f, 0.816496581f, 0.471404521f, 0.471404521f};
    float *resultingMean = mean.host<float>();
    float *resultingStdev = stdev.host<float>();
    for (int i = 0; i < 24; i++) {
        ASSERT_NEAR(resultingMean[i], expectedMean[i % 12], EPSILON * 3e3);
        ASSERT_NEAR(resultingStdev[i], expectedStdev[i % 12], EPSILON * 3e3);
    }
}

void meanStdevMEqualsLength() {
    float data[] = {10, 10, 11, 11, 12, 11, 10, 10, 11, 12, 11, 10, 10, 11};
    af::array t = af::array(14, data);
    af::array tss = af::tile(t, 1, 2);

    long m = 14;
    af::array mean;
    af::array stdev;

    khiva::matrix::meanStdev(tss, m, mean, stdev);

    ASSERT_EQ(mean.dims(0), 1);
    ASSERT_EQ(mean.dims(1), 2);
    ASSERT_EQ(stdev.dims(0), 1);
    ASSERT_EQ(stdev.dims(1), 2);

    float expectedMean[] = {10.714285f};
    float expectedStdev[] = {0.699862f};
    float *resultingMean = mean.host<float>();
    float *resultingStdev = stdev.host<float>();
    ASSERT_NEAR(resultingMean[0], expectedMean[0], EPSILON * 3e3);
    ASSERT_NEAR(resultingMean[1], expectedMean[0], EPSILON * 3e3);
    ASSERT_NEAR(resultingStdev[0], expectedStdev[0], EPSILON * 3e3);
    ASSERT_NEAR(resultingStdev[1], expectedStdev[0], EPSILON * 3e3);
}

void generateMask() {
    af::array mask = khiva::matrix::generateMask(3, 4, 2, 8, 2);

    ASSERT_EQ(mask.dims(0), 4);
    ASSERT_EQ(mask.dims(1), 8);
    ASSERT_EQ(mask.dims(2), 2);

    float *maskCalculated = af::transpose(mask).as(af::dtype::f32).host<float>();

    float maskExpected[] = {1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0,
                            0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1};

    for (int i = 0; i < 64; i++) {
        ASSERT_EQ(maskCalculated[i], maskExpected[i % 32]);
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

    af::array qtss = khiva::matrix::slidingDotProduct(q, tss);
    khiva::matrix::meanStdev(tss, aux, m, mean, stdev);

    af::array distance;
    af::array index;

    khiva::matrix::calculateDistanceProfile(qtss, aux, af::sum(q, 0), af::sum(af::pow(q, 2), 0), mean, stdev, distance,
                                            index);

    float expectedDistance = 19.0552097998f;
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

    af::array qtss = khiva::matrix::slidingDotProduct(q, tss);
    khiva::matrix::meanStdev(tss, aux, m, mean, stdev);

    af::array distance;
    af::array index;

    af::array mask = khiva::matrix::generateMask(m, 1, 0, 12, 2);

    khiva::matrix::calculateDistanceProfile(qtss, aux, af::sum(q, 0), af::sum(af::pow(q, 2), 0), mean, stdev, mask,
                                            distance, index);

    float expectedDistance = 19.0552097998f;
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

    khiva::matrix::meanStdev(tss, aux, m, mean, stdev);

    af::array distance;
    af::array index;

    af::array mask = khiva::matrix::generateMask(m, 1, 0, 12, 2);

    khiva::matrix::mass(q, tss, aux, mean, stdev, mask, distance, index);

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

    khiva::matrix::meanStdev(tss, aux, m, mean, stdev);

    af::array distance;
    af::array index;

    khiva::matrix::mass(q, tss, aux, mean, stdev, distance, index);

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

    khiva::matrix::stomp(tss, m, distance, index);

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

void stompIgnoreTrivialOneBigSeries() {
    af::array tss = af::randn(5000);

    long m = 500;

    af::array distance;
    af::array index;

    khiva::matrix::stomp(tss, m, distance, index);

    ASSERT_EQ(distance.dims(), af::dim4(4501, 1, 1, 1));
    ASSERT_EQ(index.dims(), af::dim4(4501, 1, 1, 1));

    unsigned int resultingIndex[4501];
    index.host(&resultingIndex);

    for (int i = 0; i < 4501; i++) {
        ASSERT_NE(resultingIndex[i], i);
    }
}

void stompIgnoreTrivialMultipleSeries() {
    float data[] = {10, 10, 11, 11, 10, 11, 10, 10, 11, 11, 10, 11, 10, 10,
                    11, 10, 10, 11, 10, 11, 11, 10, 11, 11, 10, 10, 11, 10};
    af::array tss = af::array(14, 2, data);

    long m = 3;

    af::array distance;
    af::array index;

    khiva::matrix::stomp(tss, m, distance, index);

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

    khiva::matrix::stomp(t, t, m, distance, index);

    unsigned int expectedIndex[] = {0, 1, 2, 3, 4, 5};
    float *resultingDistance = distance.host<float>();

    unsigned int resultingIndex[6];
    index.host(&resultingIndex);

    for (int i = 0; i < 6; i++) {
        ASSERT_NEAR(resultingDistance[i], 0.0, 1e-2);
        ASSERT_EQ(resultingIndex[i], expectedIndex[i]);
    }
}

void stompConsiderTrivialOneBigSeries() {
    af::array tss = af::randn(5000);

    long m = 500;

    af::array distance;
    af::array index;

    khiva::matrix::stomp(tss(af::seq(1000)), tss, m, distance, index);

    ASSERT_EQ(distance.dims(), af::dim4(4501, 1, 1, 1));
    ASSERT_EQ(index.dims(), af::dim4(4501, 1, 1, 1));

    unsigned int resultingIndex[4501];
    index.host(&resultingIndex);

    for (int i = 0; i < 501; i++) {
        ASSERT_EQ(resultingIndex[i], i);
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

    khiva::matrix::stomp(ta, tb, m, distance, index);

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

    khiva::matrix::stomp(ta, tb, m, distance, index);

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

void stompConsiderTrivialMultipleSeriesBigM() {
    af::array ta = af::randn(4096, 3);

    af::array tb = ta;

    long m = 4096;

    af::array distance;
    af::array index;

    khiva::matrix::stomp(ta, tb, m, distance, index);

    float *resultingDistance = distance.host<float>();

    unsigned int resultingIndex[9];
    index.host(&resultingIndex);

    for (int i = 0; i < 9; i++) {
        if (i % 4 == 0) {
            ASSERT_NEAR(resultingDistance[i], 0.0, 1e-1);
            ASSERT_EQ(resultingIndex[i], 0);
        }
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

    khiva::matrix::stomp(ta, tb, m, distance, index);

    af::array motifs;
    af::array motifsIndices;
    af::array subsequenceIndices;

    khiva::matrix::findBestNMotifs(distance, index, 3, 1, motifs, motifsIndices, subsequenceIndices);

    unsigned int *motifsIndicesHost = motifsIndices.host<unsigned int>();
    unsigned int *subsequenceIndicesHost = subsequenceIndices.host<unsigned int>();

    ASSERT_EQ(motifsIndicesHost[0], 12);

    ASSERT_EQ(subsequenceIndicesHost[0], 1);
}

void findBestMotifsMultipleProfiles() {
    float data_a[] = {10, 10, 10, 10, 10, 10, 9, 10, 10, 10, 10, 10, 11, 10, 9,
                      10, 10, 10, 10, 10, 10, 9, 10, 10, 10, 10, 10, 11, 10, 9};
    af::array ta = af::array(15, 2, data_a);

    float data_b[] = {10, 11, 10, 9, 10, 11, 10, 9};
    af::array tb = af::array(4, 2, data_b);

    long m = 3;

    af::array distance;
    af::array index;

    khiva::matrix::stomp(ta, tb, m, distance, index);

    af::array motifs;
    af::array motifsIndices;
    af::array subsequenceIndices;

    khiva::matrix::findBestNMotifs(distance, index, 3, 1, motifs, motifsIndices, subsequenceIndices);

    unsigned int *motifsIndicesHost = motifsIndices.host<unsigned int>();
    unsigned int *subsequenceIndicesHost = subsequenceIndices.host<unsigned int>();

    ASSERT_EQ(motifsIndicesHost[0], 12);
    ASSERT_EQ(motifsIndicesHost[1], 12);
    ASSERT_EQ(motifsIndicesHost[2], 12);
    ASSERT_EQ(motifsIndicesHost[3], 12);

    ASSERT_EQ(subsequenceIndicesHost[0], 1);
    ASSERT_EQ(subsequenceIndicesHost[1], 1);
    ASSERT_EQ(subsequenceIndicesHost[2], 1);
    ASSERT_EQ(subsequenceIndicesHost[3], 1);
}

void findBestMotifsMirror() {
    float data_a[] = {10.1, 11, 10.2, 10.15, 10.775, 10.1, 11, 10.2};
    af::array ta = af::array(8, data_a);

    long m = 3;

    af::array distance;
    af::array index;

    khiva::matrix::stomp(ta, m, distance, index);

    af::array motifs;
    af::array motifsIndices;
    af::array subsequenceIndices;

    khiva::matrix::findBestNMotifs(distance, index, 3, 2, motifs, motifsIndices, subsequenceIndices, true);

    unsigned int *motifsIndicesHost = motifsIndices.host<unsigned int>();
    unsigned int *subsequenceIndicesHost = subsequenceIndices.host<unsigned int>();

    ASSERT_EQ(motifsIndicesHost[0], 0);
    ASSERT_EQ(motifsIndicesHost[1], 0);

    ASSERT_EQ(subsequenceIndicesHost[0], 5);
    ASSERT_EQ(subsequenceIndicesHost[1], 3);
}

void findBestMotifsConsecutive() {
    float data_a[] = {10.1f, 11, 10.1f, 10.15f, 10.075f, 10.1f, 11, 10.1f, 10.15f};
    af::array ta = af::array(9, data_a);

    long m = 3;

    af::array distance;
    af::array index;

    khiva::matrix::stomp(ta, m, distance, index);

    af::array motifs;
    af::array motifsIndices;
    af::array subsequenceIndices;

    khiva::matrix::findBestNMotifs(distance, index, 3, 2, motifs, motifsIndices, subsequenceIndices, true);

    unsigned int *motifsIndicesHost = motifsIndices.host<unsigned int>();
    unsigned int *subsequenceIndicesHost = subsequenceIndices.host<unsigned int>();

    ASSERT_EQ(motifsIndicesHost[1], 6);

    ASSERT_EQ(subsequenceIndicesHost[1], 3);
}

void findBestMotifsMirrorException() {
    float data_a[] = {10, 11, 10, 11, 10, 11, 10};
    af::array ta = af::array(7, data_a);

    long m = 3;

    af::array distance;
    af::array index;

    khiva::matrix::stomp(ta, m, distance, index);

    af::array motifs;
    af::array motifsIndices;
    af::array subsequenceIndices;

    try {
        khiva::matrix::findBestNMotifs(distance, index, 3, 3, motifs, motifsIndices, subsequenceIndices, true);
    } catch (std::runtime_error &re) {
        EXPECT_EQ(
            re.what(),
            std::string(
                "Only 2 out of the best 3 motifs can be calculated. The resulting 1 motifs were not included because "
                "they are mirror motifs."));
    }
}

void findBestMotifsException() {
    float data_a[] = {10, 11, 10, 11, 10, 11, 10};
    af::array ta = af::array(7, data_a);

    long m = 3;

    af::array distance;
    af::array index;

    khiva::matrix::stomp(ta, m, distance, index);

    af::array motifs;
    af::array motifsIndices;
    af::array subsequenceIndices;

    try {
        khiva::matrix::findBestNMotifs(distance, index, 3, 4, motifs, motifsIndices, subsequenceIndices, true);
    } catch (std::invalid_argument &ia) {
        EXPECT_EQ(
            ia.what(),
            std::string(
                "You cannot retrieve more than (L-m+1)/(m/2) motifs, since there cannot be consecutive motifs in m/2 "
                "before and after a given one. L refers to the time series length."));
    }
}

void findBestDiscords() {
    float data_a[] = {11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11};
    af::array ta = af::array(13, data_a);

    float data_b[] = {9, 10.1f, 10.2f, 10.1f, 10.2f, 10.1f, 10.2f, 10.1f, 10.2f, 10.1f, 10.2f, 10.1f, 9};
    af::array tb = af::array(13, data_b);

    long m = 3;

    af::array distance;
    af::array index;

    khiva::matrix::stomp(ta, tb, m, distance, index);

    af::array discords;
    af::array discordsIndices;
    af::array subsequenceIndices;

    khiva::matrix::findBestNDiscords(distance, index, 3, 2, discords, discordsIndices, subsequenceIndices);

    unsigned int *subsequenceIndicesHost = subsequenceIndices.host<unsigned int>();

    ASSERT_EQ(subsequenceIndicesHost[0], 0);
    ASSERT_EQ(subsequenceIndicesHost[1], 10);
}

void findBestDiscordsMultipleProfiles() {
    float data_a[] = {11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11,
                      11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11};
    af::array ta = af::array(13, 2, data_a);

    float data_b[] = {9, 10.1f, 10.2f, 10.1f, 10.2f, 10.1f, 10.2f, 10.1f, 10.2f, 10.1f, 10.2f, 10.1f, 9,
                      9, 10.1f, 10.2f, 10.1f, 10.2f, 10.1f, 10.2f, 10.1f, 10.2f, 10.1f, 10.2f, 10.1f, 9};
    af::array tb = af::array(13, 2, data_b);

    long m = 3;

    af::array distance;
    af::array index;

    khiva::matrix::stomp(ta, tb, m, distance, index);

    af::array discords;
    af::array discordsIndices;
    af::array subsequenceIndices;

    khiva::matrix::findBestNDiscords(distance, index, 3, 2, discords, discordsIndices, subsequenceIndices);

    unsigned int *subsequenceIndicesHost = subsequenceIndices.host<unsigned int>();

    ASSERT_EQ(subsequenceIndicesHost[0], 0);
    ASSERT_EQ(subsequenceIndicesHost[1], 10);
    ASSERT_EQ(subsequenceIndicesHost[2], 0);
    ASSERT_EQ(subsequenceIndicesHost[3], 10);
    ASSERT_EQ(subsequenceIndicesHost[4], 0);
    ASSERT_EQ(subsequenceIndicesHost[5], 10);
    ASSERT_EQ(subsequenceIndicesHost[6], 0);
    ASSERT_EQ(subsequenceIndicesHost[7], 10);
}

void findBestDiscordsMirror() {
    float data_a[] = {10, 11, 10, 10, 11, 10};
    af::array ta = af::array(6, data_a);

    long m = 3;

    af::array distance;
    af::array index;

    khiva::matrix::stomp(ta, m, distance, index);

    af::array discords;
    af::array discordsIndices;
    af::array subsequenceIndices;

    khiva::matrix::findBestNDiscords(distance, index, 3, 1, discords, discordsIndices, subsequenceIndices, true);

    unsigned int *discordsIndicesHost = discordsIndices.host<unsigned int>();
    unsigned int *subsequenceIndicesHost = subsequenceIndices.host<unsigned int>();

    ASSERT_EQ(discordsIndicesHost[0], 3);

    ASSERT_EQ(subsequenceIndicesHost[0], 1);
}

void findBestDiscordsConsecutive() {
    float data_a[] = {10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 11, 10, 9.999f, 9.998f};
    af::array ta = af::array(15, data_a);

    long m = 3;

    af::array distance;
    af::array index;

    khiva::matrix::stomp(ta, m, distance, index);

    af::array discords;
    af::array discordsIndices;
    af::array subsequenceIndices;

    khiva::matrix::findBestNDiscords(distance, index, 3, 2, discords, discordsIndices, subsequenceIndices, true);

    unsigned int *subsequenceIndicesHost = subsequenceIndices.host<unsigned int>();

    ASSERT_EQ(subsequenceIndicesHost[0], 12);
    ASSERT_NE(subsequenceIndicesHost[1], 11);
}

void findBestDiscordsMirrorException() {
    float data_a[] = {10, 11, 10, 10, 11, 10};
    af::array ta = af::array(6, data_a);

    long m = 3;

    af::array distance;
    af::array index;

    khiva::matrix::stomp(ta, m, distance, index);

    af::array discords;
    af::array discordsIndices;
    af::array subsequenceIndices;

    try {
        khiva::matrix::findBestNDiscords(distance, index, 3, 2, discords, discordsIndices, subsequenceIndices, true);
    } catch (std::runtime_error &re) {
        EXPECT_EQ(re.what(), std::string(std::string("Only 1 out of the best 2 discords can be calculated. The "
                                                     "resulting 1 discords were not included because "
                                                     "they are mirror discords.")));
    }
}

void findBestDiscordsException() {
    float data_a[] = {10, 11, 10, 11, 10, 11, 10};
    af::array ta = af::array(7, data_a);

    long m = 3;

    af::array distance;
    af::array index;

    khiva::matrix::stomp(ta, m, distance, index);

    af::array discords;
    af::array discordsIndices;
    af::array subsequenceIndices;

    try {
        khiva::matrix::findBestNDiscords(distance, index, 3, 4, discords, discordsIndices, subsequenceIndices, true);
    } catch (std::invalid_argument &ia) {
        EXPECT_EQ(ia.what(),
                  std::string(
                      "You cannot retrieve more than (L-m+1)/(m/2) discords, since there cannot be "
                      "consecutive discords in m/2 before and after a given one. L refers to the time series length."));
    }
}

KHIVA_TEST(MatrixTests, SlidingDotProduct, slidingDotProduct)
KHIVA_TEST(MatrixTests, MeanStdev, meanStdev)
KHIVA_TEST(MatrixTests, MeanStdevMEqualsLength, meanStdevMEqualsLength)
KHIVA_TEST(MatrixTests, GenerateMask, generateMask)
KHIVA_TEST(MatrixTests, CalculateDistanceProfile, calculateDistanceProfile)
KHIVA_TEST(MatrixTests, CalculateDistanceProfileMiddle, calculateDistanceProfileMiddle)
KHIVA_TEST(MatrixTests, MassIgnoreTrivial, massIgnoreTrivial)
KHIVA_TEST(MatrixTests, MassConsiderTrivial, massConsiderTrivial)
KHIVA_TEST(MatrixTests, StompIgnoreTrivialOneSeries, stompIgnoreTrivialOneSeries)
KHIVA_TEST(MatrixTests, StompIgnoreTrivialOneBigSeries, stompIgnoreTrivialOneBigSeries)
KHIVA_TEST(MatrixTests, StompIgnoreTrivialMultipleSeries, stompIgnoreTrivialMultipleSeries)
KHIVA_TEST(MatrixTests, StompConsiderTrivialOneSeries, stompConsiderTrivialOneSeries)
KHIVA_TEST(MatrixTests, StompConsiderTrivialOneBigSeries, stompConsiderTrivialOneBigSeries)
KHIVA_TEST(MatrixTests, StompConsiderTrivialOneSeries2, stompConsiderTrivialOneSeries2)
KHIVA_TEST(MatrixTests, StompConsiderTrivialMultipleSeries, stompConsiderTrivialMultipleSeries)
KHIVA_TEST(MatrixTests, StompConsiderTrivialMultipleSeriesBigM, stompConsiderTrivialMultipleSeriesBigM)
KHIVA_TEST(MatrixTests, FindBestMotifs, findBestMotifs)
KHIVA_TEST(MatrixTests, FindBestMotifsMultipleProfiles, findBestMotifsMultipleProfiles)
KHIVA_TEST(MatrixTests, FindBestMotifsMirror, findBestMotifsMirror)
KHIVA_TEST(MatrixTests, FindBestMotifsConsecutive, findBestMotifsConsecutive)
KHIVA_TEST(MatrixTests, FindBestMotifsMirrorException, findBestMotifsMirrorException)
KHIVA_TEST(MatrixTests, FindBestMotifsException, findBestMotifsException)
KHIVA_TEST(MatrixTests, FindBestDiscords, findBestDiscords)
KHIVA_TEST(MatrixTests, FindBestDiscordsMultipleProfiles, findBestDiscordsMultipleProfiles)
KHIVA_TEST(MatrixTests, FindBestDiscordsMirror, findBestDiscordsMirror)
KHIVA_TEST(MatrixTests, FindBestDiscordsConsecutive, findBestDiscordsConsecutive)
KHIVA_TEST(MatrixTests, FindBestDiscordsMirrorException, findBestDiscordsMirrorException)
KHIVA_TEST(MatrixTests, FindBestDiscordsException, findBestDiscordsException)
