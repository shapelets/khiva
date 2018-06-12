#!/bin/bash

cd build
lcov --directory test --base-directory ../khiva --capture --output-file coverage.info
lcov --remove coverage.info '/usr*' '/opt*' '*/cl.hpp' -o coverage.info
bash <(curl -s https://codecov.io/bash)
cd ..