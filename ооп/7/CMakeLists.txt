cmake_minimum_required(VERSION 3.10.2)
project(oop_exercise_07)

set(CMAKE_CXX_STANDARD 17)

add_executable(oop_exercise_07 main.cpp point.h square.h square.cpp figure.h point.cpp rectangle.cpp rectangle.h trapezoid.cpp trapezoid.h document.h factory.h command.h editor.h document.cpp factory.cpp editor.cpp command.cpp)
