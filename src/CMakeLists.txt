# Copyright (c) 2019 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

CMAKE_MINIMUM_REQUIRED(VERSION 3.9.6)

include(CheckLanguage)

# Compile with C++11 support.
SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_STANDARD_REQUIRED ON) 

PROJECT(KHIVALIB) 

if(NOT ${KHIVA_ONLY_CPU_BACKEND})
	check_language(CUDA)
endif()

if(CMAKE_CUDA_COMPILER)
	message(STATUS "CUDA compiler found: ${CMAKE_CUDA_COMPILER}")
	enable_language(CUDA)
  	add_definitions("-D_HAS_CUDA_")
  	include_directories(${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})
elseif(${KHIVA_ONLY_CPU_BACKEND})
else()
	message(STATUS "No CUDA compiler found, building SCAMP without CUDA.")
endif() 

if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/scamp/SCAMP/CMakeLists.txt")
	message(FATAL_ERROR "git submodule was not initialized.")
endif()

ADD_SUBDIRECTORY(scamp)

# Find the ArrayFire package.
FIND_PACKAGE(ArrayFire REQUIRED)

SET(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Files to add to compilation
SET(KHIVA_INTERNAL_SOURCES_PATH "${KHIVALIB_SRC}/khiva")
FILE(GLOB_RECURSE KHIVALIB_CODE 
    "${KHIVA_INTERNAL_SOURCES_PATH}/*.cpp"
    "${KHIVA_INTERNAL_SOURCES_PATH}/*.h"
    "${KHIVA_INTERNAL_SOURCES_PATH}/*.hpp"
    "${KHIVALIB_INC}/*.h" )

# The output is a static library
ADD_LIBRARY(${KHIVALIB} SHARED ${KHIVALIB_CODE})

# Declare include directories
TARGET_INCLUDE_DIRECTORIES(${KHIVALIB} 
						PRIVATE
						   ${SCAMP_INCLUDE_DIRS}						
						PUBLIC
                           $<BUILD_INTERFACE:${KHIVALIB_INC}>
                           $<INSTALL_INTERFACE:${KHIVA_INSTALL_INC_DIR}>
                           ${ArrayFire_INCLUDE_DIRS})

# Declare compilation libraries
TARGET_LINK_LIBRARIES(${KHIVALIB}
	PRIVATE 
		scamp
	PUBLIC 
		$<IF:$<BOOL:${KHIVA_ONLY_CPU_BACKEND}>,ArrayFire::afcpu,ArrayFire::af>
		${CMAKE_DL_LIBS}
)


# Add compile definitions
TARGET_COMPILE_DEFINITIONS(${KHIVALIB} PRIVATE KHIVA_EXPORTS PUBLIC AF_UNIFIED)

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
