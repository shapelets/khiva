#!/bin/bash
# Copyright (c) 2018 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# Check if the file already exists
if [ ! -e "${TRAVIS_BUILD_DIR}/cmake/cmake-3.13.2-Linux-x86_64.sh" ]; then
    mkdir -p cmakebin
    wget https://github.com/Kitware/CMake/releases/download/v3.13.2/cmake-3.13.2-Linux-x86_64.sh -O cmakebin/cmake-3.13.2-Linux-x86_64.sh 
fi

# Install cmake
sudo bash cmakebin/cmake-3.13.2-Linux-x86_64.sh --prefix=./cmakebin/ --skip-license