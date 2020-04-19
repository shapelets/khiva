# Copyright (c) 2019 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

project(KHIVALIB_JNI_TEST)

find_package(GTest REQUIRED)
include(GoogleTest)

### Targets ###
# see https://cmake.org/cmake/help/v3.10/module/GoogleTest.html

add_executable(khiva_jni_test khivaJniTest.cpp)
target_link_libraries(khiva_jni_test PRIVATE ${KHIVALIB_JNI} GTest::GTest GTest::Main ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(khiva_jni_test PROPERTIES FOLDER test/jni)