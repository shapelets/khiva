#!/bin/bash


# Build the project
mkdir -p build && cd build
../bin/cmake .. -DKHIVA_COVERAGE=ON
make all