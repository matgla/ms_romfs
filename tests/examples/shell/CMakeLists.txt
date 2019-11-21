add_executable(romfs_shell_example)

target_sources(romfs_shell_example
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries(romfs_shell_example
    PRIVATE
        romfs
)

file(COPY "${PROJECT_SOURCE_DIR}/tests/core_tests/test_img.romfs" DESTINATION ${PROJECT_BINARY_DIR})
file(COPY "${PROJECT_SOURCE_DIR}/tests/example_volume.romfs" DESTINATION ${PROJECT_BINARY_DIR})

install(TARGETS romfs_shell_example DESTINATION ${CMAKE_BINARY_DIR})
