// Copyright (c) 2018 Grumpy Cat Software S.L.
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "tsa.h" 
#include <iostream>
#include <arrayfire.h>
#include <boost/math/distributions/normal.hpp>
        
af::array tsa::dimensionality::PAA(array a, int bins){
   
    int n = a.elements();
    int elem_row = n / bins;
    af::array b = af::moddims(a, elem_row, bins);
    af::array addition = af::sum(b, 0);
    af::array result = addition / elem_row;

    return result;
}

std::vector<float> computeBreakpoints(int alphabet_size){
    std::vector<float> res(alphabet_size - 1);
    boost::math::normal dist(0.0f, 1.0f);

    for(int i = 1; i < alphabet_size; i++){
        std::cout << "I: " << i  << " asize: " << alphabet_size << " exp: " << (float)i*(1/(float)alphabet_size) << std::endl;
        float value = quantile(dist, (float)i*(1/(float)alphabet_size));
        res.push_back(value);
        std::cout << "VALUE: " << value  << std::endl;
    }
    return res;
}

std::vector<float> computeBreakpoints(int alphabet_size, float mean_value, float std_value){
    std::vector<float> res;
    boost::math::normal dist(mean_value, std_value);

    for(int i = 1; i < alphabet_size; i++){
        //std::cout << "I: " << i  << " asize: " << alphabet_size << " exp: " << (float)i*(1/(float)alphabet_size) << std::endl;
        float value = quantile(dist, (float)i*(1/(float)alphabet_size));
        res.push_back(value);
        //std::cout << "VALUE: " << value  << std::endl;
    }
    return res;
}

std::vector<int> generateAlphabet(int alphabet_size){
    std::vector<int> res;
    for(int i = 0; i <alphabet_size; i++){
        res.push_back(i);
    }
    return res;
}

std::vector<int> tsa::dimensionality::SAX(array a, int alphabet_size){
    float mean_value = mean<float>(a);
    float std_value = stdev<float>(a);
    std::vector<int> aux;
    int n = a.elements();

    std::vector<float> breakingpoints = computeBreakpoints(alphabet_size, mean_value, std_value);
    std::vector<int> alphabet = generateAlphabet(alphabet_size);
    float* a_h = a.host<float>();

    for(int i = 0; i < n; i++){
        int j = 0;
        int alpha = alphabet[0];

        while((j < breakingpoints.size()) && (a_h[i] > breakingpoints[j])){
            j++;    
        }
        
        alpha = alphabet[j];
        aux.push_back(alpha);
    }
    return aux;
}
