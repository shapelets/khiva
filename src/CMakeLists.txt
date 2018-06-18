# Copyright (c) 2018 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

CMAKE_MINIMUM_REQUIRED(VERSION 3.9.6)
PROJECT(KHIVALIB)
# Find the ArrayFire package.
FIND_PACKAGE(ArrayFire REQUIRED)
# Find the Boost package
FIND_PACKAGE(Boost REQUIRED)
FIND_PACKAGE(Eigen3 CONFIG REQUIRED)

# Compile with C++11 support.
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Avoid conflicts with min and max functions
ADD_DEFINITIONS(-DNOMINMAX)

# Compile using unified backend
ADD_DEFINITIONS(-DAF_UNIFIED)

# Files to add to compilation
FILE(GLOB_RECURSE KHIVALIB_CODE 
    "${KHIVALIB_SRC}/*.cpp"
    "${KHIVALIB_INC}/*.h" )

IF(KHIVA_COVERAGE)
        ADD_COMPILE_OPTIONS(-fprofile-arcs -ftest-coverage)
ENDIF()

# The output is a static library
ADD_LIBRARY(${KHIVALIB} STATIC ${KHIVALIB_CODE} )

# Declare include directories
TARGET_INCLUDE_DIRECTORIES(${KHIVALIB} PUBLIC
                           $<BUILD_INTERFACE:${KHIVALIB_INC}>
                           $<INSTALL_INTERFACE:${KHIVA_INSTALL_INC_DIR}>
                           ${ArrayFire_INCLUDE_DIRS}
                           ${Boost_INCLUDE_DIRS})
IF(KHIVA_ONLY_CPU_BACKEND)
    # Declare compilation libraries
    TARGET_LINK_LIBRARIES(${KHIVALIB}
                      ${ArrayFire_CPU_LIBRARIES}
                      ${CMAKE_DL_LIBS})
ELSE()
    # Declare compilation libraries
    TARGET_LINK_LIBRARIES(${KHIVALIB}
            ${ArrayFire_Unified_LIBRARIES}
            ${CMAKE_DL_LIBS})
ENDIF()

# Add metadata
SET_TARGET_PROPERTIES(${KHIVALIB} PROPERTIES 
    VERSION ${VERSION_SHORT}
    SOVERSION ${VERSION_MAJOR}
    PUBLIC_HEADER "${KHIVALIB_INC}/khiva.h")

# Installation
INSTALL(TARGETS ${KHIVALIB}
        EXPORT Khiva
        COMPONENT core
        PUBLIC_HEADER DESTINATION ${KHIVA_INSTALL_INC_DIR}
        RUNTIME DESTINATION ${KHIVA_INSTALL_BIN_DIR}
        LIBRARY DESTINATION ${KHIVA_INSTALL_LIB_DIR}
        ARCHIVE DESTINATION ${KHIVA_INSTALL_LIB_DIR}
        INCLUDES DESTINATION ${KHIVA_INSTALL_INC_DIR})

INSTALL(EXPORT Khiva
         NAMESPACE Khiva::
         DESTINATION ${KHIVA_INSTALL_CMAKE_DIR}
         COMPONENT core)

EXPORT(EXPORT Khiva
        NAMESPACE Khiva::
        FILE cmake/KhivaTargets.cmake)

INSTALL(DIRECTORY ${KHIVALIB_INC}/ 
        DESTINATION ${KHIVA_INSTALL_INC_DIR}
        COMPONENT headers
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN ".gitignore" EXCLUDE
)

INSTALL(FILES ${CMAKE_BINARY_DIR}/cmake/install/KhivaConfig.cmake
              ${CMAKE_BINARY_DIR}/cmake/install/KhivaConfigVersion.cmake
              DESTINATION ${KHIVA_INSTALL_CMAKE_DIR}
              COMPONENT cmake)
