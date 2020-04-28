// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/library.h>
#include <khiva/version.h>
#include <khiva_c/internal/util.h>
#include <khiva_c/library.h>

#include <cstring>

using namespace khiva;
using namespace khiva::util;

void backend_info(char **info, int *error_code, char *error_message) {
    try {
        std::strcpy(*info, khiva::library::backendInfo().c_str());
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void set_backend(const int *backend, int *error_code, char *error_message) {
    try {
        khiva::library::setBackend(static_cast<khiva::library::Backend>(*backend));
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void get_backend(int *backend, int *error_code, char *error_message) {
    try {
        *backend = static_cast<int>(khiva::library::getBackend());
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void get_backends(int *backends, int *error_code, char *error_message) {
    try {
        *backends = khiva::library::getBackends();
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void set_device(const int *device, int *error_code, char *error_message) {
    try {
        khiva::library::setDevice(*device);
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void get_device_id(int *device_id, int *error_code, char *error_message) {
    try {
        *device_id = khiva::library::getDevice();
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void get_device_count(int *device_count, int *error_code, char *error_message) {
    try {
        *device_count = khiva::library::getDeviceCount();
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void set_device_memory_in_gb(const double *memory, int *error_code, char *error_message) {
    try {
        khiva::library::setDeviceMemoryInGB(*memory);
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}

void version(char **v, int *error_code, char *error_message) {
    try {
        strcpy(*v, khiva::version().c_str());
    } catch (af::exception &e) {
        fill_error(__func__, e.what(), error_message);
        *error_code = e.err();
    } catch (...) {
        fill_error(__func__, "Unknown error.", error_message);
        *error_code = AF_ERR_UNKNOWN;
    }
}
