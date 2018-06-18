# Khiva

| Branch        | Build Documentation                                                                                                                           | Build Linux and Mac Os                                                                                            |  Build Windows                                                                                                                                          | Code Coverage                                                                                                                    |
| ------------- |:---------------------------------------------------------------------------------------------------------------------------------------------:|:-----------------------------------------------------------------------------------------------------------------:|:-------------------------------------------------------------------------------------------------------------------------------------------------------:|:--------------------------------------------------------------------------------------------------------------------------------:|
| master        | [![Documentation Status](https://readthedocs.org/projects/khiva/badge/?version=latest)](https://khiva.readthedocs.io/en/latest/?badge=latest) | [![Build Status](https://travis-ci.com/shapelets/khiva.svg?branch=master)](https://travis-ci.com/shapelets/khiva) | [![Build status](https://ci.appveyor.com/api/projects/status/2oiggqcufnl3iddd/branch/master?svg=true)](https://ci.appveyor.com/project/shapelets/khiva) | [![Coverage Status](https://codecov.io/gh/shapelets/khiva/branch/master/graph/badge.svg)](https://codecov.io/gh/shapelets/khiva) |
| develop       | [![Documentation Status](https://readthedocs.org/projects/khiva/badge/?version=latest)](https://khiva.readthedocs.io/en/latest/?badge=latest) | [![Build Status](https://travis-ci.com/shapelets/khiva.svg?branch=develop)](https://travis-ci.com/shapelets/khiva)| [![Build status](https://ci.appveyor.com/api/projects/status/2oiggqcufnl3iddd/branch/develop?svg=true)](https://ci.appveyor.com/project/shapelets/khiva)| [![Coverage Status](https://codecov.io/gh/shapelets/khiva/branch/develop/graph/badge.svg)](https://codecov.io/gh/shapelets/khiva)|

Khiva is an open-source library of efficient algorithms to analyse time series in GPU and CPU. It can be used to extract insights from one or a group of time series. The large number of available methods allow us to understand the nature of each time series. Based on the results of this analysis, users can reduce dimensionality, find out recurrent motifs or discords, understand the seasonality or trend from a given time series, forecasting and detect anomalies.

Khiva provides a mean for time series analytics at scale. These analytics can be exploited in a wide range of [use cases](https://github.com/shapelets/khiva-use-cases)  across several industries, like energy, finance, e-health, IoT, music industry, etc.

## License
This project is licensed under [MPL-v2](https://www.mozilla.org/en-US/MPL/2.0/).

## Installation
1. Install conan, c++ package manager, preferably through `pip install conan`.  For more information and alternative installation options, please refer to [conan manual page](http://docs.conan.io/en/latest/installation.html)
2. Run `conan remote add conan-mpusz https://api.bintray.com/conan/mpusz/conan-mpusz`
3. Create `build` folder and, after moving into the new folder, run `cmake ..` 
4. Run `make -j8 && make install`.

### Generating the Khiva installers
This project can be packaged to be installed in a Windows, Linux or Mac OS system. CPack is used in order to perform this task.
1. For **Windows** the installer can be generated running the command `cpack -G NSIS` inside the `build` folder. You need [NSIS](http://nsis.sourceforge.net/Download) installed in your system.
2. For **linux** either a **deb** or a **rpm** package the installer can be generated. This could be done running the command `cpack -G DEB` or `cpack -G RPM` respectively inside the `build` folder.
3. For **Mac OS** the installer can be generated running the command `cpack -G productbuild` inside the `build` folder.

**Notes:** Before generating the installer the project should be built. The generated package will be stored in the `build` folder.

## Generating documentation

We use `sphinx + doxygen` to generate our documentation. You will need to install the following packages:
* Sphinx: `brew install sphinx`
* Doxygen: `brew install doxygen`
* Read the Docs Theme: `pip install sphinx_rtd_theme`
* Breathe: `pip install breathe`
* Exhale: `pip install exhale`

## Contributing

The rules to contribute to this project are described [here](CONTRIBUTING.md)

### Builds
We have a first approach to generate a build and execute the set of tests on every pull request to the **develop** branch. This process uses **travis** and **appveyor** and is currently under setup.
