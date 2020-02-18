# Copyright (c) 2019 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

cmake_minimum_required(VERSION 3.9.6)
project(Khiva LANGUAGES C CXX)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Using C++ 11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Required
set(CMAKE_CXX_EXTENSIONS ON) # with compiler extensions like gnu++11

# Add compile definition to avoid external users of the library to include internal headers
add_definitions(-DBUILDING_KHIVA)

# Avoid conflicts with min and max functions
if(WIN32)
    add_definitions(-DNOMINMAX)
endif()
# Load from environment variables
list(APPEND CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH})
list(APPEND CMAKE_PREFIX_PATH $ENV{CMAKE_PREFIX_PATH})
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Set the build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" 
      CACHE STRING "Build configuration 'Release' or 'Debug'."
      FORCE)
endif()

# Compile-time options
option(KHIVA_BUILD_TESTS "Build tests of the Khiva library" ON)
option(KHIVA_BUILD_BENCHMARKS "Build benchmarks of the Khiva library" ON)
option(KHIVA_BUILD_EXAMPLES "Build examples of the Khiva library" ON)
option(KHIVA_BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen, GraphViz and Sphinx)" ON)
option(KHIVA_USE_CONAN "Use the conan package manager to download the dependencies of the Khiva library" ON)
option(KHIVA_ENABLE_COVERAGE "This flag anables Code Coverage of the code" OFF)
option(KHIVA_BUILD_C_BINDINGS "Build C bindings" ON)
option(KHIVA_BUILD_JNI_BINDINGS "Build JNI bindings" ON)

if(KHIVA_ENABLE_COVERAGE AND NOT WIN32)
    # Setting compiler flags for code coverage
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
endif()

if(KHIVA_USE_CONAN)
    # Bring conan generated dependencies
    if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
        include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
    else()
        message(WARNING "The file conanbuildinfo.cmake does not exist, you have to run conan install first.\n"
                        "Check the following instructions to run conan installation:\n"
                        "https://github.com/shapelets/khiva/blob/master/doc/markdown/INSTALLATION.md#build-from-source-code-1")
    endif()
    CONAN_BASIC_SETUP(KEEP_RPATHS)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}) 
endif()

# Set the base directory to parent so src and include become equaly visible
set(KHIVALIB_BASE_DIR ${PROJECT_SOURCE_DIR})
# Define source directory
set(KHIVALIB_SRC "${KHIVALIB_BASE_DIR}/src")
# Define include directory
set(KHIVALIB_INC "${KHIVALIB_BASE_DIR}/include")
# Library Name
set(KHIVALIB "khiva")

# Bring KHIVA version and installation directories
include(KhivaVersion)
include(KhivaInstallDirs)

set(PROJECT_VERSION ${VERSION_SHORT})

# These config files will be installed so we need to set the install_destination
# path relative to the install path
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    cmake/install/KhivaConfigVersion.cmake
    COMPATIBILITY SameMajorVersion)

set(INCLUDE_DIRS include)
set(CMAKE_DIR ${KHIVA_INSTALL_CMAKE_DIR})
configure_package_config_file(
    ${KHIVALIB_BASE_DIR}/cmake/KhivaConfig.cmake.in
    cmake/install/KhivaConfig.cmake
    INSTALL_DESTINATION "${KHIVA_INSTALL_CMAKE_DIR}"
    PATH_VARS INCLUDE_DIRS CMAKE_DIR)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # Turn compiler warnings up to 11
    string(REGEX REPLACE "[-/]W[1-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -pedantic -Wno-gnu-zero-variadic-macro-arguments -Wint-conversion -Wshorten-64-to-32")
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -pedantic")
endif()

# build items in subdirectories
add_subdirectory(src)

# build examples
if(KHIVA_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# build tests
if(KHIVA_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

# build benchmarks
if(KHIVA_BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()

# build bindings for c and jni
add_subdirectory(bindings)

# build items in subdirectories
if(KHIVA_BUILD_DOCUMENTATION)
    add_subdirectory(doc)
endif()

install(DIRECTORY licenses/
    DESTINATION ${KHIVA_INSTALL_LICENSES_DIR}
    COMPONENT licenses)

include(CPackConfig)
