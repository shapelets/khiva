# Contributing

Contributions are welcome and are greatly appreciated! Every
little bit helps, and credit will always be given.


# Table of Contents
  * [Formatting Style](#formatting-style)
  * [Branching model](#branching-model)
  * [Contribution process](#contribution-process)
  * [Types of Contributions](#types-of-contributions)
      - [Report Bugs](#report-bugs)
      - [Fix Bugs](#fix-bugs)
      - [Implement Features](#implement-features)
      - [Improve Documentation](#improve-documentation)
      - [Submit Feedback](#submit-feedback)
  * [Documentation](#documentation)
  * [Development and Testing](#development-and-testing)
      - [Set up a development env using Docker](#set-up-a-development-env-using-docker)

## Formatting Style

In order to have a standarised code base, we only accept code that is formatted according to the Google rules for C++ with a column width of 120 characters and an identation of 4 whitespaces. For this purpose, we use `clang-format`, which can be installed in MacOs by executing the next command: `brew install clang-format`.
We use the `clang-format` plugin for the VS Code editor to format our codes. This plugin uses the `clang-format` program and the aforementioned rules under the hood.

## Branching model

Our branching model has two permanent branches, **develop** and **master**. We aim at using `develop` as the main branch, where all features are merged. In this sense, we use the master branch to push the release versions of the Khiva library.

## Contribution process

In order to contribute to the code base, we follow the next process :
1. The main branch is `develop`, every developer should pull the current status of the branch before starting to develop any new feature.
`git pull`
1. Create a new branch with the following pattern "feature/[name_of_the_feature]"
`git checkout -b feature/example_feature`
3. Develop the new feature on the the new branch. It includes testing and documentation.
`git commit -a -m "Bla, Bla, Bla";  git push`
4. Open a Pull Request to merge the feature branch in to develop. Currently, a pull request has to be reviewed at least by one person.
5. Finally, delete the feature branch.
6. Move back to develop branch.
`git checkout develop`
7. Pull the latest changes.
`git pull`

## Types of Contributions

### Report Bugs

Report bugs through [GitHub issues](https://github.com/shapelets/khiva/issues)

Please follow the project issue template to exhibit the problem.

### Fix Bugs

Look through the GitHub issues for bugs. Anything is open to whoever wants to implement it.

### Implement Features

Look through the [GitHub issues](https://github.com/shapelets/khiva/issues) for feature requests. Any unassigned "Improvement" issue is open to whoever wants to implement it.

We have included an initial set of algorithms, but feel free to add any new one(s).

### Improve Documentation

Khiva could always use better documentation, whether as part of the official Khiva docs,
`doc/sphinx/source/*.rst` or even description of the methods in the different namespaces.

### Submit Feedback

The best way to send feedback is to open an issue on [GitHub issues](https://github.com/shapelets/khiva/issues)

If you are proposing a feature, please follow the feature request template.

## Development and Testing

### Set up a development env using Docker

Start a new docker container.

```
# Start docker
docker run -ti shapelets/khiva 
```