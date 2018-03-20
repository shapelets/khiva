// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <tsa/library.h>
#include <tsa_c/library.h>

#ifdef __cplusplus
extern "C" {
#endif

void info() { tsa::library::backendInfo(); }

void set_backend(int *backend) { tsa::library::setBackend(static_cast<tsa::library::Backend>(*backend)); }

void get_backend(int *backend) { *backend = static_cast<int>(tsa::library::getBackend()); }

void get_backends(int *backends) { *backends = tsa::library::getBackends(); }

void set_device(int *device) { tsa::library::setDevice(*device); }

void get_device(int *device) { *device = tsa::library::getDevice(); }

#ifdef __cplusplus
}
#endif