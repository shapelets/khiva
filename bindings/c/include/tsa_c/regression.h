// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <tsa_c/defines.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Calculates a linear least-squares regression for two sets of measurements. Both arrays should have the same
 * length.
 *
 * @param xss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param yss Expects an input array whose dimension zero is the length of the time series (all the same) and dimension
 * one indicates the number of time series.
 * @param slope Slope of the regression line.
 * @param intercept Intercept of the regression line.
 * @param rvalue Correlation coefficient.
 * @param pvalue Two-sided p-value for a hypothesis test whose null hypothesis is that the slope is zero, using Wald
 * Test with t-distribution of the test statistic.
 * @param stderrest Standard error of the estimated gradient.
 */
TSAAPI void linear(af_array *xss, af_array *yss, af_array *slope, af_array *intercept, af_array *rvalue,
                   af_array *pvalue, af_array *stderrest);

#ifdef __cplusplus
}
#endif