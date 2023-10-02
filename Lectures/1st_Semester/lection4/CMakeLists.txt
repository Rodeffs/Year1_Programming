cmake_minimum_required(VERSION 3.23)

set(PROJECT_NAME lection4)

project(lection4)

set(CMAKE_CXX_STANDARD 17)

add_executable(lection4 lection4.cpp)

file(COPY input.txt DESTINATION "/")

