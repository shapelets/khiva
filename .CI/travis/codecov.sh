#!/bin/bash

lcov --zerocounters --directory .
../bin/ctest --output-on-failure
lcov --directory . --base-directory ../src --no-external --capture --output-file coverage.info
#lcov --remove coverage.info '/usr*' '/opt*' '*/cl.hpp' '*/.conan/*' -o coverage.info
lcov --list coverage.info
# Uploading report to CodeCov
bash <(curl -s https://codecov.io/bash) || echo "Codecov did not collect coverage reports"