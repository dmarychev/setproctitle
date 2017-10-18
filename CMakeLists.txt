cmake_minimum_required(VERSION 2.8)
project(setproctitle CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src/include)

add_library(setproctitle STATIC src/setproctitle.cpp)
