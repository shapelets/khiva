// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#if defined(_WIN32) || defined(_MSC_VER)
// http://msdn.microsoft.com/en-us/library/b0084kay(v=VS.80).aspx
// http://msdn.microsoft.com/en-us/library/3y1sfaz2%28v=VS.80%29.aspx
#define KHIVAAPI __declspec(dllexport)
#else
#define KHIVAAPI
#endif

typedef void *khiva_array;
