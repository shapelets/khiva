CMAKE_MINIMUM_REQUIRED(VERSION 3.9.6)

# Find the ArrayFire package.
FIND_PACKAGE(ArrayFire REQUIRED)
PROJECT(TSALIB_C)

# Compile with C++11 support.
INCLUDE(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# Set the base directory to parent so src and include become
# equaly visible
SET(TSALIB_C_BASE_DIR "${PROJECT_SOURCE_DIR}")
# Define source directory
SET(TSALIB_C_SRC "${TSALIB_C_BASE_DIR}/src")
# Define include directories
SET(TSALIB_C_INC "${TSALIB_C_BASE_DIR}/include")

# Installation directories
SET(TSA_C_INSTALL_INC_DIR ".")
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
      SET(TSA_C_INSTALL_INC_DIR "include")
ENDIF()
SET(TSA_C_INSTALL_LIB_DIR "lib")

# Library Name
SET(TSALIB_C "tsa_c")

# Files to add to compilation
FILE(GLOB_RECURSE TSALIB_C_CODE 
    "${TSALIB_C_SRC}/*.cpp"
    "${TSALIB_C_INC}/*.h" )

# The output is a static library
ADD_LIBRARY(${TSALIB_C} SHARED ${TSALIB_C_CODE})

# Declare include directories
TARGET_INCLUDE_DIRECTORIES(${TSALIB_C} PUBLIC 
                           ${TSALIB_INC}
                           ${TSALIB_C_INC})

# Declare compilation libraries
TARGET_LINK_LIBRARIES(${TSALIB_C}
                      ${TSALIB}
                      ${CMAKE_DL_LIBS})

# Add metadata
SET_TARGET_PROPERTIES(${TSALIB_C} PROPERTIES
    VERSION ${VERSION_SHORT}
    SOVERSION ${VERSION_MAJOR}
    PUBLIC_HEADER "${TSALIB_C_INC}/tsa_c.h")

# Install bindings
# C binding
INSTALL(TARGETS ${TSALIB_C} DESTINATION ${TSA_C_INSTALL_LIB_DIR})

INSTALL(DIRECTORY ${TSALIB_C_INC} 
        DESTINATION ${TSA_C_INSTALL_INC_DIR}
        COMPONENT headers
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN ".gitignore" EXCLUDE
)
