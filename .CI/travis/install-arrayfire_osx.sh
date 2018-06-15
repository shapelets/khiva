#!/bin/bash
  
###################
# Install Arrayfire
###################

wget http://arrayfire.s3.amazonaws.com/3.6.0/ArrayFire-v3.6.0_macOS_x86_64.sh
sudo mkdir /opt/arrayfire

chmod +x ArrayFire-v3.6.0_macOS_x86_64.sh
sudo ./ArrayFire-v3.6.0_macOS_x86_64.sh --prefix=/opt/arrayfire --skip-license
rm ArrayFire-v3.6.0_macOS_x86_64.sh
