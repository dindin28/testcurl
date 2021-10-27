cmake_minimum_required(VERSION 3.10)

project(Hi)
set(LIBRARY_NAME "downloader")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

#=============================
#Analyze with static analyzer
#=============================
option(ANALYZE "Turn on static analyzer" OFF)

if(ANALYZE)
  set(CMAKE_CXX_CPPCHECK "cppcheck")
endif()

#=============================
#Include unit tests
#=============================
option(TEST "Include unit tests" ON)

if(TEST)
  set(TEST_EXEC "test_downloader")

  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
  )
  # For Windows: Prevent overriding the parent project's compiler/linker settings
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
endif()

#========================
#Find CURL Lib in system
#========================

find_package(CURL)

if(NOT ${CURL_FOUND})
  message(WARNING "libcurl not found")
endif()

#========================
#Headers
#========================
set(headers_path "${PROJECT_SOURCE_DIR}/include")

#========================
#Sources
#========================
file(GLOB srcs_library "src/downloader.cpp")
file(GLOB srcs_exec "src/main.cpp")
if(TEST)
  file(GLOB srcs_test "test/*.cpp")
endif()

message(STATUS ${srcs_library})
message(STATUS ${srcs_exec})

#========================
#Building library
#========================
add_library(${LIBRARY_NAME} ${srcs_library})

target_include_directories(
  ${LIBRARY_NAME}
  PRIVATE
    ${headers_path}
)

target_link_libraries(
  ${LIBRARY_NAME}
  PUBLIC
    ${CURL_LIBRARIES}
)

#========================
#Building executable
#========================
add_executable(${PROJECT_NAME} ${srcs_exec})

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE
    ${headers_path}
)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
    ${LIBRARY_NAME}
)

#========================
#Build unit tests
#========================
if(TEST)
  enable_testing()

  add_executable(${TEST_EXEC} ${srcs_test})

  target_include_directories(
  ${TEST_EXEC}
  PRIVATE
    ${headers_path}
  )

  target_link_libraries(
    ${TEST_EXEC}
  PRIVATE
    ${LIBRARY_NAME}
      gtest_main
  )

  include(GoogleTest)
  gtest_discover_tests(${TEST_EXEC})
endif()