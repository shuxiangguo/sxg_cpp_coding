cmake_minimum_required(VERSION 3.14)
project(ch04)

set(CMAKE_CXX_STANDARD 14)

add_executable(tree tree.cpp)
add_executable(BST bintree.h bstree.h BSTree.cpp)
add_executable(avl AVL.cpp)