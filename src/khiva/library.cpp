// Copyright (c) 2018 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/library.h>
#include <iostream>

void khiva::library::backendInfo() { std::cout << std::string(af::infoString()) << std::endl; }

void khiva::library::setBackend(khiva::library::Backend be) { af::setBackend(static_cast<af::Backend>(be)); }

khiva::library::Backend khiva::library::getBackend() {
    return static_cast<khiva::library::Backend>(af::getActiveBackend());
}

int khiva::library::getBackends() { return af::getAvailableBackends(); }

void khiva::library::setDevice(int device) { af::setDevice(device); }

int khiva::library::getDevice() { return af::getDevice(); }

int khiva::library::getDeviceCount() { return af::getDeviceCount(); }
