set(Sources
    omr_test.cpp
)

add_executable(omr_test ${Sources})
add_library(l_omr_test ${Sources})

target_link_libraries(omr_test gtest_main optical_music_recognition ppm_utils)
target_link_libraries(l_omr_test gtest_main optical_music_recognition ppm_utils)

add_test(
    NAME omr_test
    COMMAND omr_test
)
