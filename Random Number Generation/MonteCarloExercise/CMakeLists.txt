cmake_minimum_required(VERSION 3.15)
project(MonteCarloExercise C)

set(CMAKE_C_STANDARD 11)

include_directories(${MKLROOT})

add_executable(MonteCarloExercise main.c)

find_package(MKL REQUIRED)
include_directories(${MKL_INCLUDE_DIRS})
link_directories(${MKL_LIBRARIES})
target_link_libraries(MonteCarloExercise
        mkl_intel_lp64
        mkl_sequential
        mkl_core
        )
