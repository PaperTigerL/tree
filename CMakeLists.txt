cmake_minimum_required(VERSION 3.25)
project(tree)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(tree
        main.cpp
        myTree.cpp
        myTree.h)
