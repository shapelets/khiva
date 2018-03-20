// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <tsa_c/library.h>

#ifdef __cplusplus
extern "C" {
#endif

void info() { af::info(); }

void set_backend(int *backend) { af::setBackend(static_cast<af::Backend>(*backend)); }

void set_device(int *device) { af::setDevice(*device); }

#ifdef __cplusplus
}
#endif