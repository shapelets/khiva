========
Bindings
========

We have developed bindings to enable the execution of TSA from the following languages. In order to make it work, you should first install 
TSA library in your machine, explained in :ref: `chapter-gettingstarted`.

Python
======

In order to install the tsa-python binding of the library, you would need to fetch the latest version of the code from:

.. code-block:: bash

    git clone https://avrgcs@bitbucket.org/gcatsoft/tsa-python.git

After cloning the repository, you can install tsa-python by executing the next commands: 


.. code-block:: bash

    cd /path_to_tsa-python
    python3 setup.py install

If the installation is successful, you are ready to start playing with the library.

Java
====

In order to install the tsa-java binding of the library, you would need to fetch the latest version of the code from:

.. code-block:: bash

    git clone https://avrgcs@bitbucket.org/gcatsoft/tsa-java.git

Once you have downloaded the code, you have to move to the source code directory and execute the following commands:

.. code-block:: bash

    cd path_to_java_tsa_dir
    mvn install
    mvn javadoc:javadoc

If all steps finished as expected, you should be able to use the TSA from your java projects.

R
===

In order to install the tsa-r binding of the library, you would need to fetch the latest version of the code from:

.. code-block:: bash

    git clone https://avrgcs@bitbucket.org/gcatsoft/tsa-r.git

After downloading the code, you would need to open an R console and execute the following commands, to set the work directory and 
install the TSA binding:

.. code-block:: bash

    setwd(<project-root-dir>/tsa/)
    devtools::install()

Once the installation of the binding has been carried out, you can make the library available by executing:

.. code-block:: bash
    
    library(tsa) 

If all previous steps were successful you will ready to start working with the library.

Matlab
======

In order to install the tsa-matlab binding of the library, you would need to fetch the latest version of the code from:

.. code-block:: bash

    git clone https://avrgcs@bitbucket.org/gcatsoft/tsa-matlab.git

Once the code is available, we just have to add the path to the tsa-matlab/+tsa folder to the Matlab path. Thus, the user will be able to 
import and call our library.
