CMAKE_MINIMUM_REQUIRED(VERSION 3.9.6)

# Find the ArrayFire package.
FIND_PACKAGE(ArrayFire REQUIRED)
FIND_PACKAGE(JNI REQUIRED)
PROJECT(TSALIB_JNI)

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
SET(TSALIB_JNI_BASE_DIR "${PROJECT_SOURCE_DIR}")
# Define source directory
SET(TSALIB_JNI_SRC "${TSALIB_JNI_BASE_DIR}/src")
# Define include directories
SET(TSALIB_JNI_INC "${TSALIB_JNI_BASE_DIR}/include")

# Installation directories
SET(TSA_JNI_INSTALL_INC_DIR ".")
SET(TSA_JNI_INSTALL_LIB_DIR "lib")

# Library Name
SET(TSALIB_JNI "tsa_jni")

# Files to add to compilation
FILE(GLOB_RECURSE TSALIB_JNI_CODE 
    "${TSALIB_JNI_SRC}/*.cpp"
    "${TSALIB_JNI_INC}/*.h" )

# The output is a static library
ADD_LIBRARY(${TSALIB_JNI} SHARED ${TSALIB_JNI_CODE})

# Declare include directories
TARGET_INCLUDE_DIRECTORIES(${TSALIB_JNI} PUBLIC 
                           ${ArrayFire_INCLUDE_DIRS}
                           ${JNI_INCLUDE_DIRS}
                           ${TSALIB_INC}
                           ${TSALIB_JNI_INC})

# Declare compilation libraries
TARGET_LINK_LIBRARIES(${TSALIB_JNI}
                      ${ArrayFire_Unified_LIBRARIES}
                      ${TSALIB}
                      ${CMAKE_DL_LIBS})

# Add metadata
SET_TARGET_PROPERTIES(${TSALIB_JNI} PROPERTIES 
    VERSION ${VERSION_SHORT}
    SOVERSION ${VERSION_MAJOR}
    PUBLIC_HEADER "${TSALIB_JNI_INC}/tsa_jni.h")

# JNI binding
INSTALL(TARGETS ${TSALIB_JNI} DESTINATION ${TSA_JNI_INSTALL_LIB_DIR})

INSTALL(DIRECTORY ${TSALIB_JNI_INC} 
        DESTINATION ${TSA_JNI_INSTALL_INC_DIR}
        COMPONENT headers
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN ".gitignore" EXCLUDE
)