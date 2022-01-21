cmake_minimum_required(VERSION 3.21)
project(barrel)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(libs)

add_executable(barrel main.cpp)

target_link_libraries(cchip8
        PRIVATE GSL
        PRIVATE argparse
        PRIVATE magic_enum)


