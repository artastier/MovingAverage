cmake_minimum_required(VERSION 3.26)
project(RunningMean)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE=Debug)

add_executable(MovingAverage Test/main.cpp
        MovingAverage.hpp
        Test/NoisySinusoid.hpp
        Test/MovingAverageTest.hpp)
