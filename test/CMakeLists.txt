cmake_minimum_required(VERSION 3.21)

include(GoogleTest)

add_subdirectory(gtest)

add_executable(barrel_test
        disk_manager_test.cpp
        )

target_include_directories(barrel_test
        PRIVATE ${gtest_SOURCE_DIR}
        PRIVATE ${gtest_SOURCE_DIR}/include)

target_link_libraries(barrel_test
        PUBLIC gtest
        PUBLIC gtest_main)

gtest_discover_tests(barrel_test)
