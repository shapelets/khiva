FIND_PACKAGE(Sphinx REQUIRED)

PROJECT(TSALIB_DOC)

SET(DOXYGEN_OUTPUT_DIR "${TSALIB_BASE_DIR}/build/doc/doxygen")
SET(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/doxygen/Doxyfile.in)
SET(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/doxygen/Doxyfile)

CONFIGURE_FILE(${doxyfile_in} ${doxyfile} @ONLY)

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
SET(SPHINX_HTML_DIR "${CMAKE_CURRENT_BINARY_DIR}/sphinx/build/html")
 
CONFIGURE_FILE(
    "${CMAKE_CURRENT_SOURCE_DIR}/sphinx/source/conf.py.in"
    "${BINARY_BUILD_DIR}/conf.py"
    @ONLY)
 
ADD_CUSTOM_TARGET(TSA_doc_sphinx ALL
    ${SPHINX_EXECUTABLE}
        -q -b html
        -c "${BINARY_BUILD_DIR}"
        -d "${SPHINX_CACHE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/sphinx/source"
        "${SPHINX_HTML_DIR}"
    COMMENT "Building HTML documentation with Sphinx")

# INSTALL(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc)