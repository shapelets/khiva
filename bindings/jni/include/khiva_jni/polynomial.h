// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_BINDINGJAVA_POLYNOMIAL_H
#define KHIVA_BINDINGJAVA_POLYNOMIAL_H

#include <jni.h>

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
 *
 * @return A reference to an array with the polynomial coefficients, highest power first.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Polynomial_polyfit(JNIEnv *env, jobject, jlong refX, jlong refY,
                                                                        jint deg);

/**
 * @brief Calculates the roots of a polynomial with coefficients given in \f$ref\f$. The values in the rank-1 array
 * \f$ref\f$ are coefficients of a polynomial. If the length of \f$ref\f$ is \f$n+1\f$ then the polynomial is described
 * by:
 * \f[
 *      ref[0] * x^n + ref[1] * x^{n-1} + ... + ref[n-1] * x + ref[n]
 * \f]
 *
 * @param pp Array of polynomial coefficients.
 *
 * @return A reference to  an array containing the roots of the polynomial.
 */
JNIEXPORT jlong JNICALL Java_io_shapelets_khiva_Polynomial_roots(JNIEnv *env, jobject, jlong ref);

#ifdef __cplusplus
}
#endif

#endif
