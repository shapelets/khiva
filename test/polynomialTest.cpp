// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <khiva/polynomial.h>
#include <khiva/internal/scopedHostPtr.h>
#include "khivaTest.h"

void polyfit1() {
    float data[] = {0, 1, 2, 3, 4, 5};
    af::array x = af::array(6, data);

    auto calculated = khiva::utils::makeScopedHostPtr(khiva::polynomial::polyfit(x, x, 1).host<float>());

    float expected[] = {1.0f, 0.0f};

    ASSERT_NEAR(calculated[0], expected[0], EPSILON * 1e1);
    ASSERT_NEAR(calculated[1], expected[1], EPSILON * 1e1);
}

void polyfit3() {
    float dataX[] = {0.0f, 1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    af::array x = af::array(6, dataX);

    float dataY[] = {0.0f, 0.8f, 0.9f, 0.1f, -0.8f, -1.0f};
    af::array y = af::array(6, dataY);

    auto calculated = khiva::utils::makeScopedHostPtr(khiva::polynomial::polyfit(x, y, 3).host<float>());

    float expected[] = {0.08703704f, -0.81349206f, 1.69312169f, -0.03968254f};

    for (int i = 0; i < 4; i++) {
        ASSERT_NEAR(calculated[i], expected[i], EPSILON * 1e2f);
    }
}

void roots() {
    float coeffs[] = {5, -20, 5, 50, -20, -40};
    af::array p = af::array(6, coeffs);

    af::array roots = khiva::polynomial::roots(p);

    auto calculated = khiva::utils::makeScopedHostPtr(roots.host<af::cfloat>());

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

KHIVA_TEST(PolynomialTests, Polyfit1, polyfit1)
KHIVA_TEST(PolynomialTests, Polyfit3, polyfit3)
KHIVA_TEST(PolynomialTests, Roots, roots)
