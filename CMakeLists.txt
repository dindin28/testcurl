cmake_minimum_required(VERSION 3.10)

project(Hi)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

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
file(GLOB srcs "src/*.cpp")

#========================
#Building executable
#========================
add_executable(${PROJECT_NAME} ${srcs})

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE
    ${headers_path}
)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
    ${CURL_LIBRARIES}
)