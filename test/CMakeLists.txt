# Copyright (c) 2019 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

cmake_minimum_required(VERSION 3.9.6)
project(KHIVALIB_TEST)

find_package(Threads REQUIRED)
find_package(GTest REQUIRED)
include(GoogleTest)

### Targets ###
# see https://cmake.org/cmake/help/v3.10/module/GoogleTest.html
file(GLOB_RECURSE ALL_TEST_CPP *.cpp)

set(INTERNAL_HEADERS_DIR "${KHIVALIB_SRC}/")

foreach(ONE_TEST_CPP ${ALL_TEST_CPP})
    get_filename_component(ONE_TEST_EXEC_TMP ${ONE_TEST_CPP} NAME_WE)
    string(REPLACE "Test" "" ONE_TEST_EXEC ${ONE_TEST_EXEC_TMP})
    set(TARGET_NAME ${ONE_TEST_EXEC})
    add_executable(${TARGET_NAME} ${ONE_TEST_CPP})
    target_link_libraries(${TARGET_NAME} PRIVATE ${KHIVALIB} GTest::GTest GTest::Main ${CMAKE_THREAD_LIBS_INIT})
	target_include_directories(${TARGET_NAME} PRIVATE ${INTERNAL_HEADERS_DIR})
    set_target_properties(${TARGET_NAME} PROPERTIES FOLDER test)
    gtest_discover_tests(${TARGET_NAME} AUTO
                         DISCOVER_TIMEOUT 10) 
endforeach()
