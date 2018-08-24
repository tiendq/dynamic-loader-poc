cmake_minimum_required(VERSION 3.12.0)

project(dynloader)

message(STATUS "Building for ${CMAKE_SYSTEM_NAME} system")

set(CMAKE_BUILD_TYPE Release)
message(STATUS "${CMAKE_BUILD_TYPE} build configuration is detected")

# UNIX, WIN32, WINRT, CYGWIN, APPLE are environment variables as flags set by default system
if(WIN32)
  # WIN32
elseif(APPLE)
  # APPLE
elseif(UNIX)
  # UNIX
else()
  message(FATAL_ERROR "Unsupported system. Build aborted.")
endif()

add_subdirectory(mathman)
add_subdirectory(test1)
add_subdirectory(test2)

set(MAIN_TARGET_NAME dynloader)

set(PROJECT_SOURCES
  main.cpp
  library-loader-base.h
  unix-library-loader.cpp
  unix-library-loader.h)

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/build/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# The version number
set(POC_VERSION_MAJOR 0)
set(POC_VERSION_MINOR 1)
set(POC_VERSION_PATCH 0)

# Configure a header file to pass some of the CMake settings to the source code
configure_file(
  "${PROJECT_SOURCE_DIR}/cmake-config-template.h"
  "${CMAKE_BINARY_DIR}/cmake-config.h"
)

add_executable(${MAIN_TARGET_NAME} ${PROJECT_SOURCES})

target_include_directories(${MAIN_TARGET_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/mathman")
# target_include_directories(${MAIN_TARGET_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/test1")
# target_include_directories(${MAIN_TARGET_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/test2")
target_include_directories(${MAIN_TARGET_NAME} PRIVATE ${CMAKE_BINARY_DIR})

target_link_libraries(${MAIN_TARGET_NAME} PRIVATE mathman)
# target_link_libraries(${MAIN_TARGET_NAME} PRIVATE test1)
# target_link_libraries(${MAIN_TARGET_NAME} PRIVATE test2)
target_compile_features(${MAIN_TARGET_NAME} PRIVATE cxx_std_14)

if (MSVC)
  # warning level 4 and all warnings as errors
  target_compile_options(${MAIN_TARGET_NAME} PRIVATE "/W4 /WX")
else()
  # lots of warnings and all warnings as errors
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror")
  # target_compile_options(${MAIN_TARGET_NAME} PRIVATE "SHELL: -Wall -Wextra -pedantic -Werror")
endif()