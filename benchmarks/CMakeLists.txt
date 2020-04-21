# Copyright (c) 2019 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

cmake_minimum_required(VERSION 3.9.6)
find_package(Threads REQUIRED)
if (KHIVA_USE_CONAN)
   find_package(benchmark REQUIRED)
else()
   find_package(benchmark CONFIG REQUIRED)
endif ()

file(GLOB_RECURSE ALL_BENCH_CPP *.cpp)

set(INTERNAL_HEADERS_DIR "${KHIVALIB_SRC}/")

foreach(ONE_BENCH_CPP ${ALL_BENCH_CPP})
   get_filename_component(ONE_BENCH_EXEC ${ONE_BENCH_CPP} NAME_WE)
   set(TARGET_NAME ${ONE_BENCH_EXEC})
   add_executable(${TARGET_NAME} ${ONE_BENCH_CPP})
   
   set_target_properties(${TARGET_NAME} PROPERTIES OUTPUT_NAME ${ONE_BENCH_EXEC} FOLDER benchmarks)
   target_link_libraries(${TARGET_NAME} benchmark::benchmark ${KHIVALIB} ${CMAKE_THREAD_LIBS_INIT})
   target_include_directories(${TARGET_NAME} PRIVATE ${INTERNAL_HEADERS_DIR})
endforeach()
