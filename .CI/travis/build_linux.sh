#!/bin/bash
# Copyright (c) 2019 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
function check-error() {
  KHIVA_ERROR=$?
  if [ $KHIVA_ERROR -ne 0 ]; then
      echo "$1: $KHIVA_ERROR"
      exit $KHIVA_ERROR
  fi
}

cmake --version
mkdir -p build && cd build
conan profile new --detect --force default
conan profile update settings.compiler.libcxx=libstdc++11 default
conan install .. --build missing
cmake ..
check-error "Error generating CMake configuration"
cmake --build . -- -j8
check-error "Error building Khiva"
ctest --output-on-failure
check-error "Error executing tests"
