#pragma once

#include <cstdint>

namespace romfs
{

template <typename T>
constexpr auto align(const T value, const uint32_t alignment)
{
    return value % alignment ? value + (alignment - value % alignment) : value;
}

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

} // namespace romfs
