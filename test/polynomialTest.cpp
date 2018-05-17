// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <tsa/polynomial.h>
#include "tsaTest.h"

void polyfit1() {
    float data[] = {0, 1, 2, 3, 4, 5};
    af::array x = af::array(6, data);

    float *calculated = tsa::polynomial::polyfit(x, x, 1).host<float>();

    float expected[] = {1.0f, 0.0f};

    ASSERT_NEAR(calculated[0], expected[0], EPSILON);
    ASSERT_NEAR(calculated[1], expected[1], EPSILON);
}

void polyfit3() {
    float dataX[] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    af::array x = af::array(6, dataX);

    float dataY[] = {0.0f, 0.8f, 0.9f, 0.1f, -0.8f, -1.0f};
    af::array y = af::array(6, dataY);

    float *calculated = tsa::polynomial::polyfit(x, y, 3).host<float>();

    float expected[] = {0.08703704f, -0.81349206f, 1.69312169f, -0.03968254f};

    for (int i = 0; i < 4; i++) {
        ASSERT_NEAR(calculated[i], expected[i], EPSILON * 3);
    }
}

void roots() {
    float coeffs[] = {5, -20, 5, 50, -20, -40};
    af::array p = af::array(6, coeffs);

    af::array roots = tsa::polynomial::roots(p);

    af::cfloat *calculated = roots.host<af::cfloat>();

    af::cfloat expected[5];
    expected[0] = af::cfloat(2, 0);
    expected[1] = af::cfloat(2, 0);
    expected[2] = af::cfloat(2, 0);
    expected[3] = af::cfloat(-1, 0);
    expected[4] = af::cfloat(-1, 0);

    for (int i = 0; i < 5; i++) {
        ASSERT_NEAR(calculated[i].real, expected[i].real, 1e-2);
        ASSERT_NEAR(calculated[i].imag, expected[i].imag, 1e-2);
    }
}

// Not testing in CPU because the static linking of OpenMP that Arrayfire does makes the test crash
TSA_TEST_BACKENDS(PolynomialTests, Polyfit1, polyfit1, true, true, false, true, true, false)
TSA_TEST_BACKENDS(PolynomialTests, Polyfit3, polyfit3, true, true, false, true, true, false)
TSA_TEST_BACKENDS(PolynomialTests, Roots, roots, true, true, false, true, true, false)