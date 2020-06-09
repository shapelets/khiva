FROM nvidia/cuda:10.1-devel-ubuntu18.04 AS khiva-cuda-builder-base
RUN apt-get update && apt-get install -y --no-install-recommends \
    software-properties-common \
    build-essential \
    cmake \
    git \
    libboost-all-dev \
    libfftw3-dev \
    libfreeimage-dev \
    liblapack-dev \
    liblapacke-dev \
    libopenblas-dev \
    openjdk-8-jdk \
    python3-pip && \
    pip3 install setuptools && \
    pip3 install conan --upgrade && \
    conan profile new --detect default && \
    conan profile update settings.compiler.libcxx=libstdc++11 default && \
    rm -rf /var/lib/apt/lists/* /var/tmp/* /tmp/*

# AF_DISABLE_GRAPHICS - Environment variable to disable graphics at
# runtime due to lack of graphics support by docker - visit
# http://arrayfire.org/docs/configuring_environment.htm#af_disable_graphics
# for more information
# For build instructions: https://github.com/arrayfire/arrayfire/wiki/Build-Instructions-for-Linux
ENV CXX g++-7
ENV CC gcc-7
WORKDIR /root

COPY *.patch ./
FROM khiva-cuda-builder-base AS arrayfire-cuda-builder
ENV AF_DISABLE_GRAPHICS=1
RUN git clone -b v3.6.2 --depth 1 --recurse-submodules -j 8 https://github.com/arrayfire/arrayfire.git && \
    cd arrayfire && \
    mkdir build && cd build && \
    cmake .. -DCMAKE_INSTALL_PREFIX=/opt/arrayfire \
             -DCMAKE_BUILD_TYPE=Release \
             -DAF_BUILD_CPU=ON \
             -DAF_BUILD_CUDA=ON \
             -DAF_BUILD_OPENCL=OFF \
             -DCUDA_cublas_device_LIBRARY=/usr/local/cuda/lib64 \
             -DAF_BUILD_UNIFIED=ON \
             -DAF_WITH_GRAPHICS=OFF \
             -DAF_WITH_NONFREE=OFF \
             -DAF_BUILD_EXAMPLES=OFF \
             -DBUILD_TESTING=OFF \
             -DAF_BUILD_DOCS=OFF \
             -DAF_WITH_LOGGING=OFF \
             -DAF_WITH_STATIC_FREEIMAGE=OFF && \
    cmake --build . --target install -- -j8

FROM khiva-cuda-builder-base AS khiva-cuda-builder
ARG KHIVA_BRANCH=v0.5.0
COPY --from=arrayfire-cuda-builder /opt/arrayfire /opt/arrayfire
ENV JAVA_HOME /usr/lib/jvm/java-8-openjdk-amd64
RUN echo /opt/arrayfire/lib > /etc/ld.so.conf.d/arrayfire.conf && \
    ldconfig && \
    git clone -b ${KHIVA_BRANCH} --depth 1  --recurse-submodules -j 8 https://github.com/shapelets/khiva.git && \
    cd khiva && \
    mkdir build && \
    cd build && \
    conan install .. --build missing && \
    cmake .. \
        -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=/opt/khiva \
        -DKHIVA_BUILD_TESTS=ON \
        -DKHIVA_BUILD_BENCHMARKS=ON \
        -DKHIVA_BUILD_EXAMPLES=OFF \
        -DKHIVA_BUILD_DOCUMENTATION=OFF \
        -DKHIVA_USE_CONAN=ON \
        -DKHIVA_BUILD_C_BINDINGS=ON \
        -DKHIVA_BUILD_JNI_BINDINGS=ON && \
    cmake --build . --target install -- -j8

FROM nvidia/cuda:10.1-runtime-ubuntu18.04 AS arrayfire-cuda
COPY --from=arrayfire-cuda-builder /opt/arrayfire /opt/arrayfire
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    libopenblas-base \
    libfftw3-3 \
    liblapacke && \
    echo /opt/arrayfire/lib > /etc/ld.so.conf.d/arrayfire.conf && \
    ldconfig && \
    rm -rf /var/lib/apt/lists/* /var/tmp/* /tmp/*

FROM arrayfire-cuda AS khiva-cuda
ENV LD_LIBRARY_PATH="/opt/khiva/lib:${LD_LIBRARY_PATH}"
COPY --from=khiva-cuda-builder /opt/khiva /opt/khiva
RUN echo /opt/khiva/lib > /etc/ld.so.conf.d/khiva.conf && \
    ldconfig
