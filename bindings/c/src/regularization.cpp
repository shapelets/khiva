// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/array.h>
#include <khiva/regularization.h>
#include <khiva/internal/util.h>
#include <khiva_c/regularization.h>
#include <khiva_c/internal/util.h>

using namespace khiva;
using namespace khiva::util;

void group_by(const khiva_array *array, const int *aggregation_function, const int *n_columns_key, const int *n_columns_value,
              khiva_array *result, int *error_code, char *error_message) {
    try {
        auto var = array::from_af_array(*array);
        af::array res; 
        switch (*aggregation_function) {
            case 0:
                res = khiva::regularization::groupBy(var, af::mean, *n_columns_key, *n_columns_value);                
                break;
            case 1:
                res = khiva::regularization::groupBy(var, af::median, *n_columns_key, *n_columns_value);
                break;
            case 2:
                res = khiva::regularization::groupBy(var, af::min, *n_columns_key, *n_columns_value);
                break;
            case 3:
                res = khiva::regularization::groupBy(var, af::max, *n_columns_key, *n_columns_value);
                break;
            case 4:
                res = khiva::regularization::groupBy(var, af::stdev, *n_columns_key, *n_columns_value);
                break;
            case 5:
                res = khiva::regularization::groupBy(var, af::var, *n_columns_key, *n_columns_value);
                break;
            default:
                res = khiva::regularization::groupBy(var, af::mean, *n_columns_key, *n_columns_value);
                break;
        }
        *result = array::increment_ref_count(res.get());
        *error_code = 0;
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}
