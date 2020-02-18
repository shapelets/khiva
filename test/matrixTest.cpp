// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <khiva/internal/matrixInternal.h>
#include <khiva/internal/scopedHostPtr.h>
#include <khiva/internal/vectorUtil.h>
#include <khiva/matrix.h>

#include <stdexcept>

#include "khivaTest.h"

void slidingDotProduct() {
    float data[] = {10, 10, 10, 11, 12, 11, 10, 10, 11, 12, 11, 10, 10, 10};
    af::array t = af::array(14, data);
    af::array tss = af::tile(t, 1, 2);

    float query[] = {10, 11, 12};
    af::array q = af::array(3, query);

    af::array sdp = khiva::matrix::internal::slidingDotProduct(q, tss);
    ASSERT_EQ(sdp.dims(0), 12);
    ASSERT_EQ(sdp.dims(1), 2);

    float expected[] = {330, 342, 365, 374, 361, 340, 342, 365, 374, 361, 340, 330};
    auto result = khiva::utils::makeScopedHostPtr(sdp.host<float>());
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

    khiva::matrix::internal::meanStdev(tss, m, mean, stdev);

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
    auto resultingMean = khiva::utils::makeScopedHostPtr(mean.host<float>());
    auto resultingStdev = khiva::utils::makeScopedHostPtr(stdev.host<float>());
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

    khiva::matrix::internal::meanStdev(tss, m, mean, stdev);

    ASSERT_EQ(mean.dims(0), 1);
    ASSERT_EQ(mean.dims(1), 2);
    ASSERT_EQ(stdev.dims(0), 1);
    ASSERT_EQ(stdev.dims(1), 2);

    float expectedMean[] = {10.714285f};
    float expectedStdev[] = {0.699862f};
    auto resultingMean = khiva::utils::makeScopedHostPtr(mean.host<float>());
    auto resultingStdev = khiva::utils::makeScopedHostPtr(stdev.host<float>());
    ASSERT_NEAR(resultingMean[0], expectedMean[0], EPSILON * 3e3);
    ASSERT_NEAR(resultingMean[1], expectedMean[0], EPSILON * 3e3);
    ASSERT_NEAR(resultingStdev[0], expectedStdev[0], EPSILON * 3e3);
    ASSERT_NEAR(resultingStdev[1], expectedStdev[0], EPSILON * 3e3);
}

void tileIsFarFromDiagonal() {
    using namespace khiva::matrix;

    // Upper-Left tile corner cross
    ASSERT_FALSE(internal::tileIsFarFromDiagonal(5, 16, 2, 22, 5));

    // Upper-Right tile corner cross
    ASSERT_FALSE(internal::tileIsFarFromDiagonal(5, 16, 15, 12, 2));

    // Lower-Left tile corner cross
    ASSERT_FALSE(internal::tileIsFarFromDiagonal(5, 16, 0, 12, 12));

    // Upper side
    ASSERT_FALSE(internal::tileIsFarFromDiagonal(5, 25, 5, 25, 2));

    // Left side
    ASSERT_FALSE(internal::tileIsFarFromDiagonal(5, 25, 20, 125, 10));

    // Far
    ASSERT_TRUE(internal::tileIsFarFromDiagonal(5, 25, 0, 25, 75));
}

void generateMask() {
    {
        af::array mask = khiva::matrix::internal::generateMask(3, 4, 2, 8, 0, 2);

        ASSERT_EQ(mask.dims(0), 4);
        ASSERT_EQ(mask.dims(1), 8);
        ASSERT_EQ(mask.dims(2), 2);

        auto maskCalculated = khiva::utils::makeScopedHostPtr(af::transpose(mask).as(af::dtype::f32).host<float>());

        float maskExpected[] = {1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0,
                                0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1};

        for (int i = 0; i < 64; i++) {
            ASSERT_EQ(maskCalculated[i], maskExpected[i % 32]);
        }
    }

    {
        auto mask = khiva::matrix::internal::generateMask(3, 4, 2, 4, 4, 2);

        ASSERT_EQ(mask.dims(0), 4);
        ASSERT_EQ(mask.dims(1), 4);
        ASSERT_EQ(mask.dims(2), 2);

        int maskExpected[] = {1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1};

        auto maskCalculated = khiva::utils::makeScopedHostPtr(mask.as(af::dtype::s32).host<int>());
        for (int i = 0; i < 16; i++) {
            ASSERT_EQ(maskCalculated[i], maskExpected[i]);
        }
    }

    {
        auto mask = khiva::matrix::internal::generateMask(3, 4, 2, 4, 24, 2);

        ASSERT_EQ(mask.dims(0), 4);
        ASSERT_EQ(mask.dims(1), 4);
        ASSERT_EQ(mask.dims(2), 2);

        auto maskCalculated = khiva::utils::makeScopedHostPtr(mask.as(af::dtype::s32).host<int>());
        for (int i = 0; i < 16; i++) {
            ASSERT_EQ(maskCalculated[i], 0);
        }
    }
}

void findBestNOccurrences() {
    float data[] = {10, 10, 11, 11, 12, 11, 10, 10, 11, 12, 11, 10, 10, 11};
    af::array t = af::array(14, data);
    af::array tss = af::tile(t, 1, 2);

    float query[] = {10, 11, 12};
    af::array q = af::array(3, query);

    af::array distance, index;

    khiva::matrix::findBestNOccurrences(q, tss, 1, distance, index);

    float expectedDistance = 0.0f;
    int expectedIndex = 7;

    ASSERT_EQ(distance.dims(), af::dim4(1, 1, 2, 1));
    ASSERT_EQ(index.dims(), af::dim4(1, 1, 2, 1));

    ASSERT_NEAR(distance(0, 0, 0, 0).scalar<float>(), expectedDistance, 1e-2);
    ASSERT_NEAR(distance(0, 0, 1, 0).scalar<float>(), expectedDistance, 1e-2);
    ASSERT_EQ(index(0, 0, 0, 0).scalar<unsigned int>(), expectedIndex);
    ASSERT_EQ(index(0, 0, 1, 0).scalar<unsigned int>(), expectedIndex);
}

void findBestNOccurrencesMultipleQueries() {
    float data[] = {10, 10, 11, 11, 10, 11, 10, 10, 11, 11, 10, 11, 10, 10};
    float data2[] = {11, 10, 10, 11, 10, 11, 11, 10, 11, 11, 14, 10, 11, 10};

    float query[] = {11, 11, 10, 11};
    float query2[] = {10, 11, 11, 12};

    long n = 14;
    long m = 4;

    af::array ts1 = af::array(n, 1, data);
    af::array ts2 = af::array(n, 1, data2);
    af::array q1 = af::array(m, 1, query);
    af::array q2 = af::array(m, 1, query2);
    af::array q = af::join(1, q1, q2);
    af::array tss = af::join(1, ts1, ts2);

    af::array distance, index;

    khiva::matrix::findBestNOccurrences(q, tss, 4, distance, index);

    float expectedDistanceFirstQ1TS2 = 0.014f;
    int expectedIndexFirstQ1TS2 = 5;

    float expectedDistanceSecondQ2TS2 = 1.5307f;
    int expectedIndexSecondQ2TS2 = 2;

    ASSERT_EQ(distance.dims(), af::dim4(4, 2, 2, 1));
    ASSERT_EQ(index.dims(), af::dim4(4, 2, 2, 1));

    distance = distance.as(f32);
    index = index.as(s64);

    ASSERT_NEAR(distance(0, 0, 1, 0).scalar<float>(), expectedDistanceFirstQ1TS2, 2e-2);
    ASSERT_EQ(index(0, 0, 1, 0).scalar<long long>(), expectedIndexFirstQ1TS2);

    ASSERT_NEAR(distance(1, 1, 1, 0).scalar<float>(), expectedDistanceSecondQ2TS2, 1e-2);
    ASSERT_EQ(index(1, 1, 1, 0).scalar<long long>(), expectedIndexSecondQ2TS2);
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

    af::array qtss = khiva::matrix::internal::slidingDotProduct(q, tss);
    khiva::matrix::internal::meanStdev(tss, aux, m, mean, stdev);

    af::array distances;
    af::array distance;
    af::array index;

    khiva::matrix::internal::calculateDistances(qtss, aux, af::sum(q, 0), af::sum(af::pow(q, 2), 0), mean, stdev,
                                                distances);
    af::min(distance, index, distances, 2);

    float expectedDistance = 19.0552097998f;
    int expectedIndex = 7;

    ASSERT_EQ(distance.dims(), af::dim4(1, 2, 1, 1));
    ASSERT_EQ(index.dims(), af::dim4(1, 2, 1, 1));

    auto resultingDistance = khiva::utils::makeScopedHostPtr(distance.host<float>());

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

    af::array qtss = khiva::matrix::internal::slidingDotProduct(q, tss);
    khiva::matrix::internal::meanStdev(tss, aux, m, mean, stdev);

    af::array distances;
    af::array distance;
    af::array index;

    af::array mask = khiva::matrix::internal::generateMask(m, 1, 0, 12, 0, 2);

    khiva::matrix::internal::calculateDistances(qtss, aux, af::sum(q, 0), af::sum(af::pow(q, 2), 0), mean, stdev, mask,
                                                distances);
    af::min(distance, index, distances, 2);

    float expectedDistance = 19.0552097998f;
    int expectedIndex = 7;

    ASSERT_EQ(distance.dims(), af::dim4(1, 2, 1, 1));
    ASSERT_EQ(index.dims(), af::dim4(1, 2, 1, 1));

    auto resultingDistance = khiva::utils::makeScopedHostPtr(distance.host<float>());

    unsigned int resultingIndex[2];
    index.host(&resultingIndex);

    ASSERT_NEAR(resultingDistance[0], expectedDistance, EPSILON * 1e1);
    ASSERT_NEAR(resultingDistance[1], expectedDistance, EPSILON * 1e1);
    ASSERT_EQ(resultingIndex[0], expectedIndex);
    ASSERT_EQ(resultingIndex[1], expectedIndex);
}

void massPublic() {
    float data[] = {10, 10, 10, 11, 12, 11, 10, 10, 11, 12, 11, 14, 10, 10};
    af::array t = af::array(14, data);
    af::array tss = af::tile(t, 1, 2);

    float query[] = {4, 3, 8};
    af::array q = af::array(3, query);

    long m = 3;
    long n = 14;

    af::array mean;
    af::array stdev;
    af::array aux;

    af::array distances;

    khiva::matrix::mass(q, tss, distances);

    std::vector<float> expectedDistances = {1.7321f, 0.3286f, 1.2101f, 3.1509f, 3.2458f, 2.8221f,
                                            0.3286f, 1.2101f, 3.1509f, 0.2481f, 3.3019f, 2.8221f};
    std::vector<float> resultingDistances(n - m + 1, 0.0f);
    distances(af::span, 0, 0, 0).host(resultingDistances.data());

    ASSERT_EQ(distances.dims(), af::dim4(n - m + 1, 1, 2, 1));

    ASSERT_EQ(expectedDistances.size(), resultingDistances.size());

    for (auto itRes = resultingDistances.begin(), itExpect = expectedDistances.begin();
         itRes != resultingDistances.end(); ++itRes, ++itExpect) {
        ASSERT_NEAR(*itRes, *itExpect, 1e-3);
    }
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

    khiva::matrix::internal::meanStdev(tss, aux, m, mean, stdev);

    af::array distances;
    af::array distance;
    af::array index;

    af::array mask = khiva::matrix::internal::generateMask(m, 1, 0, 12, 0, 2);

    khiva::matrix::internal::massWithMask(q, tss, aux, mean, stdev, mask, distances);
    af::min(distance, index, distances, 2);

    float expectedDistance = 0.0;
    int expectedIndex = 7;

    ASSERT_EQ(distance.dims(), af::dim4(1, 2, 1, 1));
    ASSERT_EQ(index.dims(), af::dim4(1, 2, 1, 1));

    auto resultingDistance = khiva::utils::makeScopedHostPtr(distance.host<float>());

    unsigned int resultingIndex[2];
    index.host(&resultingIndex);

    ASSERT_NEAR(resultingDistance[0], expectedDistance, 2e-2);
    ASSERT_NEAR(resultingDistance[1], expectedDistance, 2e-2);
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

    khiva::matrix::internal::meanStdev(tss, aux, m, mean, stdev);

    af::array distances;
    af::array distance;
    af::array index;

    khiva::matrix::internal::mass(q, tss, aux, mean, stdev, distances);
    af::min(distance, index, distances, 2);

    float expectedDistance = 0.0;
    int expectedIndex = 7;

    ASSERT_EQ(distance.dims(), af::dim4(1, 2, 1, 1));
    ASSERT_EQ(index.dims(), af::dim4(1, 2, 1, 1));

    auto resultingDistance = khiva::utils::makeScopedHostPtr(distance.host<float>());

    unsigned int resultingIndex[2];
    index.host(&resultingIndex);

    ASSERT_NEAR(resultingDistance[0], expectedDistance, 2e-2);
    ASSERT_NEAR(resultingDistance[1], expectedDistance, 2e-2);
    ASSERT_EQ(resultingIndex[0], expectedIndex);
    ASSERT_EQ(resultingIndex[1], expectedIndex);
}

void matrixProfile() {
    auto ta = khiva::vectorutil::createArray(
        {-0.9247, 0.1808,  2.5441, 0.3516,  -0.3452, 0.2191, -0.7687, 0.2413, -1.1948, 0.8927, -0.5378, 0.2270,
         0.9354,  -0.7613, 0.5787, -0.6174, 0.5889,  0.7897, -0.0645, 0.9520, -1.1411, 0.8281, -0.7363, -0.7446},
        8, 3);

    auto tb = khiva::vectorutil::createArray({0.2512, 0.6436, -2.3651, -0.7734, -0.0511, 1.6693, 1.9453, -1.9047,
                                              0.8149, -0.1831, -0.1542, -1.3490, 1.2285, -1.0472, 0.3911, -0.0637},
                                             8, 2);
    long m = 3;

    af::array distance;
    af::array index;

    khiva::matrix::matrixProfile(ta, tb, m, distance, index);

    ASSERT_EQ(distance.dims(0), 6);
    ASSERT_EQ(distance.dims(1), 3);
    ASSERT_EQ(distance.dims(2), 2);
    ASSERT_EQ(distance.dims(3), 1);

    ASSERT_EQ(index.dims(0), 6);
    ASSERT_EQ(index.dims(1), 3);
    ASSERT_EQ(index.dims(2), 2);
    ASSERT_EQ(index.dims(3), 1);

    auto distanceVect = khiva::vectorutil::get<double>(distance);
    auto indexVect = khiva::vectorutil::get<unsigned int>(index);
    ASSERT_NEAR(0.0112, distanceVect[7], 1e-3);
    ASSERT_EQ(1, indexVect[7]);
    ASSERT_NEAR(0.2810, distanceVect[17], 1e-3);
    ASSERT_EQ(0, indexVect[17]);
    ASSERT_NEAR(0.4467, distanceVect[18], 1e-3);
    ASSERT_EQ(2, indexVect[18]);
    ASSERT_NEAR(0.0162, distanceVect[27], 1e-3);
    ASSERT_EQ(5, indexVect[27]);
    ASSERT_NEAR(0.9187, distanceVect[35], 1e-3);
    ASSERT_EQ(4, indexVect[35]);
}

void matrixProfileSelfJoin() {
    auto ta = khiva::vectorutil::createArray(
        {0.6010, 0.0278, 0.9806, 0.2126, 0.0655, 0.5497, 0.2864, 0.3410, 0.7509, 0.4105, 0.1583, 0.3712,
         0.3543, 0.6450, 0.9675, 0.3636, 0.4165, 0.5814, 0.8962, 0.3712, 0.6755, 0.6105, 0.5232, 0.5567,
         0.7896, 0.8966, 0.0536, 0.5775, 0.2908, 0.9941, 0.5143, 0.3670, 0.3336, 0.0363, 0.5349, 0.0123,
         0.3988, 0.9787, 0.2308, 0.6244, 0.7917, 0.1654, 0.8657, 0.3766, 0.7331, 0.2522, 0.9644, 0.4711},
        16, 3);

    long m = 6;

    af::array distance;
    af::array index;

    khiva::matrix::matrixProfile(ta, m, distance, index);

    ASSERT_EQ(distance.dims(0), 11);
    ASSERT_EQ(distance.dims(1), 3);
    ASSERT_EQ(distance.dims(2), 1);
    ASSERT_EQ(distance.dims(3), 1);

    ASSERT_EQ(index.dims(0), 11);
    ASSERT_EQ(index.dims(1), 3);
    ASSERT_EQ(index.dims(2), 1);
    ASSERT_EQ(index.dims(3), 1);

    auto distanceVect = khiva::vectorutil::get<double>(distance);
    auto indexVect = khiva::vectorutil::get<unsigned int>(index);
    ASSERT_NEAR(1.2237, distanceVect[7], 1e-3);
    ASSERT_EQ(1, indexVect[7]);
    ASSERT_NEAR(2.5324, distanceVect[21], 1e-3);
    ASSERT_EQ(1, indexVect[21]);
    ASSERT_NEAR(1.979, distanceVect[25], 1e-3);
    ASSERT_EQ(6, indexVect[25]);
}

void matrixProfileLRInternal() {
    int n = 128;
    int m = 12;
    const auto ta = khiva::vectorutil::createArray<double>(
        {-92.4662,  18.0826,   254.4097,  35.1582,   -34.5167,  21.9123,   -76.8666,  24.1255,   -119.4840, 89.2692,
         -53.7780,  22.6983,   93.5360,   -76.1285,  57.8707,   -61.7367,  58.8945,   78.9682,   -6.4519,   95.2034,
         -114.1063, 82.8133,   -73.6341,  -74.4575,  -84.1459,  129.9067,  8.8310,    65.8802,   -27.8835,  141.4345,
         -116.4987, -66.2915,  -58.0665,  -16.9934,  -72.6471,  -15.0601,  -27.8524,  -0.6336,   40.2054,   139.2524,
         -24.1727,  11.3927,   -162.7895, 14.8781,   25.1250,   64.3562,   -236.5118, -77.3420,  -5.1106,   166.9285,
         194.5296,  -190.4659, 81.4878,   -18.3076,  -15.4175,  -134.8966, 122.8539,  -104.7209, 39.1123,   -6.3669,
         -125.9402, -226.7495, 71.6115,   -255.7238, 73.6051,   14.0193,   -9.0993,   32.4544,   -109.1953, 87.6599,
         121.1325,  -8.6135,   -49.1869,  -134.8533, -139.3240, 118.1974,  22.9832,   63.0970,   -93.4303,  -193.2919,
         -43.6712,  -4.2870,   -93.5555,  -86.3817,  -26.6190,  94.3234,   -100.8066, 70.5622,   75.9013,   36.3536,
         -138.5388, 72.8221,   -145.1508, 73.7886,   -1.6499,   24.0054,   113.4099,  7.9198,    77.7093,   33.7550,
         -68.3262,  -126.4960, 120.4121,  -181.5796, -110.4838, 88.8343,   -256.1250, 3.1551,    125.7766,  -76.7836,
         0.5753,    -25.1363,  49.2497,   -74.0528,  -100.8634, -56.5037,  -75.5141,  -7.2044,   -51.6655,  -116.6414,
         182.3497,  -152.1112, 150.9720,  77.0329,   58.4420,   50.0252,   -36.1718,  -55.2495},
        n);

    const std::vector<unsigned int> leftProfile = {
        4294967295, 4294967295, 4294967295, 0,  1,  0,  1,  0,  1,  4,  5,  4,  7,  8,  0,  1,  2,  1,  8,  9,
        10,         13,         14,         15, 16, 17, 16, 17, 18, 19, 20, 19, 20, 21, 22, 13, 24, 25, 28, 27,
        35,         3,          4,          5,  13, 14, 15, 0,  17, 2,  19, 24, 25, 16, 48, 18, 3,  4,  3,  6,
        7,          8,          9,          32, 38, 34, 53, 9,  63, 37, 64, 65, 66, 67, 26, 27, 28, 29, 60, 31,
        51,         52,         53,         54, 55, 56, 57, 58, 59, 60, 61, 14, 46, 53, 54, 49, 93, 94, 95, 56,
        57,         58,         59,         60, 13, 62, 23, 24, 25, 74, 75, 76, 77, 78, 79, 57, 58};

    const std::vector<unsigned int> rightProfile = {
        47,  48,  49,  87,  88,  10,  59,  60,  61,  62,  111, 88,  89,         90,         91,        46,  53,
        48,  28,  50,  80,  81,  82,  106, 107, 108, 74,  75,  76,  77,         61,         79,        82,  83,
        84,  67,  93,  94,  64,  65,  84,  85,  86,  89,  90,  91,  92,         82,         83,        84,  108,
        80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  105, 90,         70,         71,        84,  73,
        95,  96,  97,  98,  93,  94,  109, 110, 111, 112, 113, 114, 115,        92,         93,        94,  113,
        99,  115, 116, 102, 103, 104, 105, 95,  96,  97,  98,  99,  112,        113,        114,       115, 116,
        105, 115, 116, 108, 116, 110, 113, 114, 115, 114, 115, 116, 4294967295, 4294967295, 4294967295};

    auto mpLR = khiva::matrix::internal::scampLR(khiva::vectorutil::get<double>(ta), m);

    ASSERT_TRUE(leftProfile == mpLR.first.second);
    ASSERT_TRUE(rightProfile == mpLR.second.second);
}

void matrixProfileLR() {
    int n = 128;
    int m = 12;
    const auto ta = khiva::vectorutil::createArray<double>(
        {-92.4662,  18.0826,   254.4097,  35.1582,   -34.5167,  21.9123,   -76.8666,  24.1255,   -119.4840, 89.2692,
         -53.7780,  22.6983,   93.5360,   -76.1285,  57.8707,   -61.7367,  58.8945,   78.9682,   -6.4519,   95.2034,
         -114.1063, 82.8133,   -73.6341,  -74.4575,  -84.1459,  129.9067,  8.8310,    65.8802,   -27.8835,  141.4345,
         -116.4987, -66.2915,  -58.0665,  -16.9934,  -72.6471,  -15.0601,  -27.8524,  -0.6336,   40.2054,   139.2524,
         -24.1727,  11.3927,   -162.7895, 14.8781,   25.1250,   64.3562,   -236.5118, -77.3420,  -5.1106,   166.9285,
         194.5296,  -190.4659, 81.4878,   -18.3076,  -15.4175,  -134.8966, 122.8539,  -104.7209, 39.1123,   -6.3669,
         -125.9402, -226.7495, 71.6115,   -255.7238, 73.6051,   14.0193,   -9.0993,   32.4544,   -109.1953, 87.6599,
         121.1325,  -8.6135,   -49.1869,  -134.8533, -139.3240, 118.1974,  22.9832,   63.0970,   -93.4303,  -193.2919,
         -43.6712,  -4.2870,   -93.5555,  -86.3817,  -26.6190,  94.3234,   -100.8066, 70.5622,   75.9013,   36.3536,
         -138.5388, 72.8221,   -145.1508, 73.7886,   -1.6499,   24.0054,   113.4099,  7.9198,    77.7093,   33.7550,
         -68.3262,  -126.4960, 120.4121,  -181.5796, -110.4838, 88.8343,   -256.1250, 3.1551,    125.7766,  -76.7836,
         0.5753,    -25.1363,  49.2497,   -74.0528,  -100.8634, -56.5037,  -75.5141,  -7.2044,   -51.6655,  -116.6414,
         182.3497,  -152.1112, 150.9720,  77.0329,   58.4420,   50.0252,   -36.1718,  -55.2495},
        n);

    const std::vector<unsigned int> leftProfileExpect = {
        128, 128, 128, 0,  1,  0,  1,  0,  1,  4,  5,  4,  7,  8,  0,  1,  2,  1,  8,  9,  10, 13, 14, 15,
        16,  17,  16,  17, 18, 19, 20, 19, 20, 21, 22, 13, 24, 25, 28, 27, 35, 3,  4,  5,  13, 14, 15, 0,
        17,  2,   19,  24, 25, 16, 48, 18, 3,  4,  3,  6,  7,  8,  9,  32, 38, 34, 53, 9,  63, 37, 64, 65,
        66,  67,  26,  27, 28, 29, 60, 31, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 14, 46, 53, 54, 49,
        93,  94,  95,  56, 57, 58, 59, 60, 13, 62, 23, 24, 25, 74, 75, 76, 77, 78, 79, 57, 58};

    const std::vector<unsigned int> rightProfileExpect = {
        47,  48,  49,  87,  88,  10,  59,  60,  61,  62,  111, 88,  89,  90,  91,  46,  53,  48,  28,  50,
        80,  81,  82,  106, 107, 108, 74,  75,  76,  77,  61,  79,  82,  83,  84,  67,  93,  94,  64,  65,
        84,  85,  86,  89,  90,  91,  92,  82,  83,  84,  108, 80,  81,  82,  83,  84,  85,  86,  87,  88,
        89,  90,  105, 90,  70,  71,  84,  73,  95,  96,  97,  98,  93,  94,  109, 110, 111, 112, 113, 114,
        115, 92,  93,  94,  113, 99,  115, 116, 102, 103, 104, 105, 95,  96,  97,  98,  99,  112, 113, 114,
        115, 116, 105, 115, 116, 108, 116, 110, 113, 114, 115, 114, 115, 116, 128, 128, 128};

    af::array leftProfile, leftIndexes, rightProfile, rightIndexes;
    khiva::matrix::matrixProfileLR(ta, m, leftProfile, leftIndexes, rightProfile, rightIndexes);

    ASSERT_TRUE(leftProfileExpect == khiva::vectorutil::get<unsigned int>(leftIndexes));
    ASSERT_TRUE(rightProfileExpect == khiva::vectorutil::get<unsigned int>(rightIndexes));
}

void extractAllChains() {
    const std::vector<unsigned int> leftProfile = {
        4294967295, 4294967295, 4294967295, 0,  1,  0,  1,  0,  1,  4,  5,  4,  7,  8,  0,  1,  2,  1,  8,  9,
        10,         13,         14,         15, 16, 17, 16, 17, 18, 19, 20, 19, 20, 21, 22, 13, 24, 25, 28, 27,
        35,         3,          4,          5,  13, 14, 15, 0,  17, 2,  19, 24, 25, 16, 48, 18, 3,  4,  3,  6,
        7,          8,          9,          32, 38, 34, 53, 9,  63, 37, 64, 65, 66, 67, 26, 27, 28, 29, 60, 31,
        51,         52,         53,         54, 55, 56, 57, 58, 59, 60, 61, 14, 46, 53, 54, 49, 93, 94, 95, 56,
        57,         58,         59,         60, 13, 62, 23, 24, 25, 74, 75, 76, 77, 78, 79, 57, 58};

    const std::vector<unsigned int> rightProfile = {
        47,  48,  49,  87,  88,  10,  59,  60,  61,  62,  111, 88,  89,         90,         91,        46,  53,
        48,  28,  50,  80,  81,  82,  106, 107, 108, 74,  75,  76,  77,         61,         79,        82,  83,
        84,  67,  93,  94,  64,  65,  84,  85,  86,  89,  90,  91,  92,         82,         83,        84,  108,
        80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  105, 90,         70,         71,        84,  73,
        95,  96,  97,  98,  93,  94,  109, 110, 111, 112, 113, 114, 115,        92,         93,        94,  113,
        99,  115, 116, 102, 103, 104, 105, 95,  96,  97,  98,  99,  112,        113,        114,       115, 116,
        105, 115, 116, 108, 116, 110, 113, 114, 115, 114, 115, 116, 4294967295, 4294967295, 4294967295};

    const std::vector<std::vector<unsigned int>> expectedRes = {{0, 47},
                                                                {},
                                                                {2, 49},
                                                                {},
                                                                {},
                                                                {5, 10},
                                                                {6, 59, 88},
                                                                {7, 60, 89},
                                                                {8, 61, 90},
                                                                {9, 62, 105},
                                                                {},
                                                                {},
                                                                {},
                                                                {14, 91},
                                                                {15, 46, 92},
                                                                {16, 53, 82},
                                                                {17, 48},
                                                                {18, 28, 76, 111},
                                                                {19, 50},
                                                                {},
                                                                {},
                                                                {},
                                                                {23, 106},
                                                                {24, 107},
                                                                {25, 108},
                                                                {26, 74, 109},
                                                                {27, 75, 110},
                                                                {29, 77, 112},
                                                                {},
                                                                {31, 79, 114},
                                                                {},
                                                                {},
                                                                {},
                                                                {},
                                                                {},
                                                                {},
                                                                {38, 64, 70},
                                                                {},
                                                                {},
                                                                {},
                                                                {},
                                                                {},
                                                                {},
                                                                {},
                                                                {51, 80},
                                                                {52, 81},
                                                                {54, 83},
                                                                {55, 84},
                                                                {56, 85},
                                                                {57, 86},
                                                                {58, 87},
                                                                {},
                                                                {65, 71},
                                                                {},
                                                                {67, 73},
                                                                {},
                                                                {},
                                                                {},
                                                                {78, 113},
                                                                {93, 96},
                                                                {94, 97},
                                                                {95, 98},
                                                                {},
                                                                {},
                                                                {},
                                                                {},
                                                                {},
                                                                {},
                                                                {},
                                                                {}};

    auto chains = khiva::matrix::internal::extractAllChains(leftProfile, rightProfile);

    ASSERT_TRUE(expectedRes == chains);
}

void assert_chain(const std::vector<unsigned int> &chainValues, const std::vector<unsigned int> &chain) {
    auto itFind = std::find(chainValues.begin(), chainValues.end(), chain.front());
    ASSERT_TRUE(itFind != chainValues.end());
    for (const auto &chainValue : chain) {
        ASSERT_TRUE(chainValue == *itFind);
        ++itFind;
    }
}

void getChains() {
    int n = 128;
    int m = 12;
    const auto ta = khiva::vectorutil::createArray<double>(
        {-92.4662,  18.0826,   254.4097,  35.1582,   -34.5167,  21.9123,   -76.8666,  24.1255,   -119.4840, 89.2692,
         -53.7780,  22.6983,   93.5360,   -76.1285,  57.8707,   -61.7367,  58.8945,   78.9682,   -6.4519,   95.2034,
         -114.1063, 82.8133,   -73.6341,  -74.4575,  -84.1459,  129.9067,  8.8310,    65.8802,   -27.8835,  141.4345,
         -116.4987, -66.2915,  -58.0665,  -16.9934,  -72.6471,  -15.0601,  -27.8524,  -0.6336,   40.2054,   139.2524,
         -24.1727,  11.3927,   -162.7895, 14.8781,   25.1250,   64.3562,   -236.5118, -77.3420,  -5.1106,   166.9285,
         194.5296,  -190.4659, 81.4878,   -18.3076,  -15.4175,  -134.8966, 122.8539,  -104.7209, 39.1123,   -6.3669,
         -125.9402, -226.7495, 71.6115,   -255.7238, 73.6051,   14.0193,   -9.0993,   32.4544,   -109.1953, 87.6599,
         121.1325,  -8.6135,   -49.1869,  -134.8533, -139.3240, 118.1974,  22.9832,   63.0970,   -93.4303,  -193.2919,
         -43.6712,  -4.2870,   -93.5555,  -86.3817,  -26.6190,  94.3234,   -100.8066, 70.5622,   75.9013,   36.3536,
         -138.5388, 72.8221,   -145.1508, 73.7886,   -1.6499,   24.0054,   113.4099,  7.9198,    77.7093,   33.7550,
         -68.3262,  -126.4960, 120.4121,  -181.5796, -110.4838, 88.8343,   -256.1250, 3.1551,    125.7766,  -76.7836,
         0.5753,    -25.1363,  49.2497,   -74.0528,  -100.8634, -56.5037,  -75.5141,  -7.2044,   -51.6655,  -116.6414,
         182.3497,  -152.1112, 150.9720,  77.0329,   58.4420,   50.0252,   -36.1718,  -55.2495},
        n);

    // It is not being checked directly due to a sorting difference with Travis
    // const std::vector<unsigned int> chainValues = {
    //    18,  28, 76,  111, 27, 75, 110, 16, 53, 82,  26, 74, 109, 6,  59, 88, 7,  60, 89,  8,  61,  90, 9,   62,
    //    105, 15, 46,  92,  29, 77, 112, 31, 79, 114, 38, 64, 70,  17, 48, 19, 50, 23, 106, 24, 107, 25, 108, 0,
    //    47,  2,  49,  5,   10, 14, 91,  51, 80, 52,  81, 54, 83,  55, 84, 56, 85, 57, 86,  58, 87,  65, 71,  67,
    //    73,  78, 113, 93,  96, 94, 97,  95, 98, 0,   0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0,   0,  0,   0,
    //    0,   0,  0,   0,   0,  0,  0,   0,  0,  0,   0,  0,  0,   0,  0,  0,  0,  0,  0,   0,  0};

    const std::vector<unsigned int> chainIndexes = {
        1,  1,  1,  1,  2,  2,  2,  3,  3,  3,  4,  4,  4,  5,  5,  5,  6,  6,  6,  7,  7,  7,  8,  8,
        8,  9,  9,  9,  10, 10, 10, 11, 11, 11, 12, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18,
        18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30,
        30, 31, 31, 32, 32, 33, 33, 34, 34, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0};

    af::array chains;
    khiva::matrix::getChains(ta, m, chains);

    std::vector<std::vector<unsigned int>> chainsToCheck = {
        {18, 28, 76, 111}, {27, 75, 110}, {26, 74, 109}, {6, 59, 88}, {15, 46, 92}, {95, 98},
    };
    const auto &chainValues = khiva::vectorutil::get<unsigned int>(chains(af::span, 0, 0));
    for (const auto &currChain : chainsToCheck) {
        assert_chain(chainValues, currChain);
    }

    ASSERT_TRUE(khiva::vectorutil::get<unsigned int>(chains(af::span, 1, 0)) == chainIndexes);
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

    auto resultingDistance = khiva::utils::makeScopedHostPtr(distance.host<float>());

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

    auto resultingDistance = khiva::utils::makeScopedHostPtr(distance.host<float>());

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
    auto resultingDistance = khiva::utils::makeScopedHostPtr(distance.host<float>());

    unsigned int resultingIndex[6];
    index.host(&resultingIndex);

    for (int i = 0; i < 6; i++) {
        ASSERT_NEAR(resultingDistance[i], 0.0, 2e-2);
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
    auto resultingDistance = khiva::utils::makeScopedHostPtr(distance.host<float>());

    unsigned int resultingIndex[24];
    index.host(&resultingIndex);

    for (int i = 0; i < 24; i++) {
        ASSERT_NEAR(resultingDistance[i], 0.0, 2e-2);
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
    auto resultingDistance = khiva::utils::makeScopedHostPtr(distance.host<float>());

    unsigned int resultingIndex[36];
    index.host(&resultingIndex);

    for (int i = 0; i < 36; i++) {
        ASSERT_NEAR(resultingDistance[i], 0.0, 2e-2);
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

    auto resultingDistance = khiva::utils::makeScopedHostPtr(distance.host<float>());

    unsigned int resultingIndex[9];
    index.host(&resultingIndex);

    for (int i = 0; i < 9; i++) {
        if (i % 4 == 0) {
            ASSERT_NEAR(resultingDistance[i], 0.0, 2e-1);
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

    auto motifsIndicesHost = khiva::utils::makeScopedHostPtr(motifsIndices.host<unsigned int>());
    auto subsequenceIndicesHost = khiva::utils::makeScopedHostPtr(subsequenceIndices.host<unsigned int>());

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

    auto motifsIndicesHost = khiva::utils::makeScopedHostPtr(motifsIndices.host<unsigned int>());
    auto subsequenceIndicesHost = khiva::utils::makeScopedHostPtr(subsequenceIndices.host<unsigned int>());

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

    auto motifsIndicesHost = khiva::utils::makeScopedHostPtr(motifsIndices.host<unsigned int>());
    auto subsequenceIndicesHost = khiva::utils::makeScopedHostPtr(subsequenceIndices.host<unsigned int>());

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

    auto motifsIndicesHost = khiva::utils::makeScopedHostPtr(motifsIndices.host<unsigned int>());
    auto subsequenceIndicesHost = khiva::utils::makeScopedHostPtr(subsequenceIndices.host<unsigned int>());

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

    auto subsequenceIndicesHost = khiva::utils::makeScopedHostPtr(subsequenceIndices.host<unsigned int>());

    ASSERT_TRUE((subsequenceIndicesHost[0] == 0 && subsequenceIndicesHost[1] == 10) ||
                (subsequenceIndicesHost[0] == 10 && subsequenceIndicesHost[1] == 0));
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

    auto subsequenceIndicesHost = khiva::utils::makeScopedHostPtr(subsequenceIndices.host<unsigned int>());

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

    auto discordsIndicesHost = khiva::utils::makeScopedHostPtr(discordsIndices.host<unsigned int>());
    auto subsequenceIndicesHost = khiva::utils::makeScopedHostPtr(subsequenceIndices.host<unsigned int>());

    ASSERT_EQ(discordsIndicesHost[0], 3);
    ASSERT_EQ(subsequenceIndicesHost[0], 1);
}

void findBestDiscordsConsecutive() {
    auto data_a =
        std::vector<float>{10.f, 11.f, 14.f, 11.f, -2.f, 11.f, 18.f, 11.f, 1.f, 25.f, 10.f, 11.f, 1.f, 0.f, 19.f};
    af::array ta = af::array(data_a.size(), data_a.data());
    constexpr auto subSequenceLength = 3L;
    constexpr auto numDiscords = 2L;

    af::array distance;
    af::array index;

    khiva::matrix::stomp(ta, subSequenceLength, distance, index);

    af::array discords;
    af::array discordsIndices;
    af::array subsequenceIndices;

    khiva::matrix::findBestNDiscords(distance, index, subSequenceLength, numDiscords, discords, discordsIndices,
                                     subsequenceIndices, true);
    auto subsequenceIndicesHost = khiva::utils::makeScopedHostPtr(subsequenceIndices.host<unsigned int>());
    ASSERT_EQ(subsequenceIndicesHost[0], 9);
    ASSERT_EQ(subsequenceIndicesHost[1], 3);
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
KHIVA_TEST(MatrixTests, TileIsFarFromDiagonal, tileIsFarFromDiagonal)
KHIVA_TEST(MatrixTests, GenerateMask, generateMask)
KHIVA_TEST(MatrixTests, CalculateDistanceProfile, calculateDistanceProfile)
KHIVA_TEST(MatrixTests, CalculateDistanceProfileMiddle, calculateDistanceProfileMiddle)
KHIVA_TEST(MatrixTests, MassPublic, massPublic)
KHIVA_TEST(MatrixTests, MassIgnoreTrivial, massIgnoreTrivial)
KHIVA_TEST(MatrixTests, MassConsiderTrivial, massConsiderTrivial)
KHIVA_TEST(MatrixTests, FindBestNOccurrences, findBestNOccurrences)
KHIVA_TEST(MatrixTests, FindBestNOccurrencesMultipleQueries, findBestNOccurrencesMultipleQueries)
KHIVA_TEST(MatrixTests, MatrixProfile, matrixProfile)
KHIVA_TEST(MatrixTests, MatrixProfileSelfJoin, matrixProfileSelfJoin)
KHIVA_TEST(MatrixTests, MatrixProfileLRInternal, matrixProfileLRInternal)
KHIVA_TEST(MatrixTests, MatrixProfileLR, matrixProfileLR)
KHIVA_TEST(MatrixTests, ExtractAllChains, extractAllChains)
KHIVA_TEST(MatrixTests, GetChains, getChains)
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
