// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/array.h>
#include <khiva_c/array.h>
#include <khiva_c/util.h>
#include <cstring>

void create_array(void *data, unsigned *ndims, long long *dims, khiva_array *result, int *type) {
    af_retain_array(result, khiva::array::createArray(data, *ndims, dims, *type).get());
}

void get_data(khiva_array *array, void *data) {
    af::array var = af::array(*array);
    khiva::array::getData(var, data);
    af_retain_array(array, var.get());
}

void get_dims(khiva_array *array, long long *dimens) {
    af::array var = af::array(*array);
    af::dim4 d = khiva::array::getDims(var);
    memcpy(dimens, d.dims, sizeof(d.dims));
    af_retain_array(array, var.get());
}

void display(khiva_array *array) {
    af::array var = af::array(*array);
    khiva::array::print(var);
    af_retain_array(array, var.get());
}

void delete_array(khiva_array *array) { khiva::array::deleteArray(*array); }

void get_type(khiva_array *array, int *t) {
    af::array var = af::array(*array);
    *t = khiva::array::getType(var);
    af_retain_array(array, var.get());
}

void khiva_add(khiva_array *lhs, khiva_array *rhs, khiva_array *result) {
    af::array var1;
    af::array var2;
    check_and_retain_arrays(lhs, rhs, var1, var2);
    af::array r = var1 + var2;
    af_retain_array(result, r.get());
}

void khiva_mul(khiva_array *lhs, khiva_array *rhs, khiva_array *result) {
    af::array var1;
    af::array var2;
    check_and_retain_arrays(lhs, rhs, var1, var2);
    af::array r = var1 * var2;
    af_retain_array(result, r.get());
}

void khiva_sub(khiva_array *lhs, khiva_array *rhs, khiva_array *result) {
    af::array var1;
    af::array var2;
    check_and_retain_arrays(lhs, rhs, var1, var2);
    af::array r = var1 - var2;
    af_retain_array(result, r.get());
}

void khiva_div(khiva_array *lhs, khiva_array *rhs, khiva_array *result) {
    af::array var1;
    af::array var2;
    check_and_retain_arrays(lhs, rhs, var1, var2);
    af::array r = var1 / var2;
    af_retain_array(result, r.get());
}

void khiva_mod(khiva_array *lhs, khiva_array *rhs, khiva_array *result) {
    af::array var1;
    af::array var2;
    check_and_retain_arrays(lhs, rhs, var1, var2);
    af::array r = var1 % var2;
    af_retain_array(result, r.get());
}

void khiva_pow(khiva_array *lhs, khiva_array *rhs, khiva_array *result) {
    af::array var1;
    af::array var2;
    check_and_retain_arrays(lhs, rhs, var1, var2);
    af::array r = af::pow(var1, var2);
    af_retain_array(result, r.get());
}

void khiva_lt(khiva_array *lhs, khiva_array *rhs, khiva_array *result) {
    af::array var1;
    af::array var2;
    check_and_retain_arrays(lhs, rhs, var1, var2);
    af::array r = var1 < var2;
    af_retain_array(result, r.get());
}

void khiva_gt(khiva_array *lhs, khiva_array *rhs, khiva_array *result) {
    af::array var1;
    af::array var2;
    check_and_retain_arrays(lhs, rhs, var1, var2);
    af::array r = var1 > var2;
    af_retain_array(result, r.get());
}

void khiva_le(khiva_array *lhs, khiva_array *rhs, khiva_array *result) {
    af::array var1;
    af::array var2;
    check_and_retain_arrays(lhs, rhs, var1, var2);
    af::array r = var1 <= var2;
    af_retain_array(result, r.get());
}

void khiva_ge(khiva_array *lhs, khiva_array *rhs, khiva_array *result) {
    af::array var1;
    af::array var2;
    check_and_retain_arrays(lhs, rhs, var1, var2);
    af::array r = var1 >= var2;
    af_retain_array(result, r.get());
}

void khiva_eq(khiva_array *lhs, khiva_array *rhs, khiva_array *result) {
    af::array var1;
    af::array var2;
    check_and_retain_arrays(lhs, rhs, var1, var2);
    af::array r = var1 == var2;
    af_retain_array(result, r.get());
}

void khiva_ne(khiva_array *lhs, khiva_array *rhs, khiva_array *result) {
    af::array var1;
    af::array var2;
    check_and_retain_arrays(lhs, rhs, var1, var2);
    af::array r = var1 != var2;
    af_retain_array(result, r.get());
}

void khiva_bitand(khiva_array *lhs, khiva_array *rhs, khiva_array *result) {
    af::array var1;
    af::array var2;
    check_and_retain_arrays(lhs, rhs, var1, var2);
    af::array r = var1 & var2;
    af_retain_array(result, r.get());
}

void khiva_bitor(khiva_array *lhs, khiva_array *rhs, khiva_array *result) {
    af::array var1;
    af::array var2;
    check_and_retain_arrays(lhs, rhs, var1, var2);
    af::array r = var1 | var2;
    af_retain_array(result, r.get());
}

void khiva_bitxor(khiva_array *lhs, khiva_array *rhs, khiva_array *result) {
    af::array var1;
    af::array var2;
    check_and_retain_arrays(lhs, rhs, var1, var2);
    af::array r = !var1 != !var2;
    af_retain_array(result, r.get());
}

void khiva_bitshiftl(khiva_array *array, int *n, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af::array r = var << *n;
    af_retain_array(result, r.get());
}

void khiva_bitshiftr(khiva_array *array, int *n, khiva_array *result) {
    af::array var1 = af::array(*array);
    af_retain_array(array, var1.get());
    af::array r = var1 >> *n;
    af_retain_array(result, r.get());
}

void khiva_not(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af::array r = !var;
    af_retain_array(result, r.get());
}

void khiva_transpose(khiva_array *array, bool *conjugate, khiva_array *result) {
    af::array var1 = af::array(*array);
    af_retain_array(array, var1.get());
    af_retain_array(result, af::transpose(var1, *conjugate).get());
}

void khiva_col(khiva_array *array, int *index, khiva_array *result) {
    af::array var1 = af::array(*array);
    af_retain_array(array, var1.get());
    af::array r = var1.col(*index);
    af_retain_array(result, r.get());
}

void khiva_cols(khiva_array *array, int *first, int *last, khiva_array *result) {
    af::array var1 = af::array(*array);
    af_retain_array(array, var1.get());
    af::array r = var1.cols(*first, *last);
    af_retain_array(result, r.get());
}

void khiva_row(khiva_array *array, int *index, khiva_array *result) {
    af::array var1 = af::array(*array);
    af_retain_array(array, var1.get());
    af::array r = var1.row(*index);
    af_retain_array(result, r.get());
}

void khiva_rows(khiva_array *array, int *first, int *last, khiva_array *result) {
    af::array var1 = af::array(*array);
    af_retain_array(array, var1.get());
    af::array r = var1.rows(*first, *last);
    af_retain_array(result, r.get());
}

void khiva_matmul(khiva_array *lhs, khiva_array *rhs, khiva_array *result) {
    af::array var1;
    af::array var2;
    check_and_retain_arrays(lhs, rhs, var1, var2);
    af_retain_array(result, af::matmul(var1, var2).get());
}

void from_arrayfire(khiva_array *arrayfire, khiva_array *result) {
    af::array var1 = af::array(*arrayfire);
    af_retain_array(arrayfire, var1.get());
    af_retain_array(result, var1.get());
}

void copy(khiva_array *array, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    af_retain_array(result, var.copy().get());
}

void khiva_as(khiva_array *array, const int *type, khiva_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());
    khiva::dtype dt = static_cast<khiva::dtype>(*type);
    af::array r = var.as(dt);
    af_retain_array(result, r.get());
}
