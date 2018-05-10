CMAKE_MINIMUM_REQUIRED(VERSION 3.9.6)
PROJECT(TSALIB)
# Find the ArrayFire package.
FIND_PACKAGE(ArrayFire REQUIRED)
# Find the Boost package
FIND_PACKAGE(Boost REQUIRED)

# Compile with C++11 support.
INCLUDE(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

SET(CMAKE_CXX_FLAGS "-fPIC ${CMAKE_CXX_FLAGS}")

# This if statement is required to avoid compilation problems with gcc
IF(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    IF(COMPILER_SUPPORTS_CXX11)
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    ELSEIF(COMPILER_SUPPORTS_CXX0X)
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    ELSE()
        MESSAGE(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
    ENDIF()
ENDIF()

# Avoid conflicts with min and max functions
ADD_DEFINITIONS(-DNOMINMAX)

# Compile using unified backend
ADD_DEFINITIONS(-DAF_UNIFIED)

# Install Variables
SET(TSA_INSTALL_INC_DIR "include")
IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
      SET(TSA_INSTALL_INC_DIR ".")
ENDIF()
SET(TSA_INSTALL_LIB_DIR "lib")

# Files to add to compilation
FILE(GLOB_RECURSE TSALIB_CODE 
    "${TSALIB_SRC}/*.cpp"
    "${TSALIB_INC}/*.h" )

# The output is a static library
ADD_LIBRARY(${TSALIB} STATIC ${TSALIB_CODE})

# Declare include directories
TARGET_INCLUDE_DIRECTORIES(${TSALIB} PUBLIC 
                           ${ArrayFire_INCLUDE_DIRS}
                           ${TSALIB_INC} 
                           ${Boost_INCLUDE_DIRS})

# Declare compilation libraries
TARGET_LINK_LIBRARIES(${TSALIB}
                      ${ArrayFire_Unified_LIBRARIES}
                      ${CMAKE_DL_LIBS})

# Add metadata
SET_TARGET_PROPERTIES(${TSALIB} PROPERTIES 
    VERSION ${VERSION_SHORT}
    SOVERSION ${VERSION_MAJOR}
    PUBLIC_HEADER "${TSALIB_INC}/tsa.h")

INSTALL(TARGETS ${TSALIB} DESTINATION ${TSA_INSTALL_LIB_DIR})

INSTALL(DIRECTORY ${TSALIB_INC} 
        DESTINATION ${TSA_INSTALL_INC_DIR}
        COMPONENT headers
        FILES_MATCHING
        PATTERN "*.h"
        PATTERN ".gitignore" EXCLUDE
)
