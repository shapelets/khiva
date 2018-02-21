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
    };

    namespace regularization {
        // array xyz(array source);
    }

    namespace normalization {
        /**
         * @brief Calculates a new set of timeseries with zero mean and 
         * standard deviation one.
         * 
         * @param tss Expects an input array whose dimension zero is the length of the time 
         * series (all the same) and dimension one indicates the number of 
         * time series.
         * 
         * @param epsilon Minimum standard deviation to consider.  It acts a a gatekeeper for
         * those time series that may be constant or near constant.  
         * 
         * @return array Array with the same dimensions as tss where the time series have been
         * adjusted for zero mean and one as standard deviation.
         */
        array znorm(array tss, double epsilon = 0.00000001);

        /**
         * @brief Adjusts the time series in the given input and performs z-norm 
         * inplace (without allocating further memory)
         * 
         * @param tss Expects an input array whose dimension zero is the length of the time 
         * series (all the same) and dimension one indicates the number of 
         * time series.
         * 
         * @param epsilon Minimum standard deviation to consider.  It acts a a gatekeeper for
         * those time series that may be constant or near constant.  
         */
        void znormInPlace(array &tss, double epsilon = 0.00000001);

        /**
         * @brief Normalizes the given time series according to its minimum and maximun value and 
         * adjusts each value within the range [low, high]
         * 
         * @param tss Expects an input array whose dimension zero is the length of the time 
         * series (all the same) and dimension one indicates the number of 
         * time series.
         * 
         * @param high Maximum final value.  Defaults to 1.0
         * @param low  Minimum final value.  Defaults to 0.0
         * 
         * @param epsilon Safeguard for constant (or near constant) time series as the operation implies
         * a unit scale operation between min and max values in the tss.
         * 
         * @return array An array with the same dimensions as tss, whose values (time series in dimension 0)
         * have been normalized by maximun and minimun values, and scaled as per high and low parameters.
         */
        array maxMinNorm(array tss, double high = 1.0, double low = 0.0, double epsilon = 0.00000001);

        /**
         * @brief Same as maxMinNorm, but it performs the operation in place, without allocating further memory.
         * 
         * @param tss Expects an input array whose dimension zero is the length of the time 
         * series (all the same) and dimension one indicates the number of 
         * time series.
         * 
         * @param high Maximum final value.  Defaults to 1.0
         * @param low  Minimum final value.  Defaults to 0.0
         * 
         * @param epsilon Safeguard for constant (or near constant) time series as the operation implies
         * a unit scale operation between min and max values in the tss.
         */
        void maxMinNormInPlace(array &tss, double high = 1.0, double low = 0.0, double epsilon = 0.00000001);


        

        // decimal scaling
        // adaptive normalization
    };

    namespace features {
        // tsfresh
        // PIP Perceptualy important points
    };

    namespace dimensionality {
        // PAA/PLA
        // SAX
        // Principal Components A.
        // Random Projections
    };

    namespace distances {

        /**
         * @brief Calculates euclidian distances between timeseries.  
         * 
         * @param tss Expects an input array whose dimension zero is the length of the time 
         * series (all the same) and dimension one indicates the number of 
         * time series.
         * 
         * @return array Returns an upper triangular matrix where each position corresponds to the 
         * distance between two time series.  Diagonal elements will be zero.  For example: 
         * Position row 0 column 1 will record the distance between time series 0 
         * and time series 1.
         */
        array euclidian(array tss);

        /**
         * @brief Calculates non squared version of the euclidian distance.
         * 
         * @param tss Expects an input array whose dimension zero is the length of the time 
         * series (all the same) and dimension one indicates the number of 
         * time series.
         * 
         * @return array Returns an upper triangular matrix where each position corresponds to the 
         * distance between two time series.  Diagonal elements will be zero.  For example: 
         * Position row 0 column 1 will record the distance between time series 0 
         * and time series 1.
         */
        array squaredEuclidian(array tss);

        // habituales + la ncc

        // una funcion que dada un tipo de destiancia retorna 
        // una matriz triangular de distancias entre timeseries 
    };

};

