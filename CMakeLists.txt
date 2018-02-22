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
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/include/version.h.in
               ${CMAKE_CURRENT_SOURCE_DIR}/include/version.h)

# build items in subdirectories
ADD_SUBDIRECTORY(src)

# build experiments
ADD_SUBDIRECTORY(experiments)

# test and benchmarks
ENABLE_TESTING()
ADD_SUBDIRECTORY(test)
ADD_SUBDIRECTORY(benchmarks)
# build items in subdirectories
ADD_SUBDIRECTORY(doc)



