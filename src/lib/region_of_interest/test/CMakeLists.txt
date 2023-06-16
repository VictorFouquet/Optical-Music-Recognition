set(Sources
    region_of_interest_test.cpp
)

add_executable(region_of_interest_test ${Sources})
add_library(l_region_of_interest_test ${Sources})

target_link_libraries(region_of_interest_test gtest_main region_of_interest)
target_link_libraries(l_region_of_interest_test gtest_main region_of_interest)

add_test(
    NAME region_of_interest_test
    COMMAND region_of_interest_test
)
