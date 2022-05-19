cmake_minimum_required(VERSION 3.22)
project(LinearLibrary)

set(CMAKE_CXX_STANDARD 17)
include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

add_executable(execs main.cpp MatrixLibrary.h MatrixLibrary.tpp MatrixOperations.h)

