cmake_minimum_required(VERSION 3.23)
project(Poster_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} src/main.cpp src/RandomStuff.cpp src/Stundenplan.cpp)
