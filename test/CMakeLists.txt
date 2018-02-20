CMAKE_MINIMUM_REQUIRED(VERSION 3.9.6)
PROJECT(TSALIB_TEST)

INCLUDE(GoogleTest)

### Targets ###
ADD_EXECUTABLE(simple simple.cpp)
TARGET_LINK_LIBRARIES(simple TSALIB gtest gtest_main)


# see https://cmake.org/cmake/help/v3.10/module/GoogleTest.html
gtest_add_tests(TARGET      simple
                TEST_SUFFIX .noArgs
                TEST_LIST   noArgsTests
)
