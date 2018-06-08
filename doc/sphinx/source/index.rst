=============================
Khiva (Time Series Analytics)
=============================

This is the documentation of **Khiva** library.

Khiva [#f1]_ is an open source C++ library which focus on providing efficient algorithms to perform analytics over 
time series of data. It can be used to extract insights from one or a group of time series. The large number of 
available methods allow us to understand the nature of each time series. Based on that analytics, the user can 
reduce dimensionality, find out recurrent motifs or discords, understand the seasonality or trend from a given time
series, forecasting and detect anomalies. 

It is a novel project that wants to provide a mean for time series analytics at scale. Our vision is that this kind
of analytics can be exploit in a wide range of use cases across several industries, like finance, energy, e-health,
IOT, application performance monitoring (APM), music industry, etc.  

It is just the beginning, so keep tuned, more features are coming ...  

`shapelets-khiva@googlegroups.com
<https://groups.google.com/forum/?fromgroups#!forum/shapelets-khiva>`_ is the place for discussions and questions about 
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
