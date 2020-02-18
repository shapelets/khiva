// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <khiva/linalg.h>
#include <khiva/internal/scopedHostPtr.h>
#include "khivaTest.h"

void lls() {
    float a[] = {4, 3, -1, -2};
    af::array A = af::array(2, 2, a);

    float bb[] = {3, 1};
    af::array b = af::array(2, bb);

    af::array x = khiva::linalg::lls(A, b);

    auto calculated = khiva::utils::makeScopedHostPtr(x.host<float>());

    float expected[] = {1, 1};

    ASSERT_NEAR(calculated[0], expected[0], EPSILON);
    ASSERT_NEAR(calculated[1], expected[1], EPSILON);
}

void llsMoreEquations() {
    float a[] = {4, 3, 5, -1, -2, 4};
    af::array A = af::array(3, 2, a);

    float bb[] = {3, 1, 9};
    af::array b = af::array(3, bb);

    af::array x = khiva::linalg::lls(A, b);

    auto calculated = khiva::utils::makeScopedHostPtr(x.host<float>());

    float expected[] = {1, 1};

    ASSERT_NEAR(calculated[0], expected[0], EPSILON);
    ASSERT_NEAR(calculated[1], expected[1], EPSILON);
}

void llsMoreVariables() {
    float a[] = {4, 3, 5, -1, -2, 4};
    af::array A = af::array(2, 3, a);

    float bb[] = {3, 1};
    af::array b = af::array(2, bb);

    af::array x = khiva::linalg::lls(A, b);

    auto calculated = khiva::utils::makeScopedHostPtr(x.host<float>());

    float expected[] = {0.3934987f, 0.2968349f, 0.0290847f};

    ASSERT_NEAR(calculated[0], expected[0], EPSILON);
    ASSERT_NEAR(calculated[1], expected[1], EPSILON);
    ASSERT_NEAR(calculated[2], expected[2], EPSILON);
}

KHIVA_TEST(LinAlgTests, Lls, lls)
KHIVA_TEST(LinAlgTests, LlsMoreEquations, llsMoreEquations)
KHIVA_TEST(LinAlgTests, LlsMoreVariables, llsMoreVariables)
