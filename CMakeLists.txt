project(test_rib_tree)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 14)

add_executable(test_rib_tree main.cpp tree.cpp tree.h)
