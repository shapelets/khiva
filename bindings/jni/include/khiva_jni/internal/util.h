// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_BINDINGJAVA_UTIL_H
#define KHIVA_BINDINGJAVA_UTIL_H

#include <arrayfire.h>

namespace khiva {
namespace bindings {
namespace jni {

void check_and_retain_arrays(af_array &a, af_array &b, af::array &var_a, af::array &var_b);

}
}
}

#endif
