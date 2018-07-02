#!/bin/bash
# Copyright (c) 2018 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# Forcing Python 3.6.5_1. Pip packages using cython do not compile with 3.7.0.
BREW_PREFIX=$( brew --prefix )
git checkout f2a764e ${BREW_PREFIX}/Homebrew/Library/Taps/homebrew/homebrew-core/Formula/python.rb
brew upgrade python
git checkout -- ${BREW_PREFIX}/Homebrew/Library/Taps/homebrew/homebrew-core/Formula/python.rb

brew install --force lcov

# Installing conan
sudo pip3 install --upgrade pip
sudo pip3 install conan

# Installing library dependencies with conan
conan remote add -f conan-mpusz https://api.bintray.com/conan/mpusz/conan-mpusz
