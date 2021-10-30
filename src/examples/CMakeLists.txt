cmake_minimum_required(VERSION 3.10)

#========================
#Sources
#========================
file(GLOB srcs_all "*.cpp")

foreach(target_path ${srcs_all})
  string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" target_name ${target_path}) #remove prefix path
  string(REPLACE ".cpp" "" target_name ${target_name})                         #remove extension

  #========================
  #Building executable
  #========================
  add_executable(${target_name} ${target_path})
  target_link_libraries(${target_name} PRIVATE ${LIBRARY_NAME})
  target_compile_features(${target_name} PRIVATE cxx_std_17)

endforeach()