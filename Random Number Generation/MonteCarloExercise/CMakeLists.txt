cmake_minimum_required(VERSION 3.15)
project(MonteCarloExercise C)

set(CMAKE_C_STANDARD 11)

add_executable(MonteCarloExercise main.c)

#find_package(MKL REQUIRED)
#include_directories(${MKL_INCLUDE_DIRS})
#link_directories(${MKL_LIBRARIES})
#target_link_libraries(MonteCarloExercise
#        mkl_intel_lp64
#        mkl_sequential
#        mkl_core
#        )
#
#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
#find_package(MKL REQUIRED) # FOO_INCLUDE_DIR, FOO_LIBRARIES
#
#include_directories("${MKL_INCLUDE_DIR}")
#target_link_libraries(MonteCarloExercise ${FOO_LIBRARIES} ${BOO_LIBRARIES})