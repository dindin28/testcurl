cmake_minimum_required(VERSION 3.10)

#===========================
#INCLUDE GOOGLETEST LIBRARY
#===========================

if(TEST)
  message(STATUS "Building GoogleTest library")
  set(BUILD_GMOCK OFF CACHE INTERNAL "")
  set(BUILD_SHARED_LIBS ON CACHE INTERNAL "")
  set(INSTALL_GTEST OFF CACHE INTERNAL "")
  add_subdirectory(googletest)
endif()

#========================
#INCLUDE CURL LIBRARY
#========================
find_library(LIBCURL curl)

if(NOT LIBCURL)
  message(STATUS "Building CURL library")
  set(CURL_TEST OFF CACHE INTERNAL "")
  add_subdirectory(curl)
endif()