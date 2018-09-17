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
* To run on accelerators like GPUs, `Arrayfire 3.5.1 no-gl <https://arrayfire.com/download/>`_. Note that in order to use Arrayfire on Windows you need to `install <https://www.microsoft.com/en-in/download/details.aspx?id=48145>`_ the Visual Studio 2015 (x64) runtime libraries.
* To test the functionality provided by Khiva, `Google Test <https://github.com/google/googletest>`_.
* To benchmark Khiva, `Google Benchmark <https://github.com/google/benchmark>`_.
* `Boost <https://www.boost.org/users/download/>`_.
* `Eigen <https://bitbucket.org/eigen/eigen/downloads/?tab=tags>`_.

Linux
=====
.. _section-installation-linux:

We will use `Ubuntu 16.04 LTS <http://www.ubuntu.com>`_ as our linux distribution example.

Prerequisites
^^^^^^^^^^^^^

- Install [Python-64bits](https://www.python.org/downloads) or run `apt-get install python3 python3-pip`, 32-bits version won't work.
- Download [ArrayFire 3.5.1 no-gl](http://arrayfire.s3.amazonaws.com/3.5.1/ArrayFire-no-gl-v3.5.1_Linux_x86_64.sh).
- Install ArrayFire `sudo mkdir -p /opt/arrayfire`
- Run `sudo bash arrayfire/ArrayFire-v3.5.1_Linux_x86_64.sh --prefix=/opt/arrayfire --skip-license`

Once we have installed all Khiva dependencies, we are ready to build and install Khiva. First, go to the source directory.

Build Process
^^^^^^^^^^^^^

.. code-block:: bash

    conan remote add conan-mpusz https://api.bintray.com/conan/mpusz/conan-mpusz
    mkdir build
    cd build
    conan install .. --build missing
    cmake ..
    make -j8
    make install

It will install the library in ``/usr/local/lib`` and ``/usr/local/include`` folders.

In case ArrayFire is not installed in the system default directories, it is also required to add the Arrayfire lib folder 
to the environment variable  LD_LIBRARY_PATH.

.. code-block:: bash

   export LD_LIBRARY_PATH="/pathToArrayfire/arrayfire/lib:$LD_LIBRARY_PATH"

Install Khiva library from source code
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

-  Run `make install`.

Generating the khiva installer
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

CPack is used in order to perform this task.

**Notes:** Before generating the installer the project should be built following the process explained in the `Process` section above. The generated package will be stored in the `build` folder.

For linux either a deb or a rpm package the installer can be generated. This could be done running the command `cpack -G DEB` or `cpack -G RPM` respectively inside the build folder.

Generating documentation
~~~~~~~~~~~~~~~~~~~~~~~~

We use `sphinx + doxygen` to generate our documentation. You will need to install the following packages:

- Sphinx: `brew install sphinx`.
- Doxygen: `brew install doxygen`.
- Read the Docs Theme: `pip install sphinx_rtd_theme`.
- Breathe: `pip install breathe`.

To generate the khiva documentation run the following command.

- `make KHIVA_doc_sphinx`.

Mac OS
======
.. _section-installation-mac:

Prerequisites
^^^^^^^^^^^^^

- Install [Python-64bits](https://www.python.org/downloads) or run `brew install python3`, 32-bits version won't work.
- Install [ArrayFire 3.5.1 no-gl](http://arrayfire.s3.amazonaws.com/3.5.1/ArrayFire-no-gl-v3.5.1_OSX.pkg) and add the path to the environment variable path.

Once we have installed all Khiva dependencies, we are ready to build and install Khiva. First, go to the directory 
where the source code is stored:

Build Process
^^^^^^^^^^^^^

.. code-block:: bash

    conan remote add conan-mpusz https://api.bintray.com/conan/mpusz/conan-mpusz
    mkdir build
    cd build
    conan install .. --build missing
    cmake ..
    make -j8
    make install

It will install the library in ``/usr/local/lib`` and ``/usr/local/include`` folders.

Install Khiva library from source code
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

-  Run `cmake install`.

Generating the khiva installer
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

For Mac OS the installer can be generated running the command `cpack -G productbuild` inside the build folder.

Generating documentation
~~~~~~~~~~~~~~~~~~~~~~~~

We use `sphinx + doxygen` to generate our documentation. You will need to install the following packages:

- Sphinx: `brew install sphinx`.
- Doxygen: `brew install doxygen`.
- Read the Docs Theme: `pip install sphinx_rtd_theme`.
- Breathe: `pip install breathe`.

To generate the khiva documentation run the following command.

- `make KHIVA_doc_sphinx`.

Windows
=======

Installation
~~~~~~~~~~~~

Prerequisites
^^^^^^^^^^^^^

-  Install `Python-64bits <https://www.python.org/downloads>`__ and add
   the path to the environment variable path, 32-bits version won't
   work.
-  Install `ArrayFire 3.5.1 <https://arrayfire.com/download/>`__ and add
   the path to the environment variable path.
-  Install `Vcpkg <https://docs.microsoft.com/es-es/cpp/vcpkg#installation>`__
   and add the path to the environment variable path.
-  Install `chocolatey <https://chocolatey.org/>`__ to manage windows
   dependencies and add the path to the environment variable path.

Build Process
^^^^^^^^^^^^^

-  Run ``choco install cmake.install -NoNewWindow -Wait`` Note: Add the
   path to the environment variable path and **before** than chocolately
   environment variable path.
-  Run ``choco install doxygen.install -NoNewWindow -Wait``.
-  Run ``choco install graphviz -NoNewWindow -Wait``.
-  Run ``python -m pip install --upgrade pip``.
-  Run ``pip3 install sphinx breathe sphinx_rtd_theme``.
-  Run
   ``vcpkg install --triplet x64-windows gtest eigen3 benchmark boost``.
-  Create a ``build`` folder in the root path of the project.
-  Browse inside the ``build`` folder.
-  Run
   ``cmake .. -DCMAKE_TOOLCHAIN_FILE="<PATH_TO_VPKG>/scripts/buildsystems/vcpkg.cmake" -DKHIVA_USE_CONAN=OFF -G "Visual Studio 15 2017 Win64"``
   (Do not forget to clean the build directory everytime before running
   this command).
-  Run ``cmake --build . --config Release -- /m`` to compile.

Install Khiva library from source code
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

As a final step of the installation process:

-  Run ``cmake -DBUILD_TYPE=Release -P cmake_install.cmake``.

Generating the Khiva installer
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

We use Cpack and NSIS to generate the installer.

**Notes:** Before generating the installer, the project must be built by
following the steps in the previous ``Process`` section. The generated
package will be stored in the ``build`` folder.

-  Run ``choco install nsis -NoNewWindow -Wait``.
-  The installer can be generated running the command ``cpack -G NSIS``.

**Note:** We use the ``cpack`` command from ``cmake``, be aware
``chocolatey`` has another cpack command. If you cannot run the proper
command, check out the path from ``cmake`` is placed before the path
from ``chocolatey`` in the environment variable path.

Generating documentation
~~~~~~~~~~~~~~~~~~~~~~~~

-  Run ``pip install sphinx`` to install
   `Sphinx <http://www.sphinx-doc.org/es/stable/install.html#windows-install-python-and-sphinx>`__.
-  Browse to the root path of the project.
-  Run ``sphinx-build.exe -b html doc/sphinx/source/ build/doc/html/``.