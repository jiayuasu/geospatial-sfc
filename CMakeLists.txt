cmake_minimum_required(VERSION 3.20)
project(geospatial_sfc)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake) # find geos path

find_package(GEOS REQUIRED)# if not find geo, cannot compile find geos.cmake

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O3 -march=native -Wall -Wextra")

if(APPLE)
    set(CMAKE_FIND_FRAMEWORK LAST)
    set(CMAKE_FIND_APPBUNDLE LAST)
endif()

add_executable(geospatial_sfc main.cpp hilbert/hilbert.h hilbert/hilbert.cpp Encoder.h)
target_link_libraries(geospatial_sfc PRIVATE ${GEOS_LIBRARY})
target_include_directories(geospatial_sfc PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/libmorton;${CMAKE_CURRENT_SOURCE_DIR}/hilbert;${GEOS_INCLUDE_DIR}>")
target_compile_definitions(geospatial_sfc PRIVATE __BMI2__ __AVX512BITALG__)