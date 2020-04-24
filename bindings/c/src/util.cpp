// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/internal/util.h>
#include <khiva_c/internal/util.h>

#include <algorithm>

void khiva::util::fill_error(const char *function_name, const char *src_message, char *dst_message) {
    auto msg = std::string(function_name);
    msg += ": ";
    msg += src_message;
    auto size = std::min(KHIVA_ERROR_LENGTH, msg.size());
    msg.copy(dst_message, size - 1);
    dst_message[size - 1] = '\0';
}