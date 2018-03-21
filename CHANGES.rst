=========
Changelog
=========

tsfresh uses `Semantic Versioning <http://semver.org/>`_


Version 0.11.0
==============

- new feature calculators:
    - fft_aggregated
    - cid_ce
- renamed mean_second_derivate_central to mean_second_derivative_central
- add warning if no relevant features were found in feature selection
- add columns_to_ignore parameter to from_columns method
- add distribution module, contains support for distributed feature extraction on Dask

Version 0.10.1
==============
- split test suite into unit and integration tests
- fixed the following bugs
    - use name of value column as time series kind
    - prevent the spawning of subprocesses which lead to high memory consumption
    - fix deployment from travis to pypi

Version 0.10.0
==============
- new feature calculators:
    - partial autocorrelation
- added list of calculated features to documentation
- added two ipython notebooks to
    - illustrate PCA on features
    - illustrate the Benjamini Yekutieli procedure
- fixed the following bugs
    - improperly quotation of dickey fuller settings