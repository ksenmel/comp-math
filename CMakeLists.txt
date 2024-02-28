cmake_minimum_required(VERSION 3.27)
project(comp_math C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp ")

add_executable(comp_math task-1/main.c)
