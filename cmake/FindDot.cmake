find_program(DOT_EXECUTABLE NAMES dot
    DOC "Graphviz dot"
)
 
include(FindPackageHandleStandardArgs)
 
find_package_handle_standard_args(Dot DEFAULT_MSG
    DOT_EXECUTABLE
)
 
mark_as_advanced(DOT_EXECUTABLE)