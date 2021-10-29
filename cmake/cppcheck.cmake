function(analyze_file target_name)
  add_custom_command(TARGET ${target_name}
                    POST_BUILD
                    COMMAND cppcheck
                            --enable=warning,style,performance,unusedFunction,portability
                            --template="\({file}:{line}\) {message}"
                            #--verbose
                            #--quiet
                            -I $<TARGET_PROPERTY:${target_name},INCLUDE_DIRECTORIES>
                            $<TARGET_PROPERTY:${target_name},SOURCES>
                    COMMAND echo
                    VERBATIM)
endfunction()