cmake_minimum_required(VERSION 3.21)

target_include_directories(barrel
        PRIVATE include)

target_include_directories(barrel_test
        PRIVATE include)

target_sources(barrel
        PRIVATE buffer_pool_manager.cpp
        PRIVATE clock_replacer.cpp)

target_sources(barrel_test
        PRIVATE buffer_pool_manager.cpp
        PRIVATE clock_replacer.cpp)