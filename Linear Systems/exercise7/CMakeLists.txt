cmake_minimum_required(VERSION 3.15)
project(exercise7 C)

set(CMAKE_C_STANDARD 11)

# Import GSL library
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(exercise7 main.c)