cmake_minimum_required(VERSION 3.21)

add_subdirectory(disk)

target_include_directories(barrel
        PRIVATE include)

target_include_directories(barrel_test
        PRIVATE include)