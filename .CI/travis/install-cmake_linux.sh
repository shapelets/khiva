#!/bin/bash
# Copyright (c) 2018 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

if [ ! -e "${TRAVIS_BUILD_DIR}/cmake/cmake-3.11.3-Linux-x86_64.sh" ]; then
    mkdir -p cmake && cd cmake
    wget https://cmake.org/files/v3.11/cmake-3.11.3-Linux-x86_64.sh
    cd ..
fi

mkdir cmakebin
cp cmake/cmake-3.11.3-Linux-x86_64.sh cmakebin/cmake-3.11.3-Linux-x86_64.sh
cd cmakebin
chmod +x cmake-3.11.3-Linux-x86_64.sh
sudo ./cmake-3.11.3-Linux-x86_64.sh --skip-license
cd ..