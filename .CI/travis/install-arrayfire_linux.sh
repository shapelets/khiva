#!/bin/bash
# Copyright (c) 2018 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

wget http://arrayfire.s3.amazonaws.com/3.6.0/ArrayFire-no-gl-v3.6.0_Linux_x86_84.sh
sudo mkdir /opt/arrayfire

chmod +x ArrayFire-no-gl-v3.6.0_Linux_x86_84.sh
sudo ./ArrayFire-no-gl-v3.6.0_Linux_x86_84.sh --prefix=/opt/arrayfire --skip-license
rm ArrayFire-no-gl-v3.6.0_Linux_x86_84.sh