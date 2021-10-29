cmake_minimum_required(VERSION 3.10)

set(LIBRARY_NAME "downloader")

if(ANALYZE)
  set(CMAKE_CXX_CPPCHECK "cppcheck")
endif()

#========================
#Headers
#========================
set(headers_all "${PROJECT_SOURCE_DIR}/include")

#========================
#Sources
#========================
file(GLOB srcs_all "*.cpp")

#sources for lib
set(srcs_library ${srcs_all})
list(REMOVE_ITEM srcs_library "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp") ## Remove executable file
message(DEBUG "${srcs_library}")

#source for executable
file(GLOB srcs_exec "main.cpp")
message(DEBUG "${srcs_exec}")

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
#Building executable
#========================
add_executable(${PROJECT_NAME} ${srcs_exec})

target_link_libraries(${PROJECT_NAME}
                      PRIVATE ${LIBRARY_NAME})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)