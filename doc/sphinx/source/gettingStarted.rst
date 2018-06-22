.. _chapter-gettingstarted:

===============
Getting Started
===============

Getting the source code
=======================
.. _getting-source:


You can download the `latest stable released version <https://shapelets.io/khiva>`_, or you can get the 
latest source code version by cloning our git repository:

.. code-block:: bash

    git clone https://github.com/shapelets/khiva


Dependencies
============

Khiva relies on a number of open source libraries and tools which are required to get it running.

Tools:

* A Build manager to control the compilation process `CMake <https://cmake.org/download/>`_.
* A dependency manager `Conan <https://conan.io/>`_.
* `Python 3 <https://www.python.org/downloads/>`_.
* `Pip3 <https://pypi.org/project/pip/>`_.
* Documentation builders `Doxygen <http:://www.doxygen.org>`_ and `sphinx <http://www.sphinx-doc.org/en/master/usage/installation.html>`_.
* `Graphviz and Dot <https://graphviz.gitlab.io/download/>`_.
* A C++ compiler, it can be either `Clang <http://releases.llvm.org/download.html>`_, `GCC <https://gcc.gnu.org/install/binaries.html>`_ or `Visual Studio C++ Compiler <https://www.visualstudio.com/es>`_.

.. NOTE ::
    All versions of Khiva Library require a **fully C++11-compliant**
    compiler.

Libraries: 

* OpenCL library for you GPU card (`Intel <https://software.intel.com/en-us/intel-opencl/download>`_, `AMD <https://support.amd.com/en-us/download>`_, or `Nvidia <https://developer.nvidia.com/opencl>`_).
* To run on accelerators like GPUs, `Arrayfire <https://arrayfire.com/download/>`_. Note that in order to use Arrayfire on Windows you need to `install <https://www.microsoft.com/en-in/download/details.aspx?id=48145>`_ Visual Studio 2015 (x64) runtime libraries.
* To test the functionality provided by Khiva, `Google Test <https://github.com/google/googletest>`_.
* To benchmark Khiva, `Google Benchmark <https://github.com/google/benchmark>`_.
* `Boost <https://www.boost.org/users/download/>`_.
* `Eigen <https://bitbucket.org/eigen/eigen/downloads/?tab=tags>`_.

Linux
=====
.. _section-installation-linux:

We will use `Ubuntu 16.04 LTS <http://www.ubuntu.com>`_ as our example linux distribution.

Once we have installed all Khiva dependencies, we are ready to build and install Khiva. First, go to the directory 
where the source code is stored.

.. code-block:: bash

    mkdir build
    cd build
    cmake ..
    make install

It will install the library in ``/usr/local/lib`` and ``/usr/local/include`` folders.

In case ArrayFire is not installed in the system default directories, it is also required to add the Arrayfire lib folder 
to the environment variable  LD_LIBRARY_PATH.

.. code-block:: bash

   export LD_LIBRARY_PATH="/pathToArrayfire/arrayfire/lib:$LD_LIBRARY_PATH"


Mac OS
======
.. _section-installation-mac:

Once we have installed all Khiva dependencies, we are ready to build and install Khiva. First, go to the directory 
where the source code is stored:

.. code-block:: bash

    mkdir build
    cd build
    cmake ..
    make install

It will install the library in ``/usr/local/lib`` and ``/usr/local/include`` folders.

Windows
=======
.. _section-installation-windows:

First, we need to ensure the Graphviz, Dot and Doxygen binaries are included in the environment variable PATH.
Once we have installed all Khiva dependencies, we are ready to build and install Khiva. So, go to the directory where the 
source code is stored and proceed as follows:

.. code-block:: bash

    mkdir build
    cd build
    cmake ..
    make install

It will install the library in ``C:/Program Files/Khiva/v0/lib`` and ``C:/Program Files/Khiva/v0/include`` folders.
