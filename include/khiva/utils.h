// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_CORE_UTILS_H
#define KHIVA_CORE_UTILS_H

#include <khiva/defines.h>
#include <khiva/dimensionality.h>

#include <iostream>

void printVectorSegment(std::vector<khiva::dimensionality::Segment> seg, std::vector<khiva::dimensionality::Point> ts) {
    std::cout << "VECTORPOINT: " << seg.size() << std::endl;
    int i = 0;
    for (auto &s : seg) {
        std::cout << "POS[" << i++ << "]= (" << ts[s.first].first << ", " << ts[s.first].second << ") , "
                  << "(" << ts[s.second].first << ", " << ts[s.second].second << ")" << std::endl;
    }
    std::cout << std::endl;
}

void printVectorPoint(std::vector<khiva::dimensionality::Point> vec) {
    std::cout << "VECTORPOINT: " << vec.size() << std::endl;
    int i = 0;
    for (auto &v : vec) {
        std::cout << "POS[" << i++ << "]= (" << v.first << ", " << v.second << ")" << std::endl;
    }
    std::cout << std::endl;
}

template <typename T>
void printVector(std::vector<T> vec) {
    std::cout << "PRINTVECTOR: " << vec.size() << std::endl;
    for (auto &v : vec) {
        std::cout << v << "\t";
    }
    std::cout << std::endl;
}

template <typename T>
void printArray(T *array, int len) {
    std::cout << "PRINTARRAY: " << len << std::endl;
    for (int i = 0; i < len; i++) {
        std::cout << array[i] << "\t";
    }
    std::cout << std::endl;
}

#endif
