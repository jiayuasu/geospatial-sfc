cmake_minimum_required(VERSION 3.20)
project(geospatial_sfc)

set(CMAKE_CXX_STANDARD 14)

add_executable(geospatial_sfc main.cpp hilbert.h hilbert.cpp)
