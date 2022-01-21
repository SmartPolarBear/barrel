cmake_minimum_required(VERSION 3.21)
project(barrel)

find_package(cppcoro CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(libs)

add_executable(barrel main.cpp)

target_link_libraries(barrel
        PRIVATE cppcoro
        PRIVATE GSL
        PRIVATE argparse
        PRIVATE magic_enum)


