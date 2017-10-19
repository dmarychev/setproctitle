cmake_minimum_required(VERSION 2.8)
project(setproctitle CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-std=c++11)

include_directories(src/include)

add_library(setproctitle STATIC src/setproctitle.cpp)
install(TARGETS setproctitle
        ARCHIVE DESTINATION lib)
install(DIRECTORY src/include/setproctitle
        DESTINATION include/
        FILES_MATCHING PATTERN "*.h")

find_package(CxxTest)
if (CxxTest_FOUND)
    enable_testing()
    add_subdirectory(src/unit)
else()
    message(WARNING "CxxTest was not found, unit tests will be disabled")
endif()
