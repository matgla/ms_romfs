add_library(romfs STATIC)

set (include_path "${PROJECT_SOURCE_DIR}/include/romfs")

target_sources(romfs
    PUBLIC
        ${include_path}/directory.hpp
        ${include_path}/directoryIterator.hpp
        ${include_path}/file.hpp
        ${include_path}/fileHeader.hpp
        ${include_path}/fileSystemHeader.hpp
        ${include_path}/reader.hpp
        ${include_path}/romfs.hpp
        ${include_path}/utils.hpp

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/directory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/directoryIterator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/file.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/fileHeader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/fileSystemHeader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/reader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/romfs.cpp
)

target_include_directories(romfs
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

message(STATUS "Adding custom cxx flags: ${romfs_cxx_compilation_flags}")

target_compile_options(romfs
    PRIVATE
        $<$<COMPILE_LANGUAGE:CXX>:${romfs_cxx_compilation_flags} -Werror -Wall -Wextra -Wpedantic -Wconversion -Wcast-align -Wunused -Wshadow -Wold-style-cast -Wpointer-arith -Wcast-qual -Wno-missing-braces>
        $<$<CONFIG:DEBUG>:-Og -g>
        $<$<CONFIG:RELEASE>:-Os>
)
