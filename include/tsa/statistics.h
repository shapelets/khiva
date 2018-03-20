// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>

using namespace af;

namespace tsa {

namespace statistics {
/**
 * @brief Returns the covariance matrix of the time series contained in tss
 *
 * @param xss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @param unbiased Determines whether it divides by n - 1 (if false) or
 * n (if true)
 * @return af::array The covariance matrix of the time series
 */
af::array covariance(af::array tss, bool unbiased = true);

/**
 * @brief Returns the kth moment of the given time series
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @param k The specific moment to calculate
 * @return af::array The kth moment of the given time series
 */
af::array moment(af::array tss, int k);

/**
 * @brief Estimates standard deviation based on a sample.
 * The standard deviation is calculated using the "n-1" method
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @return af::array The sample standard deviation
 */
af::array sampleStdev(af::array tss);

/**
 * @brief Returns the kurtosis of tss (calculated with the adjusted Fisher-Pearson
 * standardized moment coefficient G2).
 *
 * @param tss Expects an input array whose dimension zero is the length of the time
 * series (all the same) and dimension one indicates the number of
 * time series.
 * @return af::array The kurtosis of tss
 */
af::array kurtosis(af::array tss);
};  // namespace statistics
};  // namespace tsa