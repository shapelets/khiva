#!/bin/bash
# Copyright (c) 2018 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# Checks if the file already exists
if [ ! -e "${TRAVIS_BUILD_DIR}/arrayfire/ArrayFire-v3.6.2_OSX_x86_64.pkg" ]; then
    mkdir -p arrayfire
    wget http://arrayfire.s3.amazonaws.com/3.6.2/ArrayFire-v3.6.2_OSX_x86_64.pkg -O arrayfire/ArrayFire-v3.6.2_OSX_x86_64.pkg
fi

# Installs arrayfire
sudo installer -pkg arrayfire/ArrayFire-v3.6.2_OSX_x86_64.pkg -target /

# The new ArrayFire installer installs to /opt/arrayfire, moving to /usr/local/lib
sudo mv /opt/arrayfire/include/* /usr/local/include
sudo mv /opt/arrayfire/lib/* /usr/local/lib
sudo mv /opt/arrayfire/share/* /usr/local/share
sudo rm -rf /opt/arrayfire