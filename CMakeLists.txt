cmake_minimum_required(VERSION 3.12.0)
project(dynloader)

if(WIN32)
  add_compile_definitions(__WINDOWS__)
elseif(APPLE)
  add_compile_definitions(__MACOS__)
elseif(UNIX)
  add_compile_definitions(__LINUX__)
else()
  message(FATAL_ERROR "Unsupported system. Build aborted.")
endif()

message(STATUS "Building for ${CMAKE_SYSTEM_NAME} system")

set(CMAKE_BUILD_TYPE Release)
message(STATUS "${CMAKE_BUILD_TYPE} build configuration is detected")

set(MAIN_TARGET_NAME dynloader)
set(PROJECT_SOURCES main.cpp library-loader-base.h)

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

if(WIN32)
  set(PROJECT_SOURCES ${PROJECT_SOURCES} windows-library-loader.cpp windows-library-loader.h)
else()
  set(PROJECT_SOURCES ${PROJECT_SOURCES} unix-library-loader.cpp unix-library-loader.h)
endif()

add_subdirectory(mathman)
add_subdirectory(test1)
add_subdirectory(test2)
add_executable(${MAIN_TARGET_NAME} ${PROJECT_SOURCES})

target_include_directories(${MAIN_TARGET_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/mathman")
target_include_directories(${MAIN_TARGET_NAME} PRIVATE ${CMAKE_BINARY_DIR})

target_link_libraries(${MAIN_TARGET_NAME} PRIVATE mathman)

if(WIN32)
  # Windows only libraries
elseif(APPLE)
  # macOS only libraries
else()
  # Linux only libraries
  target_link_libraries(${MAIN_TARGET_NAME} PRIVATE dl)
endif()

target_compile_features(${MAIN_TARGET_NAME} PRIVATE cxx_std_14)

if (WIN32)
  # warning level 4 and all warnings as errors
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
else()
  # lots of warnings and all warnings as errors
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror")
  # target_compile_options(${MAIN_TARGET_NAME} PRIVATE "SHELL: -Wall -Wextra -pedantic -Werror")
endif()
