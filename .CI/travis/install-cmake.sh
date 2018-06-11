#!/bin/bash
  
###############
# Install CMAKE
###############

wget https://cmake.org/files/v3.11/cmake-3.11.3.tar.gz
tar -xzf cmake-3.11.3.tar.gz
cd cmake-3.11.3
./bootstrap > /dev/null 2>&1
sudo make install
# To update to the new version
sudo update-alternatives --install /usr/bin/cmake cmake /usr/local/bin/cmake 1 --force
cmake --version
cd ..
