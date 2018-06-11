=============================
Khiva
=============================

This is the documentation of **Khiva** library.

Khiva [#f1]_ is an open-source library of efficient algorithms to analyse time series in GPU and CPU. It can be used to extract insights from one or a group of time series. The large number of available methods allow us to understand the nature of each time series. Based on the results of this analysis, users can reduce dimensionality, find out recurrent motifs or discords, understand the seasonality or trend from a given time series, forecasting and detect anomalies.

Khiva provides a mean for time series analytics at scale. These analytics can be exploited in a wide range of use cases across several industries, like energy, finance, e-health, IoT, music industry, etc. 

This is just the beginning, so stay tuned as more features are coming ...  

`Gitter <https://gitter.im/shapelets-io/khiva>`_ is the place for discussions and questions about 
Khiva library. We use the `GitHub Issue Tracker <https://github.com/shapelets/khiva/issues>`_ to manage bug reports 
and feature requests.

You can jump right into the package by looking into our :ref:`chapter-gettingstarted`.

.. toctree::
   :caption: Table of Contents
   :maxdepth: 1
   :hidden:

   Getting Started <gettingStarted>
   API <api/main>
   Bindings to other languages <bindings/main>
   Using Khiva in your CMake project <cmake>
   Authors <authors>

Cite Us
=======

If you use Khiva Library for a publication, please cite it as:

.. code-block:: bash

     @misc{khiva-library, 
        author = "David Cuesta and Justo Ruiz and Oscar Torreno and Antonio Vilches", 
        title = "Khiva Library", 
        howpublished = "\url{https://shapelets.io/khiva}"
     }

.. rubric:: Footnotes

.. [#f1] Time series analysis comprises methods for analyzing time series data in order to extract meaningful statistics and other characteristics of the data (Source `Wikipedia <https://en.wikipedia.org/wiki/Time_series>`_).
