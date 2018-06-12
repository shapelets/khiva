#!/bin/bash

cd build
coveralls --root .. -E ".*external.*" -E ".*CMakeFiles.*" -E ".*test/.*" -E ".*bindings/.*" -E ".*benchmarks/.*" -E ".*cmake/.*" -E "/usr/*.*" -E "/opt/*.*" -E "/home/travis/.conan/*.*" --exclude lib --exclude tests --gcov-options '\-lp' 
cd ..