# TSA Tests

In order to execute the benchmarks in all the available backends and for all the devices we have defined the `TSA_TEST` macro, which defines a Google test for each available backend and device using the `TEST` macro.

The `TSA_TEST` needs 3 parameters in the following order:
1. A test **suite name** in which to include the test.
2. A **test name**.
3. The **name of the function** to be tested.

Example test file:
```C++
// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <gtest/gtest.h>
#include <tsa.h>
#include "tsatest.h"

// Simple test, does not use gmock
void test() {
    // ASSERTIONS
}

TSA_TEST(SuiteName, TestName, test);
```