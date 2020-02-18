# Installation process

## Windows users

### Installation

#### Prerequisites

- Install [Python-64bits](https://www.python.org/downloads) and add the installation path to the environment variable path, 32-bits version won't work.
- Install [ArrayFire 3.6.2](http://arrayfire.s3.amazonaws.com/index.html#!/3.6.2%2F) and add the installation path to the environment variable path.
- Install [Vcpkg](https://docs.microsoft.com/es-es/cpp/vcpkg#installation) and add the installation path to the environment variable path.
- Install [chocolatey](https://chocolatey.org/) to manage windows dependencies and add the installation path to the environment variable path.

Once we have installed all Khiva dependencies, we are ready to install Khiva by using the installers (Option 1) or from source code (Option 2).

#### (Option 1) Build using a batch installer

In the tools directory you can find the script install.bat. You must indicate the path to your vcpkg installation directory.

- Usage: install.bat <path_to_vcpkg>
- Example: install.bat c:\vcpkg

#### (Option 2) Build from source code

If you prefer, you can build Khiva step by step.
First, go to the source directory.

- Run `choco install cmake.install -NoNewWindow -Wait` Note: Add the installation path to the environment variable path and **before** than chocolately environment variable path.
- Run `choco install doxygen.install -NoNewWindow -Wait`.
- Run `choco install graphviz -NoNewWindow -Wait`.
- Run `python -m pip install --upgrade pip`.
- Run `pip3 install sphinx breathe sphinx_rtd_theme`.
- Run `vcpkg install --triplet x64-windows gtest eigen3 benchmark boost`.
- Create a `build` folder in the root path of the project.
- Browse inside the `build` folder.
- Run `git submodule update --init`
- Run `cmake .. -DCMAKE_TOOLCHAIN_FILE="<PATH_TO_VPKG>/scripts/buildsystems/vcpkg.cmake" -DKHIVA_USE_CONAN=OFF -G "Visual Studio 15 2017 Win64"` (Note: Replace <PATH_TO_VPKG> with your vcpkg installation path and do not forget to clean the build directory everytime before running this command).
- Run `cmake --build . --config Release -- /m` to compile.

#### Install Khiva library

Once the build process is finished you can install the library in your system folder:

- Run `cmake -DBUILD_TYPE=Release -P cmake_install.cmake`.

### Generating the Khiva installer

We use CPack and NSIS to generate the installer.

**Notes:** Before generating the installer, the project has to be built by following the previous `Build from source code` section. The generated package is stored in the `build` folder.

- Run `choco install nsis -NoNewWindow -Wait`.
- The installer can be generated running the command `cpack -G NSIS`.

**Note:** We use the `cpack` command from `cmake`, be aware `chocolatey` has another cpack command. If you cannot run the proper command, check out the path from `cmake` is placed before the path from `chocolatey` in the environment variable path.

### Generating documentation

- Run `pip install sphinx` to install [Sphinx](http://www.sphinx-doc.org/es/stable/install.html#windows-install-python-and-sphinx).
- Browse to the root path of the project.
- Run `sphinx-build.exe -b html doc/sphinx/source/ build/doc/html/`.

## Linux users

### Installation

#### Prerequisites

- Install [Python-64bits](https://www.python.org/downloads) or run `apt-get install python3 python3-pip`, 32-bits version won't work.
- Download [ArrayFire 3.6.2](http://arrayfire.s3.amazonaws.com/3.6.2/ArrayFire-v3.6.2_Linux_x86_64.sh).
- Install ArrayFire:

   ```bash
   ./Arrayfire_*_Linux_x86_64.sh --include-subdir --prefix=/opt
   echo /opt/arrayfire/lib64 > /etc/ld.so.conf.d/arrayfire.conf
   sudo ldconfig
   ```
- Install opencl libraries. Follow [Intel guide](https://software.intel.com/en-us/articles/opencl-drivers#inpage-nav-1-1-1)

Once we have installed all Khiva dependencies, we are ready to install Khiva from source code or by using the installers.

#### Build from source code

- Install conan, c++ package manager, preferably running `pip install conan`. For more information and alternative installation options, please refer to [conan manual page](http://docs.conan.io/en/latest/installation.html).
- Run:
  ```bash
  git submodule update --init
  mkdir build && cd build
  conan install .. --build missing
  cmake ..
  make -j8
  ```

#### Install Khiva library from source code

- Run `make install`.

### Generating the Khiva installer

The CPack utility from cmake is used to generate the installer.

**Notes:** Before generating the installer, the project has to be built by following the `Build from source code` section above. The generated package is stored in the `build` folder.

For linux, either a deb or a rpm installer package can be generated. This is done by running the command `cpack -G DEB` or `cpack -G RPM` respectively inside the build folder.

### Generating documentation

We use `sphinx + doxygen` to generate our documentation. You will need to install the following packages:

As root:

- Sphinx: `apt-get install python3-sphinx`.
- Doxygen: `apt-get install doxygen`.
- Read the Docs Theme: `pip install sphinx_rtd_theme`.
- Breathe: `pip install breathe`.

To generate the khiva documentation run the following command:

- Run `make documentation`.

## Mac OS users

### Installation

#### Prerequisites

- Install [Python-64bits](https://www.python.org/downloads) or run `brew install python3`, 32-bits version won't work.
- Install [ArrayFire 3.6.2](http://arrayfire.s3.amazonaws.com/3.6.2/ArrayFire-v3.6.2_OSX_x86_64.pkg) and then execute the following lines to move the ArrayFire files from the default installation directory to the system path for libraries:

```bash
sudo mv /opt/arrayfire/include/* /usr/local/include
sudo mv /opt/arrayfire/lib/* /usr/local/lib
sudo mv /opt/arrayfire/share/* /usr/local/share
sudo rm -rf /opt/arrayfire
```

Once we have installed all Khiva dependencies, we are ready to install Khiva from source code or by using the installers.

#### Build from source code

- First you need to install conan, c++ manager, preferably running:
`pip install conan`
For more information and alternative installation options, please refer to [conan manual page](http://docs.conan.io/en/latest/installation.html).

- Create build folder and move into the new folder:
`mkdir build && cd build`

- Run the commands below:
`git submodule update --init`
`conan install .. --build missing`
`cmake ..`
`make -j8`

#### Install Khiva library from source code

To install the library in the default system folders, run the following command inside build folder from the previous step:

- Run `make install`.

### Generating the Khiva installer

For Mac OS, the installer can be generated by running the command `cpack -G productbuild` inside the build folder.

### Generating documentation

We use `sphinx + doxygen` to generate our documentation. You will need to install the following packages:

- Sphinx: `brew install sphinx`.
- Doxygen: `brew install doxygen`.
- Read the Docs Theme: `pip install sphinx_rtd_theme`.
- Breathe: `pip install breathe`.

To generate the khiva documentation run the following command.

- `make documentation`.
