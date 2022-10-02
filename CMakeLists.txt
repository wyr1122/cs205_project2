cmake_minimum_required(VERSION 3.23)
project(project2)

set(CMAKE_CXX_STANDARD 14)

add_executable(project2 arithmetic.cpp calculation.cpp main.cpp arithmetic.h test.cpp calculation.h)
