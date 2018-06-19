#!/bin/bash
# Copyright (c) 2018 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

if [ ! -e "${TRAVIS_BUILD_DIR}/arrayfire/ArrayFire-no-gl-v3.5.1_OSX.pkg" ]; then
    mkdir -p arrayfire && cd arrayfire
    wget http://arrayfire.s3.amazonaws.com/3.5.1/ArrayFire-no-gl-v3.5.1_OSX.pkg
fi

sudo mkdir /opt/arrayfire

sudo installer -pkg ArrayFire-no-gl-v3.5.1_OSX.pkg -target /
cd ..