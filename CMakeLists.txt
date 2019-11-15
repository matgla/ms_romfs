cmake_minimum_required (VERSION 2.8)
project(msos_romfs CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set (CMAKE_CXX_FLAGS "-std=c++17 ${CMAKE_CXX_FLAGS} -g")
endif()

add_subdirectory(core)
add_subdirectory(tests)
