# Copyright (c) 2018 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

cmake_minimum_required(VERSION 3.5)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/nsis")

include(KhivaVersion)
include(CPackIFW)

set(CPACK_GENERATOR "STGZ;TGZ" CACHE STRINGS "STGZ;TGZ;DEB;RPM;productbuild")
set_property(CACHE CPACK_GENERATOR PROPERTY STRINGS STGZ DEB RPM productbuild)
mark_as_advanced(CPACK_GENERATOR)

set(VENDOR_NAME "Shapelets")
set(LIBRARY_NAME ${PROJECT_NAME})
string(TOLOWER "${LIBRARY_NAME}" APP_LOW_NAME)
set(SITE_URL "www.shapelets.io")

# Long description of the package
set(CPACK_PACKAGE_DESCRIPTION
"Khiva is an open source C++ library which focus on providing efficient
algorithms to perform analytics over time series of data. It can be
used to extract insights from one or a group of time series.

The large number of available methods allow us to understand the nature
of each time series.

Based on that analytics, the user can reduce dimensionality, find out
recurrent motifs or discords, understand the seasonality or trend from
a given time series, forecasting and detect anomalies.")

# Short description of the package
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY
  "An open source C++ library which focus on providing efficient algorithms to perform analytics over time series of data.")

# Common settings to all packaging tools
set(CPACK_PREFIX_DIR ${CMAKE_INSTALL_PREFIX})
set(CPACK_PACKAGE_NAME "${LIBRARY_NAME}")
set(CPACK_PACKAGE_VENDOR "${VENDOR_NAME}")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY ${LIBRARY_NAME})
set(CPACK_PACKAGE_CONTACT "Shapelets Development Group <dev@shapelets.io>")
set(MY_CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/assets/${APP_LOW_NAME}.ico")

file(TO_NATIVE_PATH "${CMAKE_SOURCE_DIR}/assets/" NATIVE_ASSETS_PATH)
string(REPLACE "\\" "\\\\" NATIVE_ASSETS_PATH  ${NATIVE_ASSETS_PATH})
set(CPACK_KHIVA_ASSETS_DIR "${NATIVE_ASSETS_PATH}")

set(CPACK_PACKAGE_VERSION_MAJOR "${VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${VERSION_PATCH}")

set(CPACK_PACKAGE_INSTALL_DIRECTORY "${LIBRARY_NAME}")

set(inst_pkg_name ${APP_LOW_NAME})
set(inst_pkg_version "")
if (APPLE OR WIN32)
  set(inst_pkg_version "-v${VERSION_SHORT}")
endif ()

set(CPACK_PACKAGE_FILE_NAME "${inst_pkg_name}${inst_pkg_version}")

# Platform specific settings for CPACK generators
# - OSX specific
#   - DragNDrop (OSX only)
#   - PackageMaker (OSX only)
#   - OSXX11 (OSX only)
#   - Bundle (OSX only)
# - Windows
#   - NSIS64 Generator
if(APPLE)
  set(CPACK_PACKAGING_INSTALL_PREFIX "/usr/local")
  set(OSX_INSTALL_SOURCE ${PROJECT_SOURCE_DIR}/cmake/osx_install)
  set(WELCOME_FILE       "${OSX_INSTALL_SOURCE}/welcome.html.in")
  set(WELCOME_FILE_OUT   "${CMAKE_CURRENT_BINARY_DIR}/welcome.html")

  set(README_FILE       "${OSX_INSTALL_SOURCE}/readme.html.in")
  set(README_FILE_OUT   "${CMAKE_CURRENT_BINARY_DIR}/readme.html")

  set(LICENSE_FILE       "${KHIVALIB_BASE_DIR}/LICENSE")
  set(LICENSE_FILE_OUT   "${CMAKE_CURRENT_BINARY_DIR}/license.txt")

  set(KHIVA_TITLE    "Khiva ${VERSION_SHORT}")
  configure_file(${WELCOME_FILE} ${WELCOME_FILE_OUT})
  configure_file(${README_FILE} ${README_FILE_OUT})
  configure_file(${LICENSE_FILE} ${LICENSE_FILE_OUT})
  set(CPACK_RESOURCE_FILE_LICENSE ${LICENSE_FILE_OUT})
  set(CPACK_RESOURCE_FILE_README ${README_FILE_OUT})
  set(CPACK_RESOURCE_FILE_WELCOME ${WELCOME_FILE_OUT})
elseif(WIN32)
  set(WIN_INSTALL_SOURCE ${PROJECT_SOURCE_DIR}/cmake/nsis)

  set(LICENSE_FILE       "${KHIVALIB_BASE_DIR}/LICENSE")
  set(LICENSE_FILE_OUT   "${CMAKE_CURRENT_BINARY_DIR}/license.txt")
  configure_file(${LICENSE_FILE} ${LICENSE_FILE_OUT})
  set(CPACK_RESOURCE_FILE_LICENSE ${LICENSE_FILE_OUT})

  #NSIS SPECIFIC VARIABLES
  set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
  set(CPACK_NSIS_MODIFY_PATH ON)
  set(CPACK_NSIS_DISPLAY_NAME "${LIBRARY_NAME}")
  set(CPACK_NSIS_PACKAGE_NAME "${LIBRARY_NAME}")
  set(CPACK_NSIS_HELP_LINK "${SITE_URL}")
  set(CPACK_NSIS_URL_INFO_ABOUT "${SITE_URL}")
  set(CPACK_NSIS_INSTALLED_ICON_NAME "${MY_CPACK_PACKAGE_ICON}")
  if (CMAKE_CL_64)
    set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
  else (CMAKE_CL_64)
    set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
  endif (CMAKE_CL_64)
else()
  set(CPACK_RESOURCE_FILE_LICENSE "${KHIVALIB_BASE_DIR}/LICENSE")
  set(CPACK_RESOURCE_FILE_README "${KHIVALIB_BASE_DIR}/README.md")
endif()

# Set the default components installed in the package
get_cmake_property(CPACK_COMPONENTS_ALL COMPONENTS)

include(CPackComponent)

cpack_add_install_type(Runtime DISPLAY_NAME "Runtime")
cpack_add_install_type(Development DISPLAY_NAME "Development")
cpack_add_install_type(Extra DISPLAY_NAME "Extra")

# Khiva group
##############################################################
cpack_add_component_group(khiva
  DISPLAY_NAME "Khiva"
  DESCRIPTION "Khiva Core, Bindings, Headers, Library"
  EXPANDED)
##############################################################

cpack_add_component(core
  DISPLAY_NAME "Core"
  DESCRIPTION "Khiva Core"
  GROUP khiva
  REQUIRED)
cpack_add_component(c_binding
  DISPLAY_NAME "C Binding"
  DESCRIPTION "C binding to connect with the Python, R and MATLAB programming languages"
  GROUP khiva
  REQUIRED)
cpack_add_component(jni_binding
  DISPLAY_NAME "JNI Binding"
  DESCRIPTION "JNI Binding to connect with the Java programming language"
  GROUP khiva
  REQUIRED)
cpack_add_component(headers
  DISPLAY_NAME "C/C++ Headers"
  DESCRIPTION "Headers for the Khiva Library."
  GROUP khiva
  INSTALL_TYPES Development Extra)
cpack_add_component(cmake
  DISPLAY_NAME "CMake Support"
  DESCRIPTION "Configuration files to use Khiva using CMake."
  GROUP khiva
  INSTALL_TYPES Development Extra)
if(KHIVA_BUILD_DOCUMENTATION)
  cpack_add_component(documentation
    DISPLAY_NAME "Khiva Documentation"
    DESCRIPTION "Sphinx documentation"
    GROUP khiva
    INSTALL_TYPES Extra)
endif()
if(KHIVA_BUILD_EXAMPLES)
  cpack_add_component(examples
    DISPLAY_NAME "Khiva Examples"
    DESCRIPTION "Various examples using Khiva."
    GROUP khiva
    INSTALL_TYPES Extra)
endif()
cpack_add_component(licenses
  DISPLAY_NAME "Licenses"
  DESCRIPTION "License files for upstream libraries and Khiva."
  GROUP khiva
  REQUIRED)

##
# IFW CPACK generator
# Uses Qt installer framework, cross platform installer generator.
# Uniform installer GUI on all major desktop platforms: Windows, OSX & Linux.
##
set(CPACK_IFW_PACKAGE_TITLE "${CPACK_PACKAGE_NAME}")
set(CPACK_IFW_PACKAGE_PUBLISHER "${CPACK_PACKAGE_VENDOR}")
set(CPACK_IFW_PRODUCT_URL "${SITE_URL}")
set(CPACK_IFW_PACKAGE_ICON "${MY_CPACK_PACKAGE_ICON}")
set(CPACK_IFW_PACKAGE_WINDOW_ICON "${CMAKE_SOURCE_DIR}/assets/${APP_LOW_NAME}_icon.png")
set(CPACK_IFW_PACKAGE_WIZARD_DEFAULT_WIDTH 640)
set(CPACK_IFW_PACKAGE_WIZARD_DEFAULT_HEIGHT 480)
if (WIN32)
    set(CPACK_IFW_ADMIN_TARGET_DIRECTORY "@ApplicationsDirX64@/${CPACK_PACKAGE_INSTALL_DIRECTORY}")
else ()
    set(CPACK_IFW_ADMIN_TARGET_DIRECTORY "/usr/local")
endif ()

set(arrayfire_lic_path "${CMAKE_SOURCE_DIR}/LICENSES/ArrayFire License.txt")
set(boost_lic_path "${CMAKE_SOURCE_DIR}/licenses/Boost Software License.txt")
set(mpl2_lic_path "${CMAKE_SOURCE_DIR}/LICENSES/MPL2 License.txt")

cpack_ifw_configure_component_group(khiva)
cpack_ifw_configure_component(core FORCED_INSTALLATION)
cpack_ifw_configure_component(c_binding FORCED_INSTALLATION)
cpack_ifw_configure_component(jni_binding FORCED_INSTALLATION)
cpack_ifw_configure_component(headers)
cpack_ifw_configure_component(cmake)
if(KHIVA_BUILD_DOCUMENTATION)
  cpack_ifw_configure_component(documentation)
endif()
if(KHIVA_BUILD_EXAMPLES)
  cpack_ifw_configure_component(examples)
endif()
cpack_ifw_configure_component(licenses FORCED_INSTALLATION
  LICENSES "ArrayFire" ${arrayfire_lic_path} "Boost" ${boost_lic_path} "Eigen" ${mpl2_lic_path} "Khiva" ${mpl2_lic_path}
)

##
# Debian package
##
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE http://www.shapelets.io)

##
# RPM package
##
set(CPACK_RPM_FILE_NAME RPM-DEFAULT)
set(CPACK_RPM_PACKAGE_LICENSE "MPL")
set(CPACK_RPM_PACKAGE_AUTOREQPROV " no")

set(CPACK_PACKAGE_GROUP "Development/Libraries")
##
# Source package
##
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_SOURCE_PACKAGE_FILE_NAME
    ${CPACK_PACKAGE_NAME}_src_${GIT_COMMIT_HASH}_${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR})
set(CPACK_SOURCE_IGNORE_FILES
    "/build"
    "CMakeFiles"
    "/\\\\.dir"
    "/\\\\.git"
    "/\\\\.gitignore$"
    ".*~$"
    "\\\\.bak$"
    "\\\\.swp$"
    "\\\\.orig$"
    "/\\\\.DS_Store$"
    "/Thumbs\\\\.db"
    "/CMakeLists.txt.user$"
    ${CPACK_SOURCE_IGNORE_FILES})
# Ignore build directories that may be in the source tree
file(GLOB_RECURSE CACHES "${CMAKE_SOURCE_DIR}/CMakeCache.txt")

if (WIN32)
  # Configure file with custom definitions for NSIS.
  configure_file(
    ${PROJECT_SOURCE_DIR}/cmake/nsis/NSIS.definitions.nsh.in
    ${CMAKE_CURRENT_BINARY_DIR}/NSIS.definitions.nsh)
endif ()

include(CPack)
