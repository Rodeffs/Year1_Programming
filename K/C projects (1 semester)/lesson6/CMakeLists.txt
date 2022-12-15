cmake_minimum_required (VERSION 3.23)

set(PROJECT_NAME lesson6)

project (lesson6)

set(CMAKE_C_STANDARD 17)

add_executable(lesson6 lesson6.pro main.c)

file(COPY sample.txt DESTINATION "/")