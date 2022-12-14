cmake_minimum_required(VERSION 3.24)
project(lab5__kr5_ C)

set(CMAKE_C_STANDARD 17)

add_executable(lab5__kr5_ main.c)

file(COPY lab5_kr5_task.jpg DESTINATION "/")
