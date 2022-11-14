cmake_minimum_required(VERSION 3.23)
project(Poster_1)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} src/main.cpp src/EightQueens.cpp src/KartenFaerben.cpp src/RandomStuff.cpp)
