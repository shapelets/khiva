#!/bin/bash


# Build the project
mkdir -p build && cd build
cmake .. -DKHIVA_BUILD_DOCUMENTATION=OFF -DKHIVA_BUILD_EXAMPLES=OFF -DKHIVA_BUILD_BENCHMARKS=OFF
make all
AF_PRINT_ERRORS=1 ./bin/dimensionality
make test

cd ..