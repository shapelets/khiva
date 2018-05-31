CMAKE_MINIMUM_REQUIRED(VERSION 3.9.6)
PROJECT(TSA
    LANGUAGES C CXX)
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
SET(TSALIB_INC "${TSALIB_BASE_DIR}/include/")
# Library Name
SET(TSALIB "tsa")

# bring TSA version and installation directories
INCLUDE(Version)
INCLUDE(TSAInstallDirs)

SET(PROJECT_VERSION ${VERSION_SHORT})

# These config files will be installed so we need to set the install_destination
# path relative to the install path
INCLUDE(CMakePackageConfigHelpers)
WRITE_BASIC_PACKAGE_VERSION_FILE(
    cmake/install/TSAConfigVersion.cmake
    COMPATIBILITY SameMajorVersion)

SET(INCLUDE_DIRS include)
SET(CMAKE_DIR ${TSA_INSTALL_CMAKE_DIR})
CONFIGURE_PACKAGE_CONFIG_FILE(
    ${CMAKE_MODULE_PATH}/TSAConfig.cmake.in
    cmake/install/TSAConfig.cmake
    INSTALL_DESTINATION "${TSA_INSTALL_CMAKE_DIR}"
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
ADD_SUBDIRECTORY(examples)

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

INSTALL(DIRECTORY examples/
    DESTINATION ${TSA_INSTALL_EXAMPLE_DIR}
    COMPONENT examples
    FILES_MATCHING
    PATTERN "*.cpp"
    PATTERN "*.h")

INSTALL(DIRECTORY licenses/
    DESTINATION ${TSA_INSTALL_LICENSES_DIR}
    COMPONENT licenses)

INCLUDE(CPackConfig)