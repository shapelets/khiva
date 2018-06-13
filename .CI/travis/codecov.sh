#!/bin/bash

cd build
lcov --zerocounters --directory .
make test
lcov --directory .. --base-directory ../src --no-external --capture --output-file coverage.info
lcov --remove coverage.info 'test/*' 'include/*' -o coverage.info
lcov --list coverage.info

# Uploading report to CodeCov
bash <(curl -s https://codecov.io/bash) -X gcov
