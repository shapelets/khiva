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


ADD_EXECUTABLE(distances distancesTest.cpp)
TARGET_LINK_LIBRARIES(distances TSALIB gtest gtest_main)
gtest_add_tests(TARGET      distances
                TEST_SUFFIX .noArgs
                TEST_LIST   noArgsTests
)

ADD_EXECUTABLE(normalization normalizationTest.cpp)
TARGET_LINK_LIBRARIES(normalization TSALIB gtest gtest_main)
gtest_add_tests(TARGET      normalization
                TEST_SUFFIX .noArgs
                TEST_LIST   noArgsTests
)

ADD_EXECUTABLE(matrix matrixTest.cpp)
TARGET_LINK_LIBRARIES(matrix TSALIB gtest gtest_main)
gtest_add_tests(TARGET      matrix
                TEST_SUFFIX .noArgs
                TEST_LIST   noArgsTests
)



