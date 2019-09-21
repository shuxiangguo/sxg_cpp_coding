cmake_minimum_required(VERSION 3.14)
project(ch03)

set(CMAKE_CXX_STANDARD 14)

add_executable(slist slist.c)
add_executable(slist2 slist.cpp)
add_executable(llist LList.c)
add_executable(stack Stack.c)
add_executable(queue Queue.c)
add_executable(singleQueue singleQueue.cpp)
add_executable(bank bank.cpp)