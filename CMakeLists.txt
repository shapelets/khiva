CMAKE_MINIMUM_REQUIRED(VERSION 3.9.6)
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

# Using C++ 11
SET(CMAKE_CXX_STANDARD 11)

# bring conan generated dependencies
INCLUDE(conanbuildinfo.cmake)
CONAN_BASIC_SETUP()

# Load from environment variables
SET(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH})
SET(CMAKE_PREFIX_PATH $ENV{CMAKE_PREFIX_PATH})
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Set the build type
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "Release" 
      CACHE STRING "Build configuration 'Release' or 'Debug'."
      FORCE)
ENDIF()

# Set the base directory to parent so src and include become
# equaly visible
SET(TSALIB_BASE_DIR ${PROJECT_SOURCE_DIR})
# Define source directory
SET(TSALIB_SRC "${TSALIB_BASE_DIR}/src")
# Define include directory
SET(TSALIB_INC "${TSALIB_BASE_DIR}/include")
# Library Name
SET(TSALIB "tsa")

# git support
INCLUDE(GetGitRevisionDescription)

# get current version from git tags
git_describe(VERSION --tags --dirty=-dirty)

# parse the version information into pieces.
STRING(REGEX REPLACE "^v([0-9]+)\\..*" "\\1" VERSION_MAJOR "${VERSION}")
STRING(REGEX REPLACE "^v[0-9]+\\.([0-9]+).*" "\\1" VERSION_MINOR "${VERSION}")
STRING(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" VERSION_PATCH "${VERSION}")
STRING(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.[0-9]+(.*)" "\\1" VERSION_SHA1 "${VERSION}")
SET(VERSION_SHORT "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

# dump version information down to a header file
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/include/tsa/version.h.in
               ${CMAKE_CURRENT_SOURCE_DIR}/include/tsa/version.h)

# dump version to the version test file
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/test/versionTest.cpp.in
               ${CMAKE_CURRENT_SOURCE_DIR}/test/versionTest.cpp)

IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # Turn compiler warnings up to 11
    STRING(REGEX REPLACE "[-/]W[1-4]" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
ELSEIF(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -pedantic -Wno-gnu-zero-variadic-macro-arguments")
ENDIF()

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    SET(CMAKE_INSTALL_PREFIX "C:/Program Files/TSA/")
ENDIF()

# build items in subdirectories
ADD_SUBDIRECTORY(src)

# build experiments
ADD_SUBDIRECTORY(experiments)

# test and benchmarks
ENABLE_TESTING()
ADD_SUBDIRECTORY(test)
ADD_SUBDIRECTORY(benchmarks)

# build bindings for c and jni
ADD_SUBDIRECTORY(bindings)

# build items in subdirectories
ADD_SUBDIRECTORY(doc)



