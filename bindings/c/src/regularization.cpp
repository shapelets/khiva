// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa/regularization.h>
#include <tsa_c/regularization.h>

#ifdef __cplusplus
extern "C" {
#endif

TSAAPI void group_by(af_array *array, int *aggregation_function, int *n_columns_key, int *n_columns_value,
                     af_array *result) {
    af::array var = af::array(*array);
    af_retain_array(array, var.get());

    switch (*aggregation_function) {
        case 0:
            af_retain_array(result,
                            tsa::regularization::groupBy(var, af::mean, *n_columns_key, *n_columns_value).get());
            break;
        case 1:
            af_retain_array(result,
                            tsa::regularization::groupBy(var, af::median, *n_columns_key, *n_columns_value).get());
            break;
        case 2:
            af_retain_array(result, tsa::regularization::groupBy(var, af::min, *n_columns_key, *n_columns_value).get());
            break;
        case 3:
            af_retain_array(result, tsa::regularization::groupBy(var, af::max, *n_columns_key, *n_columns_value).get());
            break;
        case 4:
            af_retain_array(result,
                            tsa::regularization::groupBy(var, af::stdev, *n_columns_key, *n_columns_value).get());
            break;
        case 5:
            af_retain_array(result, tsa::regularization::groupBy(var, af::var, *n_columns_key, *n_columns_value).get());
            break;
        default:
            af_retain_array(result,
                            tsa::regularization::groupBy(var, af::mean, *n_columns_key, *n_columns_value).get());
            break;
    }
}

#ifdef __cplusplus
}
#endif