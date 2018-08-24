set(PROJECT_SOURCES main.cpp test1.cpp test1.h test3.cpp test3.h)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_library(test1 SHARED ${PROJECT_SOURCES})