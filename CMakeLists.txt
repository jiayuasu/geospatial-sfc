cmake_minimum_required(VERSION 3.20)
project(geospatial_sfc)

set(CMAKE_CXX_STANDARD 14)

add_executable(geospatial_sfc main.cpp hilbert/hilbert.h hilbert/hilbert.cpp)
target_include_directories(geospatial_sfc PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libmorton;${CMAKE_CURRENT_SOURCE_DIR}/hilbert>")
target_compile_definitions(geospatial_sfc PRIVATE __BMI2__ __AVX512BITALG__)
