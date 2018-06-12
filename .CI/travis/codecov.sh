#!/bin/bash

cd build
lcov --zerocounters --directory .
lcov --capture --initial --directory . --base-directory ../src --no-external --output-file coverage.info
make test
lcov --directory . --base-directory ../src --no-external --capture --output-file coverage.info
lcov --remove coverage.info '/usr*' '/opt*' '*/cl.hpp' -o coverage.info
bash <(curl -s https://codecov.io/bash)
cd ..