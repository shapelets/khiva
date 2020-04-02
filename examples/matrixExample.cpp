// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva.h>

void stompIgnoreTrivialOneSeries() {
    float data[] = {10, 10, 11, 11, 10, 11, 10, 10, 11, 11, 10, 11, 10, 10};
    af::array tss = af::array(14, data);

    long m = 3;

    af::array distance;
    af::array index;

    khiva::matrix::stomp(tss, m, distance, index);

    auto *resultingDistance = distance.host<float>();

    unsigned int resultingIndex[12];
    index.host(&resultingIndex);
    af::freeHost(resultingDistance);
}

void stompIgnoreTrivialMultipleSeries() {
    float data[] = {10, 10, 11, 11, 10, 11, 10, 10, 11, 11, 10, 11, 10, 10,
                    11, 10, 10, 11, 10, 11, 11, 10, 11, 11, 10, 10, 11, 10};
    af::array tss = af::array(14, 2, data);

    long m = 3;

    af::array distance;
    af::array index;

    khiva::matrix::stomp(tss, m, distance, index);

    auto *resultingDistance = distance.host<float>();

    unsigned int resultingIndex[24];
    index.host(&resultingIndex);
    af::freeHost(resultingDistance);
}

void stompConsiderTrivialOneSeries() {
    float data[] = {10, 10, 11, 11, 10, 11, 10, 10};
    af::array t = af::array(8, data);

    long m = 3;

    af::array distance;
    af::array index;

    khiva::matrix::stomp(t, t, m, distance, index);

    auto *resultingDistance = distance.host<float>();

    unsigned int resultingIndex[6];
    index.host(&resultingIndex);
    af::freeHost(resultingDistance);
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

    auto *resultingDistance = distance.host<float>();

    unsigned int resultingIndex[36];
    index.host(&resultingIndex);
    af::freeHost(resultingDistance);
}

void visvalingamTest(){
    float pointList[] = {0.0f, 1.0f, 2.0f,  3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f,
                         0.0f, 0.1f, -0.1f, 5.0f, 6.0f, 7.0f, 8.1f, 9.0f, 9.0f, 9.0f};
    af::array points(10, 2, pointList);
    std::vector<khiva::dimensionality::Point> expected = {
            khiva::dimensionality::Point(0.0f, 0.0f), khiva::dimensionality::Point(2.0f, -0.1f),
            khiva::dimensionality::Point(3.0f, 5.0f), khiva::dimensionality::Point(7.0f, 9.0f),
            khiva::dimensionality::Point(9.0f, 9.0f)};

    af::array res = khiva::dimensionality::visvalingam(points, 5);
    auto *points_x = res.col(0).host<float>();
    auto *points_y = res.col(1).host<float>();

    for (size_t i = 0; i < expected.size(); i++) {
       std::cout <<  expected[i].first << ", " << points_y[i] << std::endl;
    }
}

int main() {
    visvalingamTest();

    return 0;
}
