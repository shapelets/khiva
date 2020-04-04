// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_BINDINGC_POLINOMIAL_H
#define KHIVA_BINDINGC_POLINOMIAL_H

#include <khiva_c/defines.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Least squares polynomial fit. Fit a polynomial \f$p(x) = p[0] * x^{deg} + ... + p[deg]\f$ of degree \f$deg\f$
 * to points \f$(x, y)\f$. Returns a vector of coefficients \f$p\f$ that minimises the squared error.
 *
 * @param x x-coordinates of the M sample points \f$(x[i], y[i])\f$.
 * @param y y-coordinates of the sample points.
 * @param deg Degree of the fitting polynomial.
 * @param result Polynomial coefficients, highest power first.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void polyfit(khiva_array *x, khiva_array *y, const int *deg, khiva_array *result, int *error_code,
                         char *error_message);

/**
 * @brief Calculates the roots of a polynomial with coefficients given in \f$p\f$. The values in the rank-1 array
 * \f$p\f$ are coefficients of a polynomial. If the length of \f$p\f$ is \f$n+1\f$ then the polynomial is described by:
 * \f[
 *      p[0] * x^n + p[1] * x^{n-1} + ... + p[n-1] * x + p[n]
 * \f]
 *
 * @param pp Array of polynomial coefficients.
 * @param result Array containing the roots of the polynomial.
 * @param error_code Allocated pointer to integer, where the resulting error_code is stored.
 * @param error_message Allocated char array to KHIVA_ERROR_LENGTH, where the resulting error message is stored.
 */
KHIVA_C_API void roots(khiva_array *p, khiva_array *result, int *error_code, char *error_message);

#ifdef __cplusplus
}
#endif

#endif
