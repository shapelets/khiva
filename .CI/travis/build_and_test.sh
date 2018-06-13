#!/bin/bash


# Build the project
mkdir -p build && cd build
../bin/cmake .. -DKHIVA_COVERAGE=ON
make -j4
ctest --output-on-failure