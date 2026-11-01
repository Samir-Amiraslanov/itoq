cmake_minimum_required(VERSION 3.20)
project(proga)
add_executable(proga itoq.cpp)
file(COPY input.txt DESTINATION ${CMAKE_BINARY_DIR})