// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef _KHIVA_HEADER_
#define _KHIVA_HEADER_

#if defined(_WIN32) || defined(_MSC_VER)
#if defined(KHIVA_EXPORTS)
#define KHIVAAPI __declspec(dllexport)
#else
#define KHIVAAPI __declspec(dllimport)
#endif
#else
#define KHIVAAPI
#endif

#endif
