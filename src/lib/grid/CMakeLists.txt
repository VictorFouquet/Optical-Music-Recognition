project(grid)

add_library(grid SHARED grid.cpp)

add_subdirectory(test)

target_include_directories(grid PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
