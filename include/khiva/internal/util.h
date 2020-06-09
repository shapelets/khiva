// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_CORE_UTIL_H
#define KHIVA_CORE_UTIL_H

#ifndef BUILDING_KHIVA
#error Internal headers cannot be included from user code
#endif

#include <arrayfire.h>
#include <string>

namespace khiva {
namespace util {

std::string khiva_file_path(const std::string &path);

}  // namespace util
}  // namespace khiva

#endif