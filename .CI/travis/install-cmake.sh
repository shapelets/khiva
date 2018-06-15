#!/bin/bash
  
###############
# Install CMAKE
###############

# Installing dependencies
wget https://cmake.org/files/v3.11/cmake-3.11.3-Linux-x86_64.sh
chmod +x cmake-3.11.3-Linux-x86_64.sh
sudo ./cmake-3.11.3-Linux-x86_64.sh --skip-license
rm cmake-3.11.3-Linux-x86_64.sh