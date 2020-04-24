// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/internal/util.h>

std::string khiva::util::khiva_file_path(const std::string &path) {
    auto pos = path.rfind("khiva");
    return (pos == std::string::npos) ? path : path.substr(pos);
}

af_array khiva::util::increment_ref_count(const af_array array) {
    af_array ptr;
    auto af_error = af_retain_array(&ptr, array);
    if (af_error != AF_SUCCESS) {
        throw af::exception("Error retaining array", __func__, khiva_file_path(__FILE__).c_str(), __LINE__, af_error);
    }
    return ptr;
}
