// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <khiva/internal/util.h>

std::string khiva::util::khiva_file_path(const std::string &path) {
    auto pos = path.rfind("khiva");
    return (pos == std::string::npos) ? path : path.substr(pos);
}
