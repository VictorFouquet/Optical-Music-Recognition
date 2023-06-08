cmake_minimum_required(VERSION 3.21.2)

project(omr)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(external)
add_subdirectory(src/lib)

target_link_libraries(${PROJECT_NAME} grid region_of_interest)
