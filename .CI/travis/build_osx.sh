#!/bin/bash
# Copyright (c) 2018 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# Build the project
mkdir -p build && cd build
conan install .. -s compiler=apple-clang -s compiler.version=9.1 -s compiler.libcxx=libc++ --build missing
if [[ -z "${TRAVIS_TAG}" ]]; then
  cmake .. -DKHIVA_ENABLE_COVERAGE=ON -DKHIVA_ONLY_CPU_BACKEND=ON -DKHIVA_BUILD_DOCUMENTATION=OFF -DKHIVA_BUILD_EXAMPLES=OFF -DKHIVA_BUILD_BENCHMARKS=OFF
  make all -j8
  make test
else
  cmake ..
  make all -j8
fi
