cmake_minimum_required(VERSION 3.14)
project(ch05)

set(CMAKE_CXX_STANDARD 14)


add_executable(heap heap.c)
add_executable(priority_queue priority_queue.cpp)
add_executable(SetTest SetTest.cpp)
add_executable(disjointSet disjointSet.cpp)