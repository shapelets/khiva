#!/bin/bash
# Copyright (c) 2018 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

sudo apt-get update -y
sudo apt-get remove -y cmake
sudo apt-get install -y lcov python3 python3-pip rpm

# Installing conan
sudo pip3 install conan==1.6.1

if ! [[ -z "${TRAVIS_TAG}" ]]; then
  sudo apt-get install -y doxygen graphviz
  sudo pip3 install sphinx breathe sphinx_rtd_theme
fi

# Installing library dependencies with conan
conan remote add -f conan-mpusz https://api.bintray.com/conan/mpusz/conan-mpusz
