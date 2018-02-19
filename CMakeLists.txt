CMAKE_MINIMUM_REQUIRED(VERSION 3.5.1)

SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

# Load from environmnet variables
set(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH})
set(CMAKE_PREFIX_PATH $ENV{CMAKE_PREFIX_PATH})

# Set the build type
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "Release" 
      CACHE STRING "Build configuration 'Release' or 'Debug'."
      FORCE)
ENDIF()

# we have custom CMake configuration files, tell CMake to use them:
LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

INCLUDE(GetGitRevisionDescription)
git_describe(VERSION --tags --dirty=-dirty)

MESSAGE( STATUS "xxx:         " ${VERSION} )

#parse the version information into pieces.
STRING(REGEX REPLACE "^v([0-9]+)\\..*" "\\1" VERSION_MAJOR "${VERSION}")
STRING(REGEX REPLACE "^v[0-9]+\\.([0-9]+).*" "\\1" VERSION_MINOR "${VERSION}")
STRING(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" VERSION_PATCH "${VERSION}")
STRING(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.[0-9]+(.*)" "\\1" VERSION_SHA1 "${VERSION}")
SET(VERSION_SHORT "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/include/version.h.in
               ${CMAKE_CURRENT_SOURCE_DIR}/include/version.h)

# build items in subdirectories
ADD_SUBDIRECTORY(src)
