// Copyright (c) 2018 Grumpy Cat Software S.L.
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa.h>

af::array tsa::features::absEnergy(af::array base){
    af::array exp= af::constant(2, 10);
    af::array p2 = af::pow(base, exp);
    af::array sp2 = af::sum(p2);
    return sp2;
}

void tsa::features::absEnergyInPlace(af::array in){

}