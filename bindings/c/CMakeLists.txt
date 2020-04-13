# Copyright (c) 2019 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

cmake_minimum_required(VERSION 3.9.6)

project(KHIVALIB_C)

# Compile with C++11 support.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define source directory
set(KHIVALIB_C_SRC "${PROJECT_SOURCE_DIR}/src")
# Define include directories
set(KHIVALIB_C_INC "${PROJECT_SOURCE_DIR}/include")

# Library Name
set(KHIVALIB_C "khiva_c")

# Sources to add to compilation
set(KHIVALIB_C_SOURCES ${KHIVALIB_C_SRC}/array.cpp
                       ${KHIVALIB_C_SRC}/clustering.cpp
                       ${KHIVALIB_C_SRC}/dimensionality.cpp
                       ${KHIVALIB_C_SRC}/distances.cpp
                       ${KHIVALIB_C_SRC}/features.cpp
                       ${KHIVALIB_C_SRC}/library.cpp
                       ${KHIVALIB_C_SRC}/linalg.cpp
                       ${KHIVALIB_C_SRC}/matrix.cpp
                       ${KHIVALIB_C_SRC}/normalization.cpp
                       ${KHIVALIB_C_SRC}/polynomial.cpp
                       ${KHIVALIB_C_SRC}/regression.cpp
                       ${KHIVALIB_C_SRC}/regularization.cpp
                       ${KHIVALIB_C_SRC}/statistics.cpp
                       ${KHIVALIB_C_SRC}/util.cpp)

# Headers to add to compilation
set(KHIVALIB_C_HEADERS ${KHIVALIB_C_INC}/khiva_c/array.h
                       ${KHIVALIB_C_INC}/khiva_c/clustering.h
                       ${KHIVALIB_C_INC}/khiva_c/defines.h
                       ${KHIVALIB_C_INC}/khiva_c/dimensionality.h
                       ${KHIVALIB_C_INC}/khiva_c/distances.h
                       ${KHIVALIB_C_INC}/khiva_c/features.h
                       ${KHIVALIB_C_INC}/khiva_c/library.h
                       ${KHIVALIB_C_INC}/khiva_c/linalg.h
                       ${KHIVALIB_C_INC}/khiva_c/matrix.h
                       ${KHIVALIB_C_INC}/khiva_c/normalization.h
                       ${KHIVALIB_C_INC}/khiva_c/polynomial.h
                       ${KHIVALIB_C_INC}/khiva_c/regression.h
                       ${KHIVALIB_C_INC}/khiva_c/regularization.h
                       ${KHIVALIB_C_INC}/khiva_c/statistics.h
                       ${KHIVALIB_C_INC}/khiva_c/internal/util.h)

# The output is a static library
add_library(${KHIVALIB_C} SHARED ${KHIVALIB_C_HEADERS} ${KHIVALIB_C_SOURCES})

# Declare include directories
target_include_directories(${KHIVALIB_C} PUBLIC
        ${KHIVALIB_INC}
        ${KHIVALIB_INC}/internal
        ${KHIVALIB_C_INC})

# Declare compilation libraries
target_link_libraries(${KHIVALIB_C}
    PUBLIC ${KHIVALIB}
    PRIVATE ${CMAKE_DL_LIBS})

# Add compile definitions
target_compile_definitions(${KHIVALIB_C} PRIVATE KHIVA_C_EXPORTS)

# Add metadata
set_target_properties(${KHIVALIB_C} PROPERTIES
        FOLDER bindings
        VERSION ${VERSION_SHORT}
        SOVERSION ${VERSION_MAJOR}
        PUBLIC_HEADER "${KHIVALIB_C_INC}/khiva_c.h")

# Install bindings
# C binding
install(TARGETS ${KHIVALIB_C} DESTINATION ${KHIVA_INSTALL_LIB_DIR}
        COMPONENT c_binding
        PUBLIC_HEADER DESTINATION ${KHIVA_INSTALL_INC_DIR})

install(DIRECTORY ${KHIVALIB_C_INC}/
        DESTINATION ${KHIVA_INSTALL_INC_DIR}
        COMPONENT headers
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN ".gitignore" EXCLUDE
        PATTERN "internal/*.h" EXCLUDE
        )
