#!/bin/bash

# Installing dependencies
sudo apt-get update
sudo apt-get install -y python3 cmake

# Installing conan
pip install conan

# Installing library dependencies with conan
conan install . --build missing -s compiler.libcxx=libstdc++11

# Preparing the build
mkdir build
cd build
cmake ..
make all
