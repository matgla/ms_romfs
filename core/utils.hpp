#pragma once

#include <cstdint>
#include <string>
#include <vector>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

template <typename T>
T* make_aligned_ptr(const T* memoryAddress, std::size_t alignment)
{
    uintptr_t addr = reinterpret_cast<uintptr_t>(memoryAddress);
    if (addr % alignment != 0)
    {
        addr += alignment - addr % alignment;
    }
    return (T*) addr;
}

u32 read32(u8 **fp);
u32 readString(char **str, u8 **fp);
std::vector<std::string> getFilesArray(std::string filePath);