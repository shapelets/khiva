// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_CORE_PRIVATE_HOST_PTR_H
#define KHIVA_CORE_PRIVATE_HOST_PTR_H

#ifndef BUILDING_KHIVA
#error Internal headers cannot be included from user code
#endif

#include <arrayfire.h>

#include <memory>

namespace khiva {
namespace utils {

template <typename T>
using ScopedHostPtr = std::unique_ptr<T[], decltype(&af::freeHost)>;

template <typename T>
ScopedHostPtr<T> makeScopedHostPtr(T *ptr) {
    return ScopedHostPtr<T>(ptr, &af::freeHost);
}
}  // namespace utils
}  // namespace khiva

#endif