#!/bin/bash
# Copyright (c) 2019 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

brew upgrade pyenv
brew upgrade cmake
pyenv install 3.6.5 -s
pyenv init -
pyenv local 3.6.5

export PATH=$HOME/.pyenv/shims:$HOME/.pyenv/versions/${TRAVIS_PYTHON_VERSION}/bin:$PATH
export PYTHON_VERSION=$(echo $TRAVIS_PYTHON_VERSION | awk -F'.' '{print $1 "." $2}')

brew install --force lcov
brew install --force freeimage fontconfig glfw glbinding

# Installing conan
pip${PYTHON_VERSION} install --upgrade pip
pip${PYTHON_VERSION} install conan==1.22.2

if ! [[ -z "${TRAVIS_TAG}" ]]; then
  brew install doxygen graphviz
  pip${PYTHON_VERSION} install sphinx==1.7.5 breathe==4.9.1 sphinx_rtd_theme==0.4.0
fi

# Installing library dependencies with conan
conan remote add -f conan-mpusz https://api.bintray.com/conan/mpusz/conan-mpusz
