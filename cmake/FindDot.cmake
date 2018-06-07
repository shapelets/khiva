# Copyright (c) 2018 Shapelets.io
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

find_program(DOT_EXECUTABLE NAMES dot
    DOC "Graphviz dot"
)
 
include(FindPackageHandleStandardArgs)
 
find_package_handle_standard_args(Dot DEFAULT_MSG
    DOT_EXECUTABLE
)
 
mark_as_advanced(DOT_EXECUTABLE)
