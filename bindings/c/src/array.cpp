// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/array.h>
#include <khiva_c/array.h>
#include <khiva_c/internal/util.h>
#include <cstring>
#include <thread>

void create_array(void *data, unsigned *ndims, long long *dims, khiva_array *result, int *type, int *error_code,
                  char *error_message) {
    try {
        af_retain_array(result, khiva::array::createArray(data, *ndims, dims, *type).get());
    } catch (const std::exception &e) {
        fill_error("display", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("display", error_message, error_code, -1);
    }
}

void delete_array(khiva_array *array, int *error_code, char *error_message) {
    try {
        khiva::array::deleteArray(*array);
    } catch (const std::exception &e) {
        fill_error("display", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("display", error_message, error_code, -1);
    }
}

void display(khiva_array *array, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        khiva::array::print(var);
        af_retain_array(array, var.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("display", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("display", error_message, error_code, -1);
    }
}

void get_data(khiva_array *array, void *data, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        khiva::array::getData(var, data);
        af_retain_array(array, var.get());

        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("get_data", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("get_data", error_message, error_code, -1);
    }
}

void get_dims(khiva_array *array, long long *dimens, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af::dim4 d = khiva::array::getDims(var);
        std::memcpy(dimens, d.dims, sizeof(d.dims));
        af_retain_array(array, var.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("get_dims", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("get_dims", error_message, error_code, -1);
    }
}

void get_type(khiva_array *array, int *t, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        *t = khiva::array::getType(var);
        af_retain_array(array, var.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("get_type", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("get_type", error_message, error_code, -1);
    }
}

void join(int *dim, khiva_array *first, khiva_array *second, khiva_array *result, int *error_code,
          char *error_message) {
    try {
        af::array var1;
        af::array var2;
        check_and_retain_arrays(first, second, var1, var2);
        af::array r = khiva::array::join(*dim, var1, var2);
        af_retain_array(result, r.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("join", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("join", error_message, error_code, -1);
    }
}

void khiva_add(khiva_array *lhs, khiva_array *rhs, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var1;
        af::array var2;
        check_and_retain_arrays(lhs, rhs, var1, var2);
        af::array r = var1 + var2;
        af_retain_array(result, r.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("khiva_add", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("khiva_add", error_message, error_code, -1);
    }
}

void khiva_mul(khiva_array *lhs, khiva_array *rhs, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var1;
        af::array var2;
        check_and_retain_arrays(lhs, rhs, var1, var2);
        af::array r = var1 * var2;
        af_retain_array(result, r.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("khiva_mul", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("khiva_mul", error_message, error_code, -1);
    }
}

void khiva_sub(khiva_array *lhs, khiva_array *rhs, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var1;
        af::array var2;
        check_and_retain_arrays(lhs, rhs, var1, var2);
        af::array r = var1 - var2;
        af_retain_array(result, r.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("khiva_sub", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("khiva_sub", error_message, error_code, -1);
    }
}

void khiva_div(khiva_array *lhs, khiva_array *rhs, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var1;
        af::array var2;
        check_and_retain_arrays(lhs, rhs, var1, var2);
        af::array r = var1 / var2;
        af_retain_array(result, r.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("khiva_div", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("khiva_div", error_message, error_code, -1);
    }
}

void khiva_mod(khiva_array *lhs, khiva_array *rhs, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var1;
        af::array var2;
        check_and_retain_arrays(lhs, rhs, var1, var2);
        af::array r = var1 % var2;
        af_retain_array(result, r.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("khiva_mod", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("khiva_mod", error_message, error_code, -1);
    }
}

void khiva_pow(khiva_array *lhs, khiva_array *rhs, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var1;
        af::array var2;
        check_and_retain_arrays(lhs, rhs, var1, var2);
        af::array r = af::pow(var1, var2);
        af_retain_array(result, r.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("khiva_pow", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("khiva_pow", error_message, error_code, -1);
    }
}

void khiva_lt(khiva_array *lhs, khiva_array *rhs, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var1;
        af::array var2;
        check_and_retain_arrays(lhs, rhs, var1, var2);
        af::array r = var1 < var2;
        af_retain_array(result, r.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("khiva_lt", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("khiva_lt", error_message, error_code, -1);
    }
}

void khiva_gt(khiva_array *lhs, khiva_array *rhs, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var1;
        af::array var2;
        check_and_retain_arrays(lhs, rhs, var1, var2);
        af::array r = var1 > var2;
        af_retain_array(result, r.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("khiva_gt", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("khiva_gt", error_message, error_code, -1);
    }
}

void khiva_le(khiva_array *lhs, khiva_array *rhs, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var1;
        af::array var2;
        check_and_retain_arrays(lhs, rhs, var1, var2);
        af::array r = var1 <= var2;
        af_retain_array(result, r.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("khiva_le", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("khiva_le", error_message, error_code, -1);
    }
}

void khiva_ge(khiva_array *lhs, khiva_array *rhs, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var1;
        af::array var2;
        check_and_retain_arrays(lhs, rhs, var1, var2);
        af::array r = var1 >= var2;
        af_retain_array(result, r.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("khiva_ge", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("khiva_ge", error_message, error_code, -1);
    }
}

void khiva_eq(khiva_array *lhs, khiva_array *rhs, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var1;
        af::array var2;
        check_and_retain_arrays(lhs, rhs, var1, var2);
        af::array r = var1 == var2;
        af_retain_array(result, r.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("khiva_eq", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("khiva_eq", error_message, error_code, -1);
    }
}

void khiva_ne(khiva_array *lhs, khiva_array *rhs, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var1;
        af::array var2;
        check_and_retain_arrays(lhs, rhs, var1, var2);
        af::array r = var1 != var2;
        af_retain_array(result, r.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("khiva_ne", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("khiva_ne", error_message, error_code, -1);
    }
}

void khiva_bitand(khiva_array *lhs, khiva_array *rhs, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var1;
        af::array var2;
        check_and_retain_arrays(lhs, rhs, var1, var2);
        af::array r = var1 & var2;
        af_retain_array(result, r.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("khiva_bitand", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("khiva_bitand", error_message, error_code, -1);
    }
}

void khiva_bitor(khiva_array *lhs, khiva_array *rhs, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var1;
        af::array var2;
        check_and_retain_arrays(lhs, rhs, var1, var2);
        af::array r = var1 | var2;
        af_retain_array(result, r.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("khiva_bitor", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("khiva_bitor", error_message, error_code, -1);
    }
}

void khiva_bitxor(khiva_array *lhs, khiva_array *rhs, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var1;
        af::array var2;
        check_and_retain_arrays(lhs, rhs, var1, var2);
        af::array r = !var1 != !var2;
        af_retain_array(result, r.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("khiva_bitxor", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("khiva_bitxor", error_message, error_code, -1);
    }
}

void khiva_bitshiftl(khiva_array *array, int *n, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af::array r = var << *n;
        af_retain_array(result, r.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("khiva_bitshiftl", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("khiva_bitshiftl", error_message, error_code, -1);
    }
}

void khiva_bitshiftr(khiva_array *array, int *n, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var1 = af::array(*array);
        af_retain_array(array, var1.get());
        af::array r = var1 >> *n;
        af_retain_array(result, r.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("khiva_bitshiftr", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("khiva_bitshiftr", error_message, error_code, -1);
    }
}

void khiva_not(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af::array r = !var;
        af_retain_array(result, r.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("khiva_not", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("khiva_not", error_message, error_code, -1);
    }
}

void khiva_transpose(khiva_array *array, bool *conjugate, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var1 = af::array(*array);
        af_retain_array(array, var1.get());
        af_retain_array(result, af::transpose(var1, *conjugate).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("khiva_transpose", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("khiva_transpose", error_message, error_code, -1);
    }
}

void khiva_col(khiva_array *array, int *index, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var1 = af::array(*array);
        af_retain_array(array, var1.get());
        af::array r = var1.col(*index);
        af_retain_array(result, r.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("khiva_col", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("khiva_col", error_message, error_code, -1);
    }
}

void khiva_cols(khiva_array *array, int *first, int *last, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var1 = af::array(*array);
        af_retain_array(array, var1.get());
        af::array r = var1.cols(*first, *last);
        af_retain_array(result, r.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("khiva_cols", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("khiva_cols", error_message, error_code, -1);
    }
}

void khiva_row(khiva_array *array, int *index, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var1 = af::array(*array);
        af_retain_array(array, var1.get());
        af::array r = var1.row(*index);
        af_retain_array(result, r.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("khiva_row", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("khiva_row", error_message, error_code, -1);
    }
}

void khiva_rows(khiva_array *array, int *first, int *last, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var1 = af::array(*array);
        af_retain_array(array, var1.get());
        af::array r = var1.rows(*first, *last);
        af_retain_array(result, r.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("khiva_rows", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("khiva_rows", error_message, error_code, -1);
    }
}

void khiva_matmul(khiva_array *lhs, khiva_array *rhs, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var1;
        af::array var2;
        check_and_retain_arrays(lhs, rhs, var1, var2);
        af_retain_array(result, af::matmul(var1, var2).get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("khiva_matmul", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("khiva_matmul", error_message, error_code, -1);
    }
}

void from_arrayfire(khiva_array *arrayfire, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var1 = af::array(*arrayfire);
        af_retain_array(arrayfire, var1.get());
        af_retain_array(result, var1.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("from_arrayfire", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("from_arrayfire", error_message, error_code, -1);
    }
}

void copy(khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        af_retain_array(result, var.copy().get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("copy", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("copy", error_message, error_code, -1);
    }
}

void khiva_as(khiva_array *array, const int *type, khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());
        khiva::dtype dt = static_cast<khiva::dtype>(*type);
        af::array r = var.as(dt);
        af_retain_array(result, r.get());
        *error_code = 0;
    } catch (const std::exception &e) {
        fill_error("khiva_as", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("khiva_as", error_message, error_code, -1);
    }
}
