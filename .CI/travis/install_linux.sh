#!/bin/bash

sudo apt-get update -y
sudo apt-get install -y lcov python3 python3-pip libboost-all-dev doxygen graphviz

# Installing conan
pip3 install conan sphinx sphinx_rtd_theme breathe

# Installing library dependencies with conan
conan remote add -f conan-mpusz https://api.bintray.com/conan/mpusz/conan-mpusz
conan remote add -f boost_math https://api.bintray.com/conan/bincrafters/public-conan
