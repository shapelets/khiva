#!/bin/bash

# Installing dependencies
sudo apt-get update
sudo apt-get install -y python3 python3-pip cmake libboost-all-dev

# Installing conan
sudo pip3 install conan

# Installing library dependencies with conan
conan remote add conan-mpusz https://api.bintray.com/conan/mpusz/conan-mpusz
conan remote add boost_math https://api.bintray.com/conan/bincrafters/public-conan
conan install . --build missing -s compiler.libcxx=libstdc++11

# Preparing the build
mkdir build
cd build
cmake ..
make all
