cmake_minimum_required(VERSION 3.26)
project(RunningMean)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE=Debug)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

include_directories(MovingAverageFilters)
include_directories(SignalWrappers)
add_executable(MovingAverage MovingAverageFilters SignalWrappers Test/main.cpp
        Test/NoisySinusoid.hpp
        Test/TemporalSmootherTest.hpp
        )

target_link_libraries(MovingAverage Eigen3::Eigen)