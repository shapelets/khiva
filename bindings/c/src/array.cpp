// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <tsa/array.h>
#include <tsa_c/array.h>
#include <cstring>

#ifdef __cplusplus
extern "C" {
#endif

TSAAPI void create_array(void *data, unsigned *ndims, long long *dims, tsa_array *result, int *type) {
    af_retain_array(result, tsa::array::createArray(data, *ndims, dims, *type).get());
}

TSAAPI void get_data(tsa_array *array, void *data) {
    af::array var = af::array(*array);
    tsa::array::getData(var, data);
    af_retain_array(array, var.get());
}

TSAAPI void get_dims(tsa_array *array, long long *dimens) {
    af::array var = af::array(*array);
    af::dim4 d = tsa::array::getDims(var);
    memcpy(dimens, d.dims, sizeof(d.dims));
    af_retain_array(array, var.get());
}

TSAAPI void print(tsa_array *array) {
    af::array var = af::array(*array);
    tsa::array::print(var);
    af_retain_array(array, var.get());
}

TSAAPI void delete_array(tsa_array *array) { tsa::array::deleteArray(*array); }

TSAAPI void get_type(tsa_array *array, int *t) {
    af::array var = af::array(*array);
    *t = tsa::array::getType(var);
    af_retain_array(array, var.get());
}

TSAAPI void tsa_add(tsa_array *lhs, tsa_array *rhs, tsa_array *result) {
    af::array var1 = af::array(*lhs);
    af::array var2 = af::array(*rhs);
    af_retain_array(lhs, var1.get());
    af_retain_array(rhs, var2.get());
    af::array r = var1 + var2;
    af_retain_array(result, r.get());
}

TSAAPI void tsa_mul(tsa_array *lhs, tsa_array *rhs, tsa_array *result) {
    af::array var1 = af::array(*lhs);
    af::array var2 = af::array(*rhs);
    af_retain_array(lhs, var1.get());
    af_retain_array(rhs, var2.get());
    af::array r = var1 * var2;
    af_retain_array(result, r.get());
}

TSAAPI void tsa_sub(tsa_array *lhs, tsa_array *rhs, tsa_array *result) {
    af::array var1 = af::array(*lhs);
    af::array var2 = af::array(*rhs);
    af_retain_array(lhs, var1.get());
    af_retain_array(rhs, var2.get());
    af::array r = var1 - var2;
    af_retain_array(result, r.get());
}

TSAAPI void tsa_div(tsa_array *lhs, tsa_array *rhs, tsa_array *result) {
    af::array var1 = af::array(*lhs);
    af::array var2 = af::array(*rhs);
    af_retain_array(lhs, var1.get());
    af_retain_array(rhs, var2.get());
    af::array r = var1 / var2;
    af_retain_array(result, r.get());
}

TSAAPI void tsa_mod(tsa_array *lhs, tsa_array *rhs, tsa_array *result) {
    af::array var1 = af::array(*lhs);
    af::array var2 = af::array(*rhs);
    af_retain_array(lhs, var1.get());
    af_retain_array(rhs, var2.get());
    af::array r = var1 % var2;
    af_retain_array(result, r.get());
}

TSAAPI void tsa_pow(tsa_array *lhs, tsa_array *rhs, tsa_array *result) {
    af::array var1 = af::array(*lhs);
    af::array var2 = af::array(*rhs);
    af_retain_array(lhs, var1.get());
    af_retain_array(rhs, var2.get());
    af::array r = af::pow(var1, var2);
    af_retain_array(result, r.get());
}

TSAAPI void tsa_lt(tsa_array *lhs, tsa_array *rhs, tsa_array *result) {
    af::array var1 = af::array(*lhs);
    af::array var2 = af::array(*rhs);
    af_retain_array(lhs, var1.get());
    af_retain_array(rhs, var2.get());
    af::array r = var1 < var2;
    af_retain_array(result, r.get());
}

TSAAPI void tsa_gt(tsa_array *lhs, tsa_array *rhs, tsa_array *result) {
    af::array var1 = af::array(*lhs);
    af::array var2 = af::array(*rhs);
    af_retain_array(lhs, var1.get());
    af_retain_array(rhs, var2.get());
    af::array r = var1 > var2;
    af_retain_array(result, r.get());
}

TSAAPI void tsa_le(tsa_array *lhs, tsa_array *rhs, tsa_array *result) {
    af::array var1 = af::array(*lhs);
    af::array var2 = af::array(*rhs);
    af_retain_array(lhs, var1.get());
    af_retain_array(rhs, var2.get());
    af::array r = var1 <= var2;
    af_retain_array(result, r.get());
}

TSAAPI void tsa_ge(tsa_array *lhs, tsa_array *rhs, tsa_array *result) {
    af::array var1 = af::array(*lhs);
    af::array var2 = af::array(*rhs);
    af_retain_array(lhs, var1.get());
    af_retain_array(rhs, var2.get());
    af::array r = var1 >= var2;
    af_retain_array(result, r.get());
}

TSAAPI void tsa_eq(tsa_array *lhs, tsa_array *rhs, tsa_array *result) {
    af::array var1 = af::array(*lhs);
    af::array var2 = af::array(*rhs);
    af_retain_array(lhs, var1.get());
    af_retain_array(rhs, var2.get());
    af::array r = var1 == var2;
    af_retain_array(result, r.get());
}

TSAAPI void tsa_ne(tsa_array *lhs, tsa_array *rhs, tsa_array *result) {
    af::array var1 = af::array(*lhs);
    af::array var2 = af::array(*rhs);
    af_retain_array(lhs, var1.get());
    af_retain_array(rhs, var2.get());
    af::array r = var1 != var2;
    af_retain_array(result, r.get());
}

TSAAPI void tsa_bitand(tsa_array *lhs, tsa_array *rhs, tsa_array *result) {
    af::array var1 = af::array(*lhs);
    af::array var2 = af::array(*rhs);
    af_retain_array(lhs, var1.get());
    af_retain_array(rhs, var2.get());
    af::array r = var1 & var2;
    af_retain_array(result, r.get());
}

TSAAPI void tsa_bitor(tsa_array *lhs, tsa_array *rhs, tsa_array *result) {
    af::array var1 = af::array(*lhs);
    af::array var2 = af::array(*rhs);
    af_retain_array(lhs, var1.get());
    af_retain_array(rhs, var2.get());
    af::array r = var1 | var2;
    af_retain_array(result, r.get());
}

TSAAPI void tsa_bitxor(tsa_array *lhs, tsa_array *rhs, tsa_array *result) {
    af::array var1 = af::array(*lhs);
    af::array var2 = af::array(*rhs);
    af_retain_array(lhs, var1.get());
    af_retain_array(rhs, var2.get());
    af::array r = !var1 != !var2;
    af_retain_array(result, r.get());
}

TSAAPI void tsa_bitshiftl(tsa_array *array, int *n, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af::array r = var << *n;
    af_retain_array(result, r.get());
}

TSAAPI void tsa_bitshiftr(tsa_array *array, int *n, tsa_array *result) {
    af::array var1 = af::array(*array);
    af_retain_array(array, var1.get());
    af::array r = var1 >> *n;
    af_retain_array(result, r.get());
}

TSAAPI void tsa_not(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af::array r = !var;
    af_retain_array(result, r.get());
}

TSAAPI void tsa_transpose(tsa_array *array, bool *conjugate, tsa_array *result) {
    af::array var1 = af::array(*array);
    af_retain_array(array, var1.get());
    af_retain_array(result, af::transpose(var1, *conjugate).get());
}

TSAAPI void tsa_col(tsa_array *array, int *index, tsa_array *result) {
    af::array var1 = af::array(*array);
    af_retain_array(array, var1.get());
    af::array r = var1.col(*index);
    af_retain_array(result, r.get());
}

TSAAPI void tsa_cols(tsa_array *array, int *first, int *last, tsa_array *result) {
    af::array var1 = af::array(*array);
    af_retain_array(array, var1.get());
    af::array r = var1.cols(*first, *last);
    af_retain_array(result, r.get());
}

TSAAPI void tsa_row(tsa_array *array, int *index, tsa_array *result) {
    af::array var1 = af::array(*array);
    af_retain_array(array, var1.get());
    af::array r = var1.row(*index);
    af_retain_array(result, r.get());
}

TSAAPI void tsa_rows(tsa_array *array, int *first, int *last, tsa_array *result) {
    af::array var1 = af::array(*array);
    af_retain_array(array, var1.get());
    af::array r = var1.rows(*first, *last);
    af_retain_array(result, r.get());
}

TSAAPI void tsa_matmul(tsa_array *lhs, tsa_array *rhs, tsa_array *result) {
    af::array var1 = af::array(*lhs);
    af_retain_array(lhs, var1.get());
    af::array var2 = af::array(*rhs);
    af_retain_array(rhs, var2.get());
    af_retain_array(result, af::matmul(var1, var2).get());
}

TSAAPI void from_arrayfire(tsa_array *arrayfire, tsa_array *result) {
    af::array var1 = af::array(*arrayfire);
    af_retain_array(arrayfire, var1.get());
    af_retain_array(result, var1.get());
}

TSAAPI void copy(tsa_array *array, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, var.copy().get());
}

TSAAPI void tsa_as(tsa_array *array, const int *type, tsa_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    tsa::dtype dt = static_cast<tsa::dtype>(*type);
    af::array r = var.as(dt);
    af_retain_array(result, r.get());
}
#ifdef __cplusplus
}
#endif