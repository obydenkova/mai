project(lab3) 

add_executable(oop_exercise_03 main.cpp point.cpp figure.cpp quadrate.cpp rectangle.cpp trapeze.cpp) 

set(MY_FLAGS "-Wall -g -Wextra") 

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MYCOMPILE_FLAGS}")
