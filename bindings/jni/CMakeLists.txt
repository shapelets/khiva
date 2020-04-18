# Copyright (c) 2019 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
cmake_minimum_required(VERSION 3.9.6)
project(KHIVALIB_JNI C CXX)

# Find the ArrayFire package.
find_package(ArrayFire CONFIG REQUIRED)
find_package(JNI)
if (NOT JNI_FOUND)
    message(FATAL_ERROR "JDK not found. Please install JDK or disable building JNI bindings by using the flag KHIVA_BUILD_JNI_BINDINGS.")
endif ()

# Compile with C++11 support.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define source directory
set(KHIVALIB_JNI_SRC "${PROJECT_SOURCE_DIR}/src")
# Define include directories
set(KHIVALIB_JNI_INC "${PROJECT_SOURCE_DIR}/include")

# Sources to add to compilation
set(KHIVALIB_JNI_HEADERS ${KHIVALIB_JNI_INC}/khiva_jni/array.h
                         ${KHIVALIB_JNI_INC}/khiva_jni/clustering.h
                         ${KHIVALIB_JNI_INC}/khiva_jni/dimensionality.h
                         ${KHIVALIB_JNI_INC}/khiva_jni/distances.h
                         ${KHIVALIB_JNI_INC}/khiva_jni/features.h
                         ${KHIVALIB_JNI_INC}/khiva_jni/library.h
                         ${KHIVALIB_JNI_INC}/khiva_jni/linalg.h
                         ${KHIVALIB_JNI_INC}/khiva_jni/matrix.h
                         ${KHIVALIB_JNI_INC}/khiva_jni/normalization.h
                         ${KHIVALIB_JNI_INC}/khiva_jni/polynomial.h
                         ${KHIVALIB_JNI_INC}/khiva_jni/regression.h
                         ${KHIVALIB_JNI_INC}/khiva_jni/regularization.h
                         ${KHIVALIB_JNI_INC}/khiva_jni/statistics.h
                         ${KHIVALIB_JNI_INC}/khiva_jni/internal/utils.h)

# Sources to add to compilation
set(KHIVALIB_JNI_SOURCES ${KHIVALIB_JNI_SRC}/array.cpp
                         ${KHIVALIB_JNI_SRC}/clustering.cpp
                         ${KHIVALIB_JNI_SRC}/dimensionality.cpp
                         ${KHIVALIB_JNI_SRC}/distances.cpp
                         ${KHIVALIB_JNI_SRC}/features.cpp
                         ${KHIVALIB_JNI_SRC}/library.cpp
                         ${KHIVALIB_JNI_SRC}/linalg.cpp
                         ${KHIVALIB_JNI_SRC}/matrix.cpp
                         ${KHIVALIB_JNI_SRC}/normalization.cpp
                         ${KHIVALIB_JNI_SRC}/polynomial.cpp
                         ${KHIVALIB_JNI_SRC}/regression.cpp
                         ${KHIVALIB_JNI_SRC}/regularization.cpp
                         ${KHIVALIB_JNI_SRC}/statistics.cpp)

# Library Name
set(KHIVALIB_JNI "khiva_jni")

# The output is a static library
add_library(${KHIVALIB_JNI} SHARED ${KHIVALIB_JNI_HEADERS} ${KHIVALIB_JNI_SOURCES})

# Declare include directories
target_include_directories(${KHIVALIB_JNI}
        PUBLIC ${KHIVALIB_INC} PUBLIC ${KHIVALIB_JNI_INC}
        PRIVATE ${JNI_INCLUDE_DIRS})

# Declare compilation libraries
target_link_libraries(${KHIVALIB_JNI}
        PUBLIC ${KHIVALIB}
        PRIVATE ArrayFire::af
        ${CMAKE_DL_LIBS})

# Add metadata
set_target_properties(${KHIVALIB_JNI} PROPERTIES
        VERSION ${VERSION_SHORT}
        SOVERSION ${VERSION_MAJOR}
        FOLDER bindings
        PUBLIC_HEADER "${KHIVALIB_JNI_INC}/khiva_jni.h")

if(KHIVA_BUILD_TESTS)
    add_subdirectory(test)
endif()

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
