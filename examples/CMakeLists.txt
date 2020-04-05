# Copyright (c) 2019 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

cmake_minimum_required(VERSION 3.9.6)
project(KHIVALIB_EXAMPLES)


file(GLOB_RECURSE ALL_EXAMPLE_CPP *.cpp)

foreach(ONE_EXAMPLE_CPP ${ALL_EXAMPLE_CPP})
    get_filename_component(ONE_EXAMPLE_EXEC ${ONE_EXAMPLE_CPP} NAME_WE)
    set(TARGET_NAME ${ONE_EXAMPLE_EXEC})
    add_executable(${TARGET_NAME} ${ONE_EXAMPLE_CPP})
	set_target_properties(${TARGET_NAME} PROPERTIES FOLDER examples)
    target_link_libraries(${TARGET_NAME} ${KHIVALIB})
endforeach()

install(DIRECTORY ${KHIVALIB_BASE_DIR}/examples/
    DESTINATION ${KHIVA_INSTALL_EXAMPLE_DIR}
    COMPONENT examples
    FILES_MATCHING
    PATTERN "*.cpp"
    PATTERN "*.h")
