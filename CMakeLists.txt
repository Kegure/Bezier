cmake_minimum_required(VERSION 3.28)
project(untitled)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled Bezier.cpp
        Bezier.cpp)
target_link_libraries(untitled -lglut -lglfw -lGLEW -lGL -lGLU -lSDL2)