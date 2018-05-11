===
FAQ
===

    1. **Does tsa support different time series lengths?**

       Yes, it supports different time series lengths. However, they need to be executed independently.

    2. **How can I use tsa?**

       We recommend to use any Unix system. After installing, (see :ref:`chapter-gettingstarted`)

       .. code:: Bash

           conda create -n ENV_NAME python=VERSION
           conda install -n ENV_NAME pip requests numpy pandas
           pip install tsa-python
