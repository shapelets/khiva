// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <tsa.h>
#include "tsatest.h"

void linear() {
    float dataX[] = {0.24580423, 0.59642861, 0.35879163, 0.37891011, 0.02445137,
                     0.23830957, 0.38793433, 0.68054104, 0.83934083, 0.76073689};
    af::array x = af::array(10, dataX);

    float dataY[] = {0.2217416,  0.06344161, 0.77944375, 0.72174137, 0.19413884,
                     0.51146167, 0.06880307, 0.39414268, 0.98172767, 0.30490851};
    af::array y = af::array(10, dataY);

    af::array slope, intercept, rvalue, pvalue, stderrest;
    float slope_host, intercept_host, rvalue_host, pvalue_host, stderrest_host;

    tsa::regression::linear(x, y, slope, intercept, rvalue, pvalue, stderrest);

    slope.host(&slope_host);
    intercept.host(&intercept_host);
    rvalue.host(&rvalue_host);
    pvalue.host(&pvalue_host);
    stderrest.host(&stderrest_host);

    ASSERT_NEAR(slope_host, 0.344864266, EPSILON);
    ASSERT_NEAR(intercept_host, 0.268578232, EPSILON);
    ASSERT_NEAR(rvalue_host, 0.283552942, EPSILON);
    ASSERT_NEAR(pvalue_host, 0.427239418, EPSILON);
    ASSERT_NEAR(stderrest_host, 0.412351891, EPSILON);
}

void linearMultipleTimeSeries() {
    float dataX[] = {0.24580423, 0.59642861, 0.35879163, 0.37891011, 0.02445137,
                     0.23830957, 0.38793433, 0.68054104, 0.83934083, 0.76073689};
    af::array x = af::array(10, dataX);
    af::array xss = af::tile(x, 1, 2);

    float dataY[] = {0.2217416,  0.06344161, 0.77944375, 0.72174137, 0.19413884,
                     0.51146167, 0.06880307, 0.39414268, 0.98172767, 0.30490851};
    af::array y = af::array(10, dataY);
    af::array yss = af::tile(y, 1, 2);

    af::array slope, intercept, rvalue, pvalue, stderrest;

    tsa::regression::linear(xss, yss, slope, intercept, rvalue, pvalue, stderrest);

    float *slope_host = slope.host<float>();
    float *intercept_host = intercept.host<float>();
    float *rvalue_host = rvalue.host<float>();
    float *pvalue_host = pvalue.host<float>();
    float *stderrest_host = stderrest.host<float>();

    ASSERT_NEAR(slope_host[0], 0.344864266, EPSILON);
    ASSERT_NEAR(slope_host[1], 0.344864266, EPSILON);
    ASSERT_NEAR(intercept_host[0], 0.268578232, EPSILON);
    ASSERT_NEAR(intercept_host[1], 0.268578232, EPSILON);
    ASSERT_NEAR(rvalue_host[0], 0.283552942, EPSILON);
    ASSERT_NEAR(rvalue_host[1], 0.283552942, EPSILON);
    ASSERT_NEAR(pvalue_host[0], 0.427239418, EPSILON);
    ASSERT_NEAR(pvalue_host[1], 0.427239418, EPSILON);
    ASSERT_NEAR(stderrest_host[0], 0.412351891, EPSILON);
    ASSERT_NEAR(stderrest_host[1], 0.412351891, EPSILON);
}

TSA_TEST(RegressionTests, Linear, linear);
TSA_TEST(RegressionTests, LinearMultipleTimeSeries, linearMultipleTimeSeries);
