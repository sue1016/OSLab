cmake_minimum_required(VERSION 3.10)
project(Lab4)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
set(CMAKE_CXX_FLAGS  -pthread)
add_executable(Lab4
        main.cpp
        Process.cpp
        Process.h
        Scheduler.cpp
        Scheduler.h)
