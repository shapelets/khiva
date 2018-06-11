// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#if defined(_WIN32) || defined(_MSC_VER)
// http://msdn.microsoft.com/en-us/library/b0084kay(v=VS.80).aspx
// http://msdn.microsoft.com/en-us/library/3y1sfaz2%28v=VS.80%29.aspx
#define DLL_EXPORT __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
#define DLL_IMPORT __declspec(dllimport)
#else
#define KHIVAAPI
#define DLL_EXPORT
#define DLL_IMPORT
#endif

#ifdef KHIVA_STATICLIB
#define KHIVAAPI
#else
#if defined(BUILDING_KHIVA_DLL)
#  define KHIVAAPI DLL_EXPORT
#else
#  define KHIVAAPI DLL_IMPORT
#endif
#endif

typedef void *khiva_array;
