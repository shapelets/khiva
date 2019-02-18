# Copyright (c) 2019 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

CMAKE_MINIMUM_REQUIRED(VERSION 3.9.6)
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

SET(KHIVALIB_INC "${KHIVALIB_BASE_DIR}/include")

# build bindings for c and jni
ADD_SUBDIRECTORY(c)
ADD_SUBDIRECTORY(jni)
