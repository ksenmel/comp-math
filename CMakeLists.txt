cmake_minimum_required(VERSION 3.27)
project(comp_math C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address -g")

add_executable(comp_math task-1/main.c)
