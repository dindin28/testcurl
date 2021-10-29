file(GLOB_RECURSE ALL_SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/include/**/*.hpp")

add_custom_target(cppcheck
                  COMMAND cppcheck
                          --enable=warning,style,performance,unusedFunction,portability
                          --template="\({file}:{line}\) {message}"
                          #--verbose
                          --quiet
                          -I "${PROJECT_SOURCE_DIR}/include"
                          ${ALL_SOURCE_FILES}
                  VERBATIM)