// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/linalg.h>
#include <khiva/polynomial.h>
#include <Eigen/Eigenvalues>
#include <khiva/internal/scopedHostPtr.h>

using namespace Eigen;

#define EPSILON 1e-8

af::array vandermonde(af::array x, int order, bool ascending) {
    af::array result = af::array(x.dims(0), order, x.type());
    gfor(af::seq i, order) { result(af::span, i) = af::pow(x, i); }
    if (!ascending) {
        result = af::flip(result, 1);
    }
    return result;
}

af::array khiva::polynomial::polyfit(af::array x, af::array y, int deg) {
    int order = deg + 1;
    af::array lhs = vandermonde(x, order, false);
    af::array rhs = y;

    af::array scale = af::max(af::sqrt(af::sum(lhs * lhs, 0)), EPSILON);

    lhs /= af::tile(scale, static_cast<unsigned int>(lhs.dims(0)));

    af::array c = khiva::linalg::lls(lhs, rhs);
    c = af::transpose(c);
    c /= af::tile(scale, static_cast<unsigned int>(c.dims(0)));
    c = af::transpose(c);

    return c;
}

af::array khiva::polynomial::roots(af::array pp) {
    af::array result = af::array(pp.dims(0) - 1, pp.dims(1), af::dtype::c32);
    for (int i = 0; i < pp.dims(1); i++) {
        af::array p = pp(af::span, i);
        // Strip leading and trailing zeros
        p = p(p != 0);

        p = (-1 * p(af::seq(1, static_cast<double>(p.dims(0)) - 1), af::span)) /
            af::tile(p(0, af::span), static_cast<unsigned int>(p.dims(0)) - 1);

        auto coeffs = khiva::utils::makeScopedHostPtr(p.as(af::dtype::f32).host<float>());

        Eigen::VectorXf vec = Eigen::VectorXf::Ones(p.dims(0));
        Eigen::MatrixXf diag = vec.asDiagonal();

        Eigen::MatrixXf diag2(diag.rows(), diag.cols());
        int rest = static_cast<int>(diag.rows()) - 1;
        diag2.topRows(1) = Eigen::Map<Eigen::MatrixXf>(coeffs.get(), 1, p.dims(0));
        diag2.bottomRows(rest) = diag.topRows(rest);

        Eigen::VectorXcf eivals = diag2.eigenvalues();

        result(af::span, i) = af::array(p.dims(0), (af::cfloat *)eivals.data());
    }

    return result;
}
