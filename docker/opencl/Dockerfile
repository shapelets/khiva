FROM intelopencl/intel-opencl:ubuntu-18.04-ppa AS khiva-opencl-builder-base
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    git \
    libboost-math-dev \
    libfftw3-dev \
    libfreeimage-dev \
    liblapack-dev \
    liblapacke-dev \
    libopenblas-dev \
    openjdk-8-jdk \
    ocl-icd-opencl-dev \
    python3-pip \
    software-properties-common && \
    pip3 install setuptools && \
    pip3 install conan --upgrade && \
    conan profile new --detect default && \
    conan profile update settings.compiler.libcxx=libstdc++11 default && \
    rm -rf /var/lib/apt/lists/* /var/tmp/* /tmp/*

ENV CXX g++-7
ENV CC gcc-7
WORKDIR /root
COPY *.patch ./

# AF_DISABLE_GRAPHICS - Environment variable to disable graphics at
# runtime due to lack of graphics support by docker - visit
# http://arrayfire.org/docs/configuring_environment.htm#af_disable_graphics
# for more information
# For build instructions: https://github.com/arrayfire/arrayfire/wiki/Build-Instructions-for-Linux
FROM khiva-opencl-builder-base AS arrayfire-opencl-builder
ENV AF_DISABLE_GRAPHICS=1
RUN git clone -b v3.6.2 --depth 1 --recurse-submodules -j 8 https://github.com/arrayfire/arrayfire.git && \
    cd arrayfire && \
    mkdir build && cd build && \
    cmake .. -DCMAKE_INSTALL_PREFIX=/opt/arrayfire \
             -DCMAKE_BUILD_TYPE=Release \
             -DAF_BUILD_CPU=ON \
             -DAF_BUILD_CUDA=OFF \
             -DAF_BUILD_OPENCL=ON \
             -DAF_BUILD_UNIFIED=ON \
             -DAF_WITH_GRAPHICS=OFF \
             -DAF_WITH_NONFREE=OFF \
             -DAF_BUILD_EXAMPLES=OFF \
             -DBUILD_TESTING=OFF \
             -DAF_BUILD_DOCS=OFF \
             -DAF_WITH_LOGGING=OFF \
             -DAF_WITH_STATIC_FREEIMAGE=OFF && \
    cmake --build . --target install -- -j8

FROM khiva-opencl-builder-base AS khiva-builder
ARG KHIVA_BRANCH=v0.5.0
WORKDIR /root
COPY --from=arrayfire-opencl-builder /opt/arrayfire /opt/arrayfire
RUN echo /opt/arrayfire/lib > /etc/ld.so.conf.d/arrayfire.conf && \
    ldconfig && \
    git clone -b ${KHIVA_BRANCH} --depth 1 --recurse-submodules -j 8 https://github.com/shapelets/khiva.git && \
    cd khiva && \
    mkdir build && \
    cd build && \
    conan install .. --build missing && \
    cmake .. -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=/opt/khiva \
        -DKHIVA_BUILD_TESTS=ON \
        -DKHIVA_BUILD_BENCHMARKS=ON \
        -DKHIVA_BUILD_EXAMPLES=OFF \
        -DKHIVA_BUILD_DOCUMENTATION=OFF \
        -DKHIVA_USE_CONAN=ON \
        -DKHIVA_BUILD_C_BINDINGS=ON \
        -DKHIVA_BUILD_JNI_BINDINGS=ON && \
    cmake --build . --target install -- -j8

FROM intelopencl/intel-opencl:ubuntu-18.04-ppa AS arrayfire-intel-opencl
COPY --from=arrayfire-opencl-builder /opt/arrayfire /opt/arrayfire
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    libopenblas-base \
    libfftw3-3 \
    liblapacke && \
    echo /opt/arrayfire/lib > /etc/ld.so.conf.d/arrayfire.conf && \
    ldconfig && \
    rm -rf /var/lib/apt/lists/* /var/tmp/* /tmp/*

FROM arrayfire-intel-opencl as khiva-intel-opencl
COPY --from=khiva-builder /opt/khiva /opt/khiva
RUN echo /opt/khiva/lib > /etc/ld.so.conf.d/khiva.conf && \
    ldconfig
