// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <khiva/regression.h>
#include <khiva/internal/scopedHostPtr.h>
#include "khivaTest.h"

void linear() {
    float dataX[] = {0.24580423f, 0.59642861f, 0.35879163f, 0.37891011f, 0.02445137f,
                     0.23830957f, 0.38793433f, 0.68054104f, 0.83934083f, 0.76073689f};
    af::array x = af::array(10, dataX);

    float dataY[] = {0.2217416f,  0.06344161f, 0.77944375f, 0.72174137f, 0.19413884f,
                     0.51146167f, 0.06880307f, 0.39414268f, 0.98172767f, 0.30490851f};
    af::array y = af::array(10, dataY);

    af::array slope, intercept, rvalue, pvalue, stderrest;
    float slope_host, intercept_host, rvalue_host, pvalue_host, stderrest_host;

    khiva::regression::linear(x, y, slope, intercept, rvalue, pvalue, stderrest);

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
    float dataX[] = {0.24580423f, 0.59642861f, 0.35879163f, 0.37891011f, 0.02445137f,
                     0.23830957f, 0.38793433f, 0.68054104f, 0.83934083f, 0.76073689f};
    af::array x = af::array(10, dataX);
    af::array xss = af::tile(x, 1, 2);

    float dataY[] = {0.2217416f,  0.06344161f, 0.77944375f, 0.72174137f, 0.19413884f,
                     0.51146167f, 0.06880307f, 0.39414268f, 0.98172767f, 0.30490851f};
    af::array y = af::array(10, dataY);
    af::array yss = af::tile(y, 1, 2);

    af::array slope, intercept, rvalue, pvalue, stderrest;

    khiva::regression::linear(xss, yss, slope, intercept, rvalue, pvalue, stderrest);

    auto slope_host = khiva::utils::makeScopedHostPtr(slope.host<float>());
    auto intercept_host = khiva::utils::makeScopedHostPtr(intercept.host<float>());
    auto rvalue_host = khiva::utils::makeScopedHostPtr(rvalue.host<float>());
    auto pvalue_host = khiva::utils::makeScopedHostPtr(pvalue.host<float>());
    auto stderrest_host = khiva::utils::makeScopedHostPtr(stderrest.host<float>());

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

KHIVA_TEST(RegressionTests, Linear, linear)
KHIVA_TEST(RegressionTests, LinearMultipleTimeSeries, linearMultipleTimeSeries)
