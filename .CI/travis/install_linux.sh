#!/bin/bash
# Copyright (c) 2019 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

sudo apt-get update -y
sudo apt-get install -y lcov python3 python3-pip rpm python3-setuptools

# Installing conan
sudo pip3 install conan==1.22.2

if ! [[ -z "${TRAVIS_TAG}" ]]; then
  sudo apt-get install -y doxygen graphviz
  sudo pip3 install sphinx==1.7.5 breathe==4.9.1 sphinx_rtd_theme==0.4.0
fi
