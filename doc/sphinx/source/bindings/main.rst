========
Bindings
========

We have developed bindings to enable the execution of Khiva from the following languages. In order to make it work, you should first install 
Khiva library in your machine, explained in :ref: `chapter-gettingstarted`.

Python
======

In order to install the khiva-python binding of the library, you would need to fetch the latest version of the code from:

.. code-block:: bash

    git clone https://github.com/shapelets/khiva-python.git

After cloning the repository, you can install khiva-python by executing the next commands: 


.. code-block:: bash

    cd /path_to_khiva-python
    python3 setup.py install

If the installation is successful, you are ready to start playing with the library.

Java
====

In order to install the khiva-java binding of the library, you would need to fetch the latest version of the code from:

.. code-block:: bash

    git clone https://github.com/shapelets/khiva-java.git

Once you have downloaded the code, you have to move to the source code directory and execute the following commands:

.. code-block:: bash

    cd path_to_java_khiva_dir
    mvn install
    mvn javadoc:javadoc

If all steps finished as expected, you should be able to use the Khiva from your java projects.

R
===

In order to install the khiva-r binding of the library, you would need to fetch the latest version of the code from:

.. code-block:: bash

    git clone https://github.com/shapelets/khiva-r.git

After downloading the code, you would need to open an R console and execute the following commands, to set the work directory and 
install the Khiva binding:

.. code-block:: bash

    setwd(<project-root-dir>/)
    devtools::install()

Once the installation of the binding has been carried out, you can make the library available by executing:

.. code-block:: bash
    
    library(khiva) 

If all previous steps were successful you will ready to start working with the library.

MATLAB
======

In order to install the khiva-matlab binding of the library, you would need to fetch the latest version of the code from:

.. code-block:: bash

    git clone https://github.com/shapelets/khiva-matlab.git

Once the code is available, we just have to add the path to the khiva-matlab/+khiva folder to the MATLAB path. Thus, the user will be able to 
import and call our library.
