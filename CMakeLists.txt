cmake_minimum_required(VERSION 3.10)

project(Hi)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(CURL)

if(NOT LIBCURL)
  message(WARNING "libcurl not found")
endif()

#========================
#Sources
#========================
file(GLOB srcs "*.cpp")

#========================
#Building executable
#========================
add_executable(${PROJECT_NAME} ${srcs})

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
    ${CURL_LIBRARIES}
)