// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_BINDINGC_UTIL_H
#define KHIVA_BINDINGC_UTIL_H

#include <arrayfire.h>
#include <khiva_c/defines.h>

#define KHIVA_ERROR_LENGTH 256

void check_and_retain_arrays(khiva_array *a, khiva_array *b, af::array &var_a, af::array &var_b);

void fill_error(const char *function_name, const char *src_message, char *dst_message, int *error_code, int error);

void fill_unknown(const char *function_name, char *dst_message, int *error_code, int error);

#endif
