# Copyright (c) 2018 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

CMAKE_MINIMUM_REQUIRED(VERSION 3.9.2)

# Find the ArrayFire package.
FIND_PACKAGE(ArrayFire REQUIRED)
PROJECT(KHIVALIB_C)

# Compile with C++11 support.
INCLUDE(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# Set the base directory to parent so src and include become
# equaly visible
SET(KHIVALIB_C_BASE_DIR "${PROJECT_SOURCE_DIR}")
# Define source directory
SET(KHIVALIB_C_SRC "${KHIVALIB_C_BASE_DIR}/src")
# Define include directories
SET(KHIVALIB_C_INC "${KHIVALIB_C_BASE_DIR}/include/")

# Library Name
SET(KHIVALIB_C "khiva_c")

# Files to add to compilation
FILE(GLOB_RECURSE KHIVALIB_C_CODE 
    "${KHIVALIB_C_SRC}/*.cpp"
    "${KHIVALIB_C_INC}*.h" )

# The output is a static library
ADD_LIBRARY(${KHIVALIB_C} SHARED ${KHIVALIB_C_CODE})

# Declare include directories
TARGET_INCLUDE_DIRECTORIES(${KHIVALIB_C} PUBLIC 
                           ${KHIVALIB_INC}
                           ${KHIVALIB_C_INC})

# Declare compilation libraries
TARGET_LINK_LIBRARIES(${KHIVALIB_C} PUBLIC
                      ${KHIVALIB} PRIVATE
                      ${CMAKE_DL_LIBS})

# Add metadata
SET_TARGET_PROPERTIES(${KHIVALIB_C} PROPERTIES
    VERSION ${VERSION_SHORT}
    SOVERSION ${VERSION_MAJOR}
    PUBLIC_HEADER "${KHIVALIB_C_INC}khiva_c.h")

# Install bindings
# C binding
INSTALL(TARGETS ${KHIVALIB_C} DESTINATION ${KHIVA_INSTALL_LIB_DIR}
        COMPONENT c_binding
        PUBLIC_HEADER DESTINATION ${KHIVA_INSTALL_INC_DIR})

INSTALL(DIRECTORY ${KHIVALIB_C_INC} 
        DESTINATION ${KHIVA_INSTALL_INC_DIR}
        COMPONENT headers
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN ".gitignore" EXCLUDE
)
