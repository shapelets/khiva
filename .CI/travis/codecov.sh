#!/bin/bash

cd build
lcov --directory . --base-directory ../src/khiva --no-external --capture --output-file coverage.info
lcov --remove coverage.info '*/.conan/*' '*/usr*' '*/cl.hpp' '*/include/*' '*/bindings/*' '*/test/*' -o coverage.info
lcov --list coverage.info

# Uploading report to CodeCov
bash <(curl -s https://codecov.io/bash) || echo "Codecov did not collect coverage reports"
