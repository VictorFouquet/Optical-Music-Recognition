cmake_minimum_required(VERSION 3.21.2)

set(DEBUG_IMG TRUE)
set(UNIT_TEST TRUE)

if (${DEBUG_IMG})
    # Update this value with the path to the folder you want to store the images in
    # Note: don't forget to escape the opening and closing quotation marks
    set(MY_PATH \"/path/to/output/images/folder\")
    add_definitions(-D_IMG_DEBUG_PATH=${MY_PATH})
endif()

project(omr)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} src/main.cpp)

if(${UNIT_TEST})
    add_subdirectory(external)
endif()

add_subdirectory(utils)
add_subdirectory(src/lib)

target_link_libraries(${PROJECT_NAME} grid region_of_interest ppm_utils)
