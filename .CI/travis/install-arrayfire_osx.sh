#!/bin/bash
  
###################
# Install Arrayfire
###################

wget http://arrayfire.s3.amazonaws.com/3.5.1/ArrayFire-no-gl-v3.5.1_OSX.pkg
sudo mkdir /opt/arrayfire

# chmod +x ArrayFire-no-gl-v3.5.1_OSX.pkg
sudo installer -pkg ArrayFire-no-gl-v3.5.1_OSX.pkg -target /
rm ArrayFire-no-gl-v3.5.1_OSX.pkg
