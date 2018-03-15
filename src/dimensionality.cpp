// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa.h>
#include <boost/math/distributions/normal.hpp>
#include <iostream>
#include <iterator>
#include <vector>

af::array tsa::dimensionality::PAA(array a, int bins) {
    int n = a.elements();
    int elem_row = n / bins;
    af::array b = af::moddims(a, elem_row, bins);
    af::array addition = af::sum(b, 0);
    af::array result = addition / elem_row;

    return result;
}

std::vector<float> computeBreakpoints(int alphabet_size) {
    std::vector<float> res(alphabet_size - 1);
    boost::math::normal dist(0.0f, 1.0f);

    for (int i = 1; i < alphabet_size; i++) {
        float value = quantile(dist, (float)i * (1 / (float)alphabet_size));
        res.push_back(value);
    }
    return res;
}

std::vector<float> computeBreakpoints(int alphabet_size, float mean_value, float std_value) {
    std::vector<float> res;
    boost::math::normal dist(mean_value, std_value);

    for (int i = 1; i < alphabet_size; i++) {
        float value = quantile(dist, (float)i * (1 / (float)alphabet_size));
        res.push_back(value);
    }
    return res;
}

std::vector<int> generateAlphabet(int alphabet_size) {
    std::vector<int> res;
    for (int i = 0; i < alphabet_size; i++) {
        res.push_back(i);
    }
    return res;
}

std::vector<int> tsa::dimensionality::SAX(af::array a, int alphabet_size) {
    float mean_value = mean<float>(a);
    float std_value = stdev<float>(a);
    std::vector<int> aux;
    int n = a.elements();

    std::vector<float> breakingpoints = computeBreakpoints(alphabet_size, mean_value, std_value);
    std::vector<int> alphabet = generateAlphabet(alphabet_size);
    float *a_h = a.host<float>();

    for (int i = 0; i < n; i++) {
        int j = 0;
        int alpha = alphabet[0];

        while ((j < breakingpoints.size()) && (a_h[i] > breakingpoints[j])) {
            j++;
        }

        alpha = alphabet[j];
        aux.push_back(alpha);
    }
    return aux;
}

void print_array(float *vec, int n) {
    std::cout << "s------" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << vec[i] << std::endl;
    }
    std::cout << "e------" << std::endl;
}

void print_vec(std::vector<float> vec) {
    std::cout << "s------" << std::endl;
    for (float i : vec) {
        std::cout << i << std::endl;
    }
    std::cout << "e------" << std::endl;
}

bool isPointInDesiredList(float point, std::vector<float> desired_x) {
    bool found = false;
    for (float e : desired_x) {
        if (e == point) {
            found = true;
            break;
        }
    }
    return found;
}

void getSegmentOfPoint(float point, std::vector<float> desired_x, int &i_lower, int &i_upper) {
    // We do not check the first element, as it is fixed and set to the first element of the timeseries
    for (int i = 1; i < desired_x.size(); i++) {
        if (point < desired_x[i]) {
            i_lower = i - 1;
            i_upper = i;
            break;
        }
    }
}

float verticalDistance(float p_x, float p_y, float start_x, float start_y, float end_x, float end_y) {
    float res = 0.0;
    float dy = end_y - start_y;
    float dx = end_x - start_x;
    float m = dy / dx;
    float line_y = p_x * m + start_x;
    res = std::abs(std::abs(p_y) - std::abs(line_y));

    return res;
}

void insertPointInDesiredList(float x, float y, int position, std::vector<float> &desired_x,
                              std::vector<float> &desired_y) {
    auto it_x = desired_x.begin();
    auto it_y = desired_y.begin();

    desired_x.insert(it_x + position, x);
    desired_y.insert(it_y + position, y);
}

af::array tsa::dimensionality::PIP(af::array ts, int numberIPs) {
    int n = ts.dims(0);
    int end = n - 1;

    if (n < 2) {
        throw std::invalid_argument("We can´t delete all those important points");
    } else if (n == numberIPs) {
        return ts;
    }

    // Extracting info from af::array
    float *h_x = ts.col(0).host<float>();
    float *h_y = ts.col(1).host<float>();

    // Converting c-arrays to vectors
    std::vector<float> points_x(&h_x[0], &h_x[n]);
    std::vector<float> points_y(&h_y[0], &h_y[n]);

    // Allocation vectos for two points
    std::vector<float> desired_x(2);
    std::vector<float> desired_y(2);
    desired_x[0] = points_x[0];
    desired_y[0] = points_y[0];
    desired_x[1] = points_x[end];
    desired_y[1] = points_y[end];

    // we have to find (numberIPs - 2) points, as we have already included P[0] nad P[end].
    // Number of passes over the collection
    for (int p = 0; p < (numberIPs - 2); p++) {
        float dmax = -1.0;
        int index = -1;
        int position;

        // Find the next PIP
        for (size_t i = 1; i < end; i++) {
            int i_lower, i_upper;
            if (!isPointInDesiredList(points_x[i], desired_x)) {
                getSegmentOfPoint(points_x[i], desired_x, i_lower, i_upper);
                float d = verticalDistance(points_x[i], points_y[i], desired_x[i_lower], desired_y[i_lower],
                                           desired_x[i_upper], desired_y[i_upper]);
                if (d > dmax) {
                    index = i;
                    dmax = d;
                    position = i_upper;
                }
            }
        }
        insertPointInDesiredList(points_x[index], points_y[index], position, desired_x, desired_y);
    }

    // Converting from vector to array
    float *x = &desired_x[0];
    float *y = &desired_y[0];

    // from c-array to af::array
    af::array tsx(desired_x.size(), 1, x);
    af::array tsy(desired_y.size(), 1, y);
    af::array res = af::join(1, tsx, tsy);

    return res;
}
