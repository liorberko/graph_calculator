cmake_minimum_required(VERSION 3.0.0)
project(test1 VERSION 0.1.0)

set(CMAKE_C_FLAGS "-std=c++11 -Wall -pedantic-errors -Werror -g -DNDEBUG")
add_executable(alpaca test.cpp Auxiliaries.cpp graphCalculatorParser.CPP Exception.cpp Graph.cpp GraphCalculator.cpp)
