cmake_minimum_required(VERSION 3.9)

project(tdb)

set(PROJECT_NAME tdb)
set(EXAMPLE_NAME tdb_example)

include_directories("./include")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB SOURCE_FILES "./src/*c")

add_library(${PROJECT_NAME} ${SOURCE_FILES})
add_executable(${EXAMPLE_NAME} "example-main.c")
target_link_libraries(${EXAMPLE_NAME} ${PROJECT_NAME})

