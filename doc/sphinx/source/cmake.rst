Building programs using Khiva with CMake
========================================

In order to build a program using the Khiva library with the `CMake`_ build system you need just
a couple of lines in your ``CmakeLists.txt``:

.. code-block:: cmake

    cmake_minimum_required(VERSION 3.1)
    project(example)

    find_package(Khiva REQUIRED)

    add_executable(example example.cpp)
    target_link_libraries(example Khiva::khiva)

``find_package(Khiva REQUIRED)`` may be used when Khiva was installed system wide. Please follow the installation instructions for your operating system contained at the :ref:`chapter-gettingstarted`.

.. _`CMake`: https://cmake.org/