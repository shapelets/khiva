#!/bin/bash
# Copyright (c) 2018 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

wget http://arrayfire.s3.amazonaws.com/3.5.1/ArrayFire-no-gl-v3.5.1_Linux_x86_64.sh
sudo mkdir /opt -p

chmod +x ArrayFire-no-gl-v3.5.1_Linux_x86_64.sh
sudo ./ArrayFire-no-gl-v3.5.1_Linux_x86_64.sh --prefix=/opt --skip-license

rm ArrayFire-no-gl-v3.5.1_Linux_x86_64.sh