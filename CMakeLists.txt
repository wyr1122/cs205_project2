cmake_minimum_required(VERSION 3.23)
project(project2)

set(CMAKE_CXX_STANDARD 14)

add_executable(project2 arithmetic.cpp calculation.cpp arithmetic.h main.cpp calculation.h)
IF (WIN32)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fexec-charset=GBK")
ENDIF ()
