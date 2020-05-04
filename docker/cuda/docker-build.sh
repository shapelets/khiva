#! /usr/bin/env bash
docker build --target khiva-cuda-builder-base -t $PUSH_REGISTRY/shapelets/khiva-cuda-builder-base:0.5.0 .
docker build --target arrayfire-cuda-builder -t $PUSH_REGISTRY/shapelets/arrayfire-cuda-builder:3.6.2 .
docker build --target khiva-cuda-builder --build-arg KHIVA_BRANCH=v0.5.0 -t $PUSH_REGISTRY/shapelets/khiva-cuda-builder:0.5.0 .
docker run --gpus all --workdir /root/khiva/build $PUSH_REGISTRY/shapelets/khiva-cuda-builder:0.5.0 ctest --output-on-failure -j8
docker build --target arrayfire-cuda -t $PUSH_REGISTRY/shapelets/arrayfire-cuda:3.6.2 .
docker build --target khiva-cuda -t $PUSH_REGISTRY/shapelets/khiva-cuda:0.5.0 .
docker push $PUSH_REGISTRY/shapelets/khiva-cuda-builder-base:0.5.0
docker push $PUSH_REGISTRY/shapelets/arrayfire-cuda-builder:3.6.2
docker push $PUSH_REGISTRY/shapelets/khiva-cuda-builder:0.5.0
docker push $PUSH_REGISTRY/shapelets/arrayfire-cuda:3.6.2
docker push $PUSH_REGISTRY/shapelets/khiva-cuda:0.5.0
