set(Sources
    rle_parser_test.cpp
)

add_executable(rle_parser_test ${Sources})
add_library(l_rle_parser_test ${Sources})

target_link_libraries(rle_parser_test gtest_main rle_parser)
target_link_libraries(l_rle_parser_test gtest_main rle_parser)

add_test(
    NAME rle_parser_test
    COMMAND rle_parser_test
)
