// Copyright (c) 2018 Grumpy Cat Software S.L.
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include "tsa.h" 
#include <iostream>
#include <arrayfire.h>
        
af::array tsa::dimensionality::PAA(array a, int bins){
   
    int n = a.elements();
    int elem_row = n / bins;
    af::array b = af::moddims(a, elem_row, bins);
    af::array addition = af::sum(b, 0);
    af::array result = addition / elem_row;

    return result;
}