#!/bin/bash
  
###############
# Install CMAKE
###############

sudo apt-get remove cmake
wget https://cmake.org/files/v3.11/cmake-3.11.3-Linux-x86_64.sh
chmod +x cmake-3.11.3-Linux-x86_64.sh
sudo ./cmake-3.11.3-Linux-x86_64.sh --skip-license --prefix=/usr/local
sudo ln -s /usr/local/bin/cmake /usr/bin/cmake
rm cmake-3.11.3-Linux-x86_64.sh