cmake_minimum_required(VERSION 3.14)
project(qingdao)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(ch03)
add_subdirectory(ch04)
add_subdirectory(ch05)
add_subdirectory(ch06)

add_executable(qingdao main.cpp)