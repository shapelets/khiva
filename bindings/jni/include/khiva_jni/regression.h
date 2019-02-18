// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_BINDINGJAVA_REGRESSION_H
#define KHIVA_BINDINGJAVA_REGRESSION_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Calculates a linear least-squares regression for two sets of measurements. Both arrays should have the same
 * length.
 *
 * @param ref_xss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 * @param ref_yss Expects an input array whose dimension zero is the length of the time series (all the same) and
 * dimension one indicates the number of time series.
 *
 * @return An array with the updated refs and refs to:
 *      {
 *          slope Slope of the regression line.
 *          intercept Intercept of the regression line.
 *          rvalue Correlation coefficient.
 *          pvalue Two-sided p-value for a hypothesis test whose null hypothesis is that the slope is zero, using Wald
 *                  Test with t-distribution of the test statistic.
 *          stderrest Standard error of the estimated gradient.
 *      }
 */
JNIEXPORT jlongArray JNICALL Java_io_shapelets_khiva_Regression_linear(JNIEnv *env, jobject, jlong ref_xss,
                                                                       jlong ref_yss);

#ifdef __cplusplus
}
#endif

#endif
