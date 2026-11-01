cmake_minimum_required(VERSION 3.20)
project(proga)
add_executable(proga main.cpp
        include/point.h
        src/point.cpp
        include/triangle.h
        src/triangle.cpp
        include/list.h
        src/list.cpp
)
file(COPY input.txt DESTINATION ${CMAKE_BINARY_DIR})