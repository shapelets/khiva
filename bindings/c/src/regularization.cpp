// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/regularization.h>
#include <khiva_c/regularization.h>
#include <khiva_c/internal/util.h>

void group_by(khiva_array *array, int *aggregation_function, int *n_columns_key, int *n_columns_value,
              khiva_array *result, int *error_code, char *error_message) {
    try {
        af::array var = af::array(*array);
        af_retain_array(array, var.get());

        switch (*aggregation_function) {
            case 0:
                af_retain_array(result,
                                khiva::regularization::groupBy(var, af::mean, *n_columns_key, *n_columns_value).get());
                *error_code = 0;
                break;
            case 1:
                af_retain_array(
                    result, khiva::regularization::groupBy(var, af::median, *n_columns_key, *n_columns_value).get());
                *error_code = 0;
                break;
            case 2:
                af_retain_array(result,
                                khiva::regularization::groupBy(var, af::min, *n_columns_key, *n_columns_value).get());
                *error_code = 0;
                break;
            case 3:
                af_retain_array(result,
                                khiva::regularization::groupBy(var, af::max, *n_columns_key, *n_columns_value).get());
                *error_code = 0;
                break;
            case 4:
                af_retain_array(result,
                                khiva::regularization::groupBy(var, af::stdev, *n_columns_key, *n_columns_value).get());
                *error_code = 0;
                break;
            case 5:
                af_retain_array(result,
                                khiva::regularization::groupBy(var, af::var, *n_columns_key, *n_columns_value).get());
                *error_code = 0;
                break;
            default:
                af_retain_array(result,
                                khiva::regularization::groupBy(var, af::mean, *n_columns_key, *n_columns_value).get());
                *error_code = 0;
                break;
        }
    } catch (const std::exception &e) {
        fill_error("group_by", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("group_by", error_message, error_code, -1);
    }
}
