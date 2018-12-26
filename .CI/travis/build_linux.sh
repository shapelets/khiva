#!/bin/bash
# Copyright (c) 2018 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

mkdir -p build && cd build
conan install .. --build missing
if [[ -z "${TRAVIS_TAG}" ]]; then
  ../cmakebin/bin/cmake .. -DKHIVA_ENABLE_COVERAGE=ON -DKHIVA_BUILD_DOCUMENTATION=OFF -DKHIVA_BUILD_EXAMPLES=OFF -DKHIVA_BUILD_BENCHMARKS=OFF
  make all -j8
  make test
else
  ../cmakebin/bin/cmake ..
  make all -j8
fi
