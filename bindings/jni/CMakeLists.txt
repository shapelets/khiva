# Copyright (c) 2019 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

CMAKE_MINIMUM_REQUIRED(VERSION 3.9.6)

# Find the ArrayFire package.
FIND_PACKAGE(ArrayFire REQUIRED)
FIND_PACKAGE(JNI REQUIRED)
PROJECT(KHIVALIB_JNI)

# Compile with C++11 support.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the base directory to parent so src and include become
# equaly visible
SET(KHIVALIB_JNI_BASE_DIR "${PROJECT_SOURCE_DIR}")
# Define source directory
SET(KHIVALIB_JNI_SRC "${KHIVALIB_JNI_BASE_DIR}/src")
# Define include directories
SET(KHIVALIB_JNI_INC "${KHIVALIB_JNI_BASE_DIR}/include")

# Library Name
SET(KHIVALIB_JNI "khiva_jni")

# Files to add to compilation
FILE(GLOB_RECURSE KHIVALIB_JNI_CODE 
    "${KHIVALIB_JNI_SRC}/*.cpp"
    "${KHIVALIB_JNI_INC}/*.h" )

# The output is a static library
ADD_LIBRARY(${KHIVALIB_JNI} SHARED ${KHIVALIB_JNI_CODE})

# Declare include directories
TARGET_INCLUDE_DIRECTORIES(${KHIVALIB_JNI} PUBLIC 
                           ${KHIVALIB_INC}
                           ${KHIVALIB_JNI_INC} PRIVATE
                           ${ArrayFire_INCLUDE_DIRS}
                           ${JNI_INCLUDE_DIRS})

# Declare compilation libraries
TARGET_LINK_LIBRARIES(${KHIVALIB_JNI} PUBLIC
                      ${KHIVALIB} PRIVATE
                      ${ArrayFire_Unified_LIBRARIES}
                      ${CMAKE_DL_LIBS})

# Add metadata
SET_TARGET_PROPERTIES(${KHIVALIB_JNI} PROPERTIES 
    VERSION ${VERSION_SHORT}
    SOVERSION ${VERSION_MAJOR}
	FOLDER bindings
    PUBLIC_HEADER "${KHIVALIB_JNI_INC}/khiva_jni.h")

# JNI binding
INSTALL(TARGETS ${KHIVALIB_JNI} DESTINATION ${KHIVA_INSTALL_LIB_DIR}
        COMPONENT jni_binding
        PUBLIC_HEADER DESTINATION ${KHIVA_INSTALL_INC_DIR})

INSTALL(DIRECTORY ${KHIVALIB_JNI_INC}/ 
        DESTINATION ${KHIVA_INSTALL_INC_DIR}
        COMPONENT headers
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN ".gitignore" EXCLUDE
)
