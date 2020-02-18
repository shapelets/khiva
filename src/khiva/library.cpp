// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <arrayfire.h>
#include <khiva/library.h>

#include "khiva/internal/libraryInternal.h"

std::string khiva::library::backendInfo() { return af::infoString(); }

void khiva::library::setBackend(khiva::library::Backend be) { af::setBackend(static_cast<af::Backend>(be)); }

khiva::library::Backend khiva::library::getBackend() {
    return static_cast<khiva::library::Backend>(af::getActiveBackend());
}

int khiva::library::getBackends() { return af::getAvailableBackends(); }

void khiva::library::setDevice(int device) { af::setDevice(device); }

int khiva::library::getDevice() { return af::getDevice(); }

int khiva::library::getDeviceCount() { return af::getDeviceCount(); }

void khiva::library::setDeviceMemoryInGB(double memory) { khiva::library::internal::setDeviceMemoryInGB(memory); }
