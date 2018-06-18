#!/bin/bash

# Build the project
mkdir -p build && cd build
cmake .. -DKHIVA_ENABLE_COVERAGE=ON -DKHIVA_BUILD_DOCUMENTATION=OFF -DKHIVA_BUILD_EXAMPLES=OFF -DKHIVA_BUILD_BENCHMARKS=OFF
make all
make test
cd ..