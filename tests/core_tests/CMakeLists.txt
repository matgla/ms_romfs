file(GLOB_RECURSE SRCS
     *.cpp
)

file(GLOB_RECURSE PROD_SRCS
     "${PROJECT_SOURCE_DIR}/core/*.cpp"
     "${PROJECT_SOURCE_DIR}/core/*.hpp"
)

file(COPY "${PROJECT_SOURCE_DIR}/tests/core_tests/test_img.romfs" DESTINATION ${PROJECT_BINARY_DIR}) 

include_directories("${PROJECT_SOURCE_DIR}/core")

list(REMOVE_ITEM PROD_SRCS ${PROJECT_SOURCE_DIR}/core/main.cpp)

add_executable(romfs_core_tests ${SRCS} ${PROD_SRCS})

target_link_libraries(romfs_core_tests GTest)

install(TARGETS romfs_core_tests DESTINATION ${CMAKE_BINARY_DIR})
