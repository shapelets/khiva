#!/bin/bash


# Build the project
mkdir -p build && cd build
cmake .. -DKHIVA_BUILD_DOCUMENTATION=OFF -DKHIVA_BUILD_EXAMPLES=OFF -DKHIVA_BUILD_BENCHMARKS=OFF
make all
./bin/version
./bin/dimensionality
make test

cd ..