CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

# Find the ArrayFire package.
FIND_PACKAGE(ArrayFire REQUIRED)

PROJECT(TSALIB)

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

# Avoid conflicts with min and max functions
ADD_DEFINITIONS(-DNOMINMAX)

# Compile using unified backend
ADD_DEFINITIONS(-DAF_UNIFIED)

# Set the base directory to parent so src and include become
# equaly visible
SET(TSALIB_BASE_DIR "..")
# Define source directory
SET(TSALIB_SRC "${TSALIB_BASE_DIR}/src")
# Define include directory
SET(TSALIB_INC "${TSALIB_BASE_DIR}/include")

# Files to add to compilation
FILE(GLOB_RECURSE TSALIB_CODE 
    "${TSALIB_SRC}/*.cpp"
    "${TSALIB_INC}/*.h" )

# The output is a static library
ADD_LIBRARY(TSALIB STATIC ${TSALIB_CODE})

# Declare include directories
TARGET_INCLUDE_DIRECTORIES(TSALIB PUBLIC 
                           ${ArrayFire_INCLUDE_DIRS}
                           ${TSALIB_INC} )

# Declare compilation libraries
TARGET_LINK_LIBRARIES(TSALIB
                      ${ArrayFire_Unified_LIBRARIES}
                      ${CMAKE_DL_LIBS})

# Add metadata
SET_TARGET_PROPERTIES(TSALIB PROPERTIES 
    VERSION ${VERSION_SHORT}
    SOVERSION ${VERSION_MAJOR}
    PUBLIC_HEADER "${TSALIB_INC}/tsa.h")

