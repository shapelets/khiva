# KHIVA

## License

This project is licensed under [MPL-v2] (https://www.mozilla.org/en-US/MPL/2.0/).

## Installation

1. Install Conan, C++ package manager, preferably through `pip install conan`. For more information and alternative installation options, please refer to [conan manual page] (http://docs.conan.io/en/latest/installation.html)

2. Run `conan remote add conan-mpusz https://api.bintray.com/conan/mpusz/conan-mpusz`

3. Run `conan install . --build missing -s compiler.libcxx=libstdc++11`, which will bring down dependencies and generate the necessary include files for the `cmake` build.

4. Create `build` folder and, after moving into the new folder, run `cmake ..`

5. Run the actual make for your environment.

### Generating the KHIVA installers

This project can be packaged to be installed in a Windows, Linux or Mac OS system. CPack is used to perform this task.

1. For **Windows** the installer can be generated running the command `cpack -G NSIS` inside the `build` folder. You need [NSIS] (http://nsis.sourceforge.net/Download) installed in your system.

2. For **linux** either a **deb** or a **rpm** package the installer can be generated. This could be done running the command `cpack -G DEB` or `cpack -G RPM` respectively inside the `build` folder.

3. For **Mac OS** the installer can be generated running the command `cpack -G productbuild` inside the `build` folder.

**Notes:** Before generating the installer the project should be built. The generated package will be stored in the `build` folder.

## Generating documentation

We use `sphinx + doxygen` to generate our documentation. You will need to install the following packages:

* Sphinx: `brew install sphinx`

* Doxygen: `brew install doxygen`

* Read the Docs Theme: `pip install sphinx_rtd_theme`

* Breathe: `pip install breathe`

* Exhale: `pip install exhale`

## Contributing

### Formatting Style

To have a standardised code base, we only accept code that is formatted according to the Google rules for C++ with a column width of 120 characters and an indentation of 4 whitespaces. For this purpose, we use `clang-format`, which can be installed in MacOS by executing the next command: `brew install clang-format`.

We use the `clang-format` plugin for the VS Code editor to format our codes. This plugin uses the `clang-format` program and the aforementioned rules under the hood.

### Branching model

Our branching model has two permanent branches, **develop** and **master**. We aim at using `develop` as the main branch, where all features are merged. In this sense, we use the master branch to push the release versions of the KHIVA library.

### Contribution process

To contribute to the code base, we follow the next process:

1. The main branch is developed; every developer should pull the current status of the branch before stating to develop any new feature.

`git pull`

2. Create a new branch with the following pattern "feature/[nameOfTheFeature]"

`git checkout -b feature/exampleFeature`

3. Develop the new feature on the new branch. It includes testing and documentation.

`git commit -a -m "Bla, Bla, Bla”; git push`

4. Open a Pull Request to merge the feature branch in to develop. Currently, a pull request must be reviewed at least by one person.

5. Finally, delete the feature branch.

6. Move back to develop branch.

`git checkout develop`

7. Pull the latest changes.

`git pull`

### Builds

We have a first approach to generate a build and execute the set of tests on every pull request to the **develop** branch. This process is based on bitbucket pipelines and is **currently stopped**.