# Copyright (c) 2019 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

#
# Sets KHIVA installation paths.
#

include(KhivaVersion)

if(WIN32)
    set(CMAKE_INSTALL_PREFIX "C:/Program Files/Khiva/v${VERSION_MAJOR}/")
endif()

# NOTE: These paths are all relative to the project installation prefix.

# Executables
if(NOT DEFINED KHIVA_INSTALL_BIN_DIR)
  set(KHIVA_INSTALL_BIN_DIR "lib" CACHE PATH "Installation path for executables")
endif()

# Libraries
if(NOT DEFINED KHIVA_INSTALL_LIB_DIR)
  set(KHIVA_INSTALL_LIB_DIR "lib" CACHE PATH "Installation path for libraries")
endif()

# Header files
if(NOT DEFINED KHIVA_INSTALL_INC_DIR)
  set(KHIVA_INSTALL_INC_DIR "include" CACHE PATH "Installation path for headers")
endif()

set(DATA_DIR "share/Khiva")

# Documentation
if(NOT DEFINED KHIVA_INSTALL_DOC_DIR)
  if (WIN32)
    set(KHIVA_INSTALL_DOC_DIR "doc" CACHE PATH "Installation path for documentation")
  else ()
      set(KHIVA_INSTALL_DOC_DIR "${DATA_DIR}/doc" CACHE PATH "Installation path for documentation")
  endif ()
endif()

if(NOT DEFINED KHIVA_INSTALL_EXAMPLE_DIR)
  if (WIN32)
    set(KHIVA_INSTALL_EXAMPLE_DIR "examples" CACHE PATH "Installation path for examples")
  else ()
    set(KHIVA_INSTALL_EXAMPLE_DIR "${DATA_DIR}/examples" CACHE PATH "Installation path for examples")
  endif ()
endif()

if(NOT DEFINED KHIVA_INSTALL_LICENSES_DIR)
  if (WIN32)
    set(KHIVA_INSTALL_LICENSES_DIR "licenses" CACHE PATH "Installation path for licenses")
  else ()
    set(KHIVA_INSTALL_LICENSES_DIR "${DATA_DIR}/licenses" CACHE PATH "Installation path for licenses")
  endif ()
endif()

# Man pages
if(NOT DEFINED KHIVA_INSTALL_MAN_DIR)
    set(KHIVA_INSTALL_MAN_DIR "${DATA_DIR}/man" CACHE PATH "Installation path for man pages")
endif()

# CMake files
if(NOT DEFINED KHIVA_INSTALL_CMAKE_DIR)
  if (WIN32)
    set(KHIVA_INSTALL_CMAKE_DIR "cmake" CACHE PATH "Installation path for CMake files")
  else ()
    set(KHIVA_INSTALL_CMAKE_DIR "${DATA_DIR}/cmake" CACHE PATH "Installation path for CMake files")
  endif ()
endif()

mark_as_advanced(
  KHIVA_INSTALL_BIN_DIR
  KHIVA_INSTALL_LIB_DIR
  KHIVA_INSTALL_INC_DIR
  KHIVA_INSTALL_DATA_DIR
  KHIVA_INSTALL_DOC_DIR
  KHIVA_INSTALL_EXAMPLE_DIR
  KHIVA_INSTALL_MAN_DIR
  KHIVA_INSTALL_CMAKE_DIR)
