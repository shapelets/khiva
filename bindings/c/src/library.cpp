// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/library.h>
#include <khiva/version.h>
#include <khiva_c/library.h>
#include <khiva_c/internal/util.h>
#include <cstring>

void backend_info(char **info, int *error_code, char *error_message) {
    try{
        std::strcpy(*info, khiva::library::backendInfo().c_str());
    } catch (const std::exception &e) {
        fill_error("backend_info", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("backend_info", error_message, error_code, -1);
    }
}

void set_backend(int *backend, int *error_code, char *error_message) {
    try{
        khiva::library::setBackend(static_cast<khiva::library::Backend>(*backend));
    } catch (const std::exception &e) {
        fill_error("set_backend", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("set_backend", error_message, error_code, -1);
    }
}

void get_backend(int *backend, int *error_code, char *error_message) {
    try{
        *backend = static_cast<int>(khiva::library::getBackend());
    } catch (const std::exception &e) {
        fill_error("get_backend", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("get_backend", error_message, error_code, -1);
    }
}

void get_backends(int *backends, int *error_code, char *error_message) {
    try{
        *backends = khiva::library::getBackends();
    } catch (const std::exception &e) {
        fill_error("get_backends", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("get_backends", error_message, error_code, -1);
    }
}

void set_device(int *device, int *error_code, char *error_message) {
    try{
        khiva::library::setDevice(*device);
    } catch (const std::exception &e) {
        fill_error("set_device", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("set_device", error_message, error_code, -1);
    }
}

void get_device_id(int *device_id, int *error_code, char *error_message) {
    try{
        *device_id = khiva::library::getDevice();
    } catch (const std::exception &e) {
        fill_error("get_device_id", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("get_device_id", error_message, error_code, -1);
    }
}

void get_device_count(int *device_count, int *error_code, char *error_message) {
    try{
        *device_count = khiva::library::getDeviceCount();
    } catch (const std::exception &e) {
        fill_error("get_device_count", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("get_device_count", error_message, error_code, -1);
    }
}

void set_device_memory_in_gb(double *memory, int *error_code, char *error_message) {
    try{
        khiva::library::setDeviceMemoryInGB(*memory);
    } catch (const std::exception &e) {
        fill_error("set_device_memory_in_gb", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("set_device_memory_in_gb", error_message, error_code, -1);
    }
}

void version(char **v, int *error_code, char *error_message) {
    try{
        strcpy(*v, khiva::version().c_str());
    } catch (const std::exception &e) {
        fill_error("version", e.what(), error_message, error_code, 1);
    } catch (...) {
        fill_unknown("version", error_message, error_code, -1);
    }
}
