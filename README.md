# Khiva

<img src="https://github.com/shapelets/khiva/blob/master/assets/Khiva.png" width="100">

[![License: MPL 2.0](https://img.shields.io/badge/License-MPL%202.0-brightgreen.svg)](https://github.com/shapelets/khiva-java/blob/master/LICENSE.txt)  [![Gitter chat](https://badges.gitter.im/shapelets-io/Lobby.svg)](https://gitter.im/shapelets-io/khiva?utm_source=share-link&utm_medium=link&utm_campaign=share-link)

|                                                              Build Documentation                                                              |                                                   Build Linux and Mac OS                                                   |                                                                             Build Windows                                                                             |                                                                 Code Coverage                                                                  |
| :-------------------------------------------------------------------------------------------------------------------------------------------: | :------------------------------------------------------------------------------------------------------------------------: | :-------------------------------------------------------------------------------------------------------------------------------------------------------------------: | :--------------------------------------------------------------------------------------------------------------------------------------------: |
| [![Documentation Status](https://readthedocs.org/projects/khiva/badge/?version=latest)](https://khiva.readthedocs.io/en/master/?badge=latest) | [![Build Status](https://travis-ci.org/shapelets/khiva.svg?branch=master)](https://travis-ci.org/shapelets/khiva/branches) | [![Build status](https://ci.appveyor.com/api/projects/status/2oiggqcufnl3iddd/branch/master?svg=true)](https://ci.appveyor.com/project/shapelets/khiva/branch/master) | [![Coverage Status](https://codecov.io/gh/shapelets/khiva/branch/master/graph/badge.svg)](https://codecov.io/gh/shapelets/khiva/branch/master) |

Khiva is an open-source library of efficient algorithms to analyse time series in GPU and CPU. It can be used to extract insights from one or a group of time series. The large number of available methods allow us to understand the nature of each time series. Based on the results of this analysis, users can reduce dimensionality, find out recurrent motifs or discords, understand the seasonality or trend from a given time series, forecasting and detect anomalies.

Khiva provides a mean for time series analytics at scale. These analytics can be exploited in a wide range of [use cases](https://github.com/shapelets/khiva-use-cases) across several industries, like energy, finance, e-health, IoT, music industry, etc.

Khiva is inspired by other time series libraries as [tsfresh](https://github.com/blue-yonder/tsfresh), [tslearn](https://github.com/rtavenar/tslearn) and [hctsa](https://github.com/benfulcher/hctsa) among others.

## Khiva Bindings to other languages
 - [Python](https://github.com/shapelets/khiva-python)
 - [R](https://github.com/shapelets/khiva-r)
 - [Matlab](https://github.com/shapelets/khiva-matlab)
 - [Ruby](https://github.com/ankane/khiva-ruby)
 - [Kotlin](https://github.com/shapelets/khiva-kotlin)
 - [Java](https://github.com/shapelets/khiva-java)
 - [C#](https://github.com/shapelets/khiva-csharp)

 

## Other Matrix Profile implementations
- Python implementation developed at Target: [https://github.com/target/matrixprofile-ts](https://github.com/target/matrixprofile-ts)

## License

This project is licensed under [MPL-v2](https://www.mozilla.org/en-US/MPL/2.0/).

## Installation

Currently, khiva is supported on Windows, Linux and MacOs, if you need to install the library follow the [installation guide](doc/markdown/INSTALLATION.md).

## Contributing

The rules to contribute to this project are described [here](doc/markdown/CONTRIBUTING.md).

### Builds

We have a first approach to generate a build and execute the set of tests on every pull request to the **master** branch. This process uses **travis** and **appveyor**. The status badges of the builds are contained at the beginning of this file.

## Referencing `Khiva`

If you use `Khiva` in a scientific publication, we would appreciate citations:

```bibtex
@misc{khiva,
 title={Khiva: Accelerated time-series analytics on GPUs and CPU multicores},
 author={Ruiz-Ferrer, Justo and Vilches, Antonio and Torreno, Oscar and Cuesta, David},
 year={2018},
 note={\url{https://github.com/shapelets/khiva}}
}
```
