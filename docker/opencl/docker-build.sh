#! /usr/bin/env bash
docker build --target khiva-opencl-builder-base -t $PUSH_REGISTRY/shapelets/khiva-opencl-builder-base:0.5.0 .
docker build --target arrayfire-opencl-builder -t $PUSH_REGISTRY/shapelets/arrayfire-opencl-builder:3.6.2 .
docker build --target khiva-builder --build-arg KHIVA_BRANCH=v0.5.0 -t $PUSH_REGISTRY/shapelets/khiva-builder:0.5.0 .
docker build --target arrayfire-intel-opencl -t $PUSH_REGISTRY/shapelets/arrayfire-intel-opencl:3.6.2 .
docker build --target khiva-intel-opencl -t $PUSH_REGISTRY/shapelets/khiva:0.5.0-opencl .
docker push $PUSH_REGISTRY/shapelets/khiva-opencl-builder-base:0.5.0
docker push $PUSH_REGISTRY/shapelets/arrayfire-opencl-builder:3.6.2
docker push $PUSH_REGISTRY/shapelets/khiva-builder:0.5.0
docker push $PUSH_REGISTRY/shapelets/arrayfire-intel-opencl:3.6.2
docker push $PUSH_REGISTRY/shapelets/khiva:0.5.0-opencl
