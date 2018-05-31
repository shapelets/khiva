# Copyright (c) 2018 Grumpy Cat Software S.L.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

#
# Sets TSA installation paths.
#

include(Version)

if(WIN32)
    set(CMAKE_INSTALL_PREFIX "C:/Program Files/TSA/v${VERSION_MAJOR}/")
endif()

# NOTE: These paths are all relative to the project installation prefix.

# Executables
if(NOT DEFINED TSA_INSTALL_BIN_DIR)
  set(TSA_INSTALL_BIN_DIR "lib" CACHE PATH "Installation path for executables")
endif()

# Libraries
if(NOT DEFINED TSA_INSTALL_LIB_DIR)
  set(TSA_INSTALL_LIB_DIR "lib" CACHE PATH "Installation path for libraries")
endif()

# Header files
if(NOT DEFINED TSA_INSTALL_INC_DIR)
  set(TSA_INSTALL_INC_DIR "include" CACHE PATH "Installation path for headers")
endif()

set(DATA_DIR "share/TSA")

# Documentation
if(NOT DEFINED TSA_INSTALL_DOC_DIR)
  if (WIN32)
    set(TSA_INSTALL_DOC_DIR "doc" CACHE PATH "Installation path for documentation")
  else ()
      set(TSA_INSTALL_DOC_DIR "${DATA_DIR}/doc" CACHE PATH "Installation path for documentation")
  endif ()
endif()

if(NOT DEFINED TSA_INSTALL_EXAMPLE_DIR)
  if (WIN32)
    set(TSA_INSTALL_EXAMPLE_DIR "examples" CACHE PATH "Installation path for examples")
  else ()
    set(TSA_INSTALL_EXAMPLE_DIR "${DATA_DIR}/examples" CACHE PATH "Installation path for examples")
  endif ()
endif()

if(NOT DEFINED TSA_INSTALL_LICENSES_DIR)
  if (WIN32)
    set(TSA_INSTALL_LICENSES_DIR "licenses" CACHE PATH "Installation path for licenses")
  else ()
    set(TSA_INSTALL_LICENSES_DIR "${DATA_DIR}/licenses" CACHE PATH "Installation path for licenses")
  endif ()
endif()

# Man pages
if(NOT DEFINED TSA_INSTALL_MAN_DIR)
    set(TSA_INSTALL_MAN_DIR "${DATA_DIR}/man" CACHE PATH "Installation path for man pages")
endif()

# CMake files
if(NOT DEFINED TSA_INSTALL_CMAKE_DIR)
  if (WIN32)
    set(TSA_INSTALL_CMAKE_DIR "cmake" CACHE PATH "Installation path for CMake files")
  else ()
    set(TSA_INSTALL_CMAKE_DIR "${DATA_DIR}/cmake" CACHE PATH "Installation path for CMake files")
  endif ()
endif()

mark_as_advanced(
  TSA_INSTALL_BIN_DIR
  TSA_INSTALL_LIB_DIR
  TSA_INSTALL_INC_DIR
  TSA_INSTALL_DATA_DIR
  TSA_INSTALL_DOC_DIR
  TSA_INSTALL_EXAMPLE_DIR
  TSA_INSTALL_MAN_DIR
  TSA_INSTALL_CMAKE_DIR)
