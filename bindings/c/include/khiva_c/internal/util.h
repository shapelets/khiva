// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_BINDINGC_UTIL_H
#define KHIVA_BINDINGC_UTIL_H

#include <arrayfire.h>
#include <khiva_c/defines.h>

namespace khiva {
namespace util {

constexpr size_t KHIVA_ERROR_LENGTH = 256;

void fill_error(const char *function_name, const char *src_message, char *dst_message);


}  // namespace util
}  // namespace khiva

#endif
