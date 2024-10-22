# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(AES256)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

# Add directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add all source files in src
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add the executable
add_executable(AES256 ${SOURCES})
