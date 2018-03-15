# TSA

## License
This project is licensed under [MPL-v2](https://www.mozilla.org/en-US/MPL/2.0/).

## Installation
1. Install conan, c++ package manager, preferably through `pip install conan`.  For more informacion and alternative instalation options, please refer to [conan manual page](http://docs.conan.io/en/latest/installation.html)
2. Run `conan remote add conan-mpusz https://api.bintray.com/conan/mpusz/conan-mpusz`
3. Run `conan install . --build`, which will bring down dependencies and generate the necessary include files for the `cmake` build.
4. Create `build` folder and, after moving into the new folder, run `cmake ..` 
5. Run the actual make for your environment.

## Contributing

### Formatting Style

In order to have a standarised code base, we only accept code that is formatted according to the Google rules for C++ with a column width of 120 characters and an identation of 4 whitespaces. For this purpose, we use `clang-format`, which can be installed in MacOs by executing the next command: `brew install clang-format`.
We use the `clang-format` plugin for the VS Code editor to format our codes. This plugin uses the `clang-format` program and the previously mentioned rules under the hood.

### Branching model

Our branching model has two permanent branches, **develop** and **master**. We aim at using `develop` as the main branch, where all features are merged. In this sense, we use the master branch to push the release versions of the TSA library.

### Contribution process

In order t contribute to the code base, we follow the next process :
1. The main branch is develop, every developer should pull the current status of the branch before stating to develop any new feature.
`git pull`
2. Create a new branch with the following pattern "feature/[nameOfTheFeature]"
`git checkout -b feature/exampleFeature`
3. Develop the new feature on the the new branch. It includes testing and documentation.
`git commit -a -m "Bla, Bla, Bla";  git push`
4. Open a Pull Request to merge the feature branch in to develop. Currently, a pull request has to be reviewed at least by one person.
5. Finally, delete the feature branch.
6. Move back to develop branch.
`git checkout develop`
7. Pull the latest changes.
`git pull`

### Builds
We have a first approach to generate a build and execute the set of tests on every pull request to the **develop** branch. This process is based on bitbucket pipelines and is **currently stopped**.