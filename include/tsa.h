// Copyright (c) 2018 Grumpy Cat Software S.L.
// 
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include "version.h"

using namespace af;


namespace tsa {
    const char* version();

    namespace simplification {
        //array rdp(array source, int maxPoints);
        //array visvalingam(array source, int maxPoints);         
    }

    namespace regularization {
        // array xyz(array source);
    }

    namespace normalization {
        // znorm
        // max min
        // decimal scaling
        // adaptive normalization
    }

    namespace features {
        // tsfresh
        // PIP Perceptualy important points
    }

    namespace dimensionality {
        // PAA/PLA
        // SAX
        // Principal Components A.
        // Random Projections
    }

    namespace distances {
        // habituales + la ncc

        // una funcion que dada un tipo de destiancia retorna 
        // una matriz triangular de distancias entre timeseries 
    }
}
