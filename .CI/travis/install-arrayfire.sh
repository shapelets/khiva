#!/bin/bash
  
###################
# Install Arrayfire
###################


if [ ! -d "/opt/arrayfire" ]; then
    wget http://arrayfire.s3.amazonaws.com/3.6.0/ArrayFire-no-gl-v3.6.0_Linux_x86_84.sh
    mkdir /opt/arrayfire

    chmod +x ArrayFire-no-gl-v3.6.0_Linux_x86_84.sh
    ./ArrayFire-no-gl-v3.6.0_Linux_x86_84.sh --prefix=/opt/arrayfire --skip-license
    rm ArrayFire-no-gl-v3.6.0_Linux_x86_84.sh
fi

