#!/bin/bash


# Build the project
mkdir -p build && cd build
../bin/cmake .. -DKHIVA_ENABLE_COVERAGE=ON
make all
make test
cd ..