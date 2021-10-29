cmake_minimum_required(VERSION 3.10)

file(TO_CMAKE_PATH "${CMAKE_CURRENT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
  message(FATAL_ERROR "You cannot build in a source directory. Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()


project(Downloader
        VERSION 1.0
        DESCRIPTION "Project to download files in unstable connection"
        LANGUAGES CXX)

option(ANALYZE "Turn on static analyzer" ON)
option(TEST "Include unit tests" ON)
option(DOCS "Make html doc with Doxygen" ON)

add_subdirectory(lib)
add_subdirectory(src)

if(TEST)
  add_subdirectory(test)
endif()

if(DOCS)
  add_subdirectory(doc)
endif()