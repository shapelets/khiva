// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva.h>
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

void testVisvalingam(){
    auto ind = af::range(100000);
    auto values = af::randn(100000);
    auto data = af::join(1, ind, values);

    auto start = std::chrono::steady_clock::now();
    auto res = khiva::dimensionality::visvalingam(data, 2000);

    auto end = std::chrono::steady_clock::now();

    std::cout << "Elapsed time in milliseconds : "
         << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
}

int main() {
//    stompIgnoreTrivialOneSeries();
//    stompIgnoreTrivialMultipleSeries();
//
//    stompConsiderTrivialOneSeries();
//    stompConsiderTrivialMultipleSeries();
    testVisvalingam();
    return 0;
}
