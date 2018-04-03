// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa/linalg.h>
#include <tsa/polynomial.h>

#define EPSILON 1e-8

af::array vandermonde(af::array x, int order, bool ascending) {
    af::array result = af::array(x.dims(0), order, x.type());
    gfor(af::seq i, order) { result(span, i) = af::pow(x, i); }
    if (!ascending) {
        result = af::flip(result, 1);
    }
    return result;
}

af::array tsa::polynomial::polyfit(af::array x, af::array y, int deg) {
    int order = deg + 1;
    af::array lhs = vandermonde(x, order, false);
    af::array rhs = y;

    af::array scale = af::max(af::sqrt(af::sum(lhs * lhs, 0)), EPSILON);

    lhs /= af::tile(scale, lhs.dims(0));

    af::array c = tsa::linalg::lls(lhs, rhs);
    c = af::transpose(c);
    c /= af::tile(scale, c.dims(0));
    c = af::transpose(c);

    return c;
}

af::array tsa::polynomial::roots(af::array pp) {
    af::array result = af::array(pp.dims(0) - 1, pp.dims(1), af::dtype::c32);
    for (int i = 0; i < pp.dims(1); i++) {
        af::array p = pp(span, i);
        // Strip leading and trailing zeros
        p = p(p != 0);

        p = (-1 * p(af::seq(1, p.dims(0) - 1), span)) / af::tile(p(0, span), p.dims(0) - 1);

        float *coeffs = p.as(af::dtype::f32).host<float>();

        Eigen::VectorXf vec = Eigen::VectorXf::Ones(p.dims(0));
        Eigen::MatrixXf diag = vec.asDiagonal();

        Eigen::MatrixXf diag2(diag.rows(), diag.cols());
        int rest = diag.rows() - 1;
        diag2.topRows(1) = Eigen::Map<Eigen::MatrixXf>(coeffs, 1, p.dims(0));
        diag2.bottomRows(rest) = diag.topRows(rest);

        Eigen::VectorXcf eivals = diag2.eigenvalues();

        result(span, i) = af::array(p.dims(0), (cfloat *)eivals.data());
    }

    return result;
}