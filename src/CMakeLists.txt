# Copyright (c) 2019 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

cmake_minimum_required(VERSION 3.9.6)

include(CheckLanguage)

# Compile with C++11 support.
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

project(KHIVALIB) 

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

add_subdirectory(scamp)

# Find packages.
find_package(ArrayFire REQUIRED)
find_package(Boost REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Files to add to compilation
set(KHIVA_INTERNAL_SOURCES_PATH "${KHIVALIB_SRC}/khiva")
file(GLOB_RECURSE KHIVALIB_CODE 
    "${KHIVA_INTERNAL_SOURCES_PATH}/*.cpp"
    "${KHIVA_INTERNAL_SOURCES_PATH}/*.h"
    "${KHIVA_INTERNAL_SOURCES_PATH}/*.hpp"
    "${KHIVALIB_INC}/*.h" )

# The output is a static library
add_library(${KHIVALIB} SHARED ${KHIVALIB_CODE})

# Declare include directories
target_include_directories(${KHIVALIB} 
						PRIVATE
						   ${SCAMP_INCLUDE_DIRS}						
						   ${Boost_INCLUDE_DIRS}
						   ${EIGEN3_INCLUDE_DIRS}
						PUBLIC
                           $<BUILD_INTERFACE:${KHIVALIB_INC}>
                           $<BUILD_INTERFACE:${KHIVALIB_INC}/internal>
                           $<INSTALL_INTERFACE:${KHIVA_INSTALL_INC_DIR}>)

# Declare compilation libraries
target_link_libraries(${KHIVALIB}
	PRIVATE 
		scamp
	PUBLIC 
		$<IF:$<BOOL:${KHIVA_ONLY_CPU_BACKEND}>,ArrayFire::afcpu,ArrayFire::af>
		${CMAKE_DL_LIBS}
)


# Add compile definitions
target_compile_definitions(${KHIVALIB} PRIVATE KHIVA_EXPORTS PUBLIC AF_UNIFIED)

# Add metadata
set_target_properties(${KHIVALIB} PROPERTIES 
    VERSION ${VERSION_SHORT}
    SOVERSION ${VERSION_MAJOR}
    PUBLIC_HEADER "${KHIVALIB_INC}/khiva.h")

# Installation
install(TARGETS ${KHIVALIB}
        EXPORT Khiva
        COMPONENT core
        PUBLIC_HEADER DESTINATION ${KHIVA_INSTALL_INC_DIR}
        RUNTIME DESTINATION ${KHIVA_INSTALL_BIN_DIR}
        LIBRARY DESTINATION ${KHIVA_INSTALL_LIB_DIR}
        ARCHIVE DESTINATION ${KHIVA_INSTALL_LIB_DIR}
        INCLUDES DESTINATION ${KHIVA_INSTALL_INC_DIR})

install(EXPORT Khiva
         NAMESPACE Khiva::
         DESTINATION ${KHIVA_INSTALL_CMAKE_DIR}
         COMPONENT core)

export(EXPORT Khiva
        NAMESPACE Khiva::
        FILE cmake/KhivaTargets.cmake)

install(DIRECTORY ${KHIVALIB_INC}/ 
        DESTINATION ${KHIVA_INSTALL_INC_DIR}
        COMPONENT headers
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN ".gitignore" EXCLUDE
        PATTERN "internal/*.h" EXCLUDE
)

install(FILES ${CMAKE_BINARY_DIR}/cmake/install/KhivaConfig.cmake
              ${CMAKE_BINARY_DIR}/cmake/install/KhivaConfigVersion.cmake
              DESTINATION ${KHIVA_INSTALL_CMAKE_DIR}
              COMPONENT cmake)
