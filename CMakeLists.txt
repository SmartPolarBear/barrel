cmake_minimum_required(VERSION 3.21)
project(barrel)

set(CMAKE_CXX_STANDARD 23)

# configured by vcpkg
find_package(cppcoro CONFIG REQUIRED)

add_executable(barrel main.cpp)

#3rd party libraries
add_subdirectory(libs)
target_link_libraries(barrel
        PRIVATE cppcoro
        PRIVATE GSL
        PRIVATE argparse
        PRIVATE magic_enum
        PRIVATE plog)

add_subdirectory(storage)

add_subdirectory(test)


