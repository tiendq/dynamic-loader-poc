cmake_minimum_required(VERSION 3.12.0)

project(dynloader)

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_subdirectory(mathman)

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}/mathman")

# Add the binary tree to the search path for include files so that we will find cmake-config.h
include_directories("${CMAKE_BINARY_DIR}")

# The version number
set(POC_VERSION_MAJOR 0)
set(POC_VERSION_MINOR 1)
set(POC_VERSION_PATCH 0)

# Configure a header file to pass some of the CMake settings to the source code
configure_file(
  "${PROJECT_SOURCE_DIR}/cmake-config-template.h"
  "${CMAKE_BINARY_DIR}/cmake-config.h"
)

add_executable(dynloader main.cpp)
target_link_libraries(dynloader mathman)