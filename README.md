# Khiva

[![Documentation Status](https://readthedocs.org/projects/khiva/badge/?version=latest)](https://khiva.readthedocs.io/en/latest/?badge=latest)
[![Build Status](https://travis-ci.com/shapelets/khiva.svg?branch=develop)](https://travis-ci.com/shapelets/khiva)
[![Coverage Status](https://coveralls.io/repos/github/shapelets/khiva/badge.svg?branch=develop)](https://coveralls.io/github/shapelets/khiva?branch=develop)

Khiva is an open-source library of efficient algorithms to analyse time series in GPU and CPU. It can be used to extract insights from one or a group of time series. The large number of available methods allow us to understand the nature of each time series. Based on the results of this analysis, users can reduce dimensionality, find out recurrent motifs or discords, understand the seasonality or trend from a given time series, forecasting and detect anomalies.

Khiva provides a mean for time series analytics at scale. These analytics can be exploited in a wide range of [use cases](https://github.com/shapelets/khiva-use-cases)  across several industries, like energy, finance, e-health, IoT, music industry, etc.

## License

This project is licensed under [MPL-v2] (https://www.mozilla.org/en-US/MPL/2.0/).

## Installation

1. Install Conan, C++ package manager, preferably through `pip install conan`. For more information and alternative installation options, please refer to [conan manual page] (http://docs.conan.io/en/latest/installation.html)

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

## Contributing

### Formatting Style

To have a standarised code base, we only accept code that is formatted according to the Google rules for C++ with a column width of 120 characters and an indentation of 4 white spaces. For this purpose, we use `clang-format`, which can be installed in MacOS by executing the next command: `brew install clang-format`.

We use the `clang-format` plugin for the VS Code editor to format our codes. This plugin uses the `clang-format` program and the aforementioned rules under the hood.

### Branching model

Our branching model has two permanent branches, **develop** and **master**. We aim at using `develop` as the main branch, where all features are merged. In this sense, we use the master branch to push the release versions of the KHIVA library.

### Contribution process

To contribute to the code base, we follow the next process:

1. The main branch is developed; every developer should pull the current status of the branch before stating to develop any new feature.

`git pull`

2. Create a new branch with the following pattern "feature/[nameOfTheFeature]"

`git checkout -b feature/exampleFeature`

3. Develop the new feature on the new branch. It includes testing and documentation.

`git commit -a -m "Bla, Bla, Bla”; git push`

4. Open a Pull Request to merge the feature branch in to develop. Currently, a pull request must be reviewed at least by one person.

5. Finally, delete the feature branch.

6. Move back to develop branch.

`git checkout develop`

7. Pull the latest changes.

`git pull`

### Builds

We have a first approach to generate a build and execute the set of tests on every pull request to the **develop** branch. This process is based on bitbucket pipelines and is **currently stopped**.
The rules to contribute to this project are described [here](CONTRIBUTING.md)

### Builds
We have a first approach to generate a build and execute the set of tests on every pull request to the **develop** branch. This process uses **travis** and **appveyor** and is currently under setup.
