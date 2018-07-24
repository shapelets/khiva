#!/bin/bash
# Copyright (c) 2018 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# Checks if the file already exists
if [ ! -e "${TRAVIS_BUILD_DIR}/arrayfire/ArrayFire-no-gl-v3.5.1_OSX.pkg" ]; then
    mkdir -p arrayfire
    wget http://arrayfire.s3.amazonaws.com/3.5.1/ArrayFire-no-gl-v3.5.1_OSX.pkg -O arrayfire/ArrayFire-no-gl-v3.5.1_OSX.pkg
fi

# Installs arrayfire
sudo installer -pkg arrayfire/ArrayFire-no-gl-v3.5.1_OSX.pkg -target /