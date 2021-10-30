cmake_minimum_required(VERSION 3.10)

set(LIBRARY_NAME "downloader")

#========================
#Headers
#========================
set(headers_all "${PROJECT_SOURCE_DIR}/include")

#========================
#Sources
#========================
file(GLOB srcs_library "*.cpp")

#Include static analyzer target (cppcheck)
include("${PROJECT_SOURCE_DIR}/cmake/cppcheck.cmake")

#========================
#Building library
#========================
add_library(${LIBRARY_NAME} SHARED ${srcs_library})

target_include_directories(${LIBRARY_NAME}
                          PUBLIC ${headers_all})

find_library(LIBCURL curl)
target_link_libraries(${LIBRARY_NAME}
                      PUBLIC $<IF:$<BOOL:${LIBCURL}>,${LIBCURL},libcurl>)

target_compile_features(${LIBRARY_NAME} PRIVATE cxx_std_17)

#========================
#Build examples
#========================
if(EXAMPLES)
  add_subdirectory(examples)
endif()