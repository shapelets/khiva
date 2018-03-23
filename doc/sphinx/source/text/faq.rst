FAQ
===


    1. **Does tsa support different time series lengths?**

       Yes, it supports different time series lengths. However, some feature calculators can demand a minimal length
       of the time series. If a shorter time series is passed to the calculator, a NaN is returned for those
       features.

    2. **Is it possible to extract features from rolling/shifted time series?**

       Yes, You just have to transform your data into one of the supported tsa :ref:`data-formats-label`.
       Then, you get a DataFrame with the rolled time series, that you can pass to tsa.

    3. **How can I use tsa?**

       We recommend to use any Unix system. After installing, (see :ref:`getting_started`)

       .. code:: Bash

           conda create -n ENV_NAME python=VERSION
           conda install -n ENV_NAME pip requests numpy pandas scipy statsmodels patsy scikit-learn future six tqdm
           pip install tsa-python


    4. **Does tsa support different sampling rates in the time series?**

        Yes! The feature calculators in tsa do not care about the sampling frequency.
        You will have to use the second input format, the stacked DataFramed (see :ref:`data-formats-label`)