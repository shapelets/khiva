// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_BINDINGC_DEFINES_H
#define KHIVA_BINDINGC_DEFINES_H

#if defined(_WIN32) || defined(_MSC_VER)
#if defined(KHIVA_C_EXPORTS)
#define KHIVA_C_API __declspec(dllexport)
#else
#define KHIVA_C_API __declspec(dllimport)
#endif
#else
#define KHIVA_C_API
#endif

using khiva_array = void *;

#endif
