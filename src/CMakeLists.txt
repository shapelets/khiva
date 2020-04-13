# Copyright (c) 2019 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

cmake_minimum_required(VERSION 3.9.6)

project(KHIVALIB)

include(CheckLanguage)

# Compile with C++11 support.
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

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
find_package(ArrayFire CONFIG REQUIRED)
find_package(Boost REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Sources to add to compilation
set(KHIVALIB_SOURCES ${KHIVALIB_SRC}/khiva/array.cpp
                     ${KHIVALIB_SRC}/khiva/clustering.cpp
                     ${KHIVALIB_SRC}/khiva/dimensionality.cpp
                     ${KHIVALIB_SRC}/khiva/distances.cpp
                     ${KHIVALIB_SRC}/khiva/features.cpp
                     ${KHIVALIB_SRC}/khiva/library.cpp
                     ${KHIVALIB_SRC}/khiva/libraryInternal.cpp
                     ${KHIVALIB_SRC}/khiva/linalg.cpp
                     ${KHIVALIB_SRC}/khiva/matrix.cpp
                     ${KHIVALIB_SRC}/khiva/matrixInternal.cpp
                     ${KHIVALIB_SRC}/khiva/normalization.cpp
                     ${KHIVALIB_SRC}/khiva/polynomial.cpp
                     ${KHIVALIB_SRC}/khiva/regression.cpp
                     ${KHIVALIB_SRC}/khiva/regularization.cpp
                     ${KHIVALIB_SRC}/khiva/statistics.cpp
                     ${KHIVALIB_SRC}/khiva/version.cpp)

# Headers to add to compilation
set(KHIVALIB_HEADERS ${KHIVALIB_INC}/khiva/array.h
                     ${KHIVALIB_INC}/khiva/clustering.h
                     ${KHIVALIB_INC}/khiva/defines.h
                     ${KHIVALIB_INC}/khiva/dimensionality.h
                     ${KHIVALIB_INC}/khiva/distances.h
                     ${KHIVALIB_INC}/khiva/features.h
                     ${KHIVALIB_INC}/khiva/library.h
                     ${KHIVALIB_INC}/khiva/linalg.h
                     ${KHIVALIB_INC}/khiva/matrix.h
                     ${KHIVALIB_INC}/khiva/normalization.h
                     ${KHIVALIB_INC}/khiva/polynomial.h
                     ${KHIVALIB_INC}/khiva/regression.h
                     ${KHIVALIB_INC}/khiva/regularization.h
                     ${KHIVALIB_INC}/khiva/statistics.h
                     ${KHIVALIB_INC}/khiva/utils.h
                     ${KHIVALIB_INC}/khiva/version.h
                     ${KHIVALIB_INC}/khiva/internal/libraryInternal.h
                     ${KHIVALIB_INC}/khiva/internal/matrixInternal.h
                     ${KHIVALIB_INC}/khiva/internal/scopedHostPtr.h
                     ${KHIVALIB_INC}/khiva/internal/vectorUtil.h)

# The output is a static library
add_library(${KHIVALIB} SHARED ${KHIVALIB_HEADERS} ${KHIVALIB_SOURCES})

# Declare include directories
target_include_directories(${KHIVALIB} 
                        PRIVATE
                           ${SCAMP_INCLUDE_DIRS}
                        PUBLIC
                           $<BUILD_INTERFACE:${KHIVALIB_INC}>
                           $<BUILD_INTERFACE:${KHIVALIB_INC}/internal>
                           $<INSTALL_INTERFACE:${KHIVA_INSTALL_INC_DIR}>)

# Declare compilation libraries
target_link_libraries(${KHIVALIB}
	PRIVATE 
		scamp
		Eigen3::Eigen
        Boost::boost
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
