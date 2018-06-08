#!/bin/bash

# Installing dependencies
sudo apt-get update
sudo apt-get install -y python3 pip3 cmake

# Installing conan
pip3 install conan

# Installing library dependencies with conan
conan install . --build missing -s compiler.libcxx=libstdc++11

# Preparing the build
mkdir build
cd build
cmake ..
make all
