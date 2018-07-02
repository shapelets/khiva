#!/bin/bash
# Copyright (c) 2018 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# Forcing Python 3.6.5_1. Pip packages using cython do not compile with 3.7.0.
cd "$(brew --repo homebrew/core)"
git checkout f2a764e -- ./Formula/python.rb
brew upgrade python
git reset HEAD ./Formula/python.rb
git checkout -- ./Formula/python.rb
cd $OLDPWD

brew install --force lcov

# Installing conan
sudo pip3 install --upgrade pip
sudo pip3 install conan

# Installing library dependencies with conan
conan remote add -f conan-mpusz https://api.bintray.com/conan/mpusz/conan-mpusz
