cmake_minimum_required(VERSION 3.15)
project(untitled C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(SOURCE_FILES main.c)

add_executable(untitled ${SOURCE_FILES})

find_package(GSL REQUIRED)
target_link_libraries(untitled GSL::gsl GSL::gslcblas)