// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/array.h>
#include <khiva/internal/util.h>
#include <khiva_c/array.h>
#include <khiva_c/internal/util.h>

#include <cstring>
#include <thread>

using namespace khiva;

void create_array(const void *data, unsigned ndims, const long long *dims, khiva_array *result, int type,
                  int *error_code, char *error_message) {
    try {
        auto array = array::createArray(data, ndims, dims, type);
        *result = array::increment_ref_count(array.get());
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void delete_array(khiva_array *array, int *error_code, char *error_message) {
    try {
        array::deleteArray(*array);
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void display(const khiva_array *array, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        khiva::array::print(var);
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void get_data(const khiva_array *array, void *data, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        khiva::array::getData(var, data);
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void get_dims(const khiva_array *array, long long *dims, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        af::dim4 d = khiva::array::getDims(var);
        std::copy(std::begin(d.dims), std::end(d.dims), dims);
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void get_type(const khiva_array *array, int *t, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        *t = khiva::array::getType(var);
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void join(int dim, const khiva_array *first, const khiva_array *second, khiva_array *result, int *error_code,
          char *error_message) {
    try {
        auto var1 = array::from_af_array(*first);
        auto var2 = array::from_af_array(*second);
        af::array r = khiva::array::join(dim, var1, var2);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void khiva_add(const khiva_array *lhs, const khiva_array *rhs, khiva_array *result, int *error_code,
               char *error_message) {
    try {
        auto var1 = array::from_af_array(*lhs);
        auto var2 = array::from_af_array(*rhs);
        auto r = var1 + var2;
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void khiva_mul(const khiva_array *lhs, const khiva_array *rhs, khiva_array *result, int *error_code,
               char *error_message) {
    try {
        auto var1 = array::from_af_array(*lhs);
        auto var2 = array::from_af_array(*rhs);
        auto r = var1 * var2;
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void khiva_sub(const khiva_array *lhs, const khiva_array *rhs, khiva_array *result, int *error_code,
               char *error_message) {
    try {
        auto var1 = array::from_af_array(*lhs);
        auto var2 = array::from_af_array(*rhs);
        auto r = var1 - var2;
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void khiva_div(const khiva_array *lhs, const khiva_array *rhs, khiva_array *result, int *error_code,
               char *error_message) {
    try {
        auto var1 = array::from_af_array(*lhs);
        auto var2 = array::from_af_array(*rhs);
        auto r = var1 / var2;
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void khiva_mod(const khiva_array *lhs, const khiva_array *rhs, khiva_array *result, int *error_code,
               char *error_message) {
    try {
        auto var1 = array::from_af_array(*lhs);
        auto var2 = array::from_af_array(*rhs);
        auto r = var1 % var2;
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void khiva_pow(const khiva_array *lhs, const khiva_array *rhs, khiva_array *result, int *error_code,
               char *error_message) {
    try {
        auto var1 = array::from_af_array(*lhs);
        auto var2 = array::from_af_array(*rhs);
        auto r = af::pow(var1, var2);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void khiva_lt(const khiva_array *lhs, const khiva_array *rhs, khiva_array *result, int *error_code,
              char *error_message) {
    try {
        auto var1 = array::from_af_array(*lhs);
        auto var2 = array::from_af_array(*rhs);
        auto r = var1 < var2;
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void khiva_gt(const khiva_array *lhs, const khiva_array *rhs, khiva_array *result, int *error_code,
              char *error_message) {
    try {
        auto var1 = array::from_af_array(*lhs);
        auto var2 = array::from_af_array(*rhs);
        auto r = var1 > var2;
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void khiva_le(const khiva_array *lhs, const khiva_array *rhs, khiva_array *result, int *error_code,
              char *error_message) {
    try {
        auto var1 = array::from_af_array(*lhs);
        auto var2 = array::from_af_array(*rhs);
        auto r = var1 <= var2;
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void khiva_ge(const khiva_array *lhs, const khiva_array *rhs, khiva_array *result, int *error_code,
              char *error_message) {
    try {
        auto var1 = array::from_af_array(*lhs);
        auto var2 = array::from_af_array(*rhs);
        auto r = var1 >= var2;
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void khiva_eq(const khiva_array *lhs, const khiva_array *rhs, khiva_array *result, int *error_code,
              char *error_message) {
    try {
        auto var1 = array::from_af_array(*lhs);
        auto var2 = array::from_af_array(*rhs);
        auto r = var1 == var2;
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void khiva_ne(const khiva_array *lhs, const khiva_array *rhs, khiva_array *result, int *error_code,
              char *error_message) {
    try {
        auto var1 = array::from_af_array(*lhs);
        auto var2 = array::from_af_array(*rhs);
        auto r = var1 != var2;
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void khiva_bitand(const khiva_array *lhs, const khiva_array *rhs, khiva_array *result, int *error_code,
                  char *error_message) {
    try {
        auto var1 = array::from_af_array(*lhs);
        auto var2 = array::from_af_array(*rhs);
        auto r = var1 & var2;
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void khiva_bitor(const khiva_array *lhs, const khiva_array *rhs, khiva_array *result, int *error_code,
                 char *error_message) {
    try {
        auto var1 = array::from_af_array(*lhs);
        auto var2 = array::from_af_array(*rhs);
        auto r = var1 | var2;
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void khiva_bitxor(const khiva_array *lhs, const khiva_array *rhs, khiva_array *result, int *error_code,
                  char *error_message) {
    try {
        auto var1 = array::from_af_array(*lhs);
        auto var2 = array::from_af_array(*rhs);
        auto r = (!var1) != !var2;
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void khiva_bitshiftl(const khiva_array *array, int n, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        af::array r = var << n;
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void khiva_bitshiftr(const khiva_array *array, int n, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        af::array r = var >> n;
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void khiva_not(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        af::array r = !var;
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void khiva_transpose(const khiva_array *array, bool conjugate, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto r = af::transpose(var, conjugate);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void khiva_col(const khiva_array *array, int index, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        af::array r = var.col(index);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void khiva_cols(const khiva_array *array, int first, int last, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        af::array r = var.cols(first, last);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void khiva_row(const khiva_array *array, int index, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        af::array r = var.row(index);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void khiva_rows(const khiva_array *array, int first, int last, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        af::array r = var.rows(first, last);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void khiva_matmul(const khiva_array *lhs, const khiva_array *rhs, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var1 = array::from_af_array(*lhs);
        auto var2 = array::from_af_array(*rhs);
        auto r = af::matmul(var1, var2);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void from_arrayfire(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    try {
        *result = array::increment_ref_count(*array);
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void copy(const khiva_array *array, khiva_array *result, int *error_code, char *error_message) {
    *error_code = af_copy_array(result, *array);    
}

void khiva_as(khiva_array *array, int type, khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        auto dt = static_cast<khiva::dtype>(type);
        auto r = var.as(dt);
        *result = array::increment_ref_count(r.get());
        *error_code = 0;
    } catch (af::exception &e) {
        util::fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        util::fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}
