// Copyright (c) 2018 Grumpy Cat Software S.L.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <gtest/gtest.h>
#include <tsa.h>
#include "tsaTest.h"

// Simple test, does not use gmock
void versionTest() { ASSERT_STREQ(tsa::version(), "0.0.1"); }

TSA_TEST(VersionTest, VersionTest, versionTest);