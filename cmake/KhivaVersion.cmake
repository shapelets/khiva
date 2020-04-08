# Copyright (c) 2019 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

set(VERSION_MAJOR ${Khiva_VERSION_MAJOR})
set(VERSION_MINOR ${Khiva_VERSION_MINOR})
set(VERSION_PATCH ${Khiva_VERSION_PATCH})
set(VERSION_SHORT "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

execute_process(
        COMMAND git log -1 --format=%h
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        OUTPUT_VARIABLE VERSION_SHA1
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

# dump version information down to a header file
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/khiva/version.h.in
               ${CMAKE_CURRENT_SOURCE_DIR}/include/khiva/version.h)

# dump version to the version test file
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test/versionTest.cpp.in
               ${CMAKE_CURRENT_SOURCE_DIR}/test/versionTest.cpp)
