#!/bin/bash

cd build
lcov --zerocounters  --directory .
make test
lcov --directory test --base-directory .. --capture --output-file coverage.info
lcov --remove coverage.info '/usr*' '/opt*' '*/cl.hpp' -o coverage.info
bash <(curl -s https://codecov.io/bash)
cd ..