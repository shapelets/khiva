# Copyright (c) 2018 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

FIND_PACKAGE(Sphinx REQUIRED)
FIND_PACKAGE(Dot REQUIRED)

PROJECT(KHIVALIB_DOC)

# Generating Doxygen Documentation
# check if Doxygen is installed, add a target to generate API documentation with Doxygen
FIND_PACKAGE(Doxygen REQUIRED)
OPTION(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" DOXYGEN_FOUND)

IF(NOT DOXYGEN_FOUND)
    MESSAGE(FATAL_ERROR "Doxygen is needed to build the documentation.")
ENDIF()

SET(DOXYGEN_OUTPUT_DIR "${KHIVALIB_BASE_DIR}/build/doc/doxygen")

# Generating Sphinx Documentation
IF(NOT DEFINED SPHINX_THEME)
    SET(SPHINX_THEME default)
ENDIF()
 
IF(NOT DEFINED SPHINX_THEME_DIR)
    SET(SPHINX_THEME_DIR)
ENDIF()
 
# configured documentation tools and intermediate build results
SET(BINARY_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/sphinx/source/_build")
 
# Sphinx cache with pickled ReST documents
SET(SPHINX_CACHE_DIR "${CMAKE_CURRENT_BINARY_DIR}/sphinx/source/_doctrees")
 
# HTML output directory
SET(SPHINX_HTML_DIR "${CMAKE_CURRENT_BINARY_DIR}/html")
 
ADD_CUSTOM_TARGET(KHIVA_doc_sphinx ALL
    ${SPHINX_EXECUTABLE}
        -q -b html
        -c "${CMAKE_CURRENT_SOURCE_DIR}/sphinx/source/"
        -d "${SPHINX_CACHE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/sphinx/source"
        "${SPHINX_HTML_DIR}"
    COMMENT "Building HTML documentation with Sphinx")

INSTALL(DIRECTORY ${SPHINX_HTML_DIR}
    DESTINATION ${KHIVA_INSTALL_DOC_DIR}
    COMPONENT documentation)
