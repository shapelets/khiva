// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>

using namespace af;

namespace tsa {

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
 * @return af::array Array with the same dimensions as tss where the time series have been
 * adjusted for zero mean and one as standard deviation.
 */
af::array znorm(af::array tss, double epsilon = 0.00000001);

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
void znormInPlace(af::array &tss, double epsilon = 0.00000001);

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
 * @return af::array An array with the same dimensions as tss, whose values (time series in dimension 0)
 * have been normalized by maximun and minimun values, and scaled as per high and low parameters.
 */
af::array maxMinNorm(af::array tss, double high = 1.0, double low = 0.0, double epsilon = 0.00000001);

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
void maxMinNormInPlace(af::array &tss, double high = 1.0, double low = 0.0, double epsilon = 0.00000001);

/**
 * @brief Normalizes the given time series according to its maximun value and
 * adjusts each value within the range (-1, 1)
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of time series.
 *
 * @return af::array An array with the same dimensions as tss, whose values (time series in dimension 0)
 * have been normalized by dividing each number by 10^j, where j is the number of integer digits of
 * the max number in the timeseries
 */
af::array decimalScalingNorm(af::array tss);

/**
 * @brief Same as decimalScalingNorm, but it performs the operation in place, without allocating further
 *  memory.
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of time series.
 */
void decimalScalingNormInPlace(af::array &tss);

// adaptive normalization
};  // namespace normalization
};  // namespace tsa