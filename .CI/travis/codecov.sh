#!/bin/bash
# Copyright (c) 2018 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

lcov --directory src --capture --no-external --output-file coverage.info
lcov --remove coverage.info '*/.conan/*' '*/usr*' '*/cl.hpp' '*/include/*' '*/bindings/*' '*/test/*' -o coverage.info
lcov --list coverage.info

# Uploading report to CodeCov
bash <(curl -s https://codecov.io/bash) -f coverage.info -X gcov || echo "Codecov did not collect coverage reports"
