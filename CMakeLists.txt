cmake_minimum_required (VERSION 2.8)

project(msos_romfs CXX)

add_subdirectory(source)

if (NOT DISABLE_ROMFS_TESTS)
    add_subdirectory(tests/examples)
endif()
