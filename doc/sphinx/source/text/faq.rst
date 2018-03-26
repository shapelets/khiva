FAQ
===

    1. **Does tsa support different time series lengths?**

       Yes, it supports different time series lengths. However, they need to be executed separately.

    2. **Is it possible to extract features from rolling/shifted time series?**

       Yes, you just have to transform your data into one of the supported TSA :ref:`data-formats-label`.
       Then, you get a DataFrame with the rolled time series, that you can pass to TSA.

    3. **How can I use tsa?**

       We recommend to use any Unix system. After installing, (see :ref:`getting_started`)

       .. code:: Bash

           conda create -n ENV_NAME python=VERSION
           conda install -n ENV_NAME pip requests numpy pandas
           pip install tsa-python


    4. **Does tsa support different sampling rates in the time series?**

        Yes! The feature calculators in TSA do not care about the sampling frequency.