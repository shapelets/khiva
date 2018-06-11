# Copyright (c) 2018 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

CMAKE_MINIMUM_REQUIRED(VERSION 3.9.6)
PROJECT(Khiva
    LANGUAGES C CXX)
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

# Using C++ 11
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON) # Required
SET(CMAKE_CXX_EXTENSIONS ON) # with compiler extensions like gnu++11

# Load from environment variables
LIST(APPEND CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH})
LIST(APPEND CMAKE_PREFIX_PATH $ENV{CMAKE_PREFIX_PATH})
LIST(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Set the build type
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "Release" 
      CACHE STRING "Build configuration 'Release' or 'Debug'."
      FORCE)
ENDIF()

# Compile-time options
OPTION(KHIVA_BUILD_TESTS "Build tests of the Khiva library" ON)
OPTION(KHIVA_BUILD_BENCHMARKS "Build benchmarks of the Khiva library" ON)
OPTION(KHIVA_BUILD_EXAMPLES "Build examples of the Khiva library" ON)
OPTION(KHIVA_BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen, GraphViz and Sphinx)" ON)
OPTION(KHIVA_USE_CONAN "Use the conan package manager to download the dependencies of the Khiva library" ON)

IF(KHIVA_USE_CONAN)
    INCLUDE(conan)

    IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
        SET(CONAN_CPPSTD 14)
    ELSE()
        SET(CONAN_CPPSTD 11)
    ENDIF()
    conan_cmake_run(CONANFILE conanfile.txt
                    BASIC_SETUP CMAKE_TARGETS
                    BUILD missing
                    SETTINGS cppstd=${CONAN_CPPSTD})

    # Bring conan generated dependencies
    INCLUDE(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
    CONAN_BASIC_SETUP()
ENDIF()

# Set the base directory to parent so src and include become equaly visible
SET(KHIVALIB_BASE_DIR ${PROJECT_SOURCE_DIR})
# Define source directory
SET(KHIVALIB_SRC "${KHIVALIB_BASE_DIR}/src")
# Define include directory
SET(KHIVALIB_INC "${KHIVALIB_BASE_DIR}/include")
# Library Name
SET(KHIVALIB "khiva")

# Bring KHIVA version and installation directories
INCLUDE(KhivaVersion)
INCLUDE(KhivaInstallDirs)

SET(PROJECT_VERSION ${VERSION_SHORT})

# These config files will be installed so we need to set the install_destination
# path relative to the install path
INCLUDE(CMakePackageConfigHelpers)
WRITE_BASIC_PACKAGE_VERSION_FILE(
    cmake/install/KhivaConfigVersion.cmake
    COMPATIBILITY SameMajorVersion)

SET(INCLUDE_DIRS include)
SET(CMAKE_DIR ${KHIVA_INSTALL_CMAKE_DIR})
CONFIGURE_PACKAGE_CONFIG_FILE(
    ${KHIVALIB_BASE_DIR}/cmake/KhivaConfig.cmake.in
    cmake/install/KhivaConfig.cmake
    INSTALL_DESTINATION "${KHIVA_INSTALL_CMAKE_DIR}"
    PATH_VARS INCLUDE_DIRS CMAKE_DIR)

IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # Turn compiler warnings up to 11
    STRING(REGEX REPLACE "[-/]W[1-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
ELSEIF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -pedantic -Wno-gnu-zero-variadic-macro-arguments -Wint-conversion -Wshorten-64-to-32")
ELSEIF(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -pedantic")
ENDIF()

# build items in subdirectories
ADD_SUBDIRECTORY(src)

# build examples
IF(KHIVA_BUILD_EXAMPLES)
    ADD_SUBDIRECTORY(examples)
ENDIF()

# build tests
IF(KHIVA_BUILD_TESTS)
    ENABLE_TESTING()
    ADD_SUBDIRECTORY(test)
ENDIF()

# build benchmarks
IF(KHIVA_BUILD_BENCHMARKS)
    ADD_SUBDIRECTORY(benchmarks)
ENDIF()

# build bindings for c and jni
ADD_SUBDIRECTORY(bindings)

# build items in subdirectories
IF(KHIVA_BUILD_DOCUMENTATION)
    ADD_SUBDIRECTORY(doc)
ENDIF()

INSTALL(DIRECTORY licenses/
    DESTINATION ${KHIVA_INSTALL_LICENSES_DIR}
    COMPONENT licenses)

INCLUDE(CPackConfig)
