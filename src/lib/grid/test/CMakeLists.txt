set(Sources
    grid_test.cpp
)

add_executable(grid_test ${Sources})
add_library(l_grid_test ${Sources})

target_link_libraries(grid_test gtest_main grid)
target_link_libraries(l_grid_test gtest_main grid)

add_test(
    NAME grid_test
    COMMAND grid_test
)
