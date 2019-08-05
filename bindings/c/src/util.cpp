// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva_c/util.h>
#include <string.h>

void check_and_retain_arrays(khiva_array *a, khiva_array *b, af::array &var_a, af::array &var_b) {
    if (a == b) {
        var_a = af::array(*a);
        af_retain_array(a, var_a.get());
        var_b = var_a;
    } else {
        var_a = af::array(*a);
        af_retain_array(a, var_a.get());
        var_b = af::array(*b);
        af_retain_array(b, var_b.get());
    }
}

void fill_error(const char * function_name, const char* src_message, char* dst_message, int * error_code, int error) {

    // Fill error_message
    int len = strlen(function_name) + strlen(src_message) + strlen(": ");
    char * total_message = (char*) malloc(sizeof(char)*len);
    strcpy(total_message, function_name);
    strcat(total_message, ": ");
    strcat(total_message, src_message);
    strncpy(dst_message, total_message, ERROR_LENGTH-1);
    if (strlen(src_message) >= ERROR_LENGTH-1 ){
        dst_message[ERROR_LENGTH-1] = '\0';
    }
    free(total_message);

    // Fill error_code
    *error_code = error;
}

void fill_unknown(const char * function_name, char * dst_message, int * error_code, int error){
    fill_error(function_name, "Unknown error.", dst_message, error_code, error);
}
