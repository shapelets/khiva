// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva.h>

#include "../src/khiva/vectorUtil.h"

#include <chrono>

void stompIgnoreTrivialOneSeries() {
    float data[] = {10, 10, 11, 11, 10, 11, 10, 10, 11, 11, 10, 11, 10, 10};
    af::array tss = af::array(14, data);

    long m = 3;

    af::array distance;
    af::array index;

    khiva::matrix::stomp(tss, m, distance, index);

    float *resultingDistance = distance.host<float>();

    unsigned int resultingIndex[12];
    index.host(&resultingIndex);
}

void stompIgnoreTrivialMultipleSeries() {
    float data[] = {10, 10, 11, 11, 10, 11, 10, 10, 11, 11, 10, 11, 10, 10,
                    11, 10, 10, 11, 10, 11, 11, 10, 11, 11, 10, 10, 11, 10};
    af::array tss = af::array(14, 2, data);

    long m = 3;

    af::array distance;
    af::array index;

    khiva::matrix::stomp(tss, m, distance, index);

    float *resultingDistance = distance.host<float>();

    unsigned int resultingIndex[24];
    index.host(&resultingIndex);
}

void stompConsiderTrivialOneSeries() {
    float data[] = {10, 10, 11, 11, 10, 11, 10, 10};
    af::array t = af::array(8, data);

    long m = 3;

    af::array distance;
    af::array index;

    khiva::matrix::stomp(t, t, m, distance, index);

    float *resultingDistance = distance.host<float>();

    unsigned int resultingIndex[6];
    index.host(&resultingIndex);
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

    float *resultingDistance = distance.host<float>();

    unsigned int resultingIndex[36];
    index.host(&resultingIndex);
}

#include <fstream>
std::vector<double> loadFile(const std::string &path) {
    std::vector<double> ret;
    std::ifstream infile(path);
    double value;
    while (infile >> value) {
        ret.push_back(value);
    }
    return ret;
}
af::array distancesToCorr(af::array distances, int64_t querySize) {
    return 1 - distances * distances / (2 * static_cast<double>(querySize));
}

af::array filterCandidates(af::array tss, af::array correlations, af::array indexes, int64_t m,
                           int64_t pointsToForecast, double tolerance) {
    indexes = indexes(correlations > tolerance) + m;

    if (indexes.elements() == 0) {
        throw std::runtime_error("FindBestNOccurrences couldn't find any occurrence");
    }

    auto indexesVect = khiva::vectorutil::get<unsigned int>(indexes.as(u32));
    auto candidates = af::array(pointsToForecast, indexes.dims()[0]);
    for (int i = 0; i < indexesVect.size(); ++i) {
        auto currIndex = indexesVect[i];
        candidates(af::span, i) = tss(af::seq(currIndex, currIndex + pointsToForecast - 1));
    }
    return candidates;
}

af::array getBestCentroid(af::array centroids, af::array labels, int numCentroids) {
    int bestCentroid = -1;
    int maxNumOfCandidates = -1;
    for (int i = 0; i < numCentroids; ++i) {
        auto currCandidates = af::count(labels == i).scalar<unsigned int>();
        if (currCandidates > maxNumOfCandidates) {
            bestCentroid = i;
        }
    }
    return centroids(af::span, bestCentroid);
}

af::array forecast(af::array tss, int64_t m, int64_t pointsToForecast, int64_t numberOfCandidates, double tolerance) {
    auto n = tss.dims()[0];
    auto reference = tss(af::seq(n - m, n - 1));
    auto tssNoWindow = tss(af::seq(n - m));

    af::array distances, indexes;
    khiva::matrix::findBestNOccurrences(reference, tssNoWindow, numberOfCandidates, distances, indexes);

    auto correlations = distancesToCorr(distances, m);

    auto candidates = filterCandidates(tss, correlations, indexes, m, pointsToForecast, tolerance);
    af_print(candidates);

    const int numCentroids = 2;
    af::array centroids, labels;
    khiva::clustering::kMeans(candidates, numCentroids, centroids, labels);

    return getBestCentroid(centroids, labels, numCentroids);
}

void test() {
    auto wholeDataVect = loadFile("C:\\Users\\jesus.recuerda\\Desktop\\few_points.csv");
    auto wholeData = khiva::vectorutil::createArray(wholeDataVect);
    std::cout << "SIZE = " << wholeData.dims()[0] << std::endl;

    auto start = std::chrono::steady_clock::now();
    auto wholeData2 = khiva::vectorutil::createArray(wholeDataVect);
    auto forecasted = forecast(wholeData2, 24 * 2, 24 * 2 - 1, 32, 0.9);
    auto result = khiva::vectorutil::get<double>(forecasted.as(f64));
    auto end = std::chrono::steady_clock::now();
    std::cout << "Size = " << result.size() << std::endl;
    std::cout << "Elapsed time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms"
              << std::endl;
    af_print(forecasted);
}

void testLR() {
    auto wholeDataVect = loadFile("/home/jesus.recuerda/Datasets/few_points.csv");
    auto wholeData = khiva::vectorutil::createArray(wholeDataVect);
    std::cout << "SIZE = " << wholeData.dims()[0] << std::endl;

    af::array profileLeft, profileRight, indexLeft, indexRight;

    auto start = std::chrono::steady_clock::now();
    auto wholeData2 = khiva::vectorutil::createArray(wholeDataVect).as(f32);
    khiva::matrix::matrixProfileLR(wholeData2, 50, profileLeft, indexLeft, profileRight, indexRight);
    auto end = std::chrono::steady_clock::now();

//    af_print(profileLeft);
//    af_print(profileRight);
//
//    af_print(indexLeft);
//    af_print(indexRight);
//
//    std::cout << "Elapsed time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms"
//              << std::endl;
//    std::cout << "TypeData: " << wholeData2.type() << std::endl;
//    std::cout << "Type: " << profileLeft.type() << std::endl;

    af_print(indexRight);
    af::replace(indexRight, indexRight != std::numeric_limits<unsigned int>::max(), wholeDataVect.size());
    af_print(indexRight);

}

int main() {
    // test();
    testLR();

    // stompIgnoreTrivialOneSeries();
    // stompIgnoreTrivialMultipleSeries();

    // stompConsiderTrivialOneSeries();
    // stompConsiderTrivialMultipleSeries();

    return 0;
}
