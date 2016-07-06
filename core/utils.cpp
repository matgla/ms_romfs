#include "utils.hpp"
#include <cstring>

u8 *makeAlignedPtr(u8 *memoryAddress, int alignment) {
    uintptr_t addr = reinterpret_cast<uintptr_t>(memoryAddress);
    if (addr % alignment != 0)
        addr += alignment - addr % alignment;
    return (u8 *)addr;
}

u32 read32(u8 **fp) {
    u32 decodedNumber = **fp << 24 | *(++*fp) << 16 | *(++*fp) << 8 | *(++*fp);
    ++*fp;
    return decodedNumber;
}

u32 readString(char **str, u8 **fp) {
    u32 size = 0;
    size = strlen(reinterpret_cast<char *>(*fp));

    if (size % 4) {
        size = size + 4 - (size % 4); // align to 4 bytes
    }
    size += 4;
    strcpy(*str, reinterpret_cast<char *>(*fp));
    *fp += size + 4;

    return size;
}