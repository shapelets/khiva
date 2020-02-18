# Copyright (c) 2019 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

cmake_minimum_required(VERSION 3.9.6)

# Find the ArrayFire package.
find_package(ArrayFire REQUIRED)
find_package(JNI)
if (NOT JNI_FOUND)
    message(FATAL_ERROR "JDK not found. Please install JDK or disable building JNI bindings by using the flag KHIVA_BUILD_JNI_BINDINGS.")
endif ()
project(KHIVALIB_JNI)

# Compile with C++11 support.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the base directory to parent so src and include become
# equaly visible
set(KHIVALIB_JNI_BASE_DIR "${PROJECT_SOURCE_DIR}")
# Define source directory
set(KHIVALIB_JNI_SRC "${KHIVALIB_JNI_BASE_DIR}/src")
# Define include directories
set(KHIVALIB_JNI_INC "${KHIVALIB_JNI_BASE_DIR}/include")

# Library Name
set(KHIVALIB_JNI "khiva_jni")

# Files to add to compilation
file(GLOB_RECURSE KHIVALIB_JNI_CODE
        "${KHIVALIB_JNI_SRC}/*.cpp"
        "${KHIVALIB_JNI_INC}/*.h")

# The output is a static library
add_library(${KHIVALIB_JNI} SHARED ${KHIVALIB_JNI_CODE})

# Declare include directories
target_include_directories(${KHIVALIB_JNI} PUBLIC
        ${KHIVALIB_INC}
        ${KHIVALIB_JNI_INC} PRIVATE
        ${JNI_INCLUDE_DIRS})

# Declare compilation libraries
target_link_libraries(${KHIVALIB_JNI} PUBLIC
        ${KHIVALIB} PRIVATE
        ArrayFire::af
        ${CMAKE_DL_LIBS})

# Add metadata
set_target_properties(${KHIVALIB_JNI} PROPERTIES
        VERSION ${VERSION_SHORT}
        SOVERSION ${VERSION_MAJOR}
        FOLDER bindings
        PUBLIC_HEADER "${KHIVALIB_JNI_INC}/khiva_jni.h")

# JNI binding
install(TARGETS ${KHIVALIB_JNI} DESTINATION ${KHIVA_INSTALL_LIB_DIR}
        COMPONENT jni_binding
        PUBLIC_HEADER DESTINATION ${KHIVA_INSTALL_INC_DIR})

install(DIRECTORY ${KHIVALIB_JNI_INC}/
        DESTINATION ${KHIVA_INSTALL_INC_DIR}
        COMPONENT headers
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN ".gitignore" EXCLUDE
        )
