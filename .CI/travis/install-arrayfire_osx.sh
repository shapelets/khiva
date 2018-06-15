#!/bin/bash
  
###################
# Install Arrayfire
###################

wget http://arrayfire.s3.amazonaws.com/3.5.1/ArrayFire-no-gl-v3.5.1_OSX.pkg
sudo mkdir /opt/arrayfire

chmod +x ArrayFire-v3.6.0_macOS_x86_64.sh
sudo installer -pkg ArrayFire-no-gl-v3.5.1_OSX.pkg -target /opt/arrayfire
rm ArrayFire-no-gl-v3.5.1_OSX.pkg
