project(optical_music_recognition)

add_library(optical_music_recognition SHARED omr.cpp)

if (${UNIT_TEST})
    add_subdirectory(test)
endif()

target_include_directories(optical_music_recognition PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(optical_music_recognition grid rle_parser region_of_interest ppm_utils)