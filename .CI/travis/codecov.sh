#!/bin/bash

lcov --zerocounters --directory .
make test
lcov --directory . --base-directory ../src --no-external --capture --output-file coverage.info
#lcov --remove coverage.info '/usr*' '/opt*' '*/cl.hpp' '*/.conan/*' -o coverage.info
lcov --list coverage.info

# Uploading report to CodeCov
#bash <(curl -s https://codecov.io/bash) || echo "Codecov did not collect coverage reports"
curl -s https://codecov.io/bash > .codecov
chmod +x .codecov
./.codecov