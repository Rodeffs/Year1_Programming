cmake_minimum_required(VERSION 3.23)

set(PROJECT_NAME lection7)

project(lection7)

set(CMAKE_CXX_STANDARD 17)

add_executable(lection7 lection7.cpp)

file(COPY about_gitbash.txt DESTINATION "/")

