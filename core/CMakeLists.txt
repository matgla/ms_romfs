
file(GLOB core_src
     "*.hpp"
     "*.cpp"
)

add_executable(romfs ${core_src})

install(TARGETS romfs DESTINATION ${CMAKE_BINARY_DIR})
