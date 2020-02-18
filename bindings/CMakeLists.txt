# Copyright (c) 2019 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

cmake_minimum_required(VERSION 3.9.6)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(KHIVALIB_INC "${KHIVALIB_BASE_DIR}/include")

# build bindings for c and jni

if (KHIVA_BUILD_C_BINDINGS)
    add_subdirectory(c)
endif ()

if (KHIVA_BUILD_JNI_BINDINGS)
    add_subdirectory(jni)
endif ()
