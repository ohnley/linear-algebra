cmake_minimum_required(VERSION 3.22)
project(LinearLibrary)

set(CMAKE_CXX_STANDARD 14)

add_executable(execs main.cpp MatrixLibrary.h MatrixLibrary.tpp)

