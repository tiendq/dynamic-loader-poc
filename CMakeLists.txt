cmake_minimum_required(VERSION 3.12)
project(dynloader)

message(STATUS "Building for ${CMAKE_SYSTEM_NAME} system")

set(CMAKE_BUILD_TYPE Release)
message(STATUS "${CMAKE_BUILD_TYPE} build configuration is detected")

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

add_subdirectory(mathman)
add_subdirectory(test1)
add_subdirectory(test2)
add_executable(${PROJECT_NAME} main.cpp library-loader-base.h)

if(WIN32)
  target_sources(${PROJECT_NAME}
    PRIVATE
      windows-library-loader.cpp
      windows-library-loader.h
  )
else()
  target_sources(${PROJECT_NAME}
    PRIVATE
      unix-library-loader.cpp
      unix-library-loader.h
  )
endif()

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_14)
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/mathman")
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE mathman)

if(WIN32)
  target_compile_definitions(${PROJECT_NAME} PRIVATE __WINDOWS__)
elseif(APPLE)
  target_compile_definitions(${PROJECT_NAME} PRIVATE __MACOS__)
elseif(UNIX)
  target_compile_definitions(${PROJECT_NAME} PRIVATE __LINUX__)
  target_link_libraries(${PROJECT_NAME} PRIVATE dl)
else()
  message(FATAL_ERROR "Unsupported system. Build aborted.")
endif()

if (WIN32)
  target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()
