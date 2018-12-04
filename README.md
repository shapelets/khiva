# Khiva

[![License: MPL 2.0](https://img.shields.io/badge/License-MPL%202.0-brightgreen.svg)](https://github.com/shapelets/khiva-java/blob/master/LICENSE.txt)  
[![Gitter chat](https://badges.gitter.im/shapelets-io/Lobby.svg)](https://gitter.im/shapelets-io/khiva?utm_source=share-link&utm_medium=link&utm_campaign=share-link)

|                                                              Build Documentation                                                              |                                                   Build Linux and Mac OS                                                   |                                                                             Build Windows                                                                             |                                                                 Code Coverage                                                                  |
| :-------------------------------------------------------------------------------------------------------------------------------------------: | :------------------------------------------------------------------------------------------------------------------------: | :-------------------------------------------------------------------------------------------------------------------------------------------------------------------: | :--------------------------------------------------------------------------------------------------------------------------------------------: |
| [![Documentation Status](https://readthedocs.org/projects/khiva/badge/?version=latest)](https://khiva.readthedocs.io/en/master/?badge=latest) | [![Build Status](https://travis-ci.org/shapelets/khiva.svg?branch=master)](https://travis-ci.org/shapelets/khiva/branches) | [![Build status](https://ci.appveyor.com/api/projects/status/2oiggqcufnl3iddd/branch/master?svg=true)](https://ci.appveyor.com/project/shapelets/khiva/branch/master) | [![Coverage Status](https://codecov.io/gh/shapelets/khiva/branch/master/graph/badge.svg)](https://codecov.io/gh/shapelets/khiva/branch/master) |

Khiva is an open-source library of efficient algorithms to analyse time series in GPU and CPU. It can be used to extract insights from one or a group of time series. The large number of available methods allow us to understand the nature of each time series. Based on the results of this analysis, users can reduce dimensionality, find out recurrent motifs or discords, understand the seasonality or trend from a given time series, forecasting and detect anomalies.

Khiva provides a mean for time series analytics at scale. These analytics can be exploited in a wide range of [use cases](https://github.com/shapelets/khiva-use-cases) across several industries, like energy, finance, e-health, IoT, music industry, etc.

## License

This project is licensed under [MPL-v2](https://www.mozilla.org/en-US/MPL/2.0/).

## Windows users

### Installation

#### Prerequisites

- Install [Python-64bits](https://www.python.org/downloads) and add the installation path to the environment variable path, 32-bits version won't work.
- Install [ArrayFire 3.5.1](https://arrayfire.com/download/) and add the installation path to the environment variable path.
- Install [Vcpkg](https://docs.microsoft.com/es-es/cpp/vcpkg#installation) and add the installation path to the environment variable path.
- Install [chocolatey](https://chocolatey.org/) to manage windows dependencies and add the installation path to the environment variable path.

Once we have installed all Khiva dependencies,  we are ready to install Khiva by using the installers (Option 1) or from source code (Option 2).

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
- Run `cmake .. -DCMAKE_TOOLCHAIN_FILE="<PATH_TO_VPKG>/scripts/buildsystems/vcpkg.cmake" -DKHIVA_USE_CONAN=OFF -G "Visual Studio 15 2017 Win64"` (Note: Replace <PATH_TO_VPKG> with your vcpkg installation path and do not forget to clean the build directory everytime before running this command).
- Run `cmake --build . --config Release -- /m` to compile.

#### Install Khiva library

Once the build process is finished you can install the library in your system folder:

- Run `cmake -DBUILD_TYPE=Release -P cmake_install.cmake`.

### Generating the Khiva installer

We use Cpack and NSIS to generate the installer.

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
- Download [ArrayFire 3.5.1 no-gl](http://arrayfire.s3.amazonaws.com/3.5.1/ArrayFire-no-gl-v3.5.1_Linux_x86_64.sh).
- Install ArrayFire `sudo mkdir -p /opt/arrayfire`
- Run `sudo bash arrayfire/ArrayFire-v3.5.1_Linux_x86_64.sh --prefix=/opt/arrayfire --skip-license`

Once we have installed all Khiva dependencies, we are ready to install Khiva from source code or by using the installers.

#### Build from source code

- Install conan, c++ package manager, preferably running `pip install conan`. For more information and alternative installation options, please refer to [conan manual page](http://docs.conan.io/en/latest/installation.html).
- Run `conan remote add conan-mpusz https://api.bintray.com/conan/mpusz/conan-mpusz`.
- Create `build` folder and, after moving into the new folder, run `conan install .. --build missing`.
- Run `cmake ..`.
- Run `make -j8`.

#### Install Khiva library from source code

- Run `make install`.

### Generating the Khiva installer

The CPack utility from cmake is used to generate the installer.

**Notes:** Before generating the installer, the project has to be built by following the `Build from source code` section above. The generated package is stored in the `build` folder.

For linux, either a deb or a rpm installer package can be generated. This is done by running the command `cpack -G DEB` or `cpack -G RPM` respectively inside the build folder.

### Generating documentation

We use `sphinx + doxygen` to generate our documentation. You will need to install the following packages:

- Sphinx: `brew install sphinx`.
- Doxygen: `brew install doxygen`.
- Read the Docs Theme: `pip install sphinx_rtd_theme`.
- Breathe: `pip install breathe`.

To generate the khiva documentation run the following command:

- Run `make documentation`.

## Mac OS users

### Installation

#### Prerequisites

- Install [Python-64bits](https://www.python.org/downloads) or run `brew install python3`, 32-bits version won't work.
- Install [ArrayFire 3.5.1 no-gl](http://arrayfire.s3.amazonaws.com/3.5.1/ArrayFire-no-gl-v3.5.1_OSX.pkg) and add the path to the environment variable path.

Once we have installed all Khiva dependencies, we are ready to install Khiva from source code or by using the installers.

#### Build from source code

- Install conan, c++ package manager, preferably running `pip install conan`. For more information and alternative installation options, please refer to [conan manual page](http://docs.conan.io/en/latest/installation.html).
- Run `conan remote add conan-mpusz https://api.bintray.com/conan/mpusz/conan-mpusz`.
- Create `build` folder and, after moving into the new folder, run `conan install .. --build missing`.
- Run `cmake ..`.
- Run `make -j8`.

#### Install Khiva library from source code

To install the library in the default system folders, run the following command:

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

## Contributing

The rules to contribute to this project are described [here](CONTRIBUTING.md).

### Builds

We have a first approach to generate a build and execute the set of tests on every pull request to the **master** branch. This process uses **travis** and **appveyor**. The status badges of the builds are contained at the beginning of this file.
