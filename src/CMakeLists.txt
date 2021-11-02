cmake_minimum_required(VERSION 3.10)

set(LIBRARY_NAME "downloader")

#========================
#Includes
#========================
include(GNUInstallDirs)

#========================
#Headers
#========================
set(headers_path "${PROJECT_SOURCE_DIR}/include")
file(GLOB headers "${headers_path}/**/*.hpp")

#========================
#Sources
#========================
file(GLOB srcs_library "*.cpp")

#Include static analyzer target (cppcheck)
include("${PROJECT_SOURCE_DIR}/cmake/cppcheck.cmake")

#========================
#Building library
#========================
add_library(${LIBRARY_NAME} SHARED ${headers} ${srcs_library})



target_include_directories(${LIBRARY_NAME}
                          PUBLIC
                            $<BUILD_INTERFACE:${headers_path}> # for headers when building
                            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> # for client in install mode
)


find_library(LIBCURL curl)
target_link_libraries(${LIBRARY_NAME}
                      PUBLIC $<IF:$<BOOL:${LIBCURL}>,${LIBCURL},libcurl>)

target_compile_features(${LIBRARY_NAME} PRIVATE cxx_std_17)

#========================
#Installing library
#========================
# install header file
install(DIRECTORY "${headers_path}/" DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# install the target and create export-set
install(TARGETS ${LIBRARY_NAME}
        EXPORT ${LIBRARY_NAME}Targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# generate and install export file
install(EXPORT ${LIBRARY_NAME}Targets
        FILE ${LIBRARY_NAME}Targets.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${LIBRARY_NAME}
)

# include CMakePackageConfigHelpers macro
include(CMakePackageConfigHelpers)

# create config file
configure_package_config_file(${PROJECT_SOURCE_DIR}/cmake/config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}Config.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${LIBRARY_NAME}
)

# install config files
install(FILES
          "${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}Config.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${LIBRARY_NAME}
)

# generate the export targets for the build tree
export(EXPORT ${LIBRARY_NAME}Targets
       FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/${LIBRARY_NAME}Targets.cmake"
)

#========================
#Build examples
#========================
if(EXAMPLES)
  add_subdirectory(examples)
endif()