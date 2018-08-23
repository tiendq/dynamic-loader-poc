set(PROJECT_SOURCES mysqrt.cpp mysqrt.h)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_library(mathman STATIC ${PROJECT_SOURCES})