cmake_minimum_required(VERSION 3.27)
project(Nova_Debian)

set(CMAKE_CXX_STANDARD 23)
add_executable(Nova_Debian main.cpp
)

set(lib_DIR /usr/lib/x84_64-linux-gnu)

link_directories(${lib_DIR})

target_link_libraries(Nova_Debian libjsoncpp.a)

