cmake_minimum_required(VERSION 3.15)
project(Uno)

set(CMAKE_CXX_STANDARD 11)

add_executable(Uno main.cpp Player.cpp Player.h Card.cpp Card.h Move.cpp Move.h gameLoop.cpp main.h gameLoop.h)