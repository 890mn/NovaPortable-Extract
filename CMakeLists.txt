cmake_minimum_required(VERSION 3.25)
project(Nova_Debian)
# c++17 standard
set(CMAKE_CXX_STANDARD 17)

include_directories(include include/json)

#add_compile_options(-fPIC)
# source file
aux_source_directory(./src DIR_SRC)
aux_source_directory(./include DIR_INS)
# compile file
add_executable(Nova_Debian ${DIR_SRC} ${DIR_INS})
