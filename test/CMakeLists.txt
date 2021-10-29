cmake_minimum_required(VERSION 3.10)

set(TEST_EXEC "test_downloader")

#========================
#Sources
#========================
file(GLOB srcs_test "*.cpp")

#========================
#Build unit tests
#========================
enable_testing()

add_executable(${TEST_EXEC} ${srcs_test})

#Check cmake-generator-expressions
#file(GENERATE OUTPUT ${PROJECT_SOURCE_DIR}/output.txt CONTENT  $<TARGET_FILE:downloader>)

target_link_libraries(${TEST_EXEC}
                      PRIVATE
                        downloader #Should change to cmake-generator-expressions if make install in system
                        gtest_main)

target_compile_features(${TEST_EXEC} PRIVATE cxx_std_17)

include(GoogleTest)
gtest_discover_tests(${TEST_EXEC})