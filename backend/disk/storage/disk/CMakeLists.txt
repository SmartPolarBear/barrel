cmake_minimum_required(VERSION 3.21)

target_sources(barrel
        PRIVATE disk_manager.cpp)

target_sources(barrel_test
        PRIVATE disk_manager.cpp)