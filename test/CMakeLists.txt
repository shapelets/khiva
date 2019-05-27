# Copyright (c) 2019 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

CMAKE_MINIMUM_REQUIRED(VERSION 3.9.6)
PROJECT(KHIVALIB_TEST)

FIND_PACKAGE(Threads REQUIRED)
FIND_PACKAGE(GTest REQUIRED)
INCLUDE(GoogleTest)

### Targets ###
# see https://cmake.org/cmake/help/v3.10/module/GoogleTest.html
FILE(GLOB_RECURSE ALL_TEST_CPP *.cpp)

SET(INTERNAL_HEADERS_DIR "${KHIVALIB_SRC}/")

FOREACH(ONE_TEST_CPP ${ALL_TEST_CPP})
    GET_FILENAME_COMPONENT(ONE_TEST_EXEC_TMP ${ONE_TEST_CPP} NAME_WE)
    STRING(REPLACE "Test" "" ONE_TEST_EXEC ${ONE_TEST_EXEC_TMP})
    SET(TARGET_NAME ${ONE_TEST_EXEC})
    ADD_EXECUTABLE(${TARGET_NAME} ${ONE_TEST_CPP})
    TARGET_LINK_LIBRARIES(${TARGET_NAME} PRIVATE ${KHIVALIB} GTest::GTest GTest::Main ${CMAKE_THREAD_LIBS_INIT})
	TARGET_INCLUDE_DIRECTORIES(${TARGET_NAME} PRIVATE ${INTERNAL_HEADERS_DIR})
    SET_TARGET_PROPERTIES(${TARGET_NAME} PROPERTIES FOLDER test) 

    gtest_discover_tests(${TARGET_NAME} AUTO
                         DISCOVER_TIMEOUT 10)
ENDFOREACH()
