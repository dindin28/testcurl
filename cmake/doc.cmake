configure_file(
  "${PROJECT_SOURCE_DIR}/doc/Doxyfile.in"
  "${PROJECT_BINARY_DIR}/doc/Doxyfile"
)

add_custom_target(doc
                  COMMAND doxygen Doxyfile
                  WORKING_DIRECTORY "${PROJECT_BINARY_DIR}/doc"
                  VERBATIM)