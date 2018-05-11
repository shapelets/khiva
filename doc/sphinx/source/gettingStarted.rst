.. _chapter-gettingstarted:

===============
Getting Started
===============

Getting the source code
=======================
.. _getting-source:


You can download the `latest stable released version <https://bitbucket.org/gcatsoft/tsa>`_, or you can get the 
latest source code version by cloning our git repository:

.. code-block:: bash

    git clone https://bitbucket.org/gcatsoft/tsa


Dependencies
============

TSA relies on a number of open source libraries and tools which are required to get it running.

Tools:

* A Build manager to control the compilation process `CMake <https://cmake.org/download/>`_.
* A dependency manager `Conan <https://conan.io/>`_.
* `Python <https://www.python.org/downloads/>`_ (Preferably version 3.X).
* Documentation builders `Doxygen <http:://www.doxygen.org>`_ and `sphinx <http://www.sphinx-doc.org/en/master/usage/installation.html>`_.
* A C++ compiler, it can be either `Clang <http://releases.llvm.org/download.html>`_, `GCC <https://gcc.gnu.org/install/binaries.html>`_ or `Visual Studio C++ Compiler <https://www.visualstudio.com/es>`_.

.. NOTE ::
    All versions of TSA Library require a **fully C++11-compliant**
    compiler.

Libraries: 

* OpenCL library for you GPU card (`Intel <https://software.intel.com/en-us/intel-opencl/download>`_, `AMD <https://support.amd.com/en-us/download>`_, or `Nvidia <https://developer.nvidia.com/opencl>`_).
* To run on accelerators like GPUs, `Arrayfire <https://arrayfire.com/download/>`_.
* To test the functionality provided by TSA, `Google Test <https://github.com/google/googletest>`_.
* To benchmark TSA, `Google Benchmark <https://github.com/google/benchmark>`_.
* `Boost <https://www.boost.org/users/download/>`_.
* `Eigen <https://bitbucket.org/eigen/eigen/downloads/?tab=tags>`_.

Linux
=====
.. _section-installation-linux:

We will use `Ubuntu 16.04 LTS <http://www.ubuntu.com>`_ as our example linux distribution.

Start by installing all the dependencies.

.. code-block:: bash

     # git
     sudo apt-get install git
     
     # CMake
     sudo apt-get install cmake
     
     # Google Test
     sudo apt-get install libgtest-dev
     
     # Google Benchmark
     git clone https://github.com/google/benchmark.git
     cd benchmark
     mkdir build
     cd build
     cmake .. -DCMAKE_BUILD_TYPE=RELEASE
     make
     sudo make install

     # Eigen3
     sudo apt-get install libeigen3-dev
     
     # Boost
     sudo apt-get install libboost-all-dev
     
     # Arrayfire
     wget http://arrayfire.s3.amazonaws.com/3.6.0/ArrayFire-no-gl-v3.6.0_Linux_x86_84.sh
     ./Arrayfire_*_Linux_x86_64.sh --include-subdir --prefix=/opt
     echo /opt/arrayfire/lib > /etc/ld.so.conf.d/arrayfire.conf
     sudo ldconfig


Once we have installed all dependencies, we are ready to build and install TSA. First go to the directory 
where the source code is stored.

.. code-block:: bash

    mkdir build
    cd build
    cmake ..
    make install

It will install the library in ``/usr/local/lib`` and ``/usr/local/include`` folders.


Mac Os
======
.. _section-installation-mac:

TODO


Windows
=======
.. _section-installation-windows:

Windows is not yet supported, we are working on it.