#!/bin/bash
# Copyright (c) 2019 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# Checks if the file already exists
if [ ! -e "${TRAVIS_BUILD_DIR}/arrayfire/ArrayFire-v3.6.2_Linux_x86_64.sh" ]; then
    mkdir -p arrayfire
    wget http://arrayfire.s3.amazonaws.com/3.6.2/ArrayFire-v3.6.2_Linux_x86_64.sh -O arrayfire/ArrayFire-v3.6.2_Linux_x86_64.sh
fi

# Installs arrayfire
sudo mkdir -p /opt/arrayfire
sudo bash arrayfire/ArrayFire-v3.6.2_Linux_x86_64.sh --prefix=/opt/arrayfire --skip-license
sudo echo /opt/arrayfire/lib64 > /etc/ld.so.conf.d/arrayfire.conf
sudo ldconfig
