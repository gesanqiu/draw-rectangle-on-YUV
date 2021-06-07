# created by Ricardo Lu 06-07-21

cmake_minimum_required(VERSION 3.4.1)
set(CMAKE_CXX_STANDARD 14)

PROJECT(drawRectTest)

add_executable(${PROJECT_NAME}
    drawRectNV12.cpp
    test.cpp
)