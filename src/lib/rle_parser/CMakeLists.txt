project(rle_parser)

add_library(rle_parser SHARED rle_parser.cpp)

if (${UNIT_TEST})
    add_subdirectory(test)
endif()

target_include_directories(rle_parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(rle_parser grid region_of_interest)