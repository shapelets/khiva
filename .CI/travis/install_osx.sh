#!/bin/bash
# Copyright (c) 2018 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

brew upgrade pyenv
export PATH=$HOME/.pyenv/shims:$HOME/.pyenv/versions/${TRAVIS_PYTHON_VERSION}/bin:$PATH
pyenv install 3.6.5 -s
pyenv init -
pyenv local 3.6.5

brew install --force lcov

# Installing conan
sudo pip3 install --upgrade pip
sudo pip3 install conan

# Installing library dependencies with conan
conan remote add -f conan-mpusz https://api.bintray.com/conan/mpusz/conan-mpusz
