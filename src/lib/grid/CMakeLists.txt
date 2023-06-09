project(grid)

add_library(grid SHARED grid.cpp)

if (${UNIT_TEST})
    add_subdirectory(test)
endif()

target_include_directories(grid PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
