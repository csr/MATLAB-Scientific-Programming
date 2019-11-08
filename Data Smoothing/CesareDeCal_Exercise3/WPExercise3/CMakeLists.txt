cmake_minimum_required(VERSION 3.15)
project(WPExercise3 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(SOURCE_FILES main.c)

add_executable(WPExercise3 ${SOURCE_FILES})

find_package(GSL REQUIRED)
target_link_libraries(WPExercise3 GSL::gsl GSL::gslcblas)