project(lab1) 

add_executable(oop_exercise_01 main.cpp IPAddress.h IPAddress.cpp) 

set(MY_FLAGS "-Wall -g -Wextra") 

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${MYCOMPILE_FLAGS}")
