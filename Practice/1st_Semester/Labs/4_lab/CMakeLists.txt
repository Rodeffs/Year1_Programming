cmake_minimum_required(VERSION 3.23)
project(lab4 C)

set(CMAKE_C_STANDARD 17)

add_executable(lab4 main.c)

file(COPY pilipenko_time_lab4.txt DESTINATION "/")