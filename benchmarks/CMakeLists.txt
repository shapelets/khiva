# Copyright (c) 2018 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

FIND_PACKAGE(Threads REQUIRED)
FIND_PACKAGE(Benchmark REQUIRED)

FILE(GLOB_RECURSE ALL_BENCH_CPP *.cpp)

FOREACH(ONE_BENCH_CPP ${ALL_BENCH_CPP})
   GET_FILENAME_COMPONENT(ONE_BENCH_EXEC ${ONE_BENCH_CPP} NAME_WE)
   SET(TARGET_NAME ${ONE_BENCH_EXEC})
   ADD_EXECUTABLE(${TARGET_NAME} ${ONE_BENCH_CPP})
   
   SET_TARGET_PROPERTIES(${TARGET_NAME} PROPERTIES OUTPUT_NAME ${ONE_BENCH_EXEC}) 
   TARGET_LINK_LIBRARIES(${TARGET_NAME} benchmark ${KHIVALIB} ${CMAKE_THREAD_LIBS_INIT})

   IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
      TARGET_LINK_LIBRARIES(${TARGET_NAME} Shlwapi)
   ENDIF()
ENDFOREACH()
