// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_CORE_POLYNOMIAL_H
#define KHIVA_CORE_POLYNOMIAL_H

#include <arrayfire.h>
#include <khiva/defines.h>

namespace khiva {

namespace polynomial {

/**
 * @brief Least squares polynomial fit. Fit a polynomial \f$p(x) = p[0] * x^{deg} + ... + p[deg]\f$ of degree \f$deg\f$
 * to points \f$(x, y)\f$. Returns a vector of coefficients \f$p\f$ that minimizes the squared error.
 *
 * @param x x-coordinates of the M sample points \f$(x[i], y[i])\f$.
 * @param y y-coordinates of the sample points.
 * @param deg Degree of the fitting polynomial.
 *
 * @return af::array Polynomial coefficients, highest power first.
 */
KHIVAAPI af::array polyfit(const af::array &x, const af::array &y, int deg);

/**
 * @brief Calculates the roots of a polynomial with coefficients given in \f$p\f$. The values in the rank-1 array
 * \f$p\f$ are coefficients of a polynomial. If the length of \f$p\f$ is \f$n+1\f$ then the polynomial is described by:
 * \f[
 *      p[0] * x^n + p[1] * x^{n-1} + ... + p[n-1] * x + p[n]
 * \f]
 *
 * @param pp Array of polynomial coefficients.
 *
 * @return af::array Containing the roots of the polynomial.
 */
KHIVAAPI af::array roots(const af::array &pp);

}  // namespace polynomial
}  // namespace khiva

#endif
