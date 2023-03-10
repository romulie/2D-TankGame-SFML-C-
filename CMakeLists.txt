cmake_minimum_required (VERSION 2.8.11)

project (game)

set(CMAKE_CXX_STANDARD 14)

include_directories(headers)

add_executable(game main.cpp)
