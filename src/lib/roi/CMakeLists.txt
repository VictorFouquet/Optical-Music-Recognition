project(region_of_interest)

add_library(region_of_interest SHARED region_of_interest.cpp)

if (${UNIT_TEST})
    add_subdirectory(test)
endif()

target_include_directories(region_of_interest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(region_of_interest grid)