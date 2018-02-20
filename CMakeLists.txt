CMAKE_MINIMUM_REQUIRED(VERSION 3.9.6)
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

# Load from environmnet variables
SET(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH})
SET(CMAKE_PREFIX_PATH $ENV{CMAKE_PREFIX_PATH})

# Set the build type
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "Release" 
      CACHE STRING "Build configuration 'Release' or 'Debug'."
      FORCE)
ENDIF()

# Download and unpack googletest at configure time
CONFIGURE_FILE(CMakeLists.txt.in googletest-download/CMakeLists.txt)

EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" . WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )
EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}" --build . WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download" )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
SET(gtest_force_shared_crt ON CACHE BOOL "" FORCE)


# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
ADD_SUBDIRECTORY("${CMAKE_BINARY_DIR}/googletest-src"
                 "${CMAKE_BINARY_DIR}/googletest-build")


# git support
INCLUDE("cmake/GetGitRevisionDescription.cmake")

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

enable_testing()
ADD_SUBDIRECTORY(test)
