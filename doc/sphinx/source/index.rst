===========================
TSA (Time Series Analytics)
===========================

This is the documentation of **TSA** library.

TSA [#f1]_ is an open source C++ library which focus on providing efficient algorithms to perform analytics over 
time series of data. It can be used to extract insights from one or a group of time series. The large number of 
available methods allows us to understand the nature of each time series. Based on that analytics, the user can 
reduce dimensionality, find out recurrent motifs or discords, understand the seasonality or trend from given time
series, forecasting and detect anomalies. 

It is a novel project that wants to provides a mean for analysis time series at scale. Our vision is that this kind
of analytics can be exploit in a wide range of use cases across several industries, like finance, energy, e-health,
IOT, application performance monitoring (APM), music industry, etc.  

It is just the begging, so keep tuned, more features are coming ...  

`shapelets-tsa@googlegroups.com
<https://groups.google.com/forum/?fromgroups#!forum/shapelets-tsa>`_ is the place for discussions and questions about 
TSA library. We use the `GitHub Issue Tracker <https://github.com/shapelets/tsa/issues>`_ to manage bug reports 
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
   License <license>
   Changelog <changes>

Cite Us
=======

If you use TSA Library for a publication, please cite it as::

    @misc{tsa-library, 
    author = "David Cuesta and Justo Ruiz and Oscar Torreno and Antonio Vilches", 
    title = "TSA Library", 
    howpublished = "\url{http://shapelets.io/tsa}"
    }

.. rubric:: Footnotes

.. [#f1] Time series analysis comprises methods for analyzing time series data in order to extract meaningful statistics and other characteristics of the data (Source `Wikipedia <https://en.wikipedia.org/wiki/Time_series>`_).
